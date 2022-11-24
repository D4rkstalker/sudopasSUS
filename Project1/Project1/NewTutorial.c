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

void newtutorial_init(void)
{
	CP_System_SetWindowSize(1920, 1080);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	totalElapsedTime = 0;
	tut_stage = 0;
	sound_stage = 0;

	int time = 0;
	int delay = 45;

	player.x = 960;
	player.y = 540;
}

void newtutorial_update(void)
{
	CP_Settings_Fill(CP_Color_Create(120, 120, 120, 255));
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawText("PRESS T TO SKIP TUTORIAL.", 550, 100);
	if (CP_Input_KeyTriggered(KEY_T))
	{
		CP_Engine_SetNextGameState(subgame_init, subgame_update, subgame_exit);

	}

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, 0);
	tutorialMovement();
	
	//Draw Player
	RayUpdate(0, 0);
	time++;
	if (time > 20) {
		CP_Color color = CP_Color_Create(255, 255, 255, 150);

		for (int i = 0; i < 18; i++) {
			CP_Vector v = AngleToVector(i * 20);
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
				CP_Vector v = AngleToVector(i * 18);
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
			CP_Settings_Fill(CP_Color_Create(120, 120, 120, 255));
			CP_Settings_TextSize(50.0f);
			CP_Font_DrawText("Welcome Captain, this is your current position on our radar.", 345, 435);
			CP_Settings_RectMode(CP_POSITION_CENTER);
			CP_Settings_Stroke(CP_Color_Create(150, 150, 150, 255));
			CP_Settings_Fill(CP_Color_Create(25, 25, 25, 0));
			CP_Graphics_DrawRect(960, 540, 75, 75);
		}
		if (totalElapsedTime > 500)
		{
			tut_stage = Tut_Move;
		}
	}
	//Introduce Movement
	if (tut_stage == Tut_Move)
	{
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, 255));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("Use", 623, 462);
		CP_Font_DrawText("to move your ship", 917,462 );
		CP_Settings_Stroke(CP_Color_Create(150, 150, 150, 255));
		CP_Settings_Fill(CP_Color_Create(25, 25, 25, 0));
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRectAdvanced(752, 496, 50.0f, 50.0f, 0, 10.0f);
		CP_Graphics_DrawRectAdvanced(810, 496, 50.0f, 50.0f, 0, 10.0f);
		CP_Graphics_DrawRectAdvanced(870, 496, 50.0f, 50.0f, 0, 10.0f);
		CP_Graphics_DrawRectAdvanced(810, 436, 50.0f, 50.0f, 0, 10.0f);
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, 255));
		CP_Settings_TextSize(25.0f);
		CP_Font_DrawText("W", 804, 436);
		CP_Font_DrawText("A", 744, 496);
		CP_Font_DrawText("S", 804, 496);
		CP_Font_DrawText("D", 862, 496);


		if (CP_Input_KeyTriggered(KEY_W) || CP_Input_KeyTriggered(KEY_A) || CP_Input_KeyTriggered(KEY_S) || CP_Input_KeyTriggered(KEY_D))
		{
			tut_stage = Tut_Scan;

		}

	}
	//Introduce AOE Scan
	if (tut_stage == Tut_Scan)
	{
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, 255));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("You have a sonar equipped on the ship", 555, 462);
		CP_Font_DrawText("Right Click to Use it", 790, 615);
		CP_Settings_TextSize(23.0f);
		CP_Font_DrawText("RMB", 732, 612);
		CP_Settings_Stroke(CP_Color_Create(150, 150, 150, 255));
		CP_Settings_Fill(CP_Color_Create(25, 25, 25, 0));
		CP_Graphics_DrawRectAdvanced(755, 610, 50.0f, 50.0f, 0, 10.0f);


		if (CP_Input_MouseTriggered(MOUSE_BUTTON_RIGHT))
		{
			tut_stage = Tut_Beam;

			CP_Color color = CP_Color_Create(255, 255, 255, 220);

			for (int i = 0; i < 36; i++) {
				CP_Vector v = AngleToVector(i * 10);
				CreateRay(player.x, player.y, 50, v.x, v.y, 2, color, false, 130, true);


			}
			CP_Sound_PlayAdvanced(ping, volume, 1, FALSE, 0);


		}

	}
	//Introduce Directed Scan
	if (tut_stage == Tut_Beam)
	{
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, 255));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("And a directed sound cannon.",647, 462);
		CP_Font_DrawText("Left Click to Use it", 782, 615);
		CP_Settings_TextSize(23.0f);
		CP_Font_DrawText("LMB", 723, 612);
		CP_Settings_Stroke(CP_Color_Create(150, 150, 150, 255));
		CP_Settings_Fill(CP_Color_Create(25, 25, 25, 0));
		CP_Graphics_DrawRectAdvanced(745, 610, 50.0f, 50.0f, 0, 10.0f);


		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
		{
			tut_stage = Tut_CP;

			float x = CP_System_GetWindowWidth() / 2;
			float y = CP_System_GetWindowHeight() / 2;

			CP_Color color = CP_Color_Create(255, 255, 255, 220);
			CP_Vector outv = CP_Vector_Normalize(CP_Vector_Subtract(CP_Vector_Set(CP_Input_GetMouseWorldX(), CP_Input_GetMouseWorldY()), CP_Vector_Set(x, y)));
			float a = CP_Math_Degrees(atan2(outv.y, outv.x));
			for (int i = -18; i < 18; i++) {
				CP_Vector v = AngleToVector(a + i * 1);
				CreateRay(player.x, player.y, 25, v.x, v.y, 2, color, true, 200, true);
			}
			CP_Sound_PlayAdvanced(ping, volume, 1, FALSE, 0);
		}

	}
	//Introduce Checkpoints
	if (tut_stage == Tut_CP)
	{
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, 255));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("Yellow pings are checkpoints, go interact with it.", (CP_System_GetWindowWidth() / 2.0f) - 400, (CP_System_GetWindowHeight() / 2.5f));
		if (player.x > 1100 - 25 && player.x < 1100 + 25 && player.y > 540 - 25 && player.y < 540 + 25) { //CP Position1100 540
			CP_Font_DrawText("press", 622, 610);
			CP_Font_DrawText("to use it", 1132, 610);
			CP_Settings_Stroke(CP_Color_Create(150, 150, 150, 255));
			CP_Settings_Fill(CP_Color_Create(25, 25, 25, 0));
			CP_Settings_RectMode(CP_POSITION_CENTER);
			CP_Graphics_DrawRectAdvanced(935, 608, 366.0f, 50.0f, 0, 10.0f);
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255 * 0.7));
			CP_Graphics_DrawRectAdvanced(935, 623, 186.0f, 3.0f, 0, 0.0f);


			if (CP_Input_KeyTriggered(KEY_SPACE)) // ADD Check if player is inside hitbox of checkpoint.
			{
				tut_stage = Enemy_Spawn;

				CP_Sound_PlayAdvanced(ping, volume, 2, FALSE, 0);
				CP_Color color = CP_Color_Create(0, 255, 255, 50);
				for (int i = 0; i < 36; i++) {
					CP_Vector v = AngleToVector(i * 10);
					CreateRay(player.x, player.y, 50, v.x, v.y, 0, color, false, 100, false); // @TODO
				}

			}
		}


	}

	//Introduce players to enemy
	if (tut_stage == Enemy_Spawn)
	{
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, 255));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("Red Pings are enemies, they can't be killed.", (CP_System_GetWindowWidth() / 2.0f) - 400, (CP_System_GetWindowHeight() / 2.5f));
		CP_Font_DrawText("Draw 1 Enemy here", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f)+200.0f);

		if (CP_Input_KeyTriggered(KEY_1))
		{
			tut_stage = Enemy_Move;

		}

	}
	//Introduce Stealth movement
	if (tut_stage == Enemy_Move)
	{
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, 255));
		CP_Settings_TextSize(100.0f);
		CP_Font_DrawText("We can move around the enemy without them noticing", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f));
		CP_Font_DrawText("press 2", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f) + 200.0f);

		if (CP_Input_KeyTriggered(KEY_2))
		{
			tut_stage = Enemy_Sound;

		}

	}
	//Introduce Enemy mechanics
	if (tut_stage == Enemy_Sound)
	{	// Enemy follow ping generated by World.
		if (sound_stage == Sound_Attract) {

			CP_Settings_Fill(CP_Color_Create(120, 120, 120, 255));
			CP_Settings_TextSize(100.0f);
			CP_Font_DrawText("Enemies follow sound", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f));
			CP_Font_DrawText("Watch", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f) + 200.0f);


			//create a CP ping ping.
			//enemy walk to the BLUE ping. 
			if (CP_Input_KeyTriggered(KEY_2))
			{
				sound_stage = Sound_Distract;

			}
		}
		// Enemy follow ping made by player
		if (sound_stage == Sound_Distract) {

			CP_Settings_Fill(CP_Color_Create(120, 120, 120, 255));
			CP_Settings_TextSize(100.0f);
			CP_Font_DrawText("Try using ur focused ping to distract them", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f));
			CP_Font_DrawText("Left Click!", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f) + 200.0f);


			if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
			{
				sound_stage = Sound_Trigger;

			}
		}
		// Player scans a checkpoint and triggers enemies
		if (sound_stage == Sound_Trigger) {

			CP_Settings_Fill(CP_Color_Create(120, 120, 120, 255));
			CP_Settings_TextSize(100.0f);
			CP_Font_DrawText("When you scan a checkpoint, they'll be coming", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f));
			CP_Font_DrawText("Press Space", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f) + 200.0f);


			//create a CP ping ping.
			//enemy walk to the BLUE ping. 
			if (CP_Input_KeyTriggered(KEY_SPACE))
			{
				tut_stage = Enemy_Kill;

			}
		}

		

	}
	//Enemies kill players, death screen reload to main game.
	if (tut_stage == Enemy_Kill)
	{
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, 255));
		CP_Settings_TextSize(100.0f);
		CP_Font_DrawText("Good luck out there", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f));
		CP_Font_DrawText("See you on the other side", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f) + 200.0f);

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