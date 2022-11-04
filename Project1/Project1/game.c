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
#include "enemy.h"
#include <stdlib.h>

//debug wall flag
int debug = 1;
#include "checkpoint.h"

//Ray cast stuff -HQ
float particleSize = 3.0f;

//energy used for pings -Nigel
int energy = 100;
bool clicked = false;
CP_Vector click1;
CheckPoint_1_Triggered = 0;

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
	CP_Settings_NoStroke();
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_DrawRect(barx, bary, barw, barh);
	CP_Settings_Fill(CP_Color_Create(240, 240, 240, alpha));
	CP_Graphics_DrawRect(barx, bary, barw, barh * ((float)energy / 100));
}

void CheckControls(void) {

	/*
	
	LIST OF OUR HOTKEYS

	[0] DEBUG MODE
	[T] DRAW LINE
	[Y] DRAW TRIANGLE
	[U] PLACE POINT(S)
	[I] DRAW POINTS
	[P] SAVE MAP
	[Z] UNDO LAST PLACED WALL

	[M1] FOCUSED BEAM
	[M2] AOE BEAM
	[M3] AOE BEAM

	[N] AOE BEAM FROM PLAYER

	[L] MR TEST
	[K] ENEMY TEST

	[M] MINI MAP
	[Space] Pause
	[Esc] Settings
	[Q] Quit Game
	
	*/

	if (CP_Input_KeyTriggered(KEY_0)) {
		if (debug == 0) {
			debug = 1;
		}
		else {
			debug = 0;
		}
	}

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

	if (CP_Input_KeyTriggered(KEY_P)) {
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
				CreateRay(CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY, 50, v.x * 200, v.y * 200,5, color);


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
			CreateRay(CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY, 50, v.x * 400, v.y * 400,5, color);


		}


	}
	else if (CP_Input_MouseTriggered(MOUSE_BUTTON_3)) {
		CP_Color color = CP_Color_Create(50, 50, 255, 255);
		//CP_Vector v = AngleToVector(-90);
		//CreateRay(CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY, 50, v.x * 200, v.y * 200, color);

		for (int i = 0; i < 36; i++) {
			CP_Vector v = AngleToVector(i * 10);
			CreateRay(CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY, 50, v.x * 200, v.y * 200,5, color);


		}

	}

	if (CP_Input_KeyTriggered(KEY_N)) {
		if (energy > 30) {
			CP_Color color = CP_Color_Create(0, 255, 0, 255);
			//CP_Vector v = AngleToVector(0);
			//CreateRay(CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY, 50, v.x * 200, v.y * 200, color);

			for (int i = 0; i < 36; i++) {
				CP_Vector v = AngleToVector(i * 10);
				CreateRay(-WorldX + CP_System_GetWindowWidth() / 2, -WorldY + CP_System_GetWindowHeight() / 2, 50, v.x * 200, v.y * 200, 1, color);


			}

			energy -= 30;
			CP_Sound_PlayAdvanced(ping, volume, 1, FALSE, 1);
		}
	}



	if (CP_Input_KeyTriggered(KEY_Z)) {
		UndoWall();
	}

	// MR's controller testing 
	if (CP_Input_KeyTriggered(KEY_L))
	{
		CP_Engine_SetNextGameState(controller_init, controller_update, controller_exit);

	}

	if (CP_Input_KeyTriggered(KEY_K))
	{
		CP_Engine_SetNextGameState(enemy_init, enemy_update, enemy_exit);

	}

	if (CP_Input_KeyTriggered(KEY_Q))
	{
		CP_Engine_Terminate();
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

	// Enemy test Jon
	enemy_place();
}

void subgame_update(void) {

	//1st draw layer, clear the background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));


	//CONTROL SCHEME FOR TESTING
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(20.0f);
	CP_Font_DrawText("[0] DEBUG MODE", 20, 20);
	CP_Font_DrawText("[T] DRAW LINE", 20, 40);
	CP_Font_DrawText("[Y] DRAW TRIANGLE", 20, 60);
	CP_Font_DrawText("[U] PLACE POINT(S)", 20, 80);
	CP_Font_DrawText("[I] DRAW POINTS", 20, 100);
	CP_Font_DrawText("[P] SAVE MAP", 20, 120);
	CP_Font_DrawText("[Z] UNDO LAST PLACED WALL", 20, 140);
	CP_Font_DrawText("[M1] FOCUSED BEAM", 20, 200);
	CP_Font_DrawText("[M2] AOE BEAM", 20, 220);
	CP_Font_DrawText("[M3] AOE BEAM", 20, 240);
	CP_Font_DrawText("[N] AOE BEAM FROM PLAYER", 20, 260);
	CP_Font_DrawText("[L] MR TEST", 20, 300);
	CP_Font_DrawText("[K] ENEMY TEST", 20, 320);
	CP_Font_DrawText("[M] MINI MAP", 20, 360);
	CP_Font_DrawText("[Space] Pause", 20, 380);
	CP_Font_DrawText("[Esc] Settings", 20, 400);
	CP_Font_DrawText("[Q] Quit Game", 20, 420);

	//2nd draw layer, the walls of the game
	if (debug == 1) {
		DrawWalls();
	}

	//2.5 draw Enemy
	enemy_draw();
	if (enemy_touch(WorldX, WorldY) == 1) {
		enemy[0].alpha = 0;
	}
	

	//3rd draw layer, the raycast
	RayUpdate(WorldX, WorldY);
	//4th draw layer, the UI for the game
	DrawEnergy();
	if (energy < 100) energy += 1;


	//draw checkpoints
	draw_checkpoint_1();
	//check checkppoint triggers
	cp1_triggered();
	if (CheckPoint_1_Triggered == 1)
	{
		CP_Settings_Fill(CP_Color_Create(255, 0, 255, 255));
		CP_Graphics_DrawRect(0, 0, 1000, 1000);
	}

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


	// World coords on mouse
	CP_Settings_TextSize(20.0f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	char buffer2[100] = { 0 };
	sprintf_s(buffer2, _countof(buffer2), "X:%.0f\nY:%.0f", CP_Input_GetMouseX() - WorldX, CP_Input_GetMouseY() - WorldY );
	CP_Font_DrawText(buffer2, CP_Input_GetMouseX(), CP_Input_GetMouseY() - 20);
	

}

void subgame_exit(void) {
	Sound_Deload();
}