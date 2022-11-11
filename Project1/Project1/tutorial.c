#include "cprocessing.h"
#pragma once
#include "tutorial.h"
#include "subcontroller.h"
#include "Utils.h"
#include "SoundCast.h"
#include "checkpoint.h"
#include "music.h"

//message tutorial, title, wake, rmb;

float tutorial_alpha = 0;
float tut_timer = 0.f;
float tut_duration = 2.f;
float tut_min_alpha = 0;
float tut_max_alpha = 255;
int tut_loop = 0;

float title_alpha = 0;
float title_timer = 0.f;
float title_duration = 5.f;
float title_min_alpha = 0;
float title_max_alpha = 255;
int title_loop = 0;

float wake_alpha = 0;
float wake_timer = 0.f;
float wake_duration = 2.f;
float wake_min_alpha = 0;
float wake_max_alpha = 255;
int wake_loop = 0;

float rmb_alpha = 0;
float rmb_timer = 0.f;
float rmb_duration = 2.f;
float rmb_min_alpha = 0;
float rmb_max_alpha = 255;
int rmb_loop = 0;

int dodge_loop = 0;
static int timer = 0;

float EaseInQuad(float start, float end, float value)
{
	end -= start;
	return end * value * value + start;
}

float EaseOutQuad(float start, float end, float value)
{
	end -= start;
	return -end * value * (value - 2) + start;
}

void wake_message(void)
{
	if (wake_loop == 0)
	{
		wake_timer += CP_System_GetDt();
		wake_alpha = EaseInQuad(wake_min_alpha, wake_max_alpha, wake_timer / wake_duration);

		//TUTORIAL MESSAGE
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, wake_alpha));
		CP_Settings_TextSize(100.0f);
		CP_Font_DrawText("Wake up...", (CP_System_GetWindowWidth() / 2.0f)-100, (CP_System_GetWindowHeight() / 2.5f));


		CP_Settings_Fill(CP_Color_Create(120, 120, 120, wake_alpha));
		CP_Settings_TextSize(65.0f);
		CP_Font_DrawText("Press", 600, 725);

		CP_Color StartOutline = CP_Color_Create(150, 150, 150, wake_alpha);
		CP_Settings_Stroke(StartOutline);
		CP_Settings_Fill(CP_Color_Create(25, 25, 25, wake_alpha));
		//space
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRectAdvanced(1010, 700, 500.0f, 70.0f, 0, 10.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, wake_alpha*0.7));
		CP_Graphics_DrawRectAdvanced(1010, 710, 150.0f, 5.0f, 0, 0.0f);



		if (CP_Input_KeyTriggered(KEY_SPACE))
		{
			CP_Color color = CP_Color_Create(255, 255, 255, 55);
			for (int i = 0; i < 50; i++) {
				CP_Vector v = AngleToVector(i * 7);
				CreateRay(160, -235, 25, v.x , v.y , 0.2, color, false,50);
			}
			shutdown_state = 0;
			wake_alpha = wake_alpha;
			wake_timer = 0;
			wake_loop = 1;

		}
	}
	if (wake_loop == 1)
	{
		wake_timer += CP_System_GetDt();
		wake_alpha = EaseOutQuad(wake_max_alpha, wake_min_alpha, wake_timer / wake_duration);

		CP_Settings_Fill(CP_Color_Create(120, 120, 120, wake_alpha));
		CP_Settings_TextSize(100.0f);
		CP_Font_DrawText("Wake up...", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f));


		CP_Settings_Fill(CP_Color_Create(120, 120, 120, wake_alpha));
		CP_Settings_TextSize(65.0f);
		CP_Font_DrawText("Press", 600, 725);

		CP_Color StartOutline = CP_Color_Create(150, 150, 150, wake_alpha);
		CP_Settings_Stroke(StartOutline);
		CP_Settings_Fill(CP_Color_Create(25, 25, 25, wake_alpha));
		//space
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRectAdvanced(1010, 700, 500.0f, 70.0f, 0, 10.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, wake_alpha * 0.7));
		CP_Graphics_DrawRectAdvanced(1010, 710, 150.0f, 5.0f, 0, 0.0f);


		if (wake_alpha < 20)
		{
			tutorial_state = 1;
			wake_loop = 2;

		}
	}
}

