#include <windows.h>
#include "cprocessing.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define _USE_MATH_DEFINES
#include <math.h>

CP_Image logo;

const float EPSILON = 0.0000001f;

float particleSize = 3.0f;

int particleCount = 0;
int raycount = 0;

int numParticles = 240;

float lineProximityDistance = 100.0f;
float mouseProximityDistance = 200.0f;

int recommendedWidth = 1600;
int recommendedHeight = 900;

bool drawColors = true;
bool drawFPS = true;



typedef struct _Particle
{
	CP_Vector pos;
	CP_Vector vel;
	CP_Color* color;
	bool isStatic;
} Particle;

Particle particles[240];

typedef struct _Ray
{
	Particle head;
	Particle mid;
	Particle tail;
	CP_Color* color;
	bool hasMid;
} Ray;

Ray rays[1];

CP_Color randomColors[] = {
	{ 127, 0,   0,   255 },
	{ 127, 127, 0,   255 },
	{ 0,   127, 0,   255 },
	{ 0,   127, 127, 255 },
	{ 0,   0,   127, 255 },
	{ 127, 0,   127, 255 } };

void CreateRay(float x, float y) {
	Ray* ray = &rays[raycount];
	raycount++;
	int velocityx = CP_Random_RangeFloat(-550, 550);
	int velocityy = CP_Random_RangeFloat(-550, 550);
	Particle head;
	Particle tail;
	head.vel.x = velocityx;
	head.vel.y = velocityy;
	tail.vel.x = velocityx;
	tail.vel.y = velocityy;

	head.pos.x = x;
	head.pos.y = y;
	tail.pos.x = x - velocityx;
	tail.pos.y = y - velocityy;

	head.isStatic = false;
	tail.isStatic = false;

	ray->hasMid = false;

	ray->head = head;
	ray->tail = tail;

	ray->color = &randomColors[CP_Random_RangeInt(0, 5)];
}
void CreateMidRay(float x, float y, Particle head, Particle tail, Ray* ray) {
	raycount++;
	Particle mid;
	mid.vel.x = 0;
	mid.vel.y = 0;

	mid.pos.x = x;
	mid.pos.y = y;

	mid.isStatic = true;
	mid.color = head.color;

	ray->head = head;
	ray->mid = mid;
	ray->tail = tail;

	ray->color = head.color;
	ray->hasMid = true;
}


void CreateParticle(float x, float y, CP_Color* color, bool isStatic) {
	//if (particleCount > 10) {
	//	particleCount = 0;
	//}
	Particle* part = &particles[particleCount];
	particleCount++;
	part->pos.x = x;
	part->pos.y = y;
	part->vel.x = 0;
	part->vel.y = 0;
	part->color = color;
	part->isStatic = isStatic;
}

void ParticleDisplay(Particle* part)
{
	CP_Graphics_DrawEllipse(part->pos.x, part->pos.y, particleSize, particleSize);
}


