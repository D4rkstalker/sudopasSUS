#include <cprocessing.h>
#include <stdio.h>
#include "game.h"
#include "NewTutorial.h"

/*
Splashscreen done by Nigel
*/

CP_Image logo;
int logoalpha = 255;
int titlealpha = 1;
int titledirection = 4;
int splashstate = 0;

void splashscreen_init(void) {
	logo = CP_Image_Load("../Assets/DigiPen_Singapore_WEB_WHITE.png");
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	CP_System_SetWindowSize(1920, 1080);
}

void splashscreen_update(void) {

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	if (splashstate == 0) {
		CP_Image_Draw(logo, CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2, 1525, 445, logoalpha);

		logoalpha -= 4;
		if (logoalpha <= 0) {
			splashstate = 1;
		}
	}
	else {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, titlealpha));
		CP_Settings_TextSize(200.0f);
		CP_Font_DrawText("Project", 640.0f, 350.0f);
		CP_Settings_TextSize(500.0f);
		CP_Font_DrawText("SONAR", 325.0f, 700.0f);

		titlealpha += titledirection;

		if (titlealpha >= 255) {
			titledirection = -titledirection;
		}

		if (titlealpha <= 0) {
			CP_Engine_SetNextGameState(newtutorial_init, newtutorial_update, newtutorial_exit);
		}
	}

	if (CP_Input_KeyTriggered(KEY_ANY)) {
		splashstate += 1;
	}

	if (splashstate >= 2) {
		CP_Engine_SetNextGameState(newtutorial_init, newtutorial_update, newtutorial_exit);
	}

}

void splashscreen_exit(void) {
	CP_Image_Free(logo);
}
