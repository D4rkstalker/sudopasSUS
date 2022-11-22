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
}

void newtutorial_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, 0);

	movement();

	totalElapsedTime += 5;

	//float currentElapsedTime = CP_System_GetSeconds();
	//totalElapsedTime += currentElapsedTime;
	if (tut_stage == Tut_Player)
	{

		if (totalElapsedTime < 300)
		{
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			CP_Graphics_DrawCircle(CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2, 25);

			CP_Settings_Fill(CP_Color_Create(120, 120, 120, 255));
			CP_Settings_TextSize(50.0f);
			CP_Font_DrawText("Welcome Captain, this is your current position on our radar.", 345, 435);
			CP_Settings_RectMode(CP_POSITION_CENTER);
			CP_Settings_Stroke(CP_Color_Create(150, 150, 150, 255));
			CP_Settings_Fill(CP_Color_Create(25, 25, 25, 0));
			CP_Graphics_DrawRect(960, 530, 50, 50);
		}
		if (totalElapsedTime > 300)
		{
			tut_stage = Tut_Move;
		}
	}
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

		}

	}
	
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

		}

	}

	if (tut_stage == Tut_CP)
	{
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, 255));
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("Check Point", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f));
		CP_Font_DrawText("Press", 622, 610);
		CP_Font_DrawText("to use it", 1132, 610);
		CP_Settings_Stroke(CP_Color_Create(150, 150, 150, 255));
		CP_Settings_Fill(CP_Color_Create(25, 25, 25, 0));
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRectAdvanced(935, 608, 366.0f, 50.0f, 0, 10.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255 * 0.7));
		CP_Graphics_DrawRectAdvanced(935, 623, 186.0f, 3.0f, 0, 0.0f);

		if (CP_Input_KeyTriggered(KEY_SPACE))
		{
			tut_stage = Enemy_Spawn;

		}

	}

	if (tut_stage == Enemy_Spawn)
	{
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, 255));
		CP_Settings_TextSize(100.0f);
		CP_Font_DrawText("Enemies dont die", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f));
		CP_Font_DrawText("Draw 1 Enemy here", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f)+200.0f);

		if (CP_Input_KeyTriggered(KEY_1))
		{
			tut_stage = Enemy_Move;

		}

	}

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

	if (tut_stage == Enemy_Sound)
	{
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
		if (sound_stage == Sound_Distract) {

			CP_Settings_Fill(CP_Color_Create(120, 120, 120, 255));
			CP_Settings_TextSize(100.0f);
			CP_Font_DrawText("Try using ur focused ping to distract them", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f));
			CP_Font_DrawText("Left Click!", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f) + 200.0f);


			//create a CP ping ping.
			//enemy walk to the BLUE ping. 
			if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
			{
				sound_stage = Sound_Trigger;

			}
		}

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