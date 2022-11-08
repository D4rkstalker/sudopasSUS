#include <cprocessing.h>
#pragma once


int CheckPoint_1_Triggered;
int CheckPoint_2_Triggered;
int CheckPoint_3_Triggered;
int exit_Triggered;
void cp1_triggered(void);
void draw_checkpoint_1(void);
void cp2_triggered(void);
void draw_checkpoint_2(void);
void cp3_triggered(void);
void draw_checkpoint_3(void);
void exit_triggered(void);
void draw_exit(void);
int CheckPointTrigger(float area_x, float area_y, float area_width, float area_height, float player_X, float player_Y);
void draw_checkpoint_ping (float delay, float x, float y);



typedef struct CheckPoint {
	float x;
	float y;
	float w;
	float h;

} CheckPoint;

typedef struct Gate {
	CP_Vector pos1;
	CP_Vector pos2;
} Gate;

void draw_checkpoint(void);

