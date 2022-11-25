#include <cprocessing.h>
#pragma once



//int enemy_ray_trigger(Ray* ray, int i);
//void enemy_CheckCollision(ENEMY* enemy, CP_Vector* newPos, float* time);
typedef struct ENEMY {
	int timer;
	CP_Vector pos;
	CP_Vector vel;
	float worldx;
	float worldy;
	float vel_x;
	float vel_y;
	float acceleration_x;
	float acceleration_y;
	float alpha;
	float tmp;
	float tmp_strength;
	int moving;
	int beam_timer;
	int beam_threshold;
} ENEMY;



typedef struct CHECKPOINT {
	int current_checkpoint;
	float respawn_x;
	float respawn_y;
}CHECKPOINT;

#define ENEMY_COUNT (17)
#define CHECKPOINT_COUNT (6)
//CP1 - Tutorial / Start
//CP2 - Level Start
//CP3 - Checkpoint 1
//CP4 - Checkpoint 2
//CP5 - Checkpoint 3

ENEMY enemy[ENEMY_COUNT];
CHECKPOINT checkpoint[CHECKPOINT_COUNT];

void enemy_init(void);
void enemy_update(void);
void enemy_exit(void);
void enemy_place(void);
void enemy_draw(void);
void checkpoint_init(void);
int enemy_touch(float WorldX, float WorldY);
int dead_menu(void);
void retry_game(int i);
void enemy_move(ENEMY* enemy, int i);
void enemy_beam(float x, float y);
int enemy_place_tut();
int enemy_ray_trigger(Ray* ray, int i);