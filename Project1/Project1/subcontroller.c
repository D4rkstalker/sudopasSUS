#include <stdio.h>
#include "cprocessing.h"
#include "subcontroller.h"
#include "game.h"
#include "Utils.h"
#include "music.h"
#include "walls.h"

int isPaused = 0;
int isMap = 0;
int isVolume = 0;
#define MAXSPEED 10

CP_Vector mouseMovement;

void checkMouse(CP_Vector volumeMin, CP_Vector volumeMax) {
	CP_Vector distvect = CP_Vector_Subtract(volumeMax, volumeMin);
	CP_Vector dirvect = CP_Vector_Normalize(distvect);

		mouseMovement.x = (volumeMin.x + volume * distvect.x);
		mouseMovement.y = volumeMin.y;
	CP_Graphics_DrawCircle(mouseMovement.x, mouseMovement.y, 25);

	if ((CP_Input_MouseDown(MOUSE_BUTTON_LEFT))) {
		float mouseX = CP_Input_GetMouseX();
		float mouseY = CP_Input_GetMouseY();

		if (mouseX >= volumeMin.x && mouseX <= volumeMax.x) {
			if (mouseY >= volumeMin.y - 5 && mouseY <= volumeMin.y + 5) {

				
						mouseMovement = CP_Vector_Set(mouseX, volumeMin.y);
						volume = (mouseMovement.x - volumeMin.x) / distvect.x;
						// (mouseMovement.x - volumeMin.x)/distvect.x = volume * distvect.x
						
									
			
			}
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


	if (CP_Input_KeyTriggered(KEY_T)) {
		CP_Sound_PlayAdvanced(ping, volume, 1.0f, FALSE, CP_SOUND_GROUP_0);
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

	if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
		if (!isVolume) {
			isVolume = 1;
			isPaused = 1;
		}
		else {
			isVolume = 0;
			isPaused = 0;

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
		if (debug == 0) {
			if (wallcollision()) {
				return;
			}
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

		if (isVolume) {
			CP_Settings_Fill(CP_Color_Create(155, 155, 155, 255));
			CP_Settings_RectMode(CP_POSITION_CORNER);
			float screenborderX = CP_System_GetWindowWidth() / 4;
			float screenborderY = CP_System_GetWindowHeight() / 4;
			float screensizeX = CP_System_GetWindowWidth() / 2;
			float screensizeY = CP_System_GetWindowHeight() / 2;

			CP_Vector volumeMin = CP_Vector_Set(screenborderX + screensizeX / 4, screenborderY + screensizeY / 2);
			
			CP_Vector volumeMax = CP_Vector_Set(screenborderX + screensizeX - (screensizeX / 4), screenborderY + screensizeY - (screensizeY / 2));
			
			CP_Graphics_DrawRect(screenborderX, screenborderY, screensizeX, screensizeY);

			CP_Settings_Fill(CP_Color_Create(255, 200, 200, 255));
			CP_Graphics_DrawLine(volumeMin.x, volumeMin.y, volumeMax.x, volumeMax.y);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
			checkMouse(volumeMin, volumeMax);
			
			
		}

		//	RayUpdate(0,0);
	
}



void controller_init(void) {
	
	CP_System_SetWindowSize(1920, 1080);
	CP_Settings_EllipseMode(CP_POSITION_CENTER);
	float center_x = CP_System_GetWindowWidth() / 2;
	float center_y = CP_System_GetWindowHeight() / 2;
	Sound_Init();
	player1.x = center_x;
	player1.y = center_y;
	
	volume = 0.1;

	
}

void controller_update(void) {
	
	CP_Settings_BlendMode(CP_BLEND_ALPHA);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	if (player1.x > (float)CP_System_GetWindowWidth()) {
		player1.x = (float)CP_System_GetWindowWidth();
	}
	else if (WorldX < 0) {
		player1.x = 0;
	}

	if (player1.y > (float)CP_System_GetWindowHeight()) {
		player1.y = (float)CP_System_GetWindowHeight();
	}
	else if (player1.y < 0) {
		player1.y = 0;
	}


	CP_Graphics_DrawCircle(player1.x,player1.y, 10); // Draws the player circle on default 

	
	movement();

		
	
	
	return 0;
}

void controller_exit(void) {
	return 0;
}