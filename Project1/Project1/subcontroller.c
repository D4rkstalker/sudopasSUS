#include "cprocessing.h"



struct Player {
	float x;
	float y;
	float velocity_x;
	float velocity_y;
	float acceleration_x;
	float acceleration_y;


} player1;

int isPaused = 0;

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
	
	if (CP_Input_KeyDown(KEY_SPACE)) {
		if (!isPaused) {
			isPaused = 1;
		}
		else {
			isPaused = 0;
		}
	}

	if (!isPaused) {
		if (CP_Input_KeyDown(KEY_W)) {
			player1.acceleration_y += 1;
			player1.velocity_y += player1.acceleration_y * 0.1;
			player1.y -= player1.velocity_y * 0.1;
		}
		else if (CP_Input_KeyReleased(KEY_W)) {
			
				player1.y += player1.velocity_y * 0.1;
				player1.velocity_y = 10;
				player1.acceleration_y = 10;
			
		}

		if (CP_Input_KeyDown(KEY_S)) {

			player1.acceleration_y += 1;
			player1.velocity_y += player1.acceleration_y * 0.1;
			player1.y += player1.velocity_y * 0.1;
		}
		else if (CP_Input_KeyReleased(KEY_S)) {

				player1.y += player1.velocity_y * 0.1;
				player1.velocity_y = 10;
				player1.acceleration_y = 10;
			
		}

		if (CP_Input_KeyDown(KEY_D)) {
			player1.acceleration_x += 1;
			player1.velocity_x += player1.acceleration_x * 0.1;
			player1.x += player1.velocity_x * 0.1;
		}
		else if (CP_Input_KeyReleased(KEY_D)) {
		
				player1.x += player1.velocity_x * 0.1;
				player1.velocity_x = 10;
				player1.acceleration_x = 10;
			
			
		}
		if (CP_Input_KeyDown(KEY_A)) {
			player1.acceleration_x += 1;
			player1.velocity_x += player1.acceleration_x * 0.1;
			player1.x -= player1.velocity_x * 0.1;
		}
		else if (CP_Input_KeyReleased(KEY_A)) {
			
				player1.x -= player1.velocity_x * 0.1;
				player1.acceleration_x = 10;
				player1.velocity_x = 10;
			
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
	//player1.acceleration = 10;
	//player1.acceleration = 10;
	//player1.velocity_x = 50;
	//player1.velocity_y = 10;


	
}

void controller_update(void) {
	movement();

	CP_Settings_BlendMode(CP_BLEND_ALPHA);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawCircle(player1.x,player1.y, 10); // Draws the player circle on default 
	
	
		
	
	
	return 0;
}

void controller_exit(void) {
	return 0;
}