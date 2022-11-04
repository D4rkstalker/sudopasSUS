#include <cprocessing.h>
#pragma once


void cp1_triggered(void);
void draw_checkpoint_1(void);
int CheckPointTrigger(float area_x, float area_y, float area_width, float area_height, float player_X, float player_Y);


typedef struct CheckPoint {
	float x;
	float y;
	float w;
	float h;

} CheckPoint;


