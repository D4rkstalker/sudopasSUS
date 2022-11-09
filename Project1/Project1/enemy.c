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
#include "enemy.h"


int dead_menu(int dead) {
	
	int state = 0;
	int menu_alpha = 80;
	int retry_alpha = 0;
	if (menu_alpha <= 255) {
		menu_alpha += 1;
	}
	menu_alpha += 40;
	CP_Settings_Fill(CP_Color_Create(155, 100, 100, menu_alpha));
	CP_Settings_TextSize(200.0f);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, 0);
	CP_Font_DrawText("You are Dead", CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 - 100);
	
	state = 1;
	
	if (state == 1) {
		CP_Settings_TextSize(40.0f);

		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Font_DrawText("Retry from Last Check Point", CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 + 100);

		CP_Settings_Fill(CP_Color_Create(255, 255, 255, retry_alpha));
		CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 + 90, 500, 50);
	}
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, 0);

	if (CP_Input_GetMouseWorldX() >= CP_System_GetWindowWidth() / 2 - 250 && CP_Input_GetMouseWorldX() <= CP_System_GetWindowWidth() / 2 + 250 && CP_Input_GetMouseWorldY() >= CP_System_GetWindowHeight() / 2 + 65 && CP_Input_GetMouseWorldY() <= CP_System_GetWindowHeight() / 2 + 115) {
		retry_alpha = 50;
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
			return 3;
		}
	}
	else {
		retry_alpha = 0;
	}

	//CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, 0);
	return 0;
}


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
	enemy[2].x = 1340;
	enemy[2].y = 220;
}

void enemy_draw() {
	for (int i = 0; i < ENEMY_COUNT; ++i) {
		CP_Settings_NoStroke();
		CP_Color enemy_colour = (CP_Color_Create(255, 70, 84, enemy[i].alpha));
		CP_Settings_Fill(enemy_colour);
		CP_Graphics_DrawCircle(enemy[i].x + WorldX, enemy[i].y + WorldY, 25);
		
		// Draw cords for debugging
		CP_Settings_TextSize(20.0f);
		char buffer3[100] = { 0 };
		
		sprintf_s(buffer3, _countof(buffer3), "X:%.0f\nY:%.0f", enemy[i].x, enemy[i].y);
		CP_Settings_Fill(CP_Color_Create(255, 70, 84, 255));
		CP_Font_DrawText(buffer3, enemy[i].x + WorldX - 45, enemy[i].y + WorldY - 25);
		sprintf_s(buffer3, _countof(buffer3), "Enemy [%d]", i);
		CP_Font_DrawText(buffer3, enemy[i].x + WorldX - 35, enemy[i].y + WorldY + 35);
	}
}

int enemy_touch(float WorldX , float WorldY) {
	float x = CP_System_GetWindowWidth() / 2;
	float y = CP_System_GetWindowHeight() / 2;
	float radius = 25 / 2;
	for (int i = 0; i < ENEMY_COUNT; ++i) { 
		if ( x - WorldX - enemy[i].x >= -25 && x - WorldX - enemy[i].x <= 25 && y - WorldY - enemy[i].y >= -25 && y - WorldY - enemy[i].y <= 25) {
			return 1;
		}
	}
	return 0;
}

int enemy_ray_trigger(Ray *ray, int i) {
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

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(20.0f);
	CP_Font_DrawText("[K] RETURN TO GAME", 20, 20);
	if (CP_Input_KeyTriggered(KEY_K))
	{
		CP_Engine_SetNextGameState(subgame_init, subgame_update, subgame_exit);

	}

}

void enemy_exit(void) {



}