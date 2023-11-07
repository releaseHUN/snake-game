#include "snake.h"
#include <stdlib.h>

snakeType *init(int x, int y){
	snakeType *stSnake = malloc(sizeof(snakeType));
	stSnake->iX = x;
	stSnake->iY = y;
	stSnake->next = NULL;
	return stSnake;
}

void addSegment(snakeType *stSnake) {
	snakeType *stTemp = malloc(sizeof(snakeType));
	while(stSnake->next != NULL)
		stSnake = stSnake->next;
	stSnake->next = stTemp;
	stSnake->next->iX = stSnake->iX - stSnake->iDirX;
	stSnake->next->iY = stSnake->iY - stSnake->iDirY;
	stSnake->next->iDirX = stSnake->iDirX;
	stSnake->next->iDirY = stSnake->iDirY;
}

void moveSnake(snakeType *stSnake, int dirX, int dirY) {
	stSnake->iDirX = dirX;
	stSnake->iDirY = dirY;
	while(stSnake->next != NULL){
		stSnake->next->iDirX = stSnake->iDirX;
		stSnake->next->iDirY = stSnake->iDirY;
		stSnake->iX += stSnake->iDirX;
		stSnake->iY += stSnake->iDirY;
		stSnake = stSnake->next;
	}
}