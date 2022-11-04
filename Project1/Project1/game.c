#include "cprocessing.h"
#include "walls.h"
#include "SoundCast.h"
#include "Utils.h"
#include "game.h"
#include "menu.h"
#include "music.h"
#include <stdio.h>
#include "subcontroller.h"
#include <math.h>

//Ray cast stuff -HQ
float particleSize = 3.0f;

//energy used for pings -Nigel
int energy = 100;
bool clicked = false;
CP_Vector click1;

/*
WorldX and WorldY functions as the offset for the camera system.
All coordinates used by all game objects will need to be offset by the WorldX and WorldY coordinates.
*/
float WorldX = 0;
float WorldY = 0;

void DrawEnergy(void) {

	CP_Settings_RectMode(CP_POSITION_CORNER);
	float alpha = 255;
	float barx = CP_System_GetDisplayWidth() / 2 + 50;
	float bary = CP_System_GetDisplayHeight() / 2 + 16;
	float barw = 5;
	float barh = -60;

	if (energy >= 100 && alpha >= 0) {
		alpha -= 15;
	}
	else if (alpha <= 240) {
		alpha += 15;
	}

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_DrawRect(barx, bary, barw, barh);
	CP_Settings_Fill(CP_Color_Create(240, 240, 240, alpha));
	CP_Graphics_DrawRect(barx, bary, barw, barh * ((float)energy / 100));
}

void CheckControls(void) {

	/*
	Made by Nigel

	Create a wall draw point every time you press the "T" key.
	*/
	if (CP_Input_KeyTriggered(KEY_T))
	{
		if (drawpoint == 0) {
			drawx[0] = CP_Input_GetMouseX() - WorldX;
			drawy[0] = CP_Input_GetMouseY() - WorldY;
			drawpoint += 1;
		}
		else {
			Wall_Init(CP_Input_GetMouseX() - WorldX, CP_Input_GetMouseY() - WorldY);
		}
	}

	if (CP_Input_KeyTriggered(KEY_Y))
	{
		switch (drawpoint) {

		case 0:
			drawx[0] = CP_Input_GetMouseX() - WorldX;
			drawy[0] = CP_Input_GetMouseY() - WorldY;
			drawpoint += 1;
			break;
		case 1:
			drawx[1] = CP_Input_GetMouseX() - WorldX;
			drawy[1] = CP_Input_GetMouseY() - WorldY;
			drawpoint += 1;
			break;
		default:
			drawpoint = -1;
			Wall_Init(CP_Input_GetMouseX() - WorldX, CP_Input_GetMouseY() - WorldY);
			}
	}

	if (CP_Input_KeyTriggered(KEY_U))
	{
		drawx[drawpoint] = CP_Input_GetMouseX() - WorldX;
		drawy[drawpoint] = CP_Input_GetMouseY() - WorldY;
		drawpoint += 1;
			
	}

	if (CP_Input_KeyTriggered(KEY_I))
	{
		Wall_Init(CP_Input_GetMouseX() - WorldX, CP_Input_GetMouseY() - WorldY);
	}

	if (CP_Input_KeyTriggered(KEY_S)) {
		savewalls();
	}

	//HQ stuff

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
		if (energy > 30) {
			CP_Color color = CP_Color_Create(90, 180, 77, 155);
			//CP_Vector v = AngleToVector(90);a
			//CreateRay(CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY, 50, v.x * 200, v.y * 200, color);
			CP_Vector outv = CP_Vector_Normalize(CP_Vector_Subtract(CP_Vector_Set(CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY), CP_Vector_Set(player1.x,player1.y)));
			float a = CP_Vector_Angle(outv, CP_Vector_Set(WorldX,WorldY));
			for (int i = 0; i < 1; i++) {
				CP_Vector v = AngleToVector(i * 1);
				CreateRay(CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY, 50, v.x * 200, v.y * 200,0, color);


			}

			//CreateRay(click1.x, click1.y, 50, outv.x * 400, outv.y * 400, color);


			energy -= 30;
			CP_Sound_PlayAdvanced(ping, volume, 1, FALSE, 1);


		}


	}
	else if (CP_Input_MouseTriggered(MOUSE_BUTTON_2)) {
		CP_Color color = CP_Color_Create(255, 50, 50, 255);
		//CP_Vector v = AngleToVector(0);
		//CreateRay(CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY, 50, v.x * 200, v.y * 200, color);

		for (int i = 0; i < 36; i++) {
			CP_Vector v = AngleToVector(i * 10);
			CreateRay(CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY, 50, v.x * 200, v.y * 200,1, color);


		}


	}
	else if (CP_Input_MouseTriggered(MOUSE_BUTTON_3)) {
		CP_Color color = CP_Color_Create(50, 50, 255, 255);
		//CP_Vector v = AngleToVector(-90);
		//CreateRay(CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY, 50, v.x * 200, v.y * 200, color);

		for (int i = 0; i < 36; i++) {
			CP_Vector v = AngleToVector(i * 10);
			CreateRay(CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY, 50, v.x * 200, v.y * 200,1, color);


		}


	}

	if (CP_Input_KeyTriggered(KEY_Q))
	{
		CP_Engine_SetNextGameState(mainmenu_init, mainmenu_update, mainmenu_exit);
	}

	if (CP_Input_KeyTriggered(KEY_Z)) {
		UndoWall();
	}

}



void subgame_init(void) {
	CP_System_SetWindowSize(1920, 1080);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_BlendMode(CP_BLEND_ALPHA);

	Sound_Init();
	CP_Sound_PlayAdvanced(introsound, volume, 1.0, FALSE, 7);

	//set up sound cast system
	loadwalls();
	// Player initialisation

}

void subgame_update(void) {

	//1st draw layer, clear the background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	//2nd draw layer, the walls of the game
	DrawWalls();

	//3rd draw layer, the raycast
	RayUpdate(WorldX, WorldY);
	//4th draw layer, the UI for the game
	DrawEnergy();
	if (energy < 100) energy += 1;

	//Check the controls pressed each frame
	CheckControls();


	//Creating Player
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawCircle(CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2, 25);
	// movement function
	movement();

	double title_alpha = -100;
	double tutorial_alpha = 0;
	int loop = 0;

	tutorial_message();



}

void subgame_exit(void) {
	Sound_Deload();
}