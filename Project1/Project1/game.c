#include "cprocessing.h"

float WorldX = 0;
float WorldY = 0;

int drawpoint = 0;
double drawx1;
double drawy1;
double drawx2;
double drawy2;

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
}

void Wall_Init(double x, double y) {
	wall[CWall].x1 = drawx1;
	wall[CWall].x2 = drawx2;
	wall[CWall].y1 = drawy1;
	wall[CWall].y2 = drawy2;
	wall[CWall].x3 = x;
	wall[CWall].y3 = y;
}

void subgame_init(void) {
	CP_System_SetWindowSize(2000, 2000);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
}

void subgame_update(void) {

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	DrawWalls();
	CheckControls();

	if (CP_Input_KeyDown(KEY_C))
	{
		/*
		int i;
		CWall += 1;
		i = CWall;
		wall[i].x1 = CP_Input_GetMouseX() - WorldX;
		wall[i].y1 = CP_Input_GetMouseY() - WorldY;
		wall[i].w = 50;
		wall[i].h = 50; */
	}

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

void subgame_exit(void) {

}