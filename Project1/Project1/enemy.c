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
#include "music.h"

float timer;
float EPSI = 0.00000001;
int state = 0;
int menu_alpha = 00;
int retry_alpha = 0;
void retry_game() {

	enemy_place();
	menu_alpha = 0;
	state = 0;
	WorldX = 0;
	WorldY = 0;
	game_states = resume;
	CP_Sound_PlayAdvanced(introsound, volume, 1.0, FALSE, 0);
	CP_Sound_PlayMusic((bgm_submarine));
}
int dead_menu(void) {


	if (menu_alpha <= 500) {
		menu_alpha += 3;
	}

	CP_Settings_Fill(CP_Color_Create(180, 10, 0, menu_alpha));
	CP_Settings_TextSize(200.0f);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, 0);
	CP_Font_DrawText("You are Dead", CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 - 100);

	if (menu_alpha >= 400) {
		state = 1;
	}

	if (state == 1) {
		CP_Settings_TextSize(40.0f);
		CP_Settings_Fill(CP_Color_Create(220, 220, 220, 255));
		CP_Font_DrawText("Retry from Last Check Point", CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 + 100);
		CP_Settings_Fill(CP_Color_Create(220, 220, 220, retry_alpha));
		CP_Settings_Stroke(CP_Color_Create(220, 220, 220, 255));
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 + 90, 500, 50);
	}
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, 0);
	//Retry Button
	if (CP_Input_GetMouseWorldX() >= CP_System_GetWindowWidth() / 2 - 250 && CP_Input_GetMouseWorldX() <= CP_System_GetWindowWidth() / 2 + 250 && CP_Input_GetMouseWorldY() >= CP_System_GetWindowHeight() / 2 + 65 && CP_Input_GetMouseWorldY() <= CP_System_GetWindowHeight() / 2 + 115) {
		retry_alpha = 50;
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
			retry_game();
			return 0;
		}
	}
	else {
		retry_alpha = 0;
	}
	//CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, 0);
	return 1;
}
// Placing enemy
void enemy_place() {
	for (int i = 0; i < ENEMY_COUNT; ++i) {
		enemy[i].alpha = 255;
		enemy[i].vel.x = 0;
		enemy[i].vel.y = 0;
		enemy[i].acceleration_x = 0;
		enemy[i].acceleration_y = 0;
		enemy[i].alpha = 255;
		enemy[i].moving = 0;
	
	}
	// Settings of enemy world cords
	enemy[0].pos.x = 700;
	enemy[0].pos.y = 700;
	enemy[1].pos.x = 2000;
	enemy[1].pos.y = 1500;
	enemy[2].pos.x = 1340;
	enemy[2].pos.y = 220;
}
void enemy_draw() {
	for (int i = 0; i < ENEMY_COUNT; ++i) {
		CP_Settings_NoStroke();
		CP_Color enemy_colour = (CP_Color_Create(255, 70, 84, enemy[i].alpha));
		CP_Settings_Fill(enemy_colour);
		CP_Graphics_DrawCircle(enemy[i].pos.x + WorldX, enemy[i].pos.y + WorldY, 25);

		// Draw cords for debugging
		CP_Settings_TextSize(20.0f);
		char buffer3[100] = { 0 };

		sprintf_s(buffer3, _countof(buffer3), "X:%.0f\nY:%.0f", enemy[i].pos.x, enemy[i].pos.y);
		CP_Settings_Fill(CP_Color_Create(255, 70, 84, 255));
		CP_Font_DrawText(buffer3, enemy[i].pos.x + WorldX - 45, enemy[i].pos.y + WorldY - 25);
		sprintf_s(buffer3, _countof(buffer3), "Enemy [%d]", i);
		CP_Font_DrawText(buffer3, enemy[i].pos.x + WorldX - 35, enemy[i].pos.y + WorldY + 35);
		if (enemy[i].moving == 1) {
			enemy_move(enemy, i);
		}
	}
}
int enemy_touch(float WorldX, float WorldY) {
	float x = CP_System_GetWindowWidth() / 2;
	float y = CP_System_GetWindowHeight() / 2;
	float radius = 25 / 2;
	for (int i = 0; i < ENEMY_COUNT; ++i) {
		if (x - WorldX - enemy[i].pos.x >= -25 && x - WorldX - enemy[i].pos.x <= 25 && y - WorldY - enemy[i].pos.y >= -25 && y - WorldY - enemy[i].pos.y <= 25) {
			return 1;
		}
	}
	return 0;
}
void enemy_CheckCollision(ENEMY* enemy, CP_Vector* newPos, float* time, int i) {


	for (int i = 0; i < CWall; i++) {
		if ((CP_Math_Distance(wall[i].pos1.x, wall[i].pos1.y, wall[i].pos2.x, wall[i].pos2.y)
			- CP_Math_Distance(wall[i].pos1.x, wall[i].pos1.y, newPos->x, newPos->y)
			- CP_Math_Distance(wall[i].pos2.x, wall[i].pos2.y, newPos->x, newPos->y)) > -FUZZYNESS) { //&& part->prevID != i
			CP_Vector Vwall = CP_Vector_Normalize(CP_Vector_Subtract(wall[i].pos2, wall[i].pos1));
			CP_Vector Vray = CP_Vector_Normalize(CP_Vector_Subtract(*newPos, enemy[i].pos));
			float temp = Vwall.x;
			Vwall.x = -Vwall.y;
			Vwall.y = temp;
			CP_Vector vOut = CP_Vector_Add(CP_Vector_Scale(Vwall, -2 * CP_Vector_DotProduct(Vray, Vwall)), Vray);
			enemy[i].vel = vOut;
			enemy[i].vel = CP_Vector_Scale(enemy[i].vel, 5);
			*newPos = CP_Vector_Set(enemy[i].pos.x + enemy[i].pos.x * *time, enemy[i].pos.y + enemy[i].vel.y * *time);
			//if (enemy[i].vel.x <= 0 && enemy[i].vel.y)
			return true;
		}
		else if (CP_Math_Distance(wall[i].pos1.x, wall[i].pos1.y, newPos->x, newPos->y) < 2 * FUZZYNESS || CP_Math_Distance(wall[i].pos2.x, wall[i].pos2.y, newPos->x, newPos->y) < 2 * FUZZYNESS) {
			enemy[i].vel.x *= -1;
			enemy[i].vel.x *= -1;
			*newPos = CP_Vector_Set(enemy[i].pos.x + enemy[i].vel.x * *time, enemy[i].pos.y + enemy[i].pos.y * *time);
			return true;
		}
	}
}

int enemy_ray_trigger(Ray* ray, int i) {

	enemy[i].vel = CP_Vector_Scale(ray->head.vel, -1);
	enemy[i].moving = 1;

}


void enemy_move(ENEMY* enemy, int i) {	

	float time = CP_System_GetDt();
	float timeX = time;
	float timeY = time;

	while (time > EPSI) {
		bool collisionX = false;
		bool collisionY = false;

		CP_Vector newPos = CP_Vector_Set(enemy[i].pos.x + enemy[i].vel.x * time, enemy[i].pos.y + enemy[i].vel.y * time);
		float newTime = time;
		enemy_CheckCollision(enemy, &newPos, &time, i);

		enemy[i].pos.x = newPos.x;
		enemy[i].pos.y = newPos.y;
		time = 0;

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
	CP_Graphics_DrawCircle(enemy[1].pos.x, enemy[1].pos.y, 25);
	//Referece point
	CP_Settings_Fill(CP_Color_Create(150, 250, 84, 255));
	CP_Graphics_DrawCircle(950, 500, 25);
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
