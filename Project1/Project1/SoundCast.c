
#include <cprocessing.h>
#include <stdbool.h>
#include "SoundCast.h"
#include "game.h"
#include <math.h>
const float EPSILON = 0.0000001f;

Wall* walls;
int maxWalls;


Particle particles[MAXPARTICLES];
int particleCount = 0;
Ray rays[MAXRAYS];
int rayCount = 0;

Particle CreateParticle( float x, float y, float velx, float vely, CP_Color color, bool isStatic, bool head, bool tail) {
	//if (particleCount > 10) {
	//	particleCount = 0;
	//}
	Particle part = particles[particleCount];
	particleCount++;
	if (particleCount > MAXPARTICLES) {
		particleCount = 0;
	}
	part.pos.x = x;
	part.pos.y = y;
	part.vel.x = velx;
	part.vel.y = vely;
	part.color = color;
	part.isStatic = isStatic;
	part.isHead = head;
	part.isTail = tail;
	return part;
}

void AddMidpoint(Ray* ray, int posx, int posy) {
	Particle part = CreateParticle(posx, posy, 0, 0, ray->color, true, false, false);
	ray->midpoints[ray->mids] = part;
	ray->mids++;
	//if (ray->mids > MAXBOUNCES) {
	//	ray->mids = 0;
	//}
}

void RemoveMidpoint(Ray* ray) {
	ray->midpoints[ray->trail].color.a = 0;
	ray->trail++;
	//if (ray->trail > MAXBOUNCES) {
	//	ray->trail = 0;
	//}

}

void CreateRay(float x, float y, int length, int velx, int vely, CP_Color color) {
	Ray* ray = &rays[rayCount];

	ray->color = color;

	Particle head = CreateParticle(x, y, velx, vely, ray->color, false, true, false);
	Particle tail = CreateParticle(x, y, velx, vely, ray->color, true, false, true);
	ray->mids = 0;
	ray->trail = 0;

	ray->head = head;
	ray->tail = tail;
	ray->maxLength = length;
	rayCount++;
}


void ParticleDisplay(Particle* part, int size)
{
	CP_Graphics_DrawEllipse(part->pos.x, part->pos.y, size, size);
}

float CalcArea(float pos1, float pos2, float pos3) {
	//abs((x1 - px) * (y2 - py) - (x2 - px) * (y1 - py));
}

int CheckCollision(Ray* ray, CP_Vector newPos) {
	for (int i = 0; i < maxWalls; i++) {

	}
}

void ParticleUpdate(Particle* part, Ray* ray)
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

		CP_Vector newPos = CP_Vector_Set(part->pos.x + part->vel.x * time, part->pos.y + part->vel.y * time);
		float newTime = time;
		//if (CheckCollision != -1) {

		//}
		//else
		//{
			// no collision
			part->pos.x = newPos.x;
			part->pos.y = newPos.y;
			time = 0;
		//}
	}

//// resolve collisions
//if ((collisionX == true) || (collisionY == true))
//{

//	// take the nearest time
//	if (timeX < timeY)
//	{
//		newTime = timeX;
//	}
//	else
//	{
//		newTime = timeY;
//	}

//	// move the particle
//	part->pos.x += part->vel.x * newTime;
//	part->pos.y += part->vel.y * newTime;

//	// flip velocity vectors to reflect off walls
//	if ((collisionX == true) && (collisionY == false))
//	{
//		part->vel.x *= -1;
//	}
//	else if ((collisionX == false) && (collisionY == true))
//	{
//		part->vel.y *= -1;
//	}
//	else
//	{	// they must both be colliding for this condition to occur
//		if (timeX < timeY)
//		{
//			part->vel.x *= -1;
//		}
//		else if (timeX > timeY)
//		{
//			part->vel.y *= -1;
//		}
//		else
//		{	// they must be colliding at the same time (ie. a corner)
//			part->vel.x *= -1;
//			part->vel.y *= -1;
//		}
//	}

//	// decrease time and iterate
//	time -= newTime;
//	if (part->isHead) {
//		AddMidpoint(ray, part->pos.x, part->pos.y);

//	}
//	else {
//		RemoveMidpoint(ray);
//	}

//}

}
void _RayUpdate(Ray* ray) {
	if (ray->color.a < 1) return;
	if (ray->length < ray->maxLength) {
		ray->length++;
	}
	else {
		ray->tail.isStatic = false;
	}
	ParticleUpdate(&ray->head, ray);
	ParticleUpdate(&ray->tail, ray);
	CP_Settings_NoStroke();
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_BlendMode(CP_BLEND_ADD);
	CP_Settings_StrokeWeight(3);
	CP_Settings_Stroke(ray->color);
	if (ray->mids - ray->trail == 1) {
		CP_Graphics_DrawLine(ray->head.pos.x, ray->head.pos.y, ray->midpoints[ray->trail].pos.x, ray->midpoints[ray->trail].pos.y);
		CP_Graphics_DrawLine(ray->midpoints[ray->trail].pos.x, ray->midpoints[ray->trail].pos.y, ray->tail.pos.x, ray->tail.pos.y);

	}

	else if (ray->mids - ray->trail > 1) {
		CP_Graphics_DrawLine(ray->head.pos.x, ray->head.pos.y, ray->midpoints[ray->mids - 1].pos.x, ray->midpoints[ray->mids - 1].pos.y);

		for (int i = 1; i < ray->mids - ray->trail; i++) {
			CP_Graphics_DrawLine(ray->midpoints[ray->trail].pos.x, ray->midpoints[ray->trail].pos.y, ray->midpoints[ray->trail + i].pos.x, ray->midpoints[ray->trail + i].pos.y);
		}
		CP_Graphics_DrawLine(ray->midpoints[ray->trail].pos.x, ray->midpoints[ray->trail].pos.y, ray->tail.pos.x, ray->tail.pos.y);

	}
	else {
		CP_Graphics_DrawLine(ray->head.pos.x, ray->head.pos.y, ray->tail.pos.x, ray->tail.pos.y);

	}
	ray->color.a--;
}
void RayUpdate() {
	for (int i = 0; i < rayCount; ++i)
	{
		_RayUpdate(&rays[i]);
	}
	
}

void InitScene(Wall* _walls, int _maxWalls) {
	walls = _walls;
	maxWalls = _maxWalls;
}


