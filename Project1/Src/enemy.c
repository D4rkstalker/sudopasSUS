#include "cprocessing.h"
#include <cprocessing.h>
#include "subcontroller.h"
#include "SoundCast.h"
#include "Utils.h"


struct Player {
	float x;
	float y;
	float velocity_x;
	float velocity_y;
	float acceleration_x;
	float acceleration_y;


} player1;






void enemy_init(void) {

	CP_System_SetWindowSize(1920, 1080);

	CP_System_SetWindowSize(1920, 1080);
	CP_Settings_EllipseMode(CP_POSITION_CENTER);
	float center_x = CP_System_GetDisplayWidth() / 2;
	float center_y = CP_System_GetDisplayHeight() / 2;

	player1.x = center_x;
	player1.y = center_y;
	player1.acceleration_x = 10;
	player1.acceleration_y = 10;
	player1.velocity_x = 10;
	player1.velocity_y = 10;



}

void enemy_update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(25, 25, 25, 255));

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawCircle(player1.x, player1.y, 10);

	movement();

	if (CP_Input_KeyDown(KEY_SPACE)) {
		for (int i = 0; i < 36; i++) {
			CP_Vector v = AngleToVector(i * 10.0);
			CreateRay(player1.x, player1.y, 50, v.x * 200, v.y * 200);


		}
	}




	if (CP_Input_KeyDown(KEY_Q)) {
		CP_Engine_Terminate();
	}

}

void enemy_exit(void) {



}