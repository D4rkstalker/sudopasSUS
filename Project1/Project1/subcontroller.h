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

enum the_states{
	resume, paused, theMap, volumeC, theMenu, reset
} game_states;

float center_x;
float center_y;
void theVolume(void);
void energyConsumption(void);
void movement(void);
void controller_init(void);
void tutorialMovement(void);