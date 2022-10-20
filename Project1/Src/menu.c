#include "cprocessing.h"
#include "menu.h"

double title_alpha = 0;
double tutorial_alpha = 0;
int loop = 0;


void mainmenu_init(void) {

	CP_System_SetWindowSize(1920, 1080);

}

void mainmenu_update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(25, 25, 25, 255));

	int title_alpha_speed = 5;


	if (title_alpha < 255 && loop == 0) {
		title_alpha +=1*title_alpha_speed;
	}
	if (title_alpha >= 255) {
		loop = 1;
	}
	if (title_alpha > 0 && loop == 1) {
		title_alpha -= 2*title_alpha_speed;
	}
	if (title_alpha < 0 && loop == 1) {
		loop = 2;
	}

	if (loop == 2 || loop == 3) {

		int tutorial_alpha_speed = 3;

		if (tutorial_alpha < 255 && loop == 2) {
			tutorial_alpha += 1 * tutorial_alpha_speed;
		}
		if (tutorial_alpha >= 155) {
			loop = 3;
		}

		CP_Settings_Fill(CP_Color_Create(120, 120, 120, tutorial_alpha));
		CP_Settings_TextSize(100.0f);
		CP_Font_DrawText("Hey, try moving...", 250.0f, (CP_System_GetWindowHeight() / 2.5f));



		CP_Color StartOutline = CP_Color_Create(tutorial_alpha, tutorial_alpha, tutorial_alpha, tutorial_alpha);
		CP_Settings_Stroke(StartOutline);
		CP_Settings_Fill(CP_Color_Create(25, 25, 25, tutorial_alpha));
		//W
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRectAdvanced(810, 700, 70.0f, 70.0f,0, 10.0f);
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
	}

	//TITLE CODE
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, title_alpha));
	CP_Settings_TextSize(100.0f);
	CP_Font_DrawText("project", 250.0f, 400.0f);
	CP_Settings_TextSize(250.0f);
	CP_Font_DrawText("SONAR", 250.0f, 600.0f);

	/*CP_Color StartOutline = CP_Color_Create(255, 255, 255, 255);
	CP_Settings_Fill(StartOutline);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Graphics_DrawRect((CP_System_GetWindowWidth() / 2.0f), (CP_System_GetWindowHeight() / 2.5f) + 200.0f, 500.0f, 150.0f);

	CP_Color StartFill = CP_Color_Create(25, 25, 25, 255);
	CP_Settings_Fill(StartFill);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Graphics_DrawRect((CP_System_GetWindowWidth() / 2.0f), (CP_System_GetWindowHeight() / 2.5f) + 200.0f, 490.0f,140.0f);

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(100.0f);
	CP_Font_DrawText("Game Start", (CP_System_GetWindowHeight() / 2.0f)+ 210.0f, (CP_System_GetWindowHeight() / 2.5f) + 200.0f + 27.0f);
	*/

	if (CP_Input_KeyDown(KEY_E))
	{
		title_alpha = 0;
		tutorial_alpha = 0;
		loop = 0;
		CP_Engine_SetNextGameState(game_init, game_update, game_exit);
		//CP_Engine_Terminate();
	}

}

void mainmenu_exit(void) {



}