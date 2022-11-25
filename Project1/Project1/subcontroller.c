#include <stdio.h>
#include "cprocessing.h"
#include "subcontroller.h"
#include "game.h"
#include "Utils.h"
#include "music.h"
#include "walls.h"
#include "checkpoint.h"
#include "SoundCast.h"
#include <math.h>
#include "enemy.h"
#include "NewTutorial.h"
#include "menu.h"


#define MAXSPEED 40
#define TutSpeed 2

CP_Vector mouseMovement;
int settings_alpha_1 = 0;
int settings_alpha_2 = 0;
int settings_alpha_3 = 0;
int settings_alpha_4 = 0;
int settings_alpha_5 = 0;

int time = 0;

void tutorialMovement(int isplayer) {
	if (CP_Input_KeyDown(KEY_W)) {
		player.y -= TutSpeed;
	}
	if (CP_Input_KeyDown(KEY_S)) {
		player.y += TutSpeed;
	}
	if (CP_Input_KeyDown(KEY_D)) {
		player.x += TutSpeed;
	}
	if (CP_Input_KeyDown(KEY_A)) {
		player.x -= TutSpeed;
	}

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {

			float x = CP_System_GetWindowWidth() / 2;
			float y = CP_System_GetWindowHeight() / 2;

			CP_Color color = CP_Color_Create(255, 255, 255, 220);
			CP_Vector outv = CP_Vector_Normalize(CP_Vector_Subtract(CP_Vector_Set(CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY), CP_Vector_Set(x - WorldX, y - WorldY)));
			float a = CP_Math_Degrees(atan2(outv.y, outv.x));
			for (int i = -18; i < 18; i++) {
				CP_Vector v = AngleToVector(a + i * 1);
				CreateRay(player.x, player.y, 50, v.x, v.y, 4, color, true, 200, isplayer);

			}




			CP_Sound_PlayAdvanced(ping, volume, 1, FALSE, 0);
			//CP_Sound_StopGroup(CP_SOUND_GROUP_MUSIC);
			//CP_Sound_PlayMusic((bgm_submarine));


	


	}
	else if (CP_Input_MouseTriggered(MOUSE_BUTTON_2)) {
		CP_Color color = CP_Color_Create(255, 255, 255, 220);
		for (int i = 0; i < 36; i++) {
			CP_Vector v = AngleToVector(i * 10);
			CreateRay(player.x, player.y, 50, v.x, v.y, 4, color, false, 130, isplayer);

		}
		CP_Sound_PlayAdvanced(ping, volume, 1, FALSE, 0);

		player.y -= 1;
	}
	if (CP_Input_KeyDown(KEY_S)) {
		player.y += 1;
	}
	if (CP_Input_KeyDown(KEY_D)) {
		player.x += 1;
	}
	if (CP_Input_KeyDown(KEY_A)) {
		player.x -= 1;

	}

}

void checkMouse(CP_Vector volumeMin, CP_Vector volumeMax) {
	CP_Vector distvect = CP_Vector_Subtract(volumeMax, volumeMin);
	CP_Vector dirvect = CP_Vector_Normalize(distvect);

	mouseMovement.x = (volumeMin.x + volume * distvect.x);
	mouseMovement.y = volumeMin.y;


	if ((CP_Input_MouseDown(MOUSE_BUTTON_LEFT))) {
		float mouseX = CP_Input_GetMouseX();
		float mouseY = CP_Input_GetMouseY();

		if (mouseX >= volumeMin.x && mouseX <= volumeMax.x) {
			if (mouseY >= volumeMin.y - 5 && mouseY <= volumeMin.y + 5) {

				mouseMovement = CP_Vector_Set(mouseX, volumeMin.y);
				volume = (mouseMovement.x - volumeMin.x) / distvect.x;

			}
		}




	}
	CP_Graphics_DrawCircle(mouseMovement.x, mouseMovement.y, 25);
}

