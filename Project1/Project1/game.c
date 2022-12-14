/*
All content � 2021 DigiPen Institute of Technology Singapore, all rights reserved.
*/

#include "cprocessing.h"
#include "walls.h"
#include "SoundCast.h"
#include "Utils.h"
#include "game.h"
#include "tutorial.h"
#include "music.h"
#include <stdio.h>
#include "subcontroller.h"
#include <math.h>
#include "enemy.h"
#include <stdlib.h>
#include "credits.h"
#include "NewTutorial.h"
#include "beacon.h"
#include "menu.h"

//debug wall flag
int debug = 1;
#include "checkpoint.h"

//Ray cast stuff -HQ
float particleSize = 3.0f;

//energy used for pings -Nigel
int energy = 100;
int bar_timer = 0;
int bar_alpha = 255;
bool clicked = false;
CP_Vector click1;

/*
WorldX and WorldY functions as the offset for the camera system.
All coordinates used by all game objects will need to be offset by the WorldX and WorldY coordinates.
*/
//float WorldX = 0;
//float WorldY = 0;

//float WorldX = -285 + 960;
//float WorldX = -285 + (float) CP_System_GetWindowWidth() / 2;
//float WorldY = 485 + (float) CP_System_GetWindowHeight() / 2
//float WorldY = 485 + 540;

//Start point of the map
float WorldX = 800;
float WorldY = -1700;

//enemy - Jon
int dead = 0;

void DrawEnergy(void) {

	CP_Settings_RectMode(CP_POSITION_CORNER);
	float barx = 1850;
	float bary = 1.5f * ((float) CP_System_GetWindowHeight() / 2);
	float barw = 15;
	float barh = -(float) CP_System_GetWindowHeight() / 2;

	if (energy >= 100 && bar_alpha >= 0 ) {
		bar_timer += 1;
		if (bar_timer > 20) {
			bar_alpha -= 15;
		}
	}
	else if (bar_alpha <= 240 && energy < 100) {
		bar_alpha = 255;
		bar_timer = 0;
	}
	CP_Settings_NoStroke();
	CP_Settings_Fill(CP_Color_Create(30, 30, 30, bar_alpha));
	CP_Graphics_DrawRect(barx, bary, barw, barh);
	CP_Settings_Fill(CP_Color_Create(180, 180, 180, bar_alpha));
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

	(CP_Input_KeyTriggered(KEY_1)) ? WorldX = -285 + (float) CP_System_GetWindowWidth() / 2, WorldY = 485 + (float) CP_System_GetWindowHeight() / 2 : 0;
	(CP_Input_KeyTriggered(KEY_2)) ? WorldX = -370 + (float) CP_System_GetWindowWidth() / 2, WorldY = -4465 + (float) CP_System_GetWindowHeight() / 2 : 0;
	(CP_Input_KeyTriggered(KEY_3)) ? WorldX = -3350 + (float) CP_System_GetWindowWidth() / 2, WorldY = -4500 + (float) CP_System_GetWindowHeight() / 2 : 0;
	(CP_Input_KeyTriggered(KEY_4)) ? WorldX = -5950 + (float) CP_System_GetWindowWidth() / 2, WorldY = -2785 + (float) CP_System_GetWindowHeight() / 2 : 0;
	(CP_Input_KeyTriggered(KEY_5)) ? WorldX = -2200 + (float) CP_System_GetWindowWidth() / 2, WorldY = -2300 + (float) CP_System_GetWindowHeight() / 2 : 0;



	/*
	Made by Nigel

	Create a wall draw point every time you press the "T" key.
	*/
	if (CP_Input_KeyTriggered(KEY_T))
	{
		cpfailsafe();
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
		cpfailsafe();
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
		cpfailsafe();
		Wall_Init(CP_Input_GetMouseX() - WorldX, CP_Input_GetMouseY() - WorldY);
	}

	if (CP_Input_KeyTriggered(KEY_P)) {
		savewalls();
	}

	

	if (CP_Input_KeyTriggered(KEY_Z)) {
		UndoWall();
	}



	if (CP_Input_KeyTriggered(KEY_Q))
	{
		CP_Engine_Terminate();
	}

	if (CP_Input_KeyTriggered(KEY_E))
	{
		CP_Engine_SetNextGameState(credits_init, credits_update, credits_exit);
	}

	if (CP_Input_KeyTriggered(KEY_K))
	{
		CP_Engine_SetNextGameState(mainmenu_init, mainmenu_update, mainmenu_exit);
	}

}



