#include "cprocessing.h"
#include <cprocessing.h>
#include "subcontroller.h"
#include "SoundCast.h"
#include "Utils.h"
#include <math.h>
#include "enemy.h"
#include <stdbool.h>
#include "walls.h"
#include "game.h"
#include <stdlib.h>


#define ENEMY_COUNT (10)


ENEMY enemy[ENEMY_COUNT];

/*
ray head is detection
if detected
create a line from detection to wall, then player start position
accelerate along line, decelerate when reaching player start position
*/


// Placing enemy
void enemy_place() {
	for (int i = 0; i < ENEMY_COUNT; ++i) {
		enemy[i].alpha = 255;
	}
	// Settings of enemy world cords
	enemy[0].x = 700;
	enemy[0].y = 700;
	enemy[1].x = 2000;
	enemy[1].y = 1500;
}

void enemy_draw() {
	for (int i = 0; i < ENEMY_COUNT; ++i) {
		CP_Settings_NoStroke();
		CP_Settings_Fill(CP_Color_Create(255, 70, 84, enemy[i].alpha));
		CP_Graphics_DrawCircle(enemy[i].x + WorldX, enemy[i].y + WorldY, 25);
		
		// Draw cords for debugging
		CP_Settings_TextSize(20.0f);
		char buffer3[100] = { 0 };
		sprintf_s(buffer3, _countof(buffer3), "X:%.0f\nY:%.0f", enemy[i].x, enemy[i].y);
		CP_Settings_Fill(CP_Color_Create(255, 70, 84, 255));
		CP_Font_DrawText(buffer3, enemy[i].x + WorldX, enemy[i].y + WorldY);
	}
}


// COPY
int enemy_touch(float WorldX , float WorldY) {
	// radius of circle
	float x = CP_System_GetWindowWidth() / 2;
	float y = CP_System_GetWindowHeight() / 2;
	float radius = 25 / 2;
	for (int i = 0; i < ENEMY_COUNT; ++i) { 
		if ( x - WorldX - enemy[i].x >= -25 && x - WorldX - enemy[i].x <= 25 && y - WorldY - enemy[i].y >= 25 && y - WorldY - enemy[i].y <= -25) {
			enemy[i].x += 50;
			return 1;
		}
	}
	return 0;
}

float timer;

void enemy_move(float x1, float y1, float x2, float y2, float timer) {

	//calculation of angle
	//move in that vector scaled
	float vector_x = x2 - x1;
	float vector_y = y2 - y1;
	float scale = 0;
	if (vector_x > vector_y) {
		vector_y /= vector_x;
		vector_x /= vector_x;
	}
	else {
		vector_x /= vector_y;
		vector_y /= vector_y;
	}

	// timer is to calculate the distance through fade



	if (timer > 0) {

		enemy[1].x += enemy[1].velocity_x;
		enemy[1].y += enemy[1].velocity_y;

		enemy[1].acceleration_y += 1;
		enemy[1].velocity_y -= enemy[1].acceleration_y * 0.001 * vector_y;
		enemy[1].acceleration_x += 1;
		enemy[1].velocity_x -= enemy[1].acceleration_x * 0.001 * vector_x;



		//Fade out and in
		if (timer > 60) {
			enemy[1].alpha -= 10;
		}
		else {
			enemy[1].alpha += 10;
		}
		timer -= 1;
	}
}
	



void enemy_init(void) {

	CP_System_SetWindowSize(1920, 1080);

	CP_System_SetWindowSize(1920, 1080);
	CP_Settings_EllipseMode(CP_POSITION_CENTER);
	
	// Player initialisation
	float center_x = CP_System_GetDisplayWidth() / 2;
	float center_y = CP_System_GetDisplayHeight() / 2;

	for (int i = 0; i < ENEMY_COUNT; ++i) {
		enemy[i].alpha = 255;
	}

	enemy[1].x = 600;
	enemy[1].y = 600;
	enemy[1].velocity_x = 0;
	enemy[1].velocity_y = 0;
	enemy[1].acceleration_x = 0;
	enemy[1].acceleration_y = 0;
	enemy[1].alpha = 255;

	timer = 100;
}

void enemy_update(void) {


	CP_Graphics_ClearBackground(CP_Color_Create(25, 25, 25, 255));


	//Creating Player
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawCircle(player1.x, player1.y, 25);
	//Creating Enemy
	CP_Settings_Fill(CP_Color_Create(222, 70, 84, enemy[1].alpha));
	CP_Graphics_DrawCircle(enemy[1].x, enemy[1].y, 25);
	//Referece point
	CP_Settings_Fill(CP_Color_Create(150, 250, 84, 255));
	CP_Graphics_DrawCircle(950, 500, 25);

	enemy_move(950, 500, 600, 600, timer);

}

void enemy_exit(void) {



}