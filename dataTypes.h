#ifndef SNAKE_GAME_DATATYPES_H
#define SNAKE_GAME_DATATYPES_H

typedef struct snakeSegment {
	int iX;
	int iY;
	struct snakeSegment *next;
} snakeSegment ;

typedef struct {
	int iX;
	int iY;
	int iDirX;
	int iDirY;
	snakeSegment *stSegments;
} snakeType;

typedef struct {
	int iPoints;
	int iCurrentLevel;
	int iSizeX;
	int iSizeY;
	int iScreensizeX;
	int iScreensizeY;
	int iFruitsRequired;
} gameInfoType;

#endif