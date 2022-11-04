#include <cprocessing.h>
#pragma once

void enemy_init(void);
void enemy_update(void);
void enemy_exit(void);

typedef struct ENEMY {
	float x;
	float y;
	float worldx;
	float worldy;
	float velocity_x;
	float velocity_y;
	float acceleration_x;
	float acceleration_y;
	float alpha;
} ENEMY ;

#define ENEMY_COUNT (10)
ENEMY enemy[ENEMY_COUNT];
