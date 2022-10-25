#include <cprocessing.h>
#pragma once
typedef struct Wall {
	CP_Vector pos1;
	CP_Vector pos2;
	CP_Vector pos3;
} Wall;


void subgame_init(void);
void subgame_update(void);
void subgame_exit(void);
