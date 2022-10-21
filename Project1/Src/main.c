#include <windows.h>
#include "cprocessing.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "game.h"
#include "menu.h"
#include "SoundCast.h"
#include "utils.h"
#include "subcontroller.h"
#include "enemy.h"

CP_Image logo;


float particleSize = 3.0f;


float lineProximityDistance = 100.0f;
float mouseProximityDistance = 200.0f;

int recommendedWidth = 1600;
int recommendedHeight = 900;

bool drawColors = true;
bool drawFPS = true;







void game_init(void)
{
	logo = CP_Image_Load("Assets/DigiPen_Singapore_WEB_RED.png");
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	/*for (int i = 0; i < numParticles; ++i) {
		ParticleCreate(&particles[i]);
	}*/

	CP_System_SetWindowSize(1920, 1080);
}

void game_update(void)
{
	CP_Settings_BlendMode(CP_BLEND_ALPHA);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	if (CP_Input_MouseClicked()) {
		for (int i = 0; i < 36; i++) {
			CP_Vector v = AngleToVector(i * 10);
			CreateRay(CP_Input_GetMouseWorldX(), CP_Input_GetMouseWorldY(), 50,v.x*200,v.y*200);


		}

	}

	//background(CP_Color_Create((int)(CP_Input_GetMouseX() / canvasWidth * 255.0f), 0, 0, 255));
	//CP_Graphics_Background(CP_CreateColor((int)(CP_Input_GetMouseX() / CP_Graphics_GetCanvasWidth() * 255.0f), 0, 0, 255));


	RayUpdate();

	// Profiling info and frameRate testing
	if (drawFPS)
	{
		CP_Settings_TextSize(20);
		CP_Settings_BlendMode(CP_BLEND_ALPHA);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 128));
		CP_Settings_NoStroke();
		CP_Graphics_DrawRect(0, 0, 150, 30);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		char buffer[100];
		sprintf_s(buffer, 100, "FPS: %f", CP_System_GetFrameRate());
		CP_Font_DrawText(buffer, 20, 20);
	}
	//CP_Image_Draw(logo, 0.f, 0.f, CP_Image_GetWidth(logo), CP_Image_GetHeight(logo), 255);
	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_SetNextGameState(subgame_init, subgame_update, subgame_exit);
		//CP_Engine_Terminate();
	}
	if (CP_Input_KeyDown(KEY_W))
	{
		CP_Engine_SetNextGameState(mainmenu_init, mainmenu_update, mainmenu_exit);
		//CP_Engine_Terminate();
	}


	// MR's controller testing 
	if (CP_Input_KeyDown(KEY_L))
	{
		CP_Engine_SetNextGameState(controller_init, controller_update, controller_exit);

	}

	if (CP_Input_KeyDown(KEY_K))
	{
		CP_Engine_SetNextGameState(enemy_init, enemy_update, enemy_exit);

	}
	
}


void game_exit(void)
{
	CP_Image_Free(&logo);
}




int main(void)
{
	//CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}