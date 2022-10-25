#include "cprocessing.h"
#include "SoundCast.h"
#include "Utils.h"
#include "game.h"

//Ray cast stuff -HQ
float particleSize = 3.0f;

//-------------------




int WorldX = 0;
int WorldY = 0;
int CarR[3] = { 0,0,255 };
int CarG[3] = { 0,255,0 };
int CarB[3] = { 255,0,0 };
float CarX[3] = { 100,200,300 };
float CarY[3] = { 100,200,300 };
float CarRot[3] = { 0,0,0 };
float WorldRot = 0;
int CarDiameter = 50;

typedef struct Wall {
	int x;
	int y;
	int w;
	int h;
} Wall;

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

void subgame_init(void) {

}

void subgame_update(void) {

}

/*
Made by Nigel

After creating 3 draw points, wall_init creates a triangle wall in the world.
*/
void Wall_Init(double x, double y) {

	wall[CWall].pos1 = CP_Vector_Set(drawx1, drawy1);
	wall[CWall].pos2 = CP_Vector_Set(drawx2, drawy2);
	wall[CWall].pos3 = CP_Vector_Set(x, y);

}

/*
Made by Nigel

Draw the triangle walls for each frame
*/
void DrawWalls(void) {
	int i;
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	//draw wall markers
	if (drawpoint > 0)
	CP_Graphics_DrawCircle(WorldX + drawx1, WorldY + drawy1, 20);
	if (drawpoint > 1)
	CP_Graphics_DrawCircle(WorldX + drawx2, WorldY + drawy2, 20);
	

	//draw walls
	for (i = 0; i < CWall + 1; i++) {
		CP_Graphics_DrawTriangle(WorldX + wall[i].pos1.x, WorldY + wall[i].pos1.y, WorldX + wall[i].pos2.x, WorldY + wall[i].pos2.y, WorldX + wall[i].pos3.x, WorldY + wall[i].pos3.y);
		//CP_Graphics_DrawRect(WorldX + wall[i].x1, WorldY + wall[i].y1, wall[i].w, wall[i].h);
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
		else if (drawpoint == 1) {
			drawx2 = CP_Input_GetMouseX() - WorldX;
			drawy2 = CP_Input_GetMouseY() - WorldY;
			drawpoint += 1;
		}
		else {
			Wall_Init(CP_Input_GetMouseX() - WorldX, CP_Input_GetMouseY() - WorldY);
			drawpoint = 0;
			CWall += 1;
		}
	}

	//HQ stuff

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
		CP_Color color = CP_Color_Create(90, 180, 77, 155);
		for (int i = 0; i < 36; i++) {
			CP_Vector v = AngleToVector(i * 10);
			CreateRay(CP_Input_GetMouseWorldX(), CP_Input_GetMouseWorldY(), 50, v.x * 200, v.y * 200, color);


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

}

void subgame_init(void) {
	CP_System_SetWindowSize(1920, 1080);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_BlendMode(CP_BLEND_ALPHA);

	//set up sound cast system
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

	if (CP_Input_KeyDown(KEY_C))
	{
		int i;
		CWall += 1;
		i = CWall;
		wall[i].x = CP_Input_GetMouseX() - WorldX;
		wall[i].y = CP_Input_GetMouseY() - WorldY;
		wall[i].w = 50;
		wall[i].h = 50;
	}

}

void subgame_exit(void) {

}