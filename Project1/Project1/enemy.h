#include <cprocessing.h>
#pragma once



//int enemy_ray_trigger(Ray* ray, int i);
//void enemy_CheckCollision(ENEMY* enemy, CP_Vector* newPos, float* time);
typedef struct ENEMY {
	CP_Vector pos;
	CP_Vector vel;
	float worldx;
	float worldy;
	float vel_x;
	float vel_y;
	float acceleration_x;
	float acceleration_y;
	float alpha;
	int moving;
} ENEMY;
#define DEAD()
#define ENEMY_COUNT (10)
ENEMY enemy[ENEMY_COUNT];

void enemy_init(void);
void enemy_update(void);
void enemy_exit(void);
void enemy_place(void);
void enemy_draw(void);
int enemy_touch(float WorldX, float WorldY);
int dead_menu(void);
void enemy_move(ENEMY* enemy);
