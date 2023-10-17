#include "snake.h"
#include <stdlib.h>

snakeType *init(int x, int y){
	snakeType *stSnake = malloc(sizeof(snakeType));
	stSnake->x = x;
	stSnake->y = y;
	stSnake->next = NULL;
	return stSnake;
}

void addSegment(snakeType *stSnake) {
	snakeType *stTemp = malloc(sizeof(snakeType));
	while(stSnake->next != NULL)
		stSnake = stSnake->next;
	stSnake->next = stTemp;
	stSnake->next->x = stSnake->x - stSnake->directionX;
	stSnake->next->y = stSnake->y - stSnake->directionY;
	stSnake->next->directionX = stSnake->directionX;
	stSnake->next->directionY = stSnake->directionY;
}

void moveSnake(snakeType *stSnake, int directionX, int directionY) {
	stSnake->directionX = directionX;
	stSnake->directionY = directionY;
	while(stSnake->next != NULL){
		stSnake->x += stSnake->directionX;
		stSnake->y += stSnake->directionY;
		stSnake->next->directionX = stSnake->directionX;
		stSnake->next->directionY = stSnake->directionY;
		stSnake = stSnake->next;
	}
}