void subgame_init(void) {
	CP_System_SetWindowSize(1920, 1080);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_BlendMode(CP_BLEND_ALPHA);

	game_states = resume;
	Sound_Init();
	CP_Sound_PlayAdvanced(introsound, volume, 1.0, FALSE, 0);
	center_x = (float) CP_System_GetWindowWidth() / 2;
	center_y = (float) CP_System_GetWindowHeight() / 2;
	player1.x = center_x;
	player1.y = center_y;
	//set up sound cast system
	loadwalls();
	createcpwalls();
	gate_checkpoint_init();
	// Player initialisation

	CheckPoint_1_Triggered = 0;
	CheckPoint_2_Triggered = 0;
	CheckPoint_3_Triggered = 0;
	exit_Triggered = 0;

	// Enemy test Jon
	enemy_place();
	checkpoint_init();
	dead = 0;
	debug = 0;
	shutdown_state = 1;

	WorldX = -370 + (float) CP_System_GetWindowWidth() / 2;
	WorldY = -4465 + (float) CP_System_GetWindowHeight() / 2;

	//Set up beacon system -HQ
	InitBeacon(point_1.pos);
}

void subgame_update(void) {
	//1st draw layer, clear the background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, 0);



	//CONTROL SCHEME FOR TESTING
	if (debug == 1) {
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
		CP_Font_DrawText("[M] MINI MAP", 20, 300);
		CP_Font_DrawText("[Space] Pause", 20, 340);
		CP_Font_DrawText("[Esc] Settings", 20, 360);
		CP_Font_DrawText("[Q] Quit Game", 20, 380);
	}


	//2nd draw layer, the walls of the game
	if (debug == 1) {
		DrawWalls();

	}
	//2.5 draw Enemy
	if (game_states == resume) {
		enemy_draw();
		enemy_beam(player1.x - WorldX, player1.y - WorldY);
		RayUpdate(WorldX, WorldY);
		if (energy < 100) energy += 1;
	}

	//draw checkpoints
	draw_checkpoint();

	//death feedback -HQ
	if (enemy_touch(WorldX, WorldY) == 1 && dead != 1) {
		//CP_Settings_TextSize(50.0f);
		//CP_Font_DrawText("You are Dead", (float) CP_System_GetWindowWidth() / 2, (float) CP_System_GetWindowHeight() / 2 - 200);
		CP_Color color = CP_Color_Create(255, 0, 0, 150);

		for (int i = 0; i < 72; i++) {
			CP_Vector v = AngleToVector(i * 5.f);
			CreateRay(player1.x - WorldX, player1.y - WorldY, 30, v.x, v.y, 2, color, false, 350, true);
		}

		dead = 1;
		CP_Sound_PlayAdvanced(rip, volume, 1, FALSE, 0);
		CP_Sound_StopGroup(CP_SOUND_GROUP_MUSIC);
	}
	if (dead == 1) {
		dead_menu();
		dead = dead_menu();
	}


	
	DrawEnergy();
	
	//turn on/off debug mode
	if (CP_Input_KeyTriggered(KEY_0)) {
		if (debug == 0) {
			debug = 1;
		}
		else {
			debug = 0;
		}
	}

	//Check the debug controls pressed each frame
	if (debug == 1) {
		CheckControls();
	}
	
	//Creating Player
	if (game_states == resume && debug == 1) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawCircle((float) CP_System_GetWindowWidth() / 2, (float) CP_System_GetWindowHeight() / 2, 25);
	}
	// movement function
	if (dead == 0)
	{
		movement();
	}

	UpdateBeacon();

	// World coords on mouse
	if (debug == 1) {
		CP_Settings_TextSize(20.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		char buffer2[100] = { 0 };
		sprintf_s(buffer2, _countof(buffer2), "X:%.0f\nY:%.0f", CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY);
		CP_Font_DrawText(buffer2, CP_Input_GetMouseX(), CP_Input_GetMouseY() - 20);
	}

	if (CP_Input_KeyTriggered(KEY_V))
	{
		CP_Engine_SetNextGameState(newtutorial_init, newtutorial_update, newtutorial_exit);

	}
	
}


void subgame_exit(void) {
	Sound_Deload();
	CWall = 0;
}