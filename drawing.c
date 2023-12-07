#include "drawing.h"
#include "dataTypes.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "econio.h"

//forces a given value betwen 2 values, inputs: value, min value, max value
static inline int clamp(int val, int min, int max) {
	const int t = val < min ? min : val;
	return t > max ? max : t;
}

void drawMap(char **map, snakeType stPlayer, gameInfoType gameInfo) {
	char screenbuffer[gameInfo.iScreensizeY][gameInfo.iScreensizeX];
	//memset(screenbuffer, 0, sizeof(screenbuffer));
	econio_clrscr();
	printf("Level: %d                                                                        Points: %d\n", gameInfo.iCurrentLevel, gameInfo.iPoints);
	for (int i = 0; i < gameInfo.iScreensizeX - 1; ++i)
		putchar('=');
	putchar('\n');

	for (int i = 2; i < gameInfo.iScreensizeY; ++i) {
		for (int j = 0; j < gameInfo.iScreensizeX; ++j)
//			screenbuffer[i][j] = map[clamp(i + stPlayer.iY - gameInfo.iScreensizeY / 2, 0, gameInfo.iSizeY)][clamp(j + stPlayer.iX - gameInfo.iScreensizeX / 2, 0, gameInfo.iSizeX)];
			screenbuffer[i][j] = map[i][j];
		screenbuffer[i][gameInfo.iScreensizeX] = '\n';
	}

	if (stPlayer.stSegments == NULL) {
		screenbuffer[stPlayer.iY][stPlayer.iX] = '@';
	} else {
		snakeSegment *temp = stPlayer.stSegments;
		while (temp->next != NULL) {
			screenbuffer[temp->iY][temp->iX] = '@';
			temp = temp->next;
		}
	}

	for (int i = 0; i < gameInfo.iScreensizeY; ++i)
		fputs(screenbuffer[i], stdout);
	putchar('\n');
}

void drawMenu() {
	econio_clrscr();
	FILE *file = fopen("menu.txt", "r");
	if (file == NULL)
		exit(1);

	for (int i = 0; i < 40; ++i)
		for (int j = 0; j < 102; ++j)
			putchar(fgetc(file));
}