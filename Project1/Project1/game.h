
#include <cprocessing.h>
#pragma once

typedef struct Wall {
	CP_Vector pos1;
	CP_Vector pos2;
} Wall;

int debug;

float WorldX;
float WorldY;

int CheckPoint_1_Triggered;

void subgame_init(void);
void subgame_update(void);
void subgame_exit(void);

void mainmenu_init(void);
void mainmenu_update(void);
void mainmenu_exit(void);