void rmb_tut(void)
{
	if (rmb_loop == 0)
	{
		rmb_timer += CP_System_GetDt();
		rmb_alpha = EaseInQuad(rmb_min_alpha, rmb_max_alpha, rmb_timer / rmb_duration);

		//TUTORIAL MESSAGE
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, rmb_alpha));
		CP_Settings_TextSize(100.0f);
		CP_Font_DrawText("RMB", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f));


		CP_Settings_Fill(CP_Color_Create(120, 120, 120, rmb_alpha));
		CP_Settings_TextSize(65.0f);
		CP_Font_DrawText("Press", 600, 725);

		CP_Color StartOutline = CP_Color_Create(150, 150, 150, rmb_alpha);
		CP_Settings_Stroke(StartOutline);
		CP_Settings_Fill(CP_Color_Create(25, 25, 25, rmb_alpha));
		//space
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRectAdvanced(1010, 700, 500.0f, 70.0f, 0, 10.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, rmb_alpha * 0.7));
		CP_Graphics_DrawRectAdvanced(1010, 710, 150.0f, 5.0f, 0, 0.0f);



		if (CP_Input_MouseTriggered(MOUSE_BUTTON_RIGHT))
		{
			CP_Color color = CP_Color_Create(255, 255, 255, 255);

			for (int i = 0; i < 36; i++) {
				CP_Vector v = AngleToVector(i * 10);
				CreateRay(player1.x - WorldX, player1.y - WorldY, 50, v.x, v.y, 2, color, false, 100);


			}
			CP_Sound_PlayAdvanced(creepyping, volume, 1, FALSE, 0);
			rmb_alpha = wake_alpha;
			rmb_timer = 0;
			rmb_loop = 1;

		}
	}
	if (rmb_loop == 1)
	{
		rmb_timer += CP_System_GetDt();
		rmb_alpha = EaseOutQuad(rmb_max_alpha, rmb_min_alpha, rmb_timer / rmb_duration);

		CP_Settings_Fill(CP_Color_Create(120, 120, 120, rmb_alpha));
		CP_Settings_TextSize(100.0f);
		CP_Font_DrawText("RMB", (CP_System_GetWindowWidth() / 2.0f) - 100, (CP_System_GetWindowHeight() / 2.5f));


		CP_Settings_Fill(CP_Color_Create(120, 120, 120, rmb_alpha));
		CP_Settings_TextSize(65.0f);
		CP_Font_DrawText("Press", 600, 725);

		CP_Color StartOutline = CP_Color_Create(150, 150, 150, rmb_alpha);
		CP_Settings_Stroke(StartOutline);
		CP_Settings_Fill(CP_Color_Create(25, 25, 25, rmb_alpha));
		//space
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRectAdvanced(1010, 700, 500.0f, 70.0f, 0, 10.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, rmb_alpha * 0.7));
		CP_Graphics_DrawRectAdvanced(1010, 710, 150.0f, 5.0f, 0, 0.0f);


		if (rmb_alpha < 20)
		{
			tutorial_state = 2;
		}
	}
}