void settings_menu(void) {
	CP_Settings_Fill(CP_Color_Create(220, 220, 220, 255));
	CP_Settings_TextSize(150.0f);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, 0);
	CP_Font_DrawText("Pause Menu", CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 - 200);

	CP_Settings_TextSize(40.0f);
	CP_Settings_Fill(CP_Color_Create(220, 220, 220, 255));
	CP_Font_DrawText("Resume Game", CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 - 100);
	//CP_Font_DrawText("Retry from Last Check Point", CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 );
	CP_Font_DrawText("Retry from Last Check Point", CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 + 100);
	CP_Font_DrawText("Retry Game", CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 + 200);
	CP_Font_DrawText("Return to Menu", CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 + 300);

	CP_Settings_Stroke(CP_Color_Create(220, 220, 220, 255));
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_Fill(CP_Color_Create(220, 220, 220, settings_alpha_1));
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 - 110, 500, 50);
	CP_Settings_Fill(CP_Color_Create(220, 220, 220, settings_alpha_2));
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 - 10, 500, 50);
	CP_Settings_Fill(CP_Color_Create(220, 220, 220, settings_alpha_3));
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 + 90, 500, 50);
	CP_Settings_Fill(CP_Color_Create(220, 220, 220, settings_alpha_4));
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 + 190, 500, 50);
	CP_Settings_Fill(CP_Color_Create(220, 220, 220, settings_alpha_5));
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 + 290, 500, 50);


	if (CP_Input_GetMouseWorldX() >= CP_System_GetWindowWidth() / 2 - 250 && CP_Input_GetMouseWorldX() <= CP_System_GetWindowWidth() / 2 + 250 && CP_Input_GetMouseWorldY() >= CP_System_GetWindowHeight() / 2 - 145 && CP_Input_GetMouseWorldY() <= CP_System_GetWindowHeight() / 2 - 85) {
		settings_alpha_1 = 50;
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
			game_states = resume;
		}
	}
	else {
		settings_alpha_1 = 0;
	}
	//Check for retry game
	if (CP_Input_GetMouseWorldX() >= CP_System_GetWindowWidth() / 2 - 250 && CP_Input_GetMouseWorldX() <= CP_System_GetWindowWidth() / 2 + 250 && CP_Input_GetMouseWorldY() >= CP_System_GetWindowHeight() / 2 + 65 && CP_Input_GetMouseWorldY() <= CP_System_GetWindowHeight() / 2 + 115) {
		settings_alpha_3 = 50;
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
			retry_game(checkpoint[0].current_checkpoint);

			return 0;
		}
	}
	else {
		settings_alpha_3 = 0;
	}

	if (CP_Input_GetMouseWorldX() >= CP_System_GetWindowWidth() / 2 - 250 && CP_Input_GetMouseWorldX() <= CP_System_GetWindowWidth() / 2 + 250 && CP_Input_GetMouseWorldY() >= CP_System_GetWindowHeight() / 2 + 165 && CP_Input_GetMouseWorldY() <= CP_System_GetWindowHeight() / 2 + 215) {
		settings_alpha_4 = 50;
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) { // Menu on retry game
			if (checkpoint[0].current_checkpoint != 1) {
				retry_game(checkpoint[0].current_checkpoint = 2);
				checkpoint_init();
				checkpoint_reset();
				checkpoint[0].current_checkpoint = 2;
				draw_checkpoint();
				enemy_place();



			}
			else if (checkpoint[0].current_checkpoint == 1) {
				retry_game(checkpoint[0].current_checkpoint = 1);
				checkpoint_init();
				checkpoint_reset();

				checkpoint[0].current_checkpoint = 1;
				draw_checkpoint();
				enemy_place();


			}
			return 0;
		}
	}
	else {
		settings_alpha_4 = 0;
	}
	if (CP_Input_GetMouseWorldX() >= CP_System_GetWindowWidth() / 2 - 250 && CP_Input_GetMouseWorldX() <= CP_System_GetWindowWidth() / 2 + 250 && CP_Input_GetMouseWorldY() >= CP_System_GetWindowHeight() / 2 + 265 && CP_Input_GetMouseWorldY() <= CP_System_GetWindowHeight() / 2 + 315) {
		settings_alpha_5 = 50;
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
			CP_Engine_SetNextGameState(mainmenu_init, mainmenu_update, mainmenu_exit);
			return 0;
		}
	}
	else {
		settings_alpha_5 = 0;
	}


}

