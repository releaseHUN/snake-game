#ifndef SNAKE_GAME_DRAWING_H
#define SNAKE_GAME_DRAWING_H

#include "snake.h"

void drawToScreen(char **map);

void generateScreenbuffer(snakeType *snake, char **map);

#endif