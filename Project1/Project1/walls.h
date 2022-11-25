#include "game.h"
#include "checkpoint.h"

/*
Wall functions made by Nigel
*/

int CWall;
Wall wall[99999];

/*
Made by Nigel

Variables to save the location of the circles that show up as you are drawing a triangle wall
Variable drawpoint is the number of points currently drawn
*/
int drawpoint;
float drawx1;
float drawy1;
float drawx2;
float drawy2;
float drawx3;
float drawy3;

float drawx[9999];
float drawy[9999];

void DrawWalls(void);
void Wall_Init(float x, float y);
void UndoWall(void);
void loadwalls(void);
void savewalls(void);
int wallcollision(void);
void createcpwalls(void);
void cpfailsafe(void);
void cpwallinit(Gate cp);