void volumeControl(void) {
	CP_Settings_Fill(CP_Color_Create(50, 50, 50, 0));
	CP_Settings_RectMode(CP_POSITION_CORNER);
	float screenborderX = CP_System_GetWindowWidth() / 4;
	float screenborderY = CP_System_GetWindowHeight() / 4;
	float screensizeX = CP_System_GetWindowWidth() / 2;
	float screensizeY = CP_System_GetWindowHeight() / 2;

	CP_Vector volumeMin = CP_Vector_Set(screenborderX + screensizeX / 4, (screenborderY + screensizeY / 2) - 10);

	CP_Vector volumeMax = CP_Vector_Set(screenborderX + screensizeX - (screensizeX / 4), (screenborderY + (screensizeY / 2) - 10)); //screensizeY - 

	CP_Graphics_DrawRect(screenborderX, screenborderY, screensizeX, screensizeY); // Drawing border

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawLine(volumeMin.x, volumeMin.y, volumeMax.x, volumeMax.y);
	checkMouse(volumeMin, volumeMax);
}

void mapScale() { // Mini Map Scaling

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));


	for (int i = 0; i < CWall + 1; i++) {
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawLine((wall[i].pos1.x / 9) + 550, (wall[i].pos1.y / 9) + 300, (wall[i].pos2.x / 9) + 550, (wall[i].pos2.y / 9) + 300);

	}




}

void controlskeys(void) {
	if (CP_Input_KeyTriggered(KEY_BACKSPACE)) { // Sample of a Pause phase
		game_states = game_states != paused ? paused : resume;
	}
	if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
		game_states = game_states != theMenu ? theMenu : resume;
	}
	if (CP_Input_KeyTriggered(KEY_M)) {
		game_states = game_states != theMap ? theMap : resume;
	}
	/* Obsolete, to be removed
	if (CP_Input_KeyTriggered(KEY_T)) {
		CP_Sound_PlayAdvanced(ping, volume, 1.0f, FALSE, CP_SOUND_GROUP_0);
	}
	*/
}



