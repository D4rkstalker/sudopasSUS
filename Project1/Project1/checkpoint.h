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
	CP_Vector pos;
	float w;
	float h;

} CheckPoint;

CheckPoint point_1;
CheckPoint point_2;
CheckPoint point_3;
CheckPoint point_exit;

typedef struct Gate {
	CP_Vector pos1;
	CP_Vector pos2;
} Gate;

Gate cp1_gate;
Gate cp2_gate;
Gate cp3_gate;
Gate cp1_close;
Gate cp2_close;
Gate cp3_close;


void draw_checkpoint(void);
void checkpoint_reset(void);
void gate_checkpoint_init(void);