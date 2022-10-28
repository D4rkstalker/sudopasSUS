#include <cprocessing.h>
#include "subcontroller.h"
#include "game.h"


int isPaused = 0;
int isMap = 0;
/* On Hold until there's sound
* 
void theVolume(void) {
	int volume = 0;
	if ((CP_Input_KeyDown(KEY_RIGHT_CONTROL) || CP_Input_KeyDown(KEY_LEFT_CONTROL)) && CP_Input_KeyDown(KEY_RIGHT)) { // Increase volume
		CP_Sound_GetGroupVolume(CP_SOUND_GROUP_0); // default sound

		CP_Sound_SetGroupVolume(CP_SOUND_GROUP_0, ++volume);
	}

	if ((CP_Input_KeyDown(KEY_RIGHT_CONTROL) || CP_Input_KeyDown(KEY_LEFT_CONTROL)) && CP_Input_KeyDown(KEY_LEFT)) { // Decrease volume
		CP_Sound_GetGroupVolume(CP_SOUND_GROUP_0); // default sound

		CP_Sound_SetGroupVolume(CP_SOUND_GROUP_0, --volume);
	}

}
*/ 


void energyConsumption(void) {
	/*
	if (key input){
	energyconsumption -= 10;
	}

	energy += 0.10;
	*/
}

void movement(void) {
	
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
		WorldX -= player1.velocity_x;
		WorldY -= player1.velocity_y;
		player1.velocity_y *= 0.9;
		player1.velocity_x *= 0.9;
		if (CP_Input_KeyDown(KEY_W) && CP_Input_KeyDown(KEY_S)) {
			player1.acceleration_y = 0;

		}
		else {
			if (CP_Input_KeyDown(KEY_W)) {
				player1.acceleration_y += 1;
				player1.velocity_y -= player1.acceleration_y * 0.1;

			}
			else if (CP_Input_KeyReleased(KEY_W)) {

				player1.acceleration_y = 0;

			}

			if (CP_Input_KeyDown(KEY_S)) {

				player1.acceleration_y += 1;
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
				player1.acceleration_x += 1;
				player1.velocity_x += player1.acceleration_x * 0.1;
			}
			else if (CP_Input_KeyReleased(KEY_D)) {

				player1.acceleration_x = 0;


			}
			if (CP_Input_KeyDown(KEY_A)) {
				player1.acceleration_x -= 1;
				player1.velocity_x += player1.acceleration_x * 0.1;

			}
			else if (CP_Input_KeyReleased(KEY_A)) {

				player1.acceleration_x = 0;

			}
		}
		
	}

}



void controller_init(void) {
	
	CP_System_SetWindowSize(1920, 1080);
	CP_Settings_EllipseMode(CP_POSITION_CENTER);
	float center_x = CP_System_GetDisplayWidth() / 2;
	float center_y = CP_System_GetDisplayHeight() / 2;

	player1.x = center_x;
	player1.y = center_y;



	
}

void controller_update(void) {
	movement();

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

	if (isMap) {
		CP_Settings_Fill(CP_Color_Create(188, 158, 130, 255));
		CP_Settings_RectMode(CP_POSITION_CORNER);
		CP_Graphics_DrawRect(CP_System_GetDisplayWidth()/4, CP_System_GetDisplayHeight()/4, CP_System_GetDisplayWidth() / 2, CP_System_GetDisplayHeight() / 2);
	}
	
		
	
	
	return 0;
}

void controller_exit(void) {
	return 0;
}