#include "cprocessing.h"



struct Player {
	float x;
	float y;
} player1;

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

void energyConsumption(void) {
	/*
	if (key input){
	energyconsumption -= 10;
	}

	energy += 0.10;
	*/
}

void movement(void) {
	/*
	if (CP_Input_KeyDown(Key_W)){
	y += 10;
	}

	if (CP_Input_KeyDown(Key_S)){
	y -= 10;
	}
	if (CP_Input_KeyDown(Key_D)){
	x += 10;
	}
	if (CP_Input_KeyDown(Key_A)){
	x -= 10;
	}
	*/
}


void controller_init(void) {
	CP_System_SetWindowSize(1920, 1080);


}

void controller_update(void) {
	CP_Settings_BlendMode(CP_BLEND_ALPHA);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	float center_x = CP_System_GetDisplayWidth() / 2;
	float center_y = CP_System_GetDisplayHeight() / 2;


	CP_Settings_EllipseMode(CP_POSITION_CENTER);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawCircle(center_x,center_y, 10); // Draws the player circle on default 
}

void controller_exit(void) {

}