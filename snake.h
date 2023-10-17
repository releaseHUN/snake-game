#ifndef SNAKE_GAME_SNAKE_H
#define SNAKE_GAME_SNAKE_H

typedef struct snakeType {
	int x;
	int y;
	int directionX;
	int directionY;
	struct snakeType *next;
} snakeType;

//inicializes a snake at the given coordinates
snakeType *init(int x, int y);

//adds a new segment to the snake
void addSegment(snakeType *stSnake);

//moves the snake forward in the given direction
void moveSnake(snakeType *stSnake, int directionX, int directionY);

#endif