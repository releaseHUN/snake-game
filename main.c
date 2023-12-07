#include "dataTypes.h"
#include "gameLogic.h"
#include "drawing.h"
#include "map.h"
#include "econio.h"
#include <stdio.h>

int main(void) {
	gameInfoType gameInfo;
	snakeType stSnake;
	gameSetup(&gameInfo, &stSnake);
	char filename[] = "maps/map1.txt";
	char **map = generateMap(filename, &gameInfo, &stSnake);
	while(1) {
		movement(map, &stSnake);
		drawMap(map, stSnake, gameInfo);
		econio_sleep(1);
	}
	return 0;
}