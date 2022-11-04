#include <cprocessing.h>
#include <Share.h>
#include <stdio.h>
#include "walls.h"
#include "utils.h"
#include "game.h"
#include "subcontroller.h"
#include "music.h"

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

	for (int i = 0; i < drawpoint; i++) {
		CP_Graphics_DrawCircle(WorldX + drawx[i], WorldY + drawy[i], 20);
	}
}

/*
Made by Nigel

After creating 3 draw points, wall_init creates a triangle wall in the world.
*/
void Wall_Init(double x, double y) {

	

	switch (drawpoint) {
	case 0:
		break;
	case 1:
		wall[CWall].pos1 = CP_Vector_Set(drawx[0], drawy[0]);
		wall[CWall].pos2 = CP_Vector_Set(x, y);
		CWall += 1;
		break;
	case -1:
		wall[CWall].pos1 = CP_Vector_Set(drawx[0], drawy[0]);
		wall[CWall].pos2 = CP_Vector_Set(drawx[1], drawy[1]);
		CWall += 1;
		wall[CWall].pos1 = CP_Vector_Set(drawx[1], drawy[1]);
		wall[CWall].pos2 = CP_Vector_Set(x, y);
		CWall += 1;
		break;
	default:
		for (int i = 0; i < drawpoint - 1; i++) {
			wall[CWall].pos1 = CP_Vector_Set(drawx[i], drawy[i]);
			wall[CWall].pos2 = CP_Vector_Set(drawx[i + 1], drawy[i + 1]);
			CWall += 1;
		}
		wall[CWall].pos1 = CP_Vector_Set(drawx[drawpoint - 1], drawy[drawpoint - 1]);
		wall[CWall].pos2 = CP_Vector_Set(drawx[0], drawy[0]);
		CWall += 1;
	}
	drawpoint = 0;
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
	float d = (CP_Math_Distance(wall[i].pos1.x, wall[i].pos1.y, wall[i].pos2.x, wall[i].pos2.y)
		- CP_Math_Distance(wall[i].pos1.x, wall[i].pos1.y, inputx + vx, inputy + vy)
		- CP_Math_Distance(wall[i].pos2.x, wall[i].pos2.y, inputx + vx, inputy + vy));
	return d;
}

int wallcollision(void) {
	float x1 = -WorldX + CP_System_GetWindowWidth() / 2;
	float y1 = -WorldY + CP_System_GetWindowHeight() / 2;
	float x2 = x1 + player1.velocity_x;
	float y2 = y1 + player1.velocity_y;

	for (int i = 1; i < CWall; i++) {

		float x3 = wall[i].pos1.x;
		float y3 = wall[i].pos1.y;
		float x4 = wall[i].pos2.x;
		float y4 = wall[i].pos2.y;

		float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
		float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

		if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
			int loop = 0;
			while (-walldistance(i, x1, y1, 0, 0) > 0.05) {
				if (loop++ > 1000) break;
				WorldX -= player1.velocity_x / 1000;
				WorldY -= player1.velocity_y / 1000;
				x1 = -WorldX + CP_System_GetWindowWidth() / 2;
				y1 = -WorldY + CP_System_GetWindowHeight() / 2;
			}
			if (CP_Math_Distance(0,0,player1.velocity_x,player1.velocity_y) > 5) {
				CP_Sound_PlayAdvanced(bonk, volume, 1, FALSE, 1);
			}
			player1.acceleration_x = 0;
			player1.acceleration_y = 0;
			player1.velocity_x = 0;
			player1.velocity_y = 0;
			return 1;
		}

	}
	return 0; 
}
