#include "game.h"
#include "menu.h"
#include "subcontroller.h"
#include "SoundCast.h"
#include "checkpoint.h"
#include "Utils.h"
#include "walls.h"
#include "music.h"
#include "enemy.h"
	
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
		CP_Color color = CP_Color_Create(255, 255, 0, 150);
		//CP_Vector v = AngleToVector(-90);
		//CreateRay(CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY, 50, v.x * 200, v.y * 200, color);

		for (int i = 0; i < 16; i++) {
			CP_Vector v = AngleToVector(i * 23);
			CreateRay(x, y, 50, v.x, v.y , 0, color, false,100,false);
		}

		if (x + WorldX >= 0 && x + WorldX <= CP_System_GetWindowWidth() && y + WorldY >= 0 && y + WorldY <= CP_System_GetWindowHeight()) {
			CP_Sound_PlayAdvanced(ping, volume, 2, FALSE, 0);
		}

		cp_pingtimer = 0;

	}
}


void draw_checkpoint_1(void)
{
	
	point_1.pos.x = 1640;
	point_1.pos.y = 2235;
	point_1.pos = CP_Vector_Scale(point_1.pos, 2);
	point_1.w = 50;
	point_1.h = 50;

	//CP_Settings_NoStroke();
	//CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	//CP_Graphics_DrawRect(WorldX + point_1.x, WorldY + point_1.y, point_1.w, point_1.h);
	if (debug == 1) {
		CP_Settings_NoStroke();
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(WorldX + point_1.pos.x, WorldY + point_1.pos.y, point_1.w, point_1.h);
	}

	draw_checkpoint_ping(150, point_1.pos.x, point_1.pos.y + 25);

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));
	cp1_gate.pos1 = CP_Vector_Set(1634,1903);
	cp1_gate.pos1 = CP_Vector_Scale(cp1_gate.pos1, 2);
	cp1_gate.pos2 = CP_Vector_Set(1634, 2017);
	cp1_gate.pos2 = CP_Vector_Scale(cp1_gate.pos2, 2);
	//CP_Graphics_DrawLine(WorldX+cp1_gate.pos1.x, WorldY+cp1_gate.pos1.y, WorldX+cp1_gate.pos2.x, WorldY+cp1_gate.pos2.y);

}

void draw_checkpoint_2(void)
{

	point_2.pos.x = 2960;
	point_2.pos.y = 1375;
	point_2.pos = CP_Vector_Scale(point_2.pos, 2);
	point_2.w = 50;
	point_2.h = 50;

	//CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	//CP_Graphics_DrawRect(WorldX + point_2.x, WorldY + point_2.y, point_2.w, point_2.h);
	if (debug == 1) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(WorldX + point_2.pos.x, WorldY + point_2.pos.y, point_2.w, point_2.h);
	}

	draw_checkpoint_ping(150, point_2.pos.x, point_2.pos.y + 25);

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));
	cp2_gate.pos1 = CP_Vector_Set(2395, 1311);
	cp2_gate.pos1 = CP_Vector_Scale(cp2_gate.pos1, 2);
	cp2_gate.pos2 = CP_Vector_Set(2250, 1550);
	cp2_gate.pos2 = CP_Vector_Scale(cp2_gate.pos2, 2);
	//CP_Graphics_DrawLine(WorldX + cp2_gate.pos1.x, WorldY + cp2_gate.pos1.y, WorldX + cp2_gate.pos2.x, WorldY + cp2_gate.pos2.y);

}

void draw_checkpoint_3(void)
{
	point_3.pos.x = 540;
	point_3.pos.y = 1190;
	point_3.pos = CP_Vector_Scale(point_3.pos, 2);
	point_3.w = 50;
	point_3.h = 50;

	//CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	//CP_Graphics_DrawRect(WorldX + point_3.x, WorldY + point_3.y, point_3.w, point_3.h);
	if (debug == 1) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(WorldX + point_3.pos.x, WorldY + point_3.pos.y, point_3.w, point_3.h);
	}

	draw_checkpoint_ping(150, point_3.pos.x, point_3.pos.y + 25);

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));
	cp3_gate.pos1 = CP_Vector_Set(1810, 890);
	cp3_gate.pos1 = CP_Vector_Scale(cp3_gate.pos1, 2);
	cp3_gate.pos2 = CP_Vector_Set(1850, 1030);
	cp3_gate.pos2 = CP_Vector_Scale(cp3_gate.pos2, 2);
	//CP_Graphics_DrawLine(WorldX + cp3_gate.pos1.x, WorldY + cp3_gate.pos1.y, WorldX + cp3_gate.pos2.x, WorldY + cp3_gate.pos2.y);

}

