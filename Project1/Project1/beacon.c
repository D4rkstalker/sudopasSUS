#include "checkpoint.h"
#include "game.h"
#include "Utils.h"
#include <math.h>
#include <stdbool.h>
#include "subcontroller.h"

//Beacon Script -Liu Hanqing

//Serves as a waypoint marker system to guide the player

CP_Vector beacon ;
CP_Vector target;
float size;
int alpha;
int x;
void DrawBeacon(float x, float y) {
    CP_Settings_NoFill();
	CP_Settings_Stroke(CP_Color_Create(255,255,0,alpha));
	CP_Graphics_DrawCircle(x, y, size);
}

void BeaconNext(CP_Vector pos) {
    x = 1;
    alpha = 250;

    size = 2000;
    target = pos;

}


//quick mafs

//draws the beacon at edge of the screen
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
    //cool shrink and flicker effect
    if (size > 21) {
        size-= 100;
    }
    else {
        size = 20;
        if (alpha >= 250 || alpha <= 10) {
            x *= -1;
        }
        alpha += x * 10;
    }
    lineRect(1920/2, 1080/2 + 20,target.x + WorldX,target.y + WorldY,0,0,1920,1020);

}
void InitBeacon(CP_Vector pos) {
    BeaconNext(pos);
	beacon = CP_Vector_Set(0, 0);
}



