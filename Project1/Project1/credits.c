/*
All content © 2021 DigiPen Institute of Technology Singapore, all rights reserved.


Credits ping, scrolling, draw system and buttons made by Nigel
Credits scene made by Ming Rui
*/

#include <cprocessing.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "game.h"
#include "SoundCast.h"
#include "Utils.h"
#include "subcontroller.h"
#include "music.h"
#include "checkpoint.h"
#include "menu.h"

//CreditsY for scrolling
int CreditsY = 0;

//CreditsH used for easier spacing of credits elements
float CreditsH = 0;

//Bottom of the credits
float CreditsBottom = 0;

//energy for credits ping
int credits_energy = 30;

//alpha for buttons
int restartbuttonalpha = 0;
int exitbuttonalpha = 0;

void credits_ping(void) {
	if ((CP_Input_MouseTriggered(MOUSE_BUTTON_1) || CP_Input_MouseTriggered(MOUSE_BUTTON_2)) && credits_energy >= 30) {
		CP_Color color = CP_Color_Create(rand() % 255, rand() % 255, rand() % 255, 220);

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
		CP_Sound_PlayAdvanced(ping, volume, 2, FALSE, 0);
		credits_energy = 0;
	}
}

void credits_scroll(void) {

	if (-CreditsY < CreditsBottom) { // Auto scroll, remove if unwanted
		CreditsY -= 10;
	}

	if (CP_Input_KeyDown(KEY_ESCAPE)) {
		CreditsY = -CreditsBottom;
	}

	if ((CP_Input_KeyDown(KEY_UP) || CP_Input_KeyDown(KEY_W))) {
		if (CreditsY < 0) {
			CreditsY += 10;
		}
		if (CreditsY < 0) {
			CreditsY += 10;
		}
	}
	else if ((CP_Input_KeyDown(KEY_DOWN) || CP_Input_KeyDown(KEY_S)) && -CreditsY < CreditsBottom) {
		CreditsY -= 10;
	}

}

void credits_button(int button, int* buttonalpha) {
	if (CP_Input_GetMouseWorldX() >= CP_System_GetWindowWidth() / 2 - 450 && CP_Input_GetMouseWorldX() <= CP_System_GetWindowWidth() / 2 + 450 && CP_Input_GetMouseWorldY() >= 350.0f + CreditsY + CreditsH - 50 && CP_Input_GetMouseWorldY() <= 350.0f + CreditsY + CreditsH + 50) {
		*buttonalpha = 50;
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
			if (button == 0) {
				CP_Engine_SetNextGameStateForced(mainmenu_init, mainmenu_update, mainmenu_exit);
			}
			else {
				CP_Engine_Terminate();
			}
		}
	}
	else {
		*buttonalpha = 0;
	}
}

/*
draw_credits draws text for the credits
str is the string to input
size is the size of the text
dist is the distance to the next credit element after this
*/
void draw_credits(const char* str, float size, float dist) {
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(size);
	CP_Font_DrawText(str, CP_System_GetWindowWidth() / 2, 350.0f + CreditsY + CreditsH);
	CreditsH += dist;
}
void draw_copyrightSymbol(float size, float dist) {
	
	CP_Settings_TextSize(size);
	CP_Settings_NoFill();
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawCircle((CP_System_GetWindowWidth() / 2) + 200, 350.0f + CreditsY + CreditsH - 95, 65);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("C", (CP_System_GetWindowWidth() / 2) + 200, 350.0f + CreditsY + CreditsH - 100);
	CreditsH += dist;
}


void credits_init(void) {
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	CreditsY = 0;

	srand(time(NULL));
	Sound_Init();
	CP_Sound_Free(&creepyping);
	CP_Sound_PlayAdvanced(introsound, volume, 1.0, FALSE, 0);

	CP_System_SetWindowSize(1920, 1080);
}

