#include "cprocessing.h"
#pragma once
#include "tutorial.h"
#include "subcontroller.h"
#include "Utils.h"
#include "SoundCast.h"
#include "checkpoint.h"
#include "music.h"
#include "game.h"
#include "enemy.h"
#include <stdlib.h>
#include "NewTutorial.h"
int isplayer = 0;

void newtutorial_init(void)
{
	CP_System_SetWindowSize(1920, 1080);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	enemy_place_tut();

	totalElapsedTime = 0;
	tut_stage = 0;
	sound_stage = 0;

	int time = 0;
	int delay = 45;
	int countdown = 0;
	

	player.x = 960;
	player.y = 540;
	WorldX = 0;
	WorldY = 0;
}

void newtutorial_update(void)
{	
	enemy[0].alpha = 0;

	CP_Settings_Fill(CP_Color_Create(120, 120, 120, 255));
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawText("PRESS T TO SKIP TUTORIAL", 550, 100);
	if (CP_Input_KeyTriggered(KEY_T))
	{
		CP_Engine_SetNextGameState(subgame_init, subgame_update, subgame_exit);

	}

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, 0);
	tutorialMovement(isplayer);
	
	//Constant counting
	countdown += 5;
	//Draw Player
	RayUpdate(0, 0);
	time++;
	if (time > 25) {
		CP_Color color = CP_Color_Create(255, 255, 255, 150);

		for (int i = 0; i < 18; i++) {
			CP_Vector v = AngleToVector(i * 20.f);
			CreateRay(player.x,player.y, 20, v.x, v.y, 4, color, false, 50, true);


		}
		
		time = 0;
	}
	//Draw Tut Checkpoint
	if (tut_stage == Tut_CP) {
		delay++;
		if (delay > 50)
		{
			CP_Color color = CP_Color_Create(255, 255, 0, 50);
			for (int i = 0; i < 20; i++) {
				CP_Vector v = AngleToVector(i * 18.f);
				CreateRay(1100, 540, 10, v.x, v.y, 1, color, false, 100, false);
			}
			delay = 0;
		}
	}
	//Timer for first message
	totalElapsedTime += 5;
	//Introduce Player
	if (tut_stage == Tut_Player)
	{

		if (totalElapsedTime < 500)
		{
			CP_Settings_Fill(CP_Color_Create(120, 120, 120, countdown));
			CP_Settings_TextSize(50.0f);
			CP_Font_DrawText("Welcome Captain, this is your current position on our radar", 345, 435);
			CP_Settings_RectMode(CP_POSITION_CENTER);
			CP_Settings_Stroke(CP_Color_Create(150, 150, 150, 255));
			CP_Settings_Fill(CP_Color_Create(25, 25, 25, 0));
			CP_Graphics_DrawRect(960, 540, 75, 75);
		}
		if (totalElapsedTime > 500)
		{
			tut_stage = Tut_Move;
			countdown = 0;
		}
	}
	//Introduce Movement
	if (tut_stage == Tut_Move)
	{
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, countdown));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("Use", 623, 462);
		CP_Font_DrawText("to move your ship", 917,462 );
		CP_Settings_Stroke(CP_Color_Create(150, 150, 150, countdown));
		CP_Settings_Fill(CP_Color_Create(25, 25, 25, 0));
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRectAdvanced(752, 496, 50.0f, 50.0f, 0, 10.0f);
		CP_Graphics_DrawRectAdvanced(810, 496, 50.0f, 50.0f, 0, 10.0f);
		CP_Graphics_DrawRectAdvanced(870, 496, 50.0f, 50.0f, 0, 10.0f);
		CP_Graphics_DrawRectAdvanced(810, 436, 50.0f, 50.0f, 0, 10.0f);
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, countdown));
		CP_Settings_TextSize(25.0f);
		CP_Font_DrawText("W", 804, 436);
		CP_Font_DrawText("A", 744, 496);
		CP_Font_DrawText("S", 804, 496);
		CP_Font_DrawText("D", 862, 496);

		if (countdown > 150) {
			if (CP_Input_KeyTriggered(KEY_W) || CP_Input_KeyTriggered(KEY_A) || CP_Input_KeyTriggered(KEY_S) || CP_Input_KeyTriggered(KEY_D))
			{
				tut_stage = Tut_Scan;
				countdown = 0;
			}
		}

	}
	//Introduce AOE Scan
	if (tut_stage == Tut_Scan)
	{
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, countdown));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("You have a sonar equipped on the ship", 555, 462);
		CP_Font_DrawText("Right Click to Use it", 790, 615);
		CP_Settings_TextSize(20.0f);
		CP_Font_DrawText("RMB", 735, 612);
		CP_Settings_Stroke(CP_Color_Create(150, 150, 150, countdown));
		CP_Settings_Fill(CP_Color_Create(25, 25, 25, 0));
		CP_Graphics_DrawRectAdvanced(755, 610, 50.0f, 50.0f, 0, 10.0f);

		if (countdown > 150) {
			if (CP_Input_MouseTriggered(MOUSE_BUTTON_RIGHT))
			{
				tut_stage = Tut_Beam;
				countdown = 0;

			}
		}
	}
	//Introduce Directed Scan
	if (tut_stage == Tut_Beam)
	{
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, countdown));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("And a directed sound cannon",647, 462);
		CP_Font_DrawText("Left Click to Use it", 782, 615);
		CP_Settings_TextSize(20.0f);
		CP_Font_DrawText("LMB", 725, 612);
		CP_Settings_Stroke(CP_Color_Create(150, 150, 150, countdown));
		CP_Settings_Fill(CP_Color_Create(25, 25, 25, 0));
		CP_Graphics_DrawRectAdvanced(745, 610, 50.0f, 50.0f, 0, 10.0f);

		if (countdown > 150) {
			if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
			{
				tut_stage = Tut_CP;
				countdown = 0;

			}
		}
	}
	//Introduce Checkpoints
	if (tut_stage == Tut_CP)
	{
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, countdown));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("Yellow pings are checkpoints, go interact with it", (CP_System_GetWindowWidth() / 2.0f) - 400, (CP_System_GetWindowHeight() / 2.5f));
		if (player.x > 1100 - 25 && player.x < 1100 + 25 && player.y > 540 - 25 && player.y < 540 + 25) { //CP Position1100 540
			CP_Font_DrawText("press", 622, 610);
			CP_Font_DrawText("to use it", 1132, 610);
			CP_Settings_Stroke(CP_Color_Create(150, 150, 150, 150));
			CP_Settings_Fill(CP_Color_Create(25, 25, 25, 0));
			CP_Settings_RectMode(CP_POSITION_CENTER);
			CP_Graphics_DrawRectAdvanced(935, 608, 366.0f, 50.0f, 0, 10.0f);
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, (int) (255 * 0.7)));
			CP_Graphics_DrawRectAdvanced(935, 623, 186.0f, 3.0f, 0, 0.0f);


			if (CP_Input_KeyTriggered(KEY_SPACE)) // ADD Check if player is inside hitbox of checkpoint.
			{
				tut_stage = Enemy_Spawn;
				countdown = 0;

				CP_Sound_PlayAdvanced(ping, volume, 2, FALSE, 0);
				CP_Color color = CP_Color_Create(0, 255, 255, 50);
				for (int i = 0; i < 36; i++) {
					CP_Vector v = AngleToVector(i * 10.f);
					CreateRay(player.x, player.y, 50, v.x, v.y, 0, color, false, 100, false); // @TODO
				}

			}
		}


	}
	if (tut_stage >= Enemy_Spawn)
	{
		enemy_draw();
		enemy_beam(WorldX, WorldY);
	}
	//Introduce players to enemy
	
	if (tut_stage == Enemy_Spawn)
	{	
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, countdown));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("Red Pings are enemies, they can't be killed", (CP_System_GetWindowWidth() / 2.0f) - 400, (CP_System_GetWindowHeight() / 2.5f));
		CP_Font_DrawText("Press 1", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f)+200.0f);
		

		if (CP_Input_KeyTriggered(KEY_1))
		{
			tut_stage = Enemy_Move;
			countdown = 0;

		}

	}
	//Introduce Stealth movement
	if (tut_stage == Enemy_Move)
	{
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, countdown));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("Touching an enemy will KILL YOU", (CP_System_GetWindowWidth() / 2.0f) - 400, (CP_System_GetWindowHeight() / 2.5f));
		CP_Font_DrawText("Press 2", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f) + 200.0f);

		if (CP_Input_KeyTriggered(KEY_2))
		{
			tut_stage = Enemy_Sound;
			countdown = 0;

		}

	}
	//Introduce Enemy mechanics
	if (tut_stage == Enemy_Sound)
	{	// Enemy follow ping generated by World.
		if (sound_stage == Sound_Attract) {

			CP_Settings_Fill(CP_Color_Create(120, 120, 120, countdown));
			CP_Settings_TextSize(50.0f);
			CP_Font_DrawText("Enemies follow your sound", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f));
			CP_Font_DrawText("Watch", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f) + 200.0f);


			//create a CP ping ping.
			//enemy walk to the BLUE ping. 
			if (CP_Input_KeyTriggered(KEY_2))
			{
				sound_stage = Sound_Distract;
				countdown = 0;

			}
		}
		// Enemy follow ping made by player
		if (sound_stage == Sound_Distract) {
			isplayer = 1;
			CP_Settings_Fill(CP_Color_Create(120, 120, 120, countdown));
			CP_Settings_TextSize(50.0f);
			CP_Font_DrawText("Your beams will attract enemies", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f));
			CP_Font_DrawText("Use this to your advantage...", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f) + 200.0f);


			if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
			{
				sound_stage = Sound_Trigger;
				countdown = 0;

			}
		}
		// Player scans a checkpoint and triggers enemies
		if (sound_stage == Sound_Trigger) {

			CP_Settings_Fill(CP_Color_Create(120, 120, 120, countdown));
			CP_Settings_TextSize(50.0f);
			CP_Font_DrawText("When you scan a checkpoint, they'll be coming", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f));
			CP_Font_DrawText("Press Space", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f) + 200.0f);


			//create a CP ping ping.
			//enemy walk to the BLUE ping. 
			if (CP_Input_KeyTriggered(KEY_SPACE))
			{
				tut_stage = Enemy_Kill;
				countdown = 0;

			}
		}

		

	}
	//Enemies kill players, death screen reload to main game.
	if (tut_stage == Enemy_Kill)
	{
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, countdown));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("Good luck out there", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f));
		CP_Font_DrawText("Try and make it out alive", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f) + 200.0f);

		if (CP_Input_KeyTriggered(KEY_1))
		{
			CP_Engine_SetNextGameState(subgame_init, subgame_update, subgame_exit);

		}

	}

	CP_Settings_TextSize(20.0f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	char buffer3[100] = { 0 };
	sprintf_s(buffer3, _countof(buffer3), "X:%.0f\nY:%.0f", CP_Input_GetMouseWorldX(), CP_Input_GetMouseWorldY());
	CP_Font_DrawText(buffer3, CP_Input_GetMouseX(), CP_Input_GetMouseY() - 20);

}

void newtutorial_exit(void)
{

}