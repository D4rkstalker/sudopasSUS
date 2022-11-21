#include <cprocessing.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "game.h"
#include "SoundCast.h"
#include "Utils.h"
#include "subcontroller.h"
#include "music.h"

/*
Credits done by Nigel and Ming Rui
*/

//CreditsY for scrolling
int CreditsY = 0;

//CreditsH used for easier spacing of credits elements
float CreditsH = 0;

//energy for credits ping
int credits_energy = 30;

void credits_ping(void) {
	if ((CP_Input_MouseTriggered(MOUSE_BUTTON_1) || CP_Input_MouseTriggered(MOUSE_BUTTON_2)) && credits_energy >= 30) {
		CP_Color color = CP_Color_Create(rand()%255, rand()%255, rand()%255, 220);

		for (int i = 0; i < 36; i++) {
			CP_Vector v = AngleToVector(i * 10);
			CreateRay(CP_Input_GetMouseX(), CP_Input_GetMouseY() - CreditsY, 50, v.x, v.y, 2, color, false, 130, true);


		}
		CP_Sound_PlayAdvanced(ping, volume, 1, FALSE, 0);
		credits_energy = 0;
	}

	if (credits_energy >= 120) {
		CP_Color color = CP_Color_Create(rand() % 255, rand() % 255, rand() % 255, 220);

		for (int i = 0; i < 36; i++) {
			CP_Vector v = AngleToVector(i * 10);
			CreateRay(CP_Input_GetMouseX(), CP_Input_GetMouseY() - CreditsY, 50, v.x, v.y, 2, color, false, 130, true);


		}
		CP_Sound_PlayAdvanced(ping, volume, 1, FALSE, 0);
		credits_energy = 0;
	}
}

void credits_scroll(void) {
	if (CP_Input_KeyDown(KEY_UP)) {
		CreditsY += 5;
	}
	if (CP_Input_KeyDown(KEY_DOWN)) {
		CreditsY -= 5;
	}
}

/*
draw_credits draws text for the credits
str is the string to input
size is the size of the text
dist is the distance to the next credit element after this
*/
void draw_credits(const char* str, float size, float dist) {
	CP_Settings_TextSize(size);
	CP_Font_DrawText(str, CP_System_GetWindowWidth() / 2, 350.0f + CreditsY + CreditsH);
	CreditsH += dist;
}

void credits_init(void) {
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	srand(time(NULL));
	Sound_Init();
	CP_Sound_Free(&creepyping);
	CP_Sound_PlayAdvanced(introsound, volume, 1.0, FALSE, 0);

	CP_System_SetWindowSize(1920, 1080);
}

void credits_update(void) {

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CreditsH = 0;

	credits_scroll();
	credits_ping();
	RayUpdate(0, CreditsY);

	if (credits_energy < 120) {
		credits_energy += 2;
	}

	//Draw the credits
	CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255));
	draw_credits("GAME CLEAR!", 300, 700);

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	draw_credits("project", 200, 350);
	draw_credits("SONAR",  500, 700);

	draw_credits("Team Members", 150, 200);
	draw_credits("HQ", 100, 100);
	draw_credits("Nigel", 100, 100);
	draw_credits("KC", 100, 100);
	draw_credits("MR", 100, 100);
	draw_credits("Johnathan", 100, 100);

	/*
	TO ADD:
	Buttons to restart or exit game
	*/

}

void credits_exit(void) {
	Sound_Deload();
}
