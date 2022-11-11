#include "game.h"
#include "menu.h"
#include "subcontroller.h"
#include "SoundCast.h"
#include "checkpoint.h"
#include "Utils.h"
#include "walls.h"
#include "music.h"
	
CheckPoint point_1;
CheckPoint point_2;
CheckPoint point_3;
CheckPoint point_exit;

float cp1_progress = 0;
float cp2_progress = 0;
float cp3_progress = 0;
float exit_progress = 0;

float cp_pingtimer = 0;

CheckPoint_1_Triggered = 0;
CheckPoint_2_Triggered = 0;
CheckPoint_3_Triggered = 0;
exit_Triggered = 0;

Gate cp1_gate;
Gate cp2_gate;
Gate cp3_gate;



void draw_checkpoint_ping(float delay, float x, float y)
{

	cp_pingtimer++;
	if (cp_pingtimer == delay) //Ping every 300 frames
	{
		CP_Color color = CP_Color_Create(255, 255, 0, 50);
		//CP_Vector v = AngleToVector(-90);
		//CreateRay(CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY, 50, v.x * 200, v.y * 200, color);

		for (int i = 0; i < 16; i++) {
			CP_Vector v = AngleToVector(i * 20);
			CreateRay(x, y, 50, v.x, v.y , 0.1, color, false,100);
		}

		if (x + WorldX >= 0 && x + WorldX <= CP_System_GetWindowWidth() && y + WorldY >= 0 && y + WorldY <= CP_System_GetWindowHeight()) {
			CP_Sound_PlayAdvanced(ping, volume, 2, FALSE, 0);
		}

		cp_pingtimer = 0;

	}
}


void draw_checkpoint_1(void)
{

	point_1.x = 1640;
	point_1.y = 2225;
	point_1.w = 50;
	point_1.h = 50;

	if (debug == 1) {
		CP_Settings_NoStroke();
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(WorldX + point_1.x, WorldY + point_1.y, point_1.w, point_1.h);
	}

	draw_checkpoint_ping(300, point_1.x, point_1.y + 25);

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));
	cp1_gate.pos1 = CP_Vector_Set(1634,1903);
	cp1_gate.pos2 = CP_Vector_Set(1634, 2017);
	//CP_Graphics_DrawLine(WorldX+cp1_gate.pos1.x, WorldY+cp1_gate.pos1.y, WorldX+cp1_gate.pos2.x, WorldY+cp1_gate.pos2.y);

}

void draw_checkpoint_2(void)
{

	point_2.x = 2960;
	point_2.y = 1375;
	point_2.w = 50;
	point_2.h = 50;

	if (debug == 1) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(WorldX + point_2.x, WorldY + point_2.y, point_2.w, point_2.h);
	}

	draw_checkpoint_ping(300, point_2.x, point_2.y + 25);

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));
	cp2_gate.pos1 = CP_Vector_Set(2395, 1311);
	cp2_gate.pos2 = CP_Vector_Set(2250, 1550);
	//CP_Graphics_DrawLine(WorldX + cp2_gate.pos1.x, WorldY + cp2_gate.pos1.y, WorldX + cp2_gate.pos2.x, WorldY + cp2_gate.pos2.y);

}

void draw_checkpoint_3(void)
{

	point_3.x = 540;
	point_3.y = 1190;
	point_3.w = 50;
	point_3.h = 50;

	if (debug == 1) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(WorldX + point_3.x, WorldY + point_3.y, point_3.w, point_3.h);
	}

	draw_checkpoint_ping(300, point_3.x, point_3.y + 25);

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));
	cp3_gate.pos1 = CP_Vector_Set(1810, 890);
	cp3_gate.pos2 = CP_Vector_Set(1850, 1030);
	//CP_Graphics_DrawLine(WorldX + cp3_gate.pos1.x, WorldY + cp3_gate.pos1.y, WorldX + cp3_gate.pos2.x, WorldY + cp3_gate.pos2.y);

}

