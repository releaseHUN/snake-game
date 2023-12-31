#include "drawing.h"
#include "dataTypes.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "econio.h"

//forces a given value betwen 2 values, inputs: value, min value, max value
//static inline int clamp(int val, int min, int max) {
//	const int t = val < min ? min : val;
//	return t > max ? max : t;
//}

//draws the map to the screen, first it sets up a screenbuffer, then it writes the "menu" over it, after that it puts the map into the buffer
// then it puts the snake in it and finally draws it to the screen
extern void drawMap(char **map, snakeType stPlayer, gameInfoType gameInfo) {
	char screenbuffer[gameInfo.iScreensizeY][gameInfo.iScreensizeX];
	//memset(screenbuffer, 0, sizeof(screenbuffer));
	econio_clrscr();
	printf("Level: %d                                                                        Points: %d\n", gameInfo.iCurrentLevel, gameInfo.iPoints);
	for (int i = 0; i < gameInfo.iScreensizeX - 2; ++i)
		putchar('=');
	putchar('\n');

	for (int i = 0; i < gameInfo.iScreensizeY; ++i) {
		for (int j = 0; j < gameInfo.iScreensizeX; ++j)
//			screenbuffer[i][j] = map[clamp(i + stPlayer.iY - gameInfo.iScreensizeY / 2, 0, gameInfo.iSizeY)][clamp(j + stPlayer.iX - gameInfo.iScreensizeX / 2, 0, gameInfo.iSizeX)];
			screenbuffer[i][j] = map[i][j];
		screenbuffer[i][gameInfo.iScreensizeX - 2] = '\n';
		screenbuffer[i][gameInfo.iScreensizeX - 1] = '\0';
	}

	if (stPlayer.stSegments == NULL) {
		screenbuffer[stPlayer.iY][stPlayer.iX] = '@';
	} else {
		screenbuffer[stPlayer.iY][stPlayer.iX] = '@';
		snakeSegment *temp = stPlayer.stSegments;
		while (temp->next != NULL) {
			temp = temp->next;
			screenbuffer[temp->iY][temp->iX] = '@';
		}
	}

	for (int i = 0; i < gameInfo.iScreensizeY; ++i)
		fputs(screenbuffer[i], stdout);
	putchar('\n');
}

//draws the menu to the console from a file
extern void drawMenu() {
	econio_clrscr();
	FILE *file = fopen("menu.txt", "r");
	if (file == NULL) {
		printf("the menu.txt file doesn't exist");
		exit(1);
	}

	for (int i = 0; i < 40; ++i)
		for (int j = 0; j < 102; ++j)
			putchar(fgetc(file));
	fclose(file);
}