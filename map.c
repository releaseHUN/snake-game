#include "map.h"
#include "snake.h"
#include <stdlib.h>
#include <stdio.h>

char **generateMap(char *filename, int *mapsize, snakeType *stPlayer) {
	FILE *file = fopen(filename, "r");
	if (file == NULL)
		exit(1);

	int maxLineLenght = 7;
	int currLine = 0;
	char tempLine[8];

	fgets(tempLine, 7, file);
	maxLineLenght = atoi(tempLine) + 1;
	fgets(tempLine, 7, file);
	stPlayer->iX = atoi(tempLine);
	fgets(tempLine, 7, file);
	stPlayer->iY = atoi(tempLine);
	fgets(tempLine, 7, file);
	char **out = (char**)malloc(sizeof(char**) * (currLine + 1));
	char line[maxLineLenght];

	while (fgets(line, maxLineLenght, file)) {
		out = (char**)realloc(out, sizeof(char*) * (currLine + 1));
		out[currLine] = (char*)malloc(sizeof(char) * (maxLineLenght + 1));
		for (int i = 0; i < maxLineLenght; ++i)
			out[currLine][i] = line[i];
		currLine++;
	}
	fclose(file);
	*mapsize = currLine;
	return out;
}