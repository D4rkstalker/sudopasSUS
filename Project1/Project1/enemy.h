#include <cprocessing.h>
#pragma once

void enemy_init(void);
void enemy_update(void);
void enemy_exit(void);

typedef struct ENEMY {
	float x;
	float y;
	float velocity_x;
	float velocity_y;
	float acceleration_x;
	float acceleration_y;
	float alpha;
} ENEMY ;
