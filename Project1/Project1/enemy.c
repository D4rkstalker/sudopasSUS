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
#include "checkpoint.h"

float timer;
float EPSI = 0.00000001;
int state = 0;
int menu_alpha = 0;
int retry_alpha = 0;
int beam_timer = 0;

void retry_game(int i) {
	// From last checkpoint
	enemy_place();
	menu_alpha = 0;
	state = 0;
	if (i == 5 && -WorldX < 1000) {
		CheckPoint_3_Triggered = 0;
		cpwallinit(cp3_gate);
	}
	WorldX = -checkpoint[i].respawn_x + CP_System_GetWindowWidth() / 2;
	WorldY = -checkpoint[i].respawn_y + CP_System_GetWindowHeight() / 2;
	player1.velocity_x = 0;
	player1.velocity_y = 0;
	game_states = resume;
	CP_Sound_PlayAdvanced(introsound, volume, 1.0, FALSE, 0);
	CP_Sound_PlayMusic((bgm_submarine));
}

void checkpoint_init(void) {
	checkpoint[0].current_checkpoint = 0;

	checkpoint[0].respawn_x = 285;
	checkpoint[0].respawn_y = -485;

	checkpoint[1].respawn_x = 2560;
	checkpoint[1].respawn_y = -535;

	checkpoint[2].respawn_x = 370;
	checkpoint[2].respawn_y = 4465;

	checkpoint[3].respawn_x = 3350;
	checkpoint[3].respawn_y = 4500;

	checkpoint[4].respawn_x = 5950;
	checkpoint[4].respawn_y = 2785;

	checkpoint[5].respawn_x = 2200;
	checkpoint[5].respawn_y = 2300;

}




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
	enemy[0].pos.x = 1600;
	enemy[0].pos.y = -515;

	enemy[1].pos.x = 3470;
	enemy[1].pos.y = -610;

	enemy[2].pos.x = 1990;
	enemy[2].pos.y = 4165;

	enemy[3].pos.x = 2830;
	enemy[3].pos.y = 4350;

	enemy[4].pos.x = 4900;
	enemy[4].pos.y = 3870;

	enemy[5].pos.x = 6000;
	enemy[5].pos.y = 4030;

	enemy[5].pos.x = 6000;
	enemy[5].pos.y = 4030;

	enemy[6].pos.x = 5740;
	enemy[6].pos.y = 2900;
	enemy[7].pos.x = 5900;
	enemy[7].pos.y = 2900;
	enemy[8].pos.x = 6100;
	enemy[8].pos.y = 2900;

	enemy[9].pos.x = 3700;
	enemy[9].pos.y = 2780;

	enemy[10].pos.x = 1180;
	enemy[10].pos.y = 2775;
	enemy[11].pos.x = 1180;
	enemy[11].pos.y = 2020;
	enemy[12].pos.x = 870;
	enemy[12].pos.y = 2170;
	enemy[13].pos.x = 870;
	enemy[13].pos.y = 2640;
	enemy[14].pos.x = 1445;
	enemy[14].pos.y = 2640;
	enemy[15].pos.x = 1445;
	enemy[15].pos.y = 2170;

	enemy[16].pos.x = 3610;
	enemy[16].pos.y = 1910;

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
			retry_game(checkpoint[0].current_checkpoint);
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

