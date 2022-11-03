#include <cprocessing.h>
#pragma once



struct Player {
	float x;
	float y;
	float velocity_x;
	float velocity_y;
	float acceleration_x;
	float acceleration_y;


} player1;

struct Volume {

	float sound;



} Volume1;

void theVolume(void);
void energyConsumption(void);
void movement(void);
void controller_init(void);
void controller_update(void);
void controller_exit(void);