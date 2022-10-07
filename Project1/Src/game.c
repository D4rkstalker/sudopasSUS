#include "cprocessing.h"

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

int CWall = 0;
Wall wall[9999];

void subgame_init(void) {

}

void subgame_update(void) {
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