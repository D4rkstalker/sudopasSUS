#include "cprocessing.h"
#include "SoundCast.h"
#include "Utils.h"
#include "game.h"
#include "menu.h"
#include <stdio.h>
#include <Share.h>

//sonar ping sound
CP_Sound ping = NULL;

//Ray cast stuff -HQ
float particleSize = 3.0f;

//-------------------

float WorldRot = 0;

/*
WorldX and WorldY functions as the offset for the camera system.
All coordinates used by all game objects will need to be offset by the WorldX and WorldY coordinates.
*/
float WorldX = 0;
float WorldY = 0;


/*
Made by Nigel

Variables to save the location of the circles that show up as you are drawing a triangle wall
Variable drawpoint is the number of points currently drawn
*/
int drawpoint = 0;
double drawx1;
double drawy1;
double drawx2;
double drawy2;

/*
Made by Nigel

Triangle structures meant to function as walls in game
Contains the x and y coordinates of all 3 points of the triangle
*/

int CWall = 0;
Wall wall[9999];

/*
Made by Nigel

After creating 3 draw points, wall_init creates a triangle wall in the world.
*/
void Wall_Init(double x, double y) {

	wall[CWall].pos1 = CP_Vector_Set(drawx1, drawy1);
	wall[CWall].pos2 = CP_Vector_Set(x, y);
}

void UndoWall(void) {
	CWall -= 1;
	wall[CWall].pos1 = CP_Vector_Set(0, 0);
	wall[CWall].pos2 = CP_Vector_Set(0, 0);
}

/*
Made by Nigel

Draw the line walls for each frame
*/
void DrawWalls(void) {
	int i;
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));

	//draw walls
	for (i = 0; i < CWall + 1; i++) {
		CP_Graphics_DrawLine(WorldX + wall[i].pos1.x, WorldY + wall[i].pos1.y, WorldX + wall[i].pos2.x, WorldY + wall[i].pos2.y);
		//CP_Graphics_DrawTriangle(WorldX + wall[i].pos1.x, WorldY + wall[i].pos1.y, WorldX + wall[i].pos2.x, WorldY + wall[i].pos2.y, WorldX + wall[i].pos3.x, WorldY + wall[i].pos3.y);
		//CP_Graphics_DrawRect(WorldX + wall[i].x1, WorldY + wall[i].y1, wall[i].w, wall[i].h);
	}

	//draw wall markers
	if (drawpoint > 0)
		CP_Graphics_DrawCircle(WorldX + drawx1, WorldY + drawy1, 20);
}

void loadwalls(void) {
	int c;
	int i = 0;
	FILE* in = _fsopen("walls.txt", "r", _SH_DENYNO);
	while (1) {
		c = fgetc(in);
		if (feof(in)) {
			break;
		}
		fscanf_s(in,"%f %f %f %f\n", &wall[i].pos1.x, &wall[i].pos1.y, &wall[i].pos2.x, &wall[i].pos2.y);
		++i;
	}
	CWall = i;
	fclose(in);
}

void savewalls(void) {
	FILE* out = _fsopen("walls.txt", "w", _SH_DENYNO);
	for (int i = 0; i < CWall; i++) {
		fprintf(out, "%f %f %f %f\n", wall[i].pos1.x, wall[i].pos1.y, wall[i].pos2.x, wall[i].pos2.y);
	}
}

void CheckControls(void) {
	/*
	Made by Nigel

	Offset the WorldX and WorldY, in order to create and explore a world beyond the screen resolution
	*/
	if (CP_Input_KeyDown(KEY_UP))
	{
		WorldY += 5;
	}
	if (CP_Input_KeyDown(KEY_DOWN))
	{
		WorldY += -5;
	}
	if (CP_Input_KeyDown(KEY_LEFT))
	{
		WorldX += 5;
	}
	if (CP_Input_KeyDown(KEY_RIGHT))
	{
		WorldX += -5;
	}

	/*
	Made by Nigel

	Create a wall draw point every time you press the "T" key.
	*/
	if (CP_Input_KeyTriggered(KEY_T))
	{
		if (drawpoint == 0) {
			drawx1 = CP_Input_GetMouseX() - WorldX;
			drawy1 = CP_Input_GetMouseY() - WorldY;
			drawpoint += 1;
		}
		else {
			Wall_Init(CP_Input_GetMouseX() - WorldX, CP_Input_GetMouseY() - WorldY);
			drawpoint = 0;
			CWall += 1;
		}
	}

	if (CP_Input_KeyTriggered(KEY_S)) {
		savewalls();
	}

	//HQ stuff

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
		CP_Color color = CP_Color_Create(90, 180, 77, 155);
		for (int i = 0; i < 36; i++) {
			CP_Vector v = AngleToVector(i * 10);
			CreateRay(CP_Input_GetMouseWorldX(), CP_Input_GetMouseWorldY(), 50, v.x * 200, v.y * 200, color);
			CP_Sound_PlayAdvanced(ping,0.01,1,FALSE,1);

		}
		
	}
	else if (CP_Input_MouseTriggered(MOUSE_BUTTON_2)) {
		CP_Color color = CP_Color_Create(255, 50, 50, 255);
		for (int i = 0; i < 36; i++) {
			CP_Vector v = AngleToVector(i * 10);
			CreateRay(CP_Input_GetMouseWorldX(), CP_Input_GetMouseWorldY(), 50, v.x * 200, v.y * 200, color);


		}


	}
	else if (CP_Input_MouseTriggered(MOUSE_BUTTON_3)) {
		CP_Color color = CP_Color_Create(50, 50, 255, 255);
		for (int i = 0; i < 36; i++) {
			CP_Vector v = AngleToVector(i * 10);
			CreateRay(CP_Input_GetMouseWorldX(), CP_Input_GetMouseWorldY(), 50, v.x * 200, v.y * 200, color);


		}


	}

	if (CP_Input_KeyTriggered(KEY_Q))
	{
		CP_Engine_SetNextGameState(mainmenu_init, mainmenu_update, mainmenu_exit);
	}

	if (CP_Input_KeyTriggered(KEY_Z)) {
		UndoWall();
	}

}



void subgame_init(void) {
	CP_System_SetWindowSize(1920, 1080);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_BlendMode(CP_BLEND_ALPHA);

	//initialise sound
	ping = CP_Sound_Load("ping.wav");

	//set up sound cast system
	loadwalls();
	InitScene(wall,CWall);
}

void subgame_update(void) {

	//1st draw layer, clear the background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	//2nd draw layer, the walls of the game
	DrawWalls(wall);

	//3rd draw layer, the raycast
	RayUpdate();
	//4th draw layer, the UI for the game

	//Check the controls pressed each frame
	CheckControls();

}

void subgame_exit(void) {

}