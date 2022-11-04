#include <stdio.h>
#include "cprocessing.h"
#include "subcontroller.h"
#include "game.h"
#include "Utils.h"
#include "music.h"
#include "walls.h"

int isPaused = 0;
int isMap = 0;

#define MAXSPEED 10



void theVolume(void) {
	
	if ((CP_Input_KeyDown(KEY_RIGHT_CONTROL) || CP_Input_KeyDown(KEY_LEFT_CONTROL)) && CP_Input_KeyTriggered(KEY_RIGHT)) { // Increase volume

		if (volume < 1) {
			volume += 0.1;
		}
	}

	if ((CP_Input_KeyDown(KEY_RIGHT_CONTROL) || CP_Input_KeyDown(KEY_LEFT_CONTROL)) && CP_Input_KeyTriggered(KEY_LEFT)) { // Decrease volume


		if (volume > 0.01) {
			volume -= 0.1;
		}
	}



}

void wallScale() {
	int i;
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));


	for (i = 0; i < CWall + 1; i++) {
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawLine((wall[i].pos1.x/4.5) + 550, (wall[i].pos1.y/4.5) + 300, (wall[i].pos2.x/4.5) + 550, (wall[i].pos2.y/4.5) + 300);
	
	}

}

void movement(void) {

	theVolume();

	if (CP_Input_KeyTriggered(KEY_T)) {
		CP_Sound_PlayAdvanced(ping, volume , 1.0f, TRUE, CP_SOUND_GROUP_0);
	}


	if (CP_Input_KeyTriggered(KEY_SPACE)) {
		if (!isPaused) {
			isPaused = 1;
		}
		else {
			isPaused = 0;
		}
	} 
	if (CP_Input_KeyTriggered(KEY_M)) {
		if (!isMap) {
			isMap = 1;
			isPaused = 1;
		}
		else {
			isPaused = 0;
			isMap = 0;
		}


	}
	

	if (!isPaused) {
		
		if (CP_Input_KeyDown(KEY_W) && CP_Input_KeyDown(KEY_S)) {
			player1.acceleration_y = 0;

		}
		else {
			if (CP_Input_KeyDown(KEY_W)) {
				player1.acceleration_y += (MAXSPEED - player1.acceleration_y) / MAXSPEED;
				player1.velocity_y -= player1.acceleration_y * 0.1;

			}
			else if (CP_Input_KeyReleased(KEY_W)) {

				player1.acceleration_y = 0;

			}

			if (CP_Input_KeyDown(KEY_S)) {

				player1.acceleration_y += (MAXSPEED - player1.acceleration_y) / MAXSPEED;
				player1.velocity_y += player1.acceleration_y * 0.1;

			}
			else if (CP_Input_KeyReleased(KEY_S)) {

				player1.acceleration_y = 0;

			}
		}

		if (CP_Input_KeyDown(KEY_D) && CP_Input_KeyDown(KEY_A)) {
			player1.acceleration_x = 0;
		}
		else {
			if (CP_Input_KeyDown(KEY_D)) {
				player1.acceleration_x += (MAXSPEED - player1.acceleration_x) / MAXSPEED;
				player1.velocity_x += player1.acceleration_x * 0.1;
			}
			else if (CP_Input_KeyReleased(KEY_D)) {

				player1.acceleration_x = 0;


			}
			if (CP_Input_KeyDown(KEY_A)) {
				player1.acceleration_x += (MAXSPEED - player1.acceleration_x) / MAXSPEED;
				player1.velocity_x -= player1.acceleration_x * 0.1;

			}
			else if (CP_Input_KeyReleased(KEY_A)) {

				player1.acceleration_x = 0;

			}
		}
			if (wallcollision()) {
				return;
			}
		WorldX -= player1.velocity_x;
		WorldY -= player1.velocity_y;
		player1.velocity_y *= 0.9;
		player1.velocity_x *= 0.9;
	}
	if (isMap) {
		CP_Settings_Fill(CP_Color_Create(188, 158, 130, 255));
		CP_Settings_RectMode(CP_POSITION_CORNER);
		CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 4, CP_System_GetWindowHeight() / 4, CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2);
		wallScale();
	}

//	RayUpdate(0,0);
}



void controller_init(void) {
	
	CP_System_SetWindowSize(1920, 1080);
	CP_Settings_EllipseMode(CP_POSITION_CENTER);
	float center_x = CP_System_GetDisplayWidth() / 2;
	float center_y = CP_System_GetDisplayHeight() / 2;
	Sound_Init();
	player1.x = center_x;
	player1.y = center_y;
	
	volume = 0.1;

	
}

void controller_update(void) {
	
	CP_Settings_BlendMode(CP_BLEND_ALPHA);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	if (player1.x > (float)CP_System_GetDisplayWidth()) {
		player1.x = (float)CP_System_GetDisplayWidth();
	}
	else if (WorldX < 0) {
		player1.x = 0;
	}

	if (player1.y > (float)CP_System_GetDisplayHeight()) {
		player1.y = (float)CP_System_GetDisplayHeight();
	}
	else if (player1.y < 0) {
		player1.y = 0;
	}


	CP_Graphics_DrawCircle(player1.x,player1.y, 10); // Draws the player circle on default 

	
	movement();
	theVolume();
		
	
	
	return 0;
}

void controller_exit(void) {
	return 0;
}