void tutorial_message(void)
{
	if (tut_loop == 0)
	{
		tut_timer += CP_System_GetDt();
		tutorial_alpha = EaseInQuad(tut_min_alpha, tut_max_alpha, tut_timer / tut_duration);

		//TUTORIAL MESSAGE
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, tutorial_alpha));
		CP_Settings_TextSize(100.0f);
		CP_Font_DrawText("Hey, try moving...", 250.0f, (CP_System_GetWindowHeight() / 2.5f));



		CP_Color StartOutline = CP_Color_Create(150, 150, 150, tutorial_alpha);
		CP_Settings_Stroke(StartOutline);
		CP_Settings_Fill(CP_Color_Create(25, 25, 25, tutorial_alpha));
		//W
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRectAdvanced(810, 700, 70.0f, 70.0f, 0, 10.0f);
		//A
		CP_Graphics_DrawRectAdvanced(730, 780, 70.0f, 70.0f, 0, 10.0f);
		//S
		CP_Graphics_DrawRectAdvanced(810, 780, 70.0f, 70.0f, 0, 10.0f);
		//D
		CP_Graphics_DrawRectAdvanced(890, 780, 70.0f, 70.0f, 0, 10.0f);

		CP_Settings_Fill(CP_Color_Create(120, 120, 120, tutorial_alpha));
		CP_Settings_TextSize(30.0f);
		CP_Font_DrawText("W", 785, 700);
		CP_Font_DrawText("A", 710, 780);
		CP_Font_DrawText("S", 790, 780);
		CP_Font_DrawText("D", 870, 780);


		if (CP_Input_KeyTriggered(KEY_W) || CP_Input_KeyTriggered(KEY_A) || CP_Input_KeyTriggered(KEY_S) || CP_Input_KeyTriggered(KEY_D))
		{
			tutorial_state = 3;
			tutorial_alpha = tutorial_alpha;
			tut_timer = 0;
			tut_loop = 1;

		}
	}
	if (tut_loop == 1)
	{
		tut_timer += CP_System_GetDt();
		tutorial_alpha = EaseOutQuad(tut_max_alpha, tut_min_alpha, tut_timer / tut_duration);


		//TUTORIAL MESSAGE
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, tutorial_alpha));
		CP_Settings_TextSize(100.0f);
		CP_Font_DrawText("Hey, try moving...", 250.0f, (CP_System_GetWindowHeight() / 2.5f));



		CP_Color StartOutline = CP_Color_Create(150, 150, 150, tutorial_alpha);
		CP_Settings_Stroke(StartOutline);
		CP_Settings_Fill(CP_Color_Create(25, 25, 25, tutorial_alpha));
		//W
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRectAdvanced(810, 700, 70.0f, 70.0f, 0, 10.0f);
		//A
		CP_Graphics_DrawRectAdvanced(730, 780, 70.0f, 70.0f, 0, 10.0f);
		//S
		CP_Graphics_DrawRectAdvanced(810, 780, 70.0f, 70.0f, 0, 10.0f);
		//D
		CP_Graphics_DrawRectAdvanced(890, 780, 70.0f, 70.0f, 0, 10.0f);

		CP_Settings_Fill(CP_Color_Create(120, 120, 120, tutorial_alpha));
		CP_Settings_TextSize(30.0f);
		CP_Font_DrawText("W", 785, 700);
		CP_Font_DrawText("A", 710, 780);
		CP_Font_DrawText("S", 790, 780);
		CP_Font_DrawText("D", 870, 780);


		if (tutorial_alpha < 10)
		{
			tut_loop = 2;
		}
	}
	if (tut_loop == 2)
	{
		//title_screen();
	}
}

void dodge()
{
	float x1 = -WorldX + CP_System_GetWindowWidth() / 2;
	float y1 = -WorldY + CP_System_GetWindowHeight() / 2;

	if (CheckPointTrigger(700, -300, 10, 1000, x1, y1) == 1)
	{
		dodge_loop = 1;
	}

	if (dodge_loop == 1)
	{
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, tutorial_alpha));
		CP_Settings_TextSize(100.0f);
		CP_Font_DrawText("ENEMY DODGE", 250.0f, (CP_System_GetWindowHeight() / 2.5f));
	}

	if (CheckPointTrigger(1360, -300, 10, 1000, x1, y1) == 1)
	{
		dodge_loop = 2;
	}
	if (dodge_loop == 2)
	{
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, tutorial_alpha));
		CP_Settings_TextSize(100.0f);
		CP_Font_DrawText("CLICK HERE", WorldX+1630,WorldY-500);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawCircle(WorldX+1630, WorldY-505, 25);
		//if LMB clicked update dodge_loop and  tutorialstate.
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
		{
			CP_Color color = CP_Color_Create(255, 255, 0, 150);
			for (int i = 0; i < 20; i++) {
				CP_Vector v = AngleToVector(i * 18);
				CreateRay(1990, -300, 10, v.x, v.y, 1, color, false,100);
			}
			tutorial_state = 4;
		}
	}
}

