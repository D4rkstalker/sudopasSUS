#include "game.h"

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
double drawx1;
double drawy1;
double drawx2;
double drawy2;

void DrawWalls(void);
void Wall_Init(double x, double y);
void UndoWall(void);
void loadwalls(void);
void savewalls(void);
int wallcollision(void);