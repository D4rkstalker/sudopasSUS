#include "cprocessing.h"
#pragma once
#include "menu.h"
#include "subcontroller.h"


float tutorial_alpha = 0;
float tut_timer = 0.f;
float tut_duration = 3.f;
float tut_min_alpha = 0;
float tut_max_alpha = 255;
int tut_loop = 0;

float title_alpha = 0;
float title_timer = 0.f;
float title_duration = 5.f;
float title_min_alpha = 0;
float title_max_alpha = 255;
int title_loop = 0;


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
				CP_Settings_Fill(CP_Color_Create(120, 120, 120, tutorial_alpha));
				CP_Settings_TextSize(100.0f);
				CP_Font_DrawText("get fucked", 250.0f, (CP_System_GetWindowHeight() / 2.5f));
				tut_loop = 2;
			}
		}
	if (tut_loop == 2)
	{
		title_screen();
	}
}
		//if (//check if player passes X)
		//{

		//}


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

void enemy_tutorial(void)
{
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(100.0f);
	CP_Font_DrawText("look, there's an enemy nearby.", 640.0f, 350.0f);

}