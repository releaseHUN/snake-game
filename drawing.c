#include "drawing.h"
#include "snake.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "econio.h"

static inline int clamp(int d, int min, int max) {
	const int t = d < min ? min : d;
	return t > max ? max : t;
}

void drawMap(char **map, int iLen, snakeType stPlayer) {
	char screenbuffer[40][102];
	memset(screenbuffer, 0, sizeof(screenbuffer));
	int linelen = strlen(map[0]);
	econio_clrscr();
	for (int i = 0; i < 40; ++i) {
		for (int j = 0; j < 101; ++j) {
			if (20 == i && 50 == j)
				screenbuffer[i][j] = '@';
			else {
				screenbuffer[i][j] = map[clamp(i + stPlayer.y - 20, 0, iLen)][clamp(j + stPlayer.x - 50, 0, linelen)];
				for (enemy *walker = enemyList.first; walker != NULL; walker = (enemy*)walker->next) {
					if (walker->y == i + stPlayer.y - 20 && walker->x == j + stPlayer.x - 50) {
						screenbuffer[i][j] = walker->sprite;
					}
				}
			}
		}
		screenbuffer[i][101] = '\0';
		fputs(screenbuffer[i], stdout);
#ifndef _WIN32
		putchar('\n');
#endif
	}
}

void drawUI(player p) {
	for (int i = 0; i < 101; ++i)
		putchar('=');
	printf("\n\n   Health: %3d / %3d   Defense: %3d / %3d   Attack: %3d / %3d", p.hp, p.defaultHP, p.defense, p.defaultDefense, p.attack, p.defaultAttack);
	printf("\n\n   level: %3d   Xp: %3d / %3d", p.level, p.xp, p.xpToNextLevel);
	printf("\n\n\n\n\n\n press 'q' to exit");
}

void drawMenu(char *filename, int len, int height) {
	char ch;
	econio_clrscr();
	FILE *file = fopen(filename, "r");
	if (file == NULL)
		exit(1);

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < len; ++j) {
			ch = fgetc(file);
			putchar(ch);
		}
	}
}