void draw_exit(void)
{
	point_exit.pos.x = 2425;
	point_exit.pos.y = 247;
	point_exit.pos = CP_Vector_Scale(point_exit.pos, 2);
	point_exit.w = 300;
	point_exit.h = 200;

	draw_checkpoint_ping(150, point_exit.pos.x, point_exit.pos.y + 25);

	//CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	//CP_Graphics_DrawRect(WorldX + point_exit.x, WorldY + point_exit.y, point_exit.w, point_exit.h);

	if (debug == 1) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(WorldX + point_exit.pos.x, WorldY + point_exit.pos.y, point_exit.w, point_exit.h);
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


	if (CheckPointTrigger(point_1.pos.x, point_1.pos.y, point_1.w, point_1.h, x1, y1) == 1)
	{
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, 50));
		CP_Settings_TextSize(65.0f);
		CP_Font_DrawText("Press", 600, 725);

		CP_Color StartOutline = CP_Color_Create(150, 150, 150, 50);
		CP_Settings_Stroke(StartOutline);
		CP_Settings_Fill(CP_Color_Create(25, 25, 25, 50));
		//space
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRectAdvanced(1010, 700, 500.0f, 70.0f, 0, 10.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 20));
		CP_Graphics_DrawRectAdvanced(1010, 710, 150.0f, 5.0f, 0, 0.0f);

		if (CP_Input_KeyTriggered(KEY_SPACE))
		{
			CheckPoint_1_Triggered = 1;
			UndoWall();
			CP_Sound_PlayAdvanced(ping, volume, 2, FALSE, 0);
			CP_Color color = CP_Color_Create(255, 255, 0, 50);
			//CP_Vector v = AngleToVector(-90);
			//CreateRay(CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY, 50, v.x * 200, v.y * 200, color);
			checkpoint[0].current_checkpoint = 3;
			for (int i = 0; i < 36; i++) {
				CP_Vector v = AngleToVector(i * 10);
				CreateRay(3265, 3911, 50, v.x, v.y, 0, color, false, 100,false); // @TODO
			}
		}
		/*CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2 - 50.0f, CP_System_GetWindowHeight() / 2 + 20.0f, cp1_progress, 25.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 10));
		CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2 - 50.0f, CP_System_GetWindowHeight() / 2 + 20.0f, 100.0f, 25.0f);
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
		*/
	}

}

void cp2_triggered(void)
{
	float x1 = -WorldX + CP_System_GetWindowWidth() / 2;
	float y1 = -WorldY + CP_System_GetWindowHeight() / 2;
	if (CheckPointTrigger(point_2.pos.x, point_2.pos.y, point_2.w, point_2.h, x1, y1) == 1)
	{
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, 50));
		CP_Settings_TextSize(65.0f);
		CP_Font_DrawText("Press", 600, 725);

		CP_Color StartOutline = CP_Color_Create(150, 150, 150, 50);
		CP_Settings_Stroke(StartOutline);
		CP_Settings_Fill(CP_Color_Create(25, 25, 25, 50));
		//space
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRectAdvanced(1010, 700, 500.0f, 70.0f, 0, 10.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 20));
		CP_Graphics_DrawRectAdvanced(1010, 710, 150.0f, 5.0f, 0, 0.0f);

		if (CP_Input_KeyTriggered(KEY_SPACE))
		{
			CheckPoint_2_Triggered = 1;
			UndoWall();
			CP_Sound_PlayAdvanced(ping, volume, 2, FALSE, 0);
			CP_Color color = CP_Color_Create(255, 255, 0, 50);
			//CP_Vector v = AngleToVector(-90);
			//CreateRay(CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY, 50, v.x * 200, v.y * 200, color);
			checkpoint[0].current_checkpoint = 4;
			for (int i = 0; i < 36; i++) {
				CP_Vector v = AngleToVector(i * 10);
				CreateRay(5028, 2820, 50, v.x, v.y, 0, color, false, 100,false); //@TODO
			}
		}
	}
	/*
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

	}*/

}

void cp3_triggered(void)
{
	float x1 = -WorldX + CP_System_GetWindowWidth() / 2;
	float y1 = -WorldY + CP_System_GetWindowHeight() / 2;
	if (CheckPointTrigger(point_3.pos.x, point_3.pos.y, point_3.w, point_3.h, x1, y1) == 1)

	{
		CP_Settings_Fill(CP_Color_Create(120, 120, 120, 50));
		CP_Settings_TextSize(65.0f);
		CP_Font_DrawText("Press", 600, 725);

		CP_Color StartOutline = CP_Color_Create(150, 150, 150, 50);
		CP_Settings_Stroke(StartOutline);
		CP_Settings_Fill(CP_Color_Create(25, 25, 25, 50));
		//space
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRectAdvanced(1010, 700, 500.0f, 70.0f, 0, 10.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 20));
		CP_Graphics_DrawRectAdvanced(1010, 710, 150.0f, 5.0f, 0, 0.0f);
		checkpoint[0].current_checkpoint = 5;
		if (CP_Input_KeyTriggered(KEY_SPACE))
		{
			CheckPoint_3_Triggered = 1;
			UndoWall();
			CP_Sound_PlayAdvanced(ping, volume, 2, FALSE, 0);
			CP_Color color = CP_Color_Create(255, 255, 0, 50);
			//CP_Vector v = AngleToVector(-90);
			//CreateRay(CP_Input_GetMouseWorldX() - WorldX, CP_Input_GetMouseWorldY() - WorldY, 50, v.x * 200, v.y * 200, color);

			for (int i = 0; i < 36; i++) {
				CP_Vector v = AngleToVector(i * 10);
				CreateRay(1945, 2302, 50, v.x, v.y, 0, color, false, 100,false); //@TODO
			}
		}
	}
	/*
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

	}*/

}

void exit_triggered(void)
{
	float x1 = -WorldX + CP_System_GetWindowWidth() / 2;
	float y1 = -WorldY + CP_System_GetWindowHeight() / 2;


	if (CheckPointTrigger(point_exit.pos.x, point_exit.pos.y, point_exit.w, point_exit.h, x1, y1) == 1)
	{
		CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255));
		CP_Settings_TextSize(65.0f);
		CP_Font_DrawText("YOU WON!", CP_System_GetDisplayWidth()/2, CP_System_GetDisplayHeight() / 2);
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