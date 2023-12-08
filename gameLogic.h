#ifndef SNAKE_GAME_GAMELOGIC_H
#define SNAKE_GAME_GAMELOGIC_H

#include "dataTypes.h"

extern void gameSetup(gameInfoType *gameInfo, snakeType *stSnake);

void generateFruit(char **map, snakeType *stSnake, gameInfoType gameInfo);

extern char *generateMapname(gameInfoType gameInfo, char *output);

extern int movement(char **map, snakeType *stSnake, gameInfoType *gameInfo);

#endif //SNAKE_GAME_GAMELOGIC_H