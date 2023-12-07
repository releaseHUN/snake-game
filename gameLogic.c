#include "gameLogic.h"
#include "econio.h"
#include "dataTypes.h"
#include <stdlib.h>

//sets up the basic variables for the game to work
void gameSetup(gameInfoType *gameInfo, snakeType *stSnake) {
	gameInfo->iScreensizeX = 102;
	gameInfo->iScreensizeY = 40;
	gameInfo->iPoints = 0;
	gameInfo->iCurrentLevel = 1;
	gameInfo->iGameState = 1;
	econio_set_title("Snake Game");
	econio_rawmode();
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
static int collisionCheck(char **map, snakeType *stSnake) {
	if(stSnake->stSegments != NULL) {
		snakeSegment *temp = stSnake->stSegments;
		while (temp->next != NULL) {
			if (stSnake->iX == temp->iX || stSnake->iY == temp->iY)
				return 1;
			temp = temp->next;
		}
	}
	if (map[stSnake->iY][stSnake->iX] == '@')
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

static void generateFruit(char **map, snakeType *stSnake, gameInfoType gameInfo) {
	int iValidPlacemet = 1;
	while (iValidPlacemet){
		int iGenX = rand() % gameInfo.iSizeX + 1;
		int iGenY = rand() % gameInfo.iSizeY + 1;
		if (map[iGenY][iGenX] != '#') {
			if (stSnake->stSegments != NULL) {
				snakeSegment *temp = stSnake->stSegments;
				while (temp->next != NULL) {
					if (iGenX == temp->iX && iGenY == temp->iY)
						break;
				}
				iValidPlacemet = 0;
			}
		}
	}
}

//moves the snake and checks for collisions, if a collision is detected then it runs the appropriate function
int movement(char **map, snakeType *stSnake, gameInfoType gameInfo) {
	getDir(stSnake);
	stSnake->iY += stSnake->iDirY;
	stSnake->iX += stSnake->iDirX;
	switch (collisionCheck(map, stSnake)) {
		case 0:
			return 0;

		case 1:
			return 1;

		case 2:
			addSegment(stSnake);
			generateFruit(map, stSnake, gameInfo);
			return 2;

		case 3:
			return 3;
	}
	return 0;
}