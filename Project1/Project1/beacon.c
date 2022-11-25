#include "checkpoint.h"
#include "game.h"
#include "Utils.h"
#include <math.h>
#include <stdbool.h>
#include "subcontroller.h"
CP_Vector beacon ;
CP_Vector target;
void DrawBeacon(float x, float y) {
	CP_Settings_Fill(CP_Color_Create(255,255,0,255));
	CP_Graphics_DrawCircle(x, y, 25);
}

void BeaconNext() {

}

void lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {

    float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
    float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

    float intersectionX = x1 + (uA * (x2 - x1));
    float intersectionY = y1 + (uA * (y2 - y1));
    if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
        DrawBeacon(intersectionX, intersectionY);
    }
}


void lineRect(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh) {
    lineLine(x1, y1, x2, y2, rx, ry, rx, ry + rh);
    lineLine(x1, y1, x2, y2, rx + rw, ry, rx + rw, ry + rh);
    lineLine(x1, y1, x2, y2, rx, ry, rx + rw, ry);
    lineLine(x1, y1, x2, y2, rx, ry + rh, rx + rw, ry + rh);
}


void UpdateBeacon() {
	//float d = CP_Math_Degrees(atan2(v.y, v.x));
    float x = player1.x - WorldX;
    float y = player1.y - WorldY;
    lineRect(1920/2, 1080/2 + 20,target.x + WorldX,target.y + WorldY,0,0,1920,1020);

}
void InitBeacon(CP_Vector pos) {
	target = pos;
	beacon = CP_Vector_Set(0, 0);
}



