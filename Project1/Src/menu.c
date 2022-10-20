#include "cprocessing.h"

double title_alpha = 0;
int loop = 0;


void mainmenu_init(void) {

	CP_System_SetWindowSize(1920, 1080);


}

void mainmenu_update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(25, 25, 25, 255));

	//double title_alpha_speed = 10;


	if (title_alpha < 255 && loop == 0) {
		title_alpha +=1;
	}
	if (title_alpha == 255) {
		loop = 1;
	}
	if (title_alpha > 0 && loop == 1) {
		title_alpha -= 1;
	}

	//TITLE CODE
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, title_alpha));
	CP_Settings_TextSize(250.0f);
	CP_Font_DrawText("Project S.O.N.A.", 250.0f, (CP_System_GetWindowHeight() / 2.5f));

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

}

void mainmenu_exit(void) {

}