void title_screen(void)
{
	if (title_loop == 0)
	{
		title_timer += CP_System_GetDt();
		title_alpha = EaseInQuad(title_min_alpha, title_max_alpha, title_timer / title_duration);
		if (title_alpha < 255)
		{
			//TITLE CODE
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, title_alpha));
			CP_Settings_TextSize(200.0f);
			CP_Font_DrawText("project", 640.0f, 350.0f);
			CP_Settings_TextSize(500.0f);
			CP_Font_DrawText("SONAR", 325.0f, 700.0f);
		}

		if (title_alpha > 255)
		{
			title_loop = 1;
			title_alpha = 255;
			title_timer = 0;
		}
	}
	if (title_loop == 1)
	{

		if (title_alpha > 0)
		{
			title_timer += CP_System_GetDt();
			title_alpha = EaseOutQuad(title_max_alpha, title_min_alpha, title_timer / title_duration);
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, title_alpha));
			CP_Settings_TextSize(200.0f);
			CP_Font_DrawText("project", 640.0f, 350.0f);
			CP_Settings_TextSize(500.0f);
			CP_Font_DrawText("SONAR", 325.0f, 700.0f);
		}

		if (title_alpha < 10)
		{
			tut_loop = 4;
			title_loop = 2;

		}

	}
}

void tut_exit(void)
{
	float x1 = -WorldX + CP_System_GetWindowWidth() / 2;
	float y1 = -WorldY + CP_System_GetWindowHeight() / 2;
	//CP_Graphics_DrawRect(WorldX + 1968, WorldY - 316, 50, 50);
	timer++;
	if (timer == 100) //Ping every 15 frames
	{
		CP_Color color = CP_Color_Create(255, 255, 0, 150);
		for (int i = 0; i < 20; i++) {
			CP_Vector v = AngleToVector(i * 18);
			CreateRay(1990, -320, 10, v.x , v.y, 1, color, false,100);
		}

		timer = 0;

	}
	if (CheckPointTrigger(1975, -500, 500, 750, x1, y1) == 1)
	{
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, 50));
		CP_Settings_TextSize(65.0f);
		CP_Font_DrawText("Press", 600, 725);

		CP_Color StartOutline = CP_Color_Create(150, 150, 150, 50);
		CP_Settings_Stroke(StartOutline);
		CP_Settings_Fill(CP_Color_Create(25, 25, 25, 50));
		//space
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRectAdvanced(1010, 700, 500.0f, 70.0f, 0, 10.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 20));
		CP_Graphics_DrawRectAdvanced(1010, 710, 150.0f, 5.0f, 0, 0.0f);
	}

	if (CheckPointTrigger(1990,-500, 500, 750, x1, y1) == 1 && CP_Input_KeyTriggered(KEY_SPACE))
	{
		
		CP_Color color = CP_Color_Create(255, 255, 0, 100);
		for (int i = 0; i < 10; i++) {
			CP_Vector v = AngleToVector(i * 36);
			CreateRay(123, 2230, 100, v.x, v.y, 1, color, false, 100);
		}
		for (int i = 0; i < 20; i++) {
			CP_Vector v = AngleToVector(i * 18);
			CreateRay(500, 2230, 200, v.x, v.y, 1, color, false, 75);
		}
		for (int i = 0; i < 30; i++) {
			CP_Vector v = AngleToVector(i * 12);
			CreateRay(1000, 2230, 300, v.x, v.y, 1, color, false, 25);
		}
		WorldX = 800;
		WorldY = -1700;
		tutorial_state = 5;
	}
}

void enemy_tutorial(void)
{
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(100.0f);
	CP_Font_DrawText("look, there's an enemy nearby.", 640.0f, 350.0f);

}