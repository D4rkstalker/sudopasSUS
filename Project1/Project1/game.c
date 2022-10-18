#include "cprocessing.h"

/*
Made by Nigel

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
typedef struct Wall {
	double x1;
	double y1;
	double x2;
	double y2;
	double x3;
	double y3;
} Wall;

int CWall = 0;
Wall wall[9999];

/*
Made by Nigel

After creating 3 draw points, wall_init creates a triangle wall in the world.
*/
void Wall_Init(double x, double y) {
	wall[CWall].x1 = drawx1;
	wall[CWall].x2 = drawx2;
	wall[CWall].y1 = drawy1;
	wall[CWall].y2 = drawy2;
	wall[CWall].x3 = x;
	wall[CWall].y3 = y;
}

/*
Made by Nigel

Draw the triangle walls for each frame
*/
void DrawWalls(void) {
	int i;

	//draw wall markers
	if (drawpoint > 0)
	CP_Graphics_DrawCircle(WorldX + drawx1, WorldY + drawy1, 20);
	if (drawpoint > 1)
	CP_Graphics_DrawCircle(WorldX + drawx2, WorldY + drawy2, 20);
	

	//draw walls
	for (i = 0; i < CWall + 1; i++) {
		CP_Graphics_DrawTriangle(WorldX + wall[i].x1, WorldY + wall[i].y1, WorldX + wall[i].x2, WorldY + wall[i].y2, WorldX + wall[i].x3, WorldY + wall[i].y3);
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
}

void subgame_init(void) {
	CP_System_SetWindowSize(2000, 2000);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
}

void subgame_update(void) {

	//1st draw layer, clear the background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	//2nd draw layer, the walls of the game
	DrawWalls();

	//3rd draw layer, the raycast

	//4th draw layer, the UI for the game

	//Check the controls pressed each frame
	CheckControls();

	if (CP_Input_KeyDown(KEY_C))
	{
		/*
		Code to create squares, deprecated
		Keeping just in case we want to revert to square/rectangle walls

		int i;
		CWall += 1;
		i = CWall;
		wall[i].x1 = CP_Input_GetMouseX() - WorldX;
		wall[i].y1 = CP_Input_GetMouseY() - WorldY;
		wall[i].w = 50;
		wall[i].h = 50; */
	}

}

void subgame_exit(void) {

}