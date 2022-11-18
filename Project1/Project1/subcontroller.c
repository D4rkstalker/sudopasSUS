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


#define MAXSPEED 4

CP_Vector mouseMovement;
int settings_alpha_1 = 0;
int settings_alpha_2 = 0;
int settings_alpha_3 = 0;
int settings_alpha_4 = 0;

int time = 0;


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
						// (mouseMovement.x - volumeMin.x)/distvect.x = volume * distvect.x				
			
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
	CP_Font_DrawText("Exit Game", CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 + 200);

	CP_Settings_Stroke(CP_Color_Create(220, 220, 220, 255));
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_Fill(CP_Color_Create(220, 220, 220, settings_alpha_1));
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 -110, 500, 50);
	CP_Settings_Fill(CP_Color_Create(220, 220, 220, settings_alpha_2));
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 - 10, 500, 50);
	CP_Settings_Fill(CP_Color_Create(220, 220, 220, settings_alpha_3));
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 + 90, 500, 50);
	CP_Settings_Fill(CP_Color_Create(220, 220, 220, settings_alpha_4));
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2 + 190, 500, 50);


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
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
			CP_Engine_Terminate();
			return 0;
		}
	}
	else {
		settings_alpha_4 = 0;
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
	int i;
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));	


	for (i = 0; i < CWall + 1; i++) {
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawLine((wall[i].pos1.x/9) + 550, (wall[i].pos1.y/9) + 300, (wall[i].pos2.x/9) + 550, (wall[i].pos2.y/9) + 300);
	
	}
	
	/* For Way Point
	CP_Graphics_DrawRect(point_1.x/1.78, point_1.y/2.78, point_1.w/4, point_1.h/4);
	CP_Graphics_DrawRect(point_2.x / 2.44, point_2.y / 2.25, point_2.w / 4, point_2.h / 4);
	CP_Graphics_DrawRect(point_3.x * 1.25, point_3.y / 2.1, point_3.w / 4, point_3.h / 4);
	*/


} 

void controlskeys(void) {
	if (CP_Input_KeyTriggered(KEY_BACKSPACE)) { // Sample of a Pause phase
		if (game_states != paused) {
			game_states = paused;
		}
		else {
			game_states = resume;
		}
	}
	

	if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
		if (game_states != theMenu) {
			//game_states = volumeC;
			game_states = theMenu;
		}
		else {
			game_states = resume;

		}
	}
	if (CP_Input_KeyTriggered(KEY_M)) {
		if (game_states != theMap) {
			game_states = theMap;

		}
		else {
			game_states = resume;
		}


	}

	if (CP_Input_KeyTriggered(KEY_T)) {
		CP_Sound_PlayAdvanced(ping, volume, 1.0f, FALSE, CP_SOUND_GROUP_0);
	}
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
					CreateRay(player1.x - WorldX, player1.y - WorldY, 25, v.x, v.y, 2, color, true, 200,true);

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
				CreateRay(player1.x - WorldX, player1.y - WorldY, 50, v.x, v.y, 2, color, false,130,true);


			}
			CP_Sound_PlayAdvanced(ping, volume, 1, FALSE, 0);
			energy -= 60;

		}
		//else if (CP_Input_MouseTriggered(MOUSE_BUTTON_3)) {
		//	CP_Color color = CP_Color_Create(50, 50, 255, 255);
		//	for (int i = 0; i < 36; i++) {
		//		CP_Vector v = AngleToVector(i * 10);
		//		CreateRay(player1.x - WorldX, player1.y - WorldY, 50, v.x * 200, v.y * 200, 5, color, false);


		//	}

		//}

		//if (CP_Input_KeyTriggered(KEY_N)) {
		//	if (energy > 30) {
		//		CP_Color color = CP_Color_Create(0, 255, 0, 255);

		//		for (int i = 0; i < 36; i++) {
		//			CP_Vector v = AngleToVector(i * 10);
		//			CreateRay(-WorldX + CP_System_GetWindowWidth() / 2, -WorldY + CP_System_GetWindowHeight() / 2, 50, v.x * 200, v.y * 200, 1, color, false);


		//		}

		//		energy -= 30;
		//		CP_Sound_PlayAdvanced(ping, volume, 1, FALSE, 0);
		//	}
		//}
		
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
		if (debug == 0) {
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
	if (game_states == theMenu) {
		volumeControl();
		settings_menu();
	}
	if (game_states == theMap) {
		CP_Settings_Fill(CP_Color_Create(188, 158, 130, 255));
		CP_Settings_RectMode(CP_POSITION_CORNER); // Line below draws a border



		CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 4, CP_System_GetWindowHeight() / 4, (CP_System_GetWindowWidth()+50) / 2, (CP_System_GetWindowHeight() + 50) / 2);

		mapScale();
	}
	
}



void controller_init(void) {
	
	//CP_System_SetWindowSize(1920, 1080);
	//CP_Settings_EllipseMode(CP_POSITION_CENTER);

	//player1.x = center_x;
	//player1.y = center_y;
	Sound_Init();

	
	volume = 0.1;

	
}

void controller_update(void) {
	
	CP_Settings_BlendMode(CP_BLEND_ALPHA);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	if (player1.x > (float)CP_System_GetWindowWidth()) {
		player1.x = (float)CP_System_GetWindowWidth();
	}
	

	if (player1.y > (float)CP_System_GetWindowHeight()) {
		player1.y = (float)CP_System_GetWindowHeight();
	}
	else if (player1.y < 0) {
		player1.y = 0;
	}


	CP_Graphics_DrawCircle(player1.x,player1.y, 10); // Draws the player circle on default 

	movement();

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(20.0f);
	CP_Font_DrawText("[L] RETURN TO GAME", 20, 20);
	if (CP_Input_KeyTriggered(KEY_L))
	{
		CP_Engine_SetNextGameState(subgame_init, subgame_update, subgame_exit);

	}

	
	return 0;



}

void controller_exit(void) {
	return 0;
}