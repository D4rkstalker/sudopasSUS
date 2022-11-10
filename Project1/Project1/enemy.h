#include <cprocessing.h>
#pragma once

void enemy_init(void);
void enemy_update(void);
void enemy_exit(void);
void enemy_place(void);
void enemy_draw(void);
int enemy_touch(float WorldX, float WorldY);
int dead_menu(int dead);
int enemy_ray_trigger(Ray* ray, int i);

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

#define DEAD()
#define ENEMY_COUNT (10)
ENEMY enemy[ENEMY_COUNT];
