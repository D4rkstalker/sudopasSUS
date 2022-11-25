/*
All content © 2021 DigiPen Institute of Technology Singapore, all rights reserved.


Main menu made by Nigel
*/

#include "cprocessing.h"
#include "game.h"
#include "credits.h"
#include "music.h"
#include "NewTutorial.h"

void menu_button(int button, int* buttonalpha, float y) {
	if (CP_Input_GetMouseWorldX() >= CP_System_GetWindowWidth() / 2 - y && CP_Input_GetMouseWorldX() <= CP_System_GetWindowWidth() / 2 + 350 && CP_Input_GetMouseWorldY() >= y - 50 && CP_Input_GetMouseWorldY() <= y + 50) {
		*buttonalpha = 50;
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
			CP_Sound_PlayAdvanced(ping, volume, 2, FALSE, 0);
			if (button == 0) {
				CP_Engine_SetNextGameStateForced(newtutorial_init, newtutorial_update, newtutorial_exit);
			}
			else if (button == 1) {
				CP_Engine_Terminate();
			}
			else if (button == 2) { 
				CP_Engine_SetNextGameStateForced(credits_init, credits_update, credits_exit);
			}
		}
	}
	else {
		*buttonalpha = 0;
	}
}

void draw_button(char* str, int button, float y) {
	int buttonalpha = 0;

	CP_Settings_Stroke(CP_Color_Create(220, 220, 220, 255));
	CP_Settings_RectMode(CP_POSITION_CENTER);
	menu_button(button, &buttonalpha, y);
	CP_Settings_Fill(CP_Color_Create(220, 220, 220, buttonalpha));
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2.f, y, 700, 100);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(100);
	CP_Font_DrawText(str, CP_System_GetWindowWidth() / 2.f, y);
}

void mainmenu_init(void) {
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	Sound_Init();
}

void mainmenu_update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(200);
	CP_Font_DrawText("Project SONAR", CP_System_GetWindowWidth() / 2.f, 200);

	draw_button("Start Game", 0, 400);
	draw_button("Credits", 2, 600);
	draw_button("Exit Game", 1, 800);

}

void mainmenu_exit(void) {

}