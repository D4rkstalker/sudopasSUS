#include "cprocessing.h"
#include <cprocessing.h>
#include "subcontroller.h"
#include "SoundCast.h"
#include "Utils.h"
#include <math.h>



#include <stdbool.h>

struct Player {
	float x;
	float y;
} player1;

bool player_detection;




/*
ray head is detection
if detected
create a line from detection to wall, then player start position
accelerate along line, decelerate when reaching player start position
*/


void enemy_move(float enemy_start) {

}

void enemy_init(void) {

	CP_System_SetWindowSize(1920, 1080);

	CP_System_SetWindowSize(1920, 1080);
	CP_Settings_EllipseMode(CP_POSITION_CENTER);
	
	// Player initialisation
	float center_x = CP_System_GetDisplayWidth() / 2;
	float center_y = CP_System_GetDisplayHeight() / 2;
	player1.x = center_x;
	player1.y = center_y;




}

void enemy_update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(25, 25, 25, 255));



	//Creating Player
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawCircle(player1.x, player1.y, 25);
	//Creating Enemy
	CP_Settings_Fill(CP_Color_Create(222, 70, 84, 255));
	CP_Graphics_DrawCircle(600, 300, 25);


	// movement function
	movement();




	//Creating Rays with KEY_J
	if (CP_Input_KeyTriggered(KEY_J)) {
		CP_Color color = CP_Color_Create(122, 89, 156, 155);
		for (int i = 0; i < 36; i++) {
			CP_Vector v = AngleToVector(i * 10.0);
			CreateRay(player1.x, player1.y, 50, v.x * 200, v.y * 200, color);

		}
	}
	RayUpdate();
	//


	// Press Q to Exit
	if (CP_Input_KeyDown(KEY_Q)) {
		CP_Engine_Terminate();
	}

}

void enemy_exit(void) {



}