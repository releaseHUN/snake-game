#include "dataTypes.h"
#include "gameLogic.h"
#include "drawing.h"
#include "map.h"
#include "econio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	drawMenu();
	gameInfoType gameInfo;
	snakeType stSnake;
	gameSetup(&gameInfo, &stSnake);
	char menuInput = (char)getchar();
	if (menuInput == '1') {
		char filename[17];
		strcpy(filename, generateMapname(gameInfo, filename));
		char **map = generateMap(filename, &gameInfo, &stSnake);
		//generateFruit(map, &stSnake, gameInfo);
		while (gameInfo.iGameState == 1) {
			movement(map, &stSnake, &gameInfo);
			drawMap(map, stSnake, gameInfo);
			econio_sleep(.5);
		}
		if (gameInfo.iGameState == 0)
			return 0;
		else if (gameInfo.iGameState == 2) {
			return 0;
		}
	} else if (menuInput == '2')
		return 0;

	return 0;
}