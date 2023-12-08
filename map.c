#include "map.h"
#include "dataTypes.h"
#include <stdlib.h>
#include <stdio.h>

//generates the map from a given file, opens the file, parses the information needed from the first 5 lines of the file
//then it allocates memory for the map matrix and loads the map into it, returns with the map matrix
extern char **generateMap(char *filename, gameInfoType *gameInfo, snakeType *stPlayer) {
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("the map file doesn't exist");
		exit(1);
	}

	int currLine = 0;
	char tempLine[8];

	fgets(tempLine, 7, file);
	gameInfo->iSizeX = atoi(tempLine) + 1;
	fgets(tempLine, 7, file);
	gameInfo->iSizeY = atoi(tempLine);
	fgets(tempLine, 7, file);
	gameInfo->iFruitsRequired = atoi(tempLine);
	fgets(tempLine, 7, file);
	stPlayer->iX = atoi(tempLine);
	fgets(tempLine, 7, file);
	stPlayer->iY = atoi(tempLine);
	char line[gameInfo->iSizeX + 1];
	char **out = (char**)malloc(sizeof(char*) * gameInfo->iSizeY);
	for (int i = 0; i < gameInfo->iSizeY; ++i)
		out[i] = (char*)malloc(sizeof(char) * gameInfo->iSizeX + 1);

	while (fgets(line, gameInfo->iSizeX + 1, file)) {
		//out = (char**)realloc(out, sizeof(char*) * (currLine + 1));
		//out[currLine] = (char*)malloc(sizeof(char) * (gameInfo->iSizeX + 1));
		for (int i = 0; i < gameInfo->iSizeX; ++i)
			out[currLine][i] = line[i];
		currLine++;
	}
	fclose(file);
	return out;
}