void ParticleUpdate(Particle* part, Ray* ray, bool head)
{
	// move particle based on velocity and correct for wall collisions
	if (part->isStatic) {
		return;
	}
	float time = CP_System_GetDt();
	float timeX = time;
	float timeY = time;

	while (time > EPSILON)
	{
		bool collisionX = false;
		bool collisionY = false;
		//part->vel.y += 3;

		float newPosX = part->pos.x + part->vel.x * time;
		float newPosY = part->pos.y + part->vel.y * time;
		float newTime = time;

		// check wall collisions X and Y
		if (newPosX <= 0)
		{
			timeX = part->pos.x / (part->pos.x - newPosX) * time;
			collisionX = true;
		}
		else if (newPosX >= CP_System_GetWindowWidth())
		{
			timeX = (CP_System_GetWindowWidth() - part->pos.x) / (newPosX - part->pos.x) * time;
			collisionX = true;
		}

		if (newPosY <= 0)
		{
			timeY = part->pos.y / (part->pos.y - newPosY) * time;
			collisionY = true;
		}
		else if (newPosY >= CP_System_GetWindowHeight())
		{
			timeY = (CP_System_GetWindowHeight() - part->pos.y) / (newPosY - part->pos.y) * time;
			collisionY = true;
		}

		// resolve collisions
		if ((collisionX == true) || (collisionY == true))
		{

			// take the nearest time
			if (timeX < timeY)
			{
				newTime = timeX;
			}
			else
			{
				newTime = timeY;
			}

			// move the particle
			part->pos.x += part->vel.x * newTime;
			part->pos.y += part->vel.y * newTime;

			// flip velocity vectors to reflect off walls
			if ((collisionX == true) && (collisionY == false))
			{
				part->vel.x *= -1;
			}
			else if ((collisionX == false) && (collisionY == true))
			{
				part->vel.y *= -1;
			}
			else
			{	// they must both be colliding for this condition to occur
				if (timeX < timeY)
				{
					part->vel.x *= -1;
				}
				else if (timeX > timeY)
				{
					part->vel.y *= -1;
				}
				else
				{	// they must be colliding at the same time (ie. a corner)
					part->vel.x *= -1;
					part->vel.y *= -1;
				}
			}

			// decrease time and iterate
			time -= newTime;
			CreateMidRay(part->pos.x, part->pos.y, ray->head, ray->tail, ray);

		}
		else
		{
			// no collision
			part->pos.x = newPosX;
			part->pos.y = newPosY;
			time = 0;
		}
	}
}

void RayUpdate(Ray* ray) {
	ParticleUpdate(&ray->head, ray, true);
	ParticleUpdate(&ray->tail, ray, false);
	CP_Settings_NoStroke();
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_BlendMode(CP_BLEND_ADD);
	CP_Settings_StrokeWeight(3);
	CP_Color lineColor = randomColors[CP_Random_RangeInt(0, 5)];;
	CP_Settings_Stroke(lineColor);
	if (!ray->hasMid) {
		CP_Graphics_DrawLine(ray->head.pos.x, ray->head.pos.y, ray->tail.pos.x, ray->tail.pos.y);

	}
	else {
		CP_Graphics_DrawLine(ray->head.pos.x, ray->head.pos.y, ray->mid.pos.x, ray->mid.pos.y);
		CP_Graphics_DrawLine(ray->mid.pos.x, ray->mid.pos.y, ray->tail.pos.x, ray->tail.pos.y);

	}
}


void game_init(void)
{
	logo = CP_Image_Load("Assets/DigiPen_Singapore_WEB_RED.png");
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	/*for (int i = 0; i < numParticles; ++i) {
		ParticleCreate(&particles[i]);
	}*/

	CP_System_SetWindowSize(1920, 1080);
}

void game_update(void)
{
	CP_Settings_BlendMode(CP_BLEND_ALPHA);
	CP_Graphics_ClearBackground(CP_Color_Create(51, 51, 51, 255));

	if (CP_Input_MouseClicked()) {
		CreateRay(CP_Input_GetMouseWorldX(), CP_Input_GetMouseWorldY());

	}

	//background(CP_Color_Create((int)(CP_Input_GetMouseX() / canvasWidth * 255.0f), 0, 0, 255));
	//CP_Graphics_Background(CP_CreateColor((int)(CP_Input_GetMouseX() / CP_Graphics_GetCanvasWidth() * 255.0f), 0, 0, 255));


	for (int i = 0; i < raycount; ++i)
	{
		RayUpdate(&rays[i]);
		//ParticleDisplay(&particles[i]);
	}


	// Profiling info and frameRate testing
	if (drawFPS)
	{
		CP_Settings_TextSize(20);
		CP_Settings_BlendMode(CP_BLEND_ALPHA);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 128));
		CP_Settings_NoStroke();
		CP_Graphics_DrawRect(0, 0, 150, 30);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		char buffer[100];
		sprintf_s(buffer, 100, "FPS: %f", CP_System_GetFrameRate());
		CP_Font_DrawText(buffer, 20, 20);
	}
	//CP_Image_Draw(logo, 0.f, 0.f, CP_Image_GetWidth(logo), CP_Image_GetHeight(logo), 255);
	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
	}

}

void game_exit(void)
{
	CP_Image_Free(&logo);
}




int main(void)
{
	//CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}