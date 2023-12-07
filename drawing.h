#ifndef SNAKE_GAME_DRAWING_H
#define SNAKE_GAME_DRAWING_H

#include "dataTypes.h"

void drawMap(char **map, snakeType stPlayer, gameInfoType gameInfo);

void drawMenu(char *filename, int iMaxX, int iHeight);

#endif