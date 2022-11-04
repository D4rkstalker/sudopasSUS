#include "game.h"
#include "menu.h"
#include "subcontroller.h"
#include "SoundCast.h"
#include "checkpoint.h"
	
CheckPoint point_1;
float cp1_progress = 0;

void draw_checkpoint_1(void)
{

	point_1.x = 775;
	point_1.y = 2080;
	point_1.w = 100;
	point_1.h = 100;

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 0));
	CP_Graphics_DrawRect(WorldX + point_1.x,WorldY + point_1.y,point_1.w,point_1.h);

}

int CheckPointTrigger(float area_x, float area_y, float area_width, float area_height, float player_X, float player_Y)	
{
	if (player_X > area_x && player_X < area_x+area_width && player_Y > area_y && player_Y < area_y+area_height)
	{
		return 1;
	}
	else
	{
	return 0;
	}
}

void cp1_triggered(void)
{
	float x1 = -WorldX + CP_System_GetWindowWidth() / 2;
	float y1 = -WorldY + CP_System_GetWindowHeight() / 2;


	if (CheckPointTrigger(point_1.x, point_1.y, point_1.w, point_1.h, x1, y1) == 1)
	{
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2 - 50.0f, CP_System_GetWindowHeight() / 2 + 20.0f, cp1_progress, 25.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 10));
		CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2 - 50.0f, CP_System_GetWindowHeight() / 2 + 20.0f, 100.0f, 25.0f);
		cp1_progress++;
		if (cp1_progress == 100)
		{
			CheckPoint_1_Triggered = 1;
		}
		if (CheckPoint_1_Triggered == 1)
		{
			cp1_progress = 100;
		}

	}

}



