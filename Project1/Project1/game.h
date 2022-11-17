
#include <cprocessing.h>
#pragma once

typedef struct Wall {
	CP_Vector pos1;
	CP_Vector pos2;
} Wall;

int debug;
int energy;
int dead;
float WorldX;
float WorldY;



void subgame_init(void);
void subgame_update(void);
void subgame_exit(void);

float shutdown_state;
