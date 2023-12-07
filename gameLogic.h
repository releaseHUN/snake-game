#ifndef SNAKE_GAME_GAMELOGIC_H
#define SNAKE_GAME_GAMELOGIC_H

#include "dataTypes.h"

void gameSetup(gameInfoType *gameInfo, snakeType *stSnake);

int movement(char **map, snakeType *stSnake);

#endif //SNAKE_GAME_GAMELOGIC_H