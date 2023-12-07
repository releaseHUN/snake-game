#include "dataTypes.h"
#include "gameLogic.h"
#include "drawing.h"
#include "map.h"
#include "econio.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	drawMenu();
	char menuInput = getchar();
	if (menuInput == '1') {
		gameInfoType gameInfo;
		snakeType stSnake;
		gameSetup(&gameInfo, &stSnake);
		char filename[] = "maps/map1.txt";
		char **map = generateMap(filename, &gameInfo, &stSnake);
		while (gameInfo.iGameState == 1) {
			movement(map, &stSnake, gameInfo);
			drawMap(map, stSnake, gameInfo);
			econio_sleep(1);
		}
		if (gameInfo.iGameState == 0)
			return 0;
		else if (gameInfo.iGameState == 2) {
			return 0;
		}
	} else if (menuInput == '2')
		exit(0);

	return 0;
}