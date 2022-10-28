#include "cprocessing.h"
#include <cprocessing.h>
#include "subcontroller.h"
#include "SoundCast.h"
#include "Utils.h"
#include <math.h>
#include "enemy.h"
#include <stdbool.h>


bool player_detection;
#define ENEMY_COUNT (10)


ENEMY enemy[ENEMY_COUNT];

/*
ray head is detection
if detected
create a line from detection to wall, then player start position
accelerate along line, decelerate when reaching player start position
*/

ENEMY enemy[ENEMY_COUNT];

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
	player1.x = center_x;
	player1.y = center_y;

	enemy[1].x = 600;
	enemy[1].y = 600;
	enemy[1].velocity_x = 0;
	enemy[1].velocity_y = 0;
	enemy[1].acceleration_x = 0;
	enemy[1].acceleration_y = 0;
	enemy[1].alpha = 255;

	timer = 100;
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
	timer -= 1;

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