void movement(void) {
	controlskeys();


	if (game_states == resume) {

		if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
			if (energy > 40) {
				float x = CP_System_GetWindowWidth() / 2;
				float y = CP_System_GetWindowHeight() / 2;

				CP_Color color = CP_Color_Create(255, 255, 255, 220);
				CP_Vector outv = CP_Vector_Normalize(CP_Vector_Subtract(CP_Vector_Set(CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY), CP_Vector_Set(x - WorldX, y - WorldY)));
				float a = CP_Math_Degrees(atan2(outv.y, outv.x));
				for (int i = -18; i < 18; i++) {
					CP_Vector v = AngleToVector(a + i * 1);
					CreateRay(player1.x - WorldX, player1.y - WorldY, 25, v.x, v.y, 2, color, true, 200, true);

				}



				energy -= 40;
				CP_Sound_PlayAdvanced(ping, volume, 1, FALSE, 0);
				//CP_Sound_StopGroup(CP_SOUND_GROUP_MUSIC);
				//CP_Sound_PlayMusic((bgm_submarine));


			}


		}
		else if (CP_Input_MouseTriggered(MOUSE_BUTTON_2) && energy > 60) {
			CP_Color color = CP_Color_Create(255, 255, 255, 220);

			for (int i = 0; i < 36; i++) {
				CP_Vector v = AngleToVector(i * 10);
				CreateRay(player1.x - WorldX, player1.y - WorldY, 50, v.x, v.y, 2, color, false, 130, true);


			}
			CP_Sound_PlayAdvanced(ping, volume, 1, FALSE, 0);
			energy -= 60;

		}

		if (CP_Input_KeyDown(KEY_W) && CP_Input_KeyDown(KEY_S)) {
			player1.acceleration_y = 0;

		}
		else {
			if (CP_Input_KeyDown(KEY_W)) {
				player1.acceleration_y += (MAXSPEED - player1.acceleration_y) / MAXSPEED;
				player1.velocity_y -= player1.acceleration_y * 0.1;
				time++;

			}
			else if (CP_Input_KeyReleased(KEY_W)) {

				player1.acceleration_y = 0;

			}

			if (CP_Input_KeyDown(KEY_S)) {

				player1.acceleration_y += (MAXSPEED - player1.acceleration_y) / MAXSPEED;
				player1.velocity_y += player1.acceleration_y * 0.1;
				time++;
			}
			else if (CP_Input_KeyReleased(KEY_S)) {

				player1.acceleration_y = 0;

			}
		}

		if (CP_Input_KeyDown(KEY_D) && CP_Input_KeyDown(KEY_A)) {
			player1.acceleration_x = 0;
		}
		else {
			if (CP_Input_KeyDown(KEY_D)) {
				player1.acceleration_x += (MAXSPEED - player1.acceleration_x) / MAXSPEED;
				player1.velocity_x += player1.acceleration_x * 0.1;
				time++;
			}
			else if (CP_Input_KeyReleased(KEY_D)) {

				player1.acceleration_x = 0;


			}
			if (CP_Input_KeyDown(KEY_A)) {
				player1.acceleration_x += (MAXSPEED - player1.acceleration_x) / MAXSPEED;
				player1.velocity_x -= player1.acceleration_x * 0.1;
				time++;
			}
			else if (CP_Input_KeyReleased(KEY_A)) {

				player1.acceleration_x = 0;

			}
		}
		if (debug == 0 || CP_Input_KeyDown(KEY_9)) {
			if (wallcollision()) {
				if (CP_Math_Distance(0, 0, player1.velocity_x, player1.velocity_y) > 2) {
					CP_Sound_PlayAdvanced(bonk, volume, 1, FALSE, 0);

					CP_Color color = CP_Color_Create(255, 255, 255, 150);

					for (int i = 0; i < 18; i++) {
						CP_Vector v = AngleToVector(i * 20);
						CreateRay(player1.x - WorldX, player1.y - WorldY, 30, v.x, v.y, 2, color, false, 150, true);
					}
				}
				return;
			}
		}
		WorldX -= player1.velocity_x;
		WorldY -= player1.velocity_y;
		player1.velocity_y *= 0.9;
		player1.velocity_x *= 0.9;

		time++;
		if (time > 25) {
			CP_Color color = CP_Color_Create(255, 255, 255, 150);

			for (int i = 0; i < 18; i++) {
				CP_Vector v = AngleToVector(i * 20);
				CreateRay(player1.x - WorldX, player1.y - WorldY, 20, v.x, v.y, 4, color, false, 50, true);
			}
			time = 0;
		}

	}
	game_states == theMenu ? volumeControl(), settings_menu() : 0;
	game_states == theMap ?
		CP_Settings_Fill(CP_Color_Create(188, 158, 130, 255)),
		CP_Settings_RectMode(CP_POSITION_CORNER), // Line below draws a border
		CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 4, CP_System_GetWindowHeight() / 4, (CP_System_GetWindowWidth() + 50) / 2, (CP_System_GetWindowHeight() + 50) / 2),
		mapScale() : 0;
}



void controller_init(void) {
	Sound_Init();
	volume = 0.1;
}