void credit_scene(void) {
	//Draw the credits
	if (CheckPoint_3_Triggered == 1) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255));
		CP_Settings_TextSize(300);
		CP_Font_DrawText("GAME CLEAR!", CP_System_GetWindowWidth() / 2, 350.0f + CreditsY + CreditsH);
		CreditsH += 700;
	}

	draw_credits("Project", 200, 350);
	draw_credits("SONAR", 500, 700);

	draw_credits("WWW.DIGIPEN.EDU", 75, 100);
	draw_credits("All Content ", 75, 100);
	draw_copyrightSymbol(75, 0);
	draw_credits("2022 DigiPen Institute of Technology Singapore.", 75, 100);
	draw_credits("All Rights Reserved", 75, 300);

	draw_credits("Team Members", 125, 150);
	draw_credits("LIU HAN QING", 50, 100);
	draw_credits("NIGEL FOONG", 50, 100);
	draw_credits("TAN KIAN CHEW", 50, 100);
	draw_credits("LIONG MING RUI", 50, 100);
	draw_credits("JONATHAN HO", 50, 200);


	// Faculty & Advisors
	draw_credits("Instructors", 125, 150);
	draw_credits("CHENG DING XIANG", 50, 100);
	draw_credits("GERALD WONG", 50, 200);
	//draw_credits("Special Thanks", 150, 200);
	//draw_credits("Gerald", 100, 100);
	//draw_credits("Ding Xiang", 100, 100);
	//draw_credits("Playtesters", 100, 400);


	// Place of Creation
	draw_credits("Created at", 100, 100);
	draw_credits("DigiPen Institute of Technology Singapore", 100, 250);

	// President
	draw_credits("President", 125, 150);
	draw_credits("CLAUDE COMAIR", 50, 250);

	// Executives
	draw_credits("Executives", 125, 150);
	draw_credits("JASON CHU", 50, 100);
	draw_credits("CHRISTOPHER COMAIR", 50, 100);
	draw_credits("MICHAEL GATS", 50, 100);

	draw_credits("MICHELE COMAIR", 50, 100);
	draw_credits("RAYMOND YAN", 50, 100);
	draw_credits("SAMIR ABOU SAMRA", 50, 100);

	draw_credits("PRASANNA GHALI", 50, 100);
	draw_credits("JOHN BAUER", 50, 100);
	draw_credits("DR. ERIK MOHRMANN", 50, 100);

	draw_credits("MELVIN GONSALVEZ", 50, 100);
	draw_credits("ANGELA KUGLER", 50, 100);
	draw_credits("Dr. Charles DUBA", 50, 100);

	draw_credits("BEN ELLINGER", 50, 100);
	draw_credits("JOHNNY DEEK", 50, 350);



	
	//©

	draw_credits("Thanks for playing!", 100, 300);

	CP_Settings_Stroke(CP_Color_Create(220, 220, 220, 255));
	CP_Settings_RectMode(CP_POSITION_CENTER);
	credits_button(0, &restartbuttonalpha);
	CP_Settings_Fill(CP_Color_Create(220, 220, 220, restartbuttonalpha));
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2, 350.0f + CreditsY + CreditsH, 900, 100);
	draw_credits("Return to main menu", 100, 200);

	CP_Settings_Stroke(CP_Color_Create(220, 220, 220, 255));
	CP_Settings_RectMode(CP_POSITION_CENTER);
	credits_button(1, &exitbuttonalpha);
	CP_Settings_Fill(CP_Color_Create(220, 220, 220, exitbuttonalpha));
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2, 350.0f + CreditsY + CreditsH, 900, 100);
	draw_credits("Exit Game", 100, 100);


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



	credit_scene(); // Credit draw
	CreditsH -= 500;
	if (CreditsBottom < CreditsH) {
		CreditsBottom = CreditsH;
	}
	//©
	/*
	TO ADD:
	Buttons to restart or exit game
	*/





}

void credits_exit(void) {
	Sound_Deload();
}



