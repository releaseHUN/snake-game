#include "gameLogic.h"
#include "econio.h"
#include "dataTypes.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//sets up the basic variables for the game to work
extern void gameSetup(gameInfoType *gameInfo, snakeType *stSnake) {
	gameInfo->iScreensizeX = 103;
	gameInfo->iScreensizeY = 40;
	gameInfo->iPoints = 0;
	gameInfo->iCurrentLevel = 1;
	gameInfo->iGameState = 1;
	econio_set_title("Snake Game");
	econio_rawmode();
}

//generates the filepath to the current level, returns the path
extern char *generateMapname(gameInfoType gameInfo, char *output) {
	char temp[3];
	strcpy(output, "maps/");
	strcat(output, "map");
	sprintf(temp, "%d", gameInfo.iCurrentLevel);
	strcat(output, temp);
	strcat(output, ".txt\0");
	return output;
}

//checks for input and updates the movement direction of the snake
static void getDir(snakeType *stSnake) {
	if(econio_kbhit()) {
		switch (econio_getch()) {
			case 'w':
				stSnake->iDirY = -1;
				stSnake->iDirX = 0;
				break;

			case 's':
				stSnake->iDirY = 1;
				stSnake->iDirX = 0;
				break;

			case 'a':
				stSnake->iDirY = 0;
				stSnake->iDirX = -1;
				break;

			case 'd':
				stSnake->iDirY = 0;
				stSnake->iDirX = 1;
				break;
		}
	}
}

//checks for collisions and returns with a non-zero identifier if a collision is found
//0 if no collision is found, 1 if the snake hits a wall or itself, 2 if the snake hits a fruit
static int collisionCheck(char **map, snakeType *stSnake) {
	if(stSnake->stSegments != NULL) {
		snakeSegment *temp = stSnake->stSegments;
		while (temp->next != NULL) {
			if (stSnake->iX == temp->iX || stSnake->iY == temp->iY)
				return 1;
			temp = temp->next;
		}
	}
	if (map[stSnake->iY][stSnake->iX] == '#')
		return 1;
	else if (map[stSnake->iY][stSnake->iX] == 'O')
		return 2;
	else
		return 0;
}

//adds a segment to the snake, just a basic linked list insert at the beginning
static void addSegment(snakeType *stSnake) {
	snakeSegment *stTemp = malloc(sizeof(snakeSegment));
	stTemp->iX = stSnake->iX;
	stTemp->iY = stSnake->iY;
	if (stSnake->stSegments == NULL) {
		stSnake->stSegments = stTemp;
		stTemp->next = NULL;
	} else {
		stTemp->next = stSnake->stSegments;
		stSnake->stSegments = stTemp;
	}
}

//generates a new fruit randomly on the map
void generateFruit(char **map, snakeType *stSnake, gameInfoType gameInfo) {
	int iValidPlacemet = 1;
	while (iValidPlacemet){
		int iGenX = rand() % gameInfo.iSizeX;
		int iGenY = rand() % gameInfo.iSizeY;
		if (map[iGenY][iGenX] != '#') {
			if (stSnake->stSegments != NULL) {
				snakeSegment *temp = stSnake->stSegments;
				while (temp != NULL) {
					if (iGenX == temp->iX && iGenY == temp->iY) {
						break;
					}
					temp = temp->next;
				}
				iValidPlacemet = 0;
			}
		}
		map[iGenY][iGenX] = 'O';
	}
}

//frees the map from memory
extern void freeMap(char **map, gameInfoType gameInfo) {
	for (int i = 0; i < gameInfo.iSizeY; i++)
		free(map[i]);
	free(map);
}

//frees the snake segments from memory
extern void freeList (snakeType stSnake) {
	if (stSnake.stSegments == NULL)
		return;
	snakeSegment *head = stSnake.stSegments;
	snakeSegment *tmp;
	while (head != NULL) {
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

//moves the snake and checks for collisions, if a collision is detected then it runs the appropriate function
//returns with an identifier about what happened
//0 if the snake just moved, 1 if it's game over, 2 if a new segment was added to the snake, 3 if the snake moved into a portal
extern int movement(char **map, snakeType *stSnake, gameInfoType *gameInfo) {
	getDir(stSnake);
	stSnake->iY += stSnake->iDirY;
	stSnake->iX += stSnake->iDirX;
	switch (collisionCheck(map, stSnake)) {
		case 0:
			return 0;

		case 1:
			freeList(*stSnake);
			freeMap(map, *gameInfo);
			econio_clrscr();
			printf("Game Over!\nAchieved Points: %d",gameInfo->iPoints);
			exit(0);
			return 1;

		case 2:
			addSegment(stSnake);
			gameInfo->iPoints += 10;
			map[stSnake->iY][stSnake->iX] = '.';
			//generateFruit(map, stSnake, *gameInfo);
			return 2;

		case 3:
			return 3;
	}
	return 0;
}