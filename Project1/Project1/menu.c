<<<<<<< Updated upstream
#include "cprocessing.h"
#pragma once
#include "menu.h"
#include "subcontroller.h"


#define TutorialWalls (10)


double title_alpha = -100;
double tutorial_alpha = 0;
int loop = 0;



void mainmenu_init(void) {

	CP_System_SetWindowSize(1920, 1080);

}

void tutorial_message(void)
{

	int tutorial_alpha_speed = 3;


	if (tutorial_alpha < 255 && loop == 0) {
		tutorial_alpha += 1 * tutorial_alpha_speed;
	}
	if (tutorial_alpha >= 255) {
		loop = 1;
	}


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

	//Wait for First Input
	if ((CP_Input_KeyTriggered(KEY_W) || CP_Input_KeyTriggered(KEY_A) || CP_Input_KeyTriggered(KEY_S) || CP_Input_KeyTriggered(KEY_D)) && loop == 1)
	{
		loop = 2;

	}

	//After First Input
	if (loop == 2 || loop == 3) {

		//fade out tutorial message
		if (tutorial_alpha > 0 && loop == 2) {
			tutorial_alpha -= 3 * tutorial_alpha_speed;
		}

		//Fade in TITLE
		int title_alpha_speed = 1;

		if (title_alpha < 255 && loop == 2) {
			title_alpha += 1 * title_alpha_speed;
		}
		if (title_alpha >= 155) {
			loop = 3;

		}
		//Fade Out Title 
		if (title_alpha > 0 && loop == 3) {
			title_alpha -= 3 * tutorial_alpha_speed;
		}

		//TITLE CODE
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, title_alpha));
		CP_Settings_TextSize(200.0f);
		CP_Font_DrawText("project", 640.0f, 350.0f);
		CP_Settings_TextSize(500.0f);
		CP_Font_DrawText("SONAR", 325.0f, 700.0f);

	}

	/*
	//DRAW MAP
	CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 0));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 10));
	CP_Settings_RectMode(CP_POSITION_CORNER);

	map tut[TutorialWalls];

	tut[0].x = 0;
	tut[0].y = 0;
	tut[0].w = 900;
	tut[0].h = 1080;
	CP_Graphics_DrawRect(tut[0].x, tut[0].y, tut[0].w, tut[0].h);

	tut[1].x = 1000;
	tut[1].y = 0;
	tut[1].w = 960;
	tut[1].h = 250;
	CP_Graphics_DrawRect(tut[1].x, tut[1].y, tut[1].w, tut[1].h);

	tut[2].x = 1000;
	tut[2].y = 350;
	tut[2].w = 600;
	tut[2].h = 400;
	CP_Graphics_DrawRect(tut[2].x, tut[2].y, tut[2].w, tut[2].h);

	tut[3].x = 1700;
	tut[3].y = 250;
	tut[3].w = 300;
	tut[3].h = 600;
	CP_Graphics_DrawRect(tut[3].x, tut[3].y, tut[3].w, tut[3].h);

	tut[4].x = 1000;
	tut[4].y = 850;
	tut[4].w = 960;
	tut[4].h = 250;
	CP_Graphics_DrawRect(tut[4].x, tut[4].y, tut[4].w, tut[4].h);
	*/
}

void mainmenu_update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(25, 25, 25, 255));

	



	/*if (CP_Input_KeyTriggered(KEY_Q))
	{
		title_alpha = 0;
		tutorial_alpha = 0;
		loop = 0;
		CP_Engine_SetNextGameState(subgame_init, subgame_update, subgame_exit);
		//CP_Engine_Terminate();
	}
	*/





}

void mainmenu_exit(void) {



}
=======
>>>>>>> Stashed changes
