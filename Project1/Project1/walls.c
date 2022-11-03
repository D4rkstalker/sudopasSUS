#include <cprocessing.h>
#include <Share.h>
#include <stdio.h>
#include "walls.h"
#include "utils.h"
#include "game.h"
#include "subcontroller.h"

int drawpoint = 0;

/*
Made by Nigel

Triangle structures meant to function as walls in game
Contains the x and y coordinates of all 3 points of the triangle
*/

int CWall = 0;
Wall wall[99999];

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

void loadwalls(void) {
	int c;
	int i = 0;
	FILE* in = _fsopen("walls.txt", "r", _SH_DENYNO);
	while (1) {
		if (feof(in)) {
			break;
		}
		fscanf_s(in, "%f %f %f %f\n", &wall[i].pos1.x, &wall[i].pos1.y, &wall[i].pos2.x, &wall[i].pos2.y);
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

float walldistance(int i, float inputx, float inputy, float vx, float vy) {
	return (CP_Math_Distance(wall[i].pos1.x, wall[i].pos1.y, wall[i].pos2.x, wall[i].pos2.y)
		- CP_Math_Distance(wall[i].pos1.x, wall[i].pos1.y, inputx + vx, inputy + vy)
		- CP_Math_Distance(wall[i].pos2.x, wall[i].pos2.y, inputx + vx, inputy + vy));
}

int collcheck(float inputx, float inputy) {
	for (int i = 1; i < CWall; i++) {
		float d = walldistance(i, inputx, inputy, 0, 0);
		if (d > -1) {
			return i;
		}
	}
	return 0;
}

int wallcollision(void) {
	float playerx = -WorldX + CP_System_GetWindowWidth() / 2;
	float playery = -WorldY + CP_System_GetWindowHeight() / 2;
	float playervx = playerx + player1.velocity_x;
	float playervy = playery + player1.velocity_y;

	
	if (collcheck(playerx, playery)) {
		int t = collcheck(playerx, playery);
		if (walldistance(t, playerx, playery, 0, 0) >= walldistance(t, playerx, playery, player1.velocity_x, player1.velocity_y)) {
			return 0;
		}
		player1.acceleration_x = 0;
		player1.acceleration_y = 0;
		player1.velocity_x = 0;
		player1.velocity_y = 0;
		return 1;
	} 
	return 0; 
}
