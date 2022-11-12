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

//debug wall flag
int debug = 1;
#include "checkpoint.h"

//Ray cast stuff -HQ
float particleSize = 3.0f;

//energy used for pings -Nigel
int energy = 100;
bool clicked = false;
CP_Vector click1;

int time = 0;

tutorial_state = 0;
shutdown_state = 1;

/*
WorldX and WorldY functions as the offset for the camera system.
All coordinates used by all game objects will need to be offset by the WorldX and WorldY coordinates.
*/
//float WorldX = 0;
//float WorldY = 0;

float WorldX = 800;
float WorldY = 775;
//Start point of the map
//float WorldX = 800;
//float WorldY = -1700;

//enemy - Jon
int dead = 0;

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


}



void subgame_init(void) {
	CP_System_SetWindowSize(1920, 1080);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_BlendMode(CP_BLEND_ALPHA);
	game_states = resume;
	Sound_Init();
	CP_Sound_PlayAdvanced(introsound, volume, 1.0, FALSE, 0);
	center_x = CP_System_GetWindowWidth() / 2;
	center_y = CP_System_GetWindowHeight() / 2;
	player1.x = center_x;
	player1.y = center_y;
	//set up sound cast system
	loadwalls();
	createcpwalls();
	// Player initialisation

	// Enemy test Jon
	enemy_place();
	dead = 0;
}

void subgame_update(void) {
	//1st draw layer, clear the background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));


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
		//CP_Font_DrawText("[K] ENEMY TEST", 20, 320);
		CP_Font_DrawText("[M] MINI MAP", 20, 300);
		CP_Font_DrawText("[Space] Pause", 20, 340);
		CP_Font_DrawText("[Esc] Settings", 20, 360);
		CP_Font_DrawText("[Q] Quit Game", 20, 380);
	}

	switch (tutorial_state) {
	case 0:
		wake_message();
		break;
	case 1:
		rmb_tut();
		break;
	case 2:
		tutorial_message();
		break;
	case 3:
		dodge();
		break;
	case 4:
		tut_exit();
		break;
	case 5:
		title_screen();
		break;
	default:
		;
	}
	//2nd draw layer, the walls of the game
	if (debug == 1) {
		DrawWalls();
		//2.5 draw Enemy
		enemy_draw();
		
	}

	//draw checkpoints
	draw_checkpoint();
	
	if (enemy_touch(WorldX, WorldY) == 1 && dead != 1) {
		//CP_Settings_TextSize(50.0f);
		//CP_Font_DrawText("You are Dead", CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 - 200);
		dead = 1;
		CP_Sound_PlayAdvanced(rip, volume, 1, FALSE, 0);
		CP_Sound_StopGroup(CP_SOUND_GROUP_MUSIC);
	}
	if (dead == 1) {
		dead_menu();
		dead = dead_menu();
	}
	
	

	//3rd draw layer, the raycast

	RayUpdate(WorldX, WorldY);
	//4th draw layer, the UI for the game
	DrawEnergy();
	if (energy < 100) energy += 1;


	//Check the controls pressed each frame

	CheckControls();

	//Creating Player
	if (game_states == resume && debug == 1) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawCircle(CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2, 25);
	}
	// movement function
	if (tutorial_state >= 3)
	{
		movement();
	}

	double title_alpha = -100;
	double tutorial_alpha = 0;
	int loop = 0;

	//tutorial_message();


	// World coords on mouse
	if (debug == 1) {
		CP_Settings_TextSize(20.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		char buffer2[100] = { 0 };
		sprintf_s(buffer2, _countof(buffer2), "X:%.0f\nY:%.0f", CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY);
		CP_Font_DrawText(buffer2, CP_Input_GetMouseX(), CP_Input_GetMouseY() - 20);
	}

	if (shutdown_state == 0 || game_states != resume){
	time++;
	if (time > 10) {
		CP_Color color = CP_Color_Create(255, 255, 255, 127);

		for (int i = 0; i < 18; i++) {
			CP_Vector v = AngleToVector(i * 20);
			CreateRay(player1.x - WorldX, player1.y - WorldY, 20, v.x, v.y, 1, color, false, 50,true);


		}
		time = 0;
	}
	}
	
}

void subgame_exit(void) {
	Sound_Deload();
}