void draw_exit(void)
{

	point_exit.x = 2425;
	point_exit.y = 247;
	point_exit.w = 50;
	point_exit.h = 50;

	if (debug == 1) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(WorldX + point_exit.x, WorldY + point_exit.y, point_exit.w, point_exit.h);
	}
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
		if (debug == 1) {
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2 - 50.0f, CP_System_GetWindowHeight() / 2 + 20.0f, cp1_progress, 25.0f);
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 10));
			CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2 - 50.0f, CP_System_GetWindowHeight() / 2 + 20.0f, 100.0f, 25.0f);
		}
		cp1_progress++;
		if (cp1_progress == 100)
		{
			CheckPoint_1_Triggered = 1;
			UndoWall();
			CP_Sound_PlayAdvanced(ping, volume, 2, FALSE, 0);
			CP_Color color = CP_Color_Create(255, 255, 0, 50);
			//CP_Vector v = AngleToVector(-90);
			//CreateRay(CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY, 50, v.x * 200, v.y * 200, color);

			for (int i = 0; i < 36; i++) {
				CP_Vector v = AngleToVector(i * 10);
				CreateRay(1645, 1960, 50, v.x, v.y, 0.5, color, false,100);

			}
		}
		if (CheckPoint_1_Triggered == 1)
		{
			cp1_progress = 100;
		}

	}

}

void cp2_triggered(void)
{
	float x1 = -WorldX + CP_System_GetWindowWidth() / 2;
	float y1 = -WorldY + CP_System_GetWindowHeight() / 2;


	if (CheckPointTrigger(point_2.x, point_2.y, point_2.w, point_2.h, x1, y1) == 1)
	{
		if (debug == 1) {
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2 - 50.0f, CP_System_GetWindowHeight() / 2 + 20.0f, cp2_progress, 25.0f);
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 10));
			CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2 - 50.0f, CP_System_GetWindowHeight() / 2 + 20.0f, 100.0f, 25.0f);
		}
		cp2_progress++;
		if (cp2_progress == 100)
		{
			CheckPoint_2_Triggered = 1;
			UndoWall();
			CP_Sound_PlayAdvanced(ping, volume, 2, FALSE, 0);
			CP_Color color = CP_Color_Create(255, 255, 0, 50);
			//CP_Vector v = AngleToVector(-90);
			//CreateRay(CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY, 50, v.x * 200, v.y * 200, color);

			for (int i = 0; i < 36; i++) {
				CP_Vector v = AngleToVector(i * 10);
				CreateRay(2395, 1420, 50, v.x, v.y, 0.5, color, false,100);

			}
		}
		if (CheckPoint_2_Triggered == 1)
		{
			cp2_progress = 100;
		}

	}

}

void cp3_triggered(void)
{
	float x1 = -WorldX + CP_System_GetWindowWidth() / 2;
	float y1 = -WorldY + CP_System_GetWindowHeight() / 2;


	if (CheckPointTrigger(point_3.x, point_3.y, point_3.w, point_3.h, x1, y1) == 1)
	{
		if (debug == 1) {
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2 - 50.0f, CP_System_GetWindowHeight() / 2 + 20.0f, cp3_progress, 25.0f);
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 10));
			CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2 - 50.0f, CP_System_GetWindowHeight() / 2 + 20.0f, 100.0f, 25.0f);
		}
		cp3_progress++;
		if (cp3_progress == 100)
		{
			CheckPoint_3_Triggered = 1;
			UndoWall();
			CP_Sound_PlayAdvanced(ping, volume, 2, FALSE, 0);
		}
		if (CheckPoint_3_Triggered == 1)
		{
			cp3_progress = 100;
		}

	}

}

void exit_triggered(void)
{
	float x1 = -WorldX + CP_System_GetWindowWidth() / 2;
	float y1 = -WorldY + CP_System_GetWindowHeight() / 2;


	if (CheckPointTrigger(point_exit.x, point_exit.y, point_exit.w, point_exit.h, x1, y1) == 1)
	{
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2 - 50.0f, CP_System_GetWindowHeight() / 2 + 20.0f, exit_progress, 25.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 10));
		CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2 - 50.0f, CP_System_GetWindowHeight() / 2 + 20.0f, 100.0f, 25.0f);
		exit_progress++;
		if (exit_progress == 100)
		{
			exit_Triggered = 1;
		}
		if (CheckPoint_3_Triggered == 1)
		{
			exit_progress = 100;
		}

	}

}



void draw_checkpoint(void)
{
	if (CheckPoint_1_Triggered == 0)
	{
		draw_checkpoint_1();
		cp1_triggered();
	}

	if (CheckPoint_1_Triggered == 1 && CheckPoint_2_Triggered == 0)
	{
		draw_checkpoint_2();
		cp2_triggered();
	}
	if (CheckPoint_2_Triggered == 1 && CheckPoint_3_Triggered == 0)
	{
		draw_checkpoint_3();
		cp3_triggered();
	}
	if (CheckPoint_3_Triggered == 1 && exit_Triggered == 0)
	{
		draw_exit();
		exit_triggered();
	}
}


//430 to 440 mouse X, to click