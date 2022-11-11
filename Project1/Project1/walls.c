#include <cprocessing.h>
#include <Share.h>
#include <stdio.h>
#include "walls.h"
#include "utils.h"
#include "game.h"
#include "subcontroller.h"
#include "music.h"
#include "checkpoint.h"

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
	cpfailsafe();
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

		if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1 || 
			((- walldistance(i, x1, y1, 0, 0) < 2 || CP_Math_Distance(x1, y1, wall[i].pos1.x, wall[i].pos1.y) < 15 || CP_Math_Distance(x1, y1, wall[i].pos2.x, wall[i].pos2.y) < 15) && (walldistance(i, x1, y1, 0, 0) < walldistance(i, x1, y1, player1.velocity_x, player1.velocity_y)))) {
			//int loop = 0;
			//uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1 || 
			//(- walldistance(i, x1, y1, 0, 0) < 4
			//circlelinecollision(i, x1, y1) == 1 && 
			//||
			//(walldistance(i, x1, y1, 0, 0) < walldistance(i, x1, y1, player1.velocity_x, player1.velocity_y)

			/*
			while (-walldistance(i, x1, y1, 0, 0) > 3) {
				if (loop++ > 1000) break;
				WorldX -= player1.velocity_x / 1000;
				WorldY -= player1.velocity_y / 1000;
				x1 = -WorldX + CP_System_GetWindowWidth() / 2;
				y1 = -WorldY + CP_System_GetWindowHeight() / 2;
			}*/
			if (CP_Math_Distance(0,0,player1.velocity_x,player1.velocity_y) > 5) {
				CP_Sound_PlayAdvanced(bonk, volume, 1, FALSE, 0);
			}
			player1.acceleration_x = 0;
			player1.acceleration_y = 0;

			/*
			CP_Vector line = CP_Vector_Set(wall[i].pos1.x-wall[i].pos2.x, wall[i].pos1.y - wall[i].pos2.y);
			if (line.x < 0) {
				line.x = -line.x;
			}
			if (line.y < 0) {
				line.y = -line.y;
			}
			CP_Vector_Scale(line, CP_Vector_Length(CP_Vector_Set(player1.velocity_x,player1.velocity_y))/CP_Vector_Length(line));
			float distx = CP_Math_ClampFloat(player1.velocity_x * line.x,-1,1);
			float disty = CP_Math_ClampFloat(player1.velocity_y * line.y,-1,1);
			if (walldistance(i, x1, y1, 0, 0) < walldistance(i, x1, y1, distx, disty)) {
				WorldX -= distx;
				WorldY -= disty;
			}*/
			player1.velocity_x = -player1.velocity_x * 0.8;
			player1.velocity_y = -player1.velocity_y * 0.8;
			return 1;
		}

	}
	return 0; 
}

void cpwallinit(Gate cp) {
	drawx[0] = cp.pos1.x;
	drawy[0] = cp.pos1.y;
	drawpoint = 1;
	Wall_Init(cp.pos2.x, cp.pos2.y);
}

void createcpwalls(void) {
	draw_checkpoint_1();
	draw_checkpoint_2();
	draw_checkpoint_3();
	cpwallinit(cp3_gate);
	cpwallinit(cp2_gate);
	cpwallinit(cp1_gate);
}

//failsafe to ensure you dont save checkpoint walls
void cpfailsafe(void) {
	if (CheckPoint_3_Triggered == 1) {

	}
	else if (CheckPoint_2_Triggered == 1) {
		UndoWall();
	}
	else if (CheckPoint_1_Triggered == 1) {
		UndoWall();
		UndoWall();
	}
	else {
		UndoWall();
		UndoWall();
		UndoWall();
	}
	CheckPoint_3_Triggered = 1;
	CheckPoint_2_Triggered = 1;
	CheckPoint_1_Triggered = 1;
}