void enemy_beam(float x, float y) {
	
	CP_Color enemy_color = CP_Color_Create(200, 50, 20, 230);
	for (int n = 0; n < ENEMY_COUNT; n++) {
		enemy[n].beam_timer++;
		if (enemy[n].moving == 1) {
			enemy[n].beam_threshold = 8;
		}
		else {
			enemy[n].beam_threshold = 50;
		}
		if (abs(x - enemy[n].pos.x) > 2000 || abs(y - enemy[n].pos.y) > 1200) {
			enemy[n].beam_threshold = 99999;
		}
		if (enemy[n].beam_timer > enemy[n].beam_threshold) {
			for (int i = 0; i < 18; i++) {
				CP_Vector v = AngleToVector(i * 20);
				CreateRay(enemy[n].pos.x, enemy[n].pos.y, 15, v.x, v.y, 5, enemy_color, false, 40, false);
			}
			enemy[n].beam_timer = 0;
		}
	}




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

		if (enemy[i].timer >= 0) {
			enemy[i].timer -= 1;
		}

		if (enemy[i].timer < 20 && enemy[i].timer > 10) {
			enemy[i].alpha + 10;
		}

		
		sprintf_s(buffer3, _countof(buffer3), "X:%.0f\nY:%.0f", enemy[i].pos.x, enemy[i].pos.y);
		CP_Settings_Fill(CP_Color_Create(255, 70, 84, 10));
		CP_Font_DrawText(buffer3, enemy[i].pos.x + WorldX - 45, enemy[i].pos.y + WorldY - 25);
		sprintf_s(buffer3, _countof(buffer3), "Enemy [%d]", i);
		CP_Font_DrawText(buffer3, enemy[i].pos.x + WorldX - 35, enemy[i].pos.y + WorldY + 35);
		if (enemy[i].moving == 1) {
			enemy_move(enemy, i);
		}

		if (debug == 1) {
			enemy[i].alpha = 255;
		}
		if (debug == 0) {
			enemy[i].alpha = 0;
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
void enemy_CheckCollision(ENEMY* enemy, CP_Vector* enemy_newPos, float* time, int n) {
	float tmp = 0;


	for (int i = 0; i < CWall; i++) {
		if ((CP_Math_Distance(wall[i].pos1.x, wall[i].pos1.y, wall[i].pos2.x, wall[i].pos2.y)
			- CP_Math_Distance(wall[i].pos1.x, wall[i].pos1.y, enemy_newPos->x, enemy_newPos->y)
			- CP_Math_Distance(wall[i].pos2.x, wall[i].pos2.y, enemy_newPos->x, enemy_newPos->y)) > -FUZZYNESS) { //&& part->prevID != i
			CP_Vector Vwall = CP_Vector_Normalize(CP_Vector_Subtract(wall[i].pos2, wall[i].pos1));
			CP_Vector Vray = CP_Vector_Normalize(CP_Vector_Subtract(*enemy_newPos, enemy[n].pos));
			tmp = Vwall.x;
			Vwall.x = -Vwall.y;
			Vwall.y = tmp;
			CP_Vector vOut = CP_Vector_Add(CP_Vector_Scale(Vwall, -2 * CP_Vector_DotProduct(Vray, Vwall)), Vray);
			enemy[n].vel = vOut;
			enemy[n].vel = CP_Vector_Scale(enemy[n].vel, 100);
			*enemy_newPos = CP_Vector_Set(enemy[n].pos.x + enemy[n].vel.x * *time, enemy[n].pos.y + enemy[n].vel.y * *time);
			//if (enemy[n].vel.x <= 0 && enemy[n].vel.y)
		}
		else if (CP_Math_Distance(wall[i].pos1.x, wall[i].pos1.y, enemy_newPos->x, enemy_newPos->y) < 2 * FUZZYNESS || CP_Math_Distance(wall[i].pos2.x, wall[i].pos2.y, enemy_newPos->x, enemy_newPos->y) < 2 * FUZZYNESS) {

			enemy[n].vel.x *= -1;
			
			*enemy_newPos = CP_Vector_Set(enemy[n].pos.x + enemy[n].vel.x * *time, enemy[n].pos.y + enemy[n].vel.y * *time);
			return true;
		}
	}
}

int enemy_ray_trigger(Ray* ray, int i) {



	if (enemy[i].timer <= 0) {
		enemy[i].vel = CP_Vector_Scale(ray->head.vel, -1);
		enemy[i].moving = 1;

		enemy[i].tmp = 230 - ray->color.a;
		enemy[i].tmp_strength = ray->fadeStrength;
		// Cooldown of enemy being beamed
		enemy[i].timer = 50;

		CP_Sound_PlayAdvanced(creepyping, volume, 1, FALSE, 0);
	}

	

	return 0;
}


void enemy_move(ENEMY* enemy, int i) {	

	float time = CP_System_GetDt();
	float timeX = time;
	float timeY = time;

	while (time > EPSI) {
		bool collisionX = false;
		bool collisionY = false;
		


		CP_Vector enemy_newPos = CP_Vector_Set(enemy[i].pos.x + enemy[i].vel.x * time, enemy[i].pos.y + enemy[i].vel.y * time);
		float newTime = time;
		enemy_CheckCollision(enemy, &enemy_newPos, &time, i);

		enemy[i].pos.x = enemy_newPos.x;
		enemy[i].pos.y = enemy_newPos.y;


		//if (enemy[i].pos.x > enemy[i].tmp_x - 100 && enemy[i].pos.x < enemy[i].tmp_x + 100 && enemy[i].pos.y > enemy[i].tmp_y - 100 && enemy[i].pos.y < enemy[i].tmp_y + 100) {
		//	enemy[i].moving = 0;
		//	enemy[i].vel_x = 0;
		//	enemy[i].vel_y = 0;
		//}

		if (enemy[i].tmp <= 0) {
			enemy[i].moving = 0;
			enemy[i].vel_x = 0;
			enemy[i].vel_y = 0;
		}
		else {
			enemy[i].tmp -= enemy[i].tmp_strength;
		}

		time = 0;
		

	}

}




void enemy_init(void) {

}
void enemy_update(void) {

}
void enemy_exit(void) {
}
