
#include <cprocessing.h>
#include <stdbool.h>
#include "SoundCast.h"
#include "game.h"
#include <math.h>
#include "utils.h"
#define PI 3.141592654
#include "walls.h"

const float EPSILON = 0.0000001f;



Particle particles[MAXPARTICLES];
int particleCount = 0;
Ray rays[MAXRAYS];
int rayCount = 0;

float wx;
float wy;

Particle CreateParticle(float x, float y, float velx, float vely, CP_Color color, bool isStatic, bool head, bool tail) {
	//if (particleCount > 10) {
	//	particleCount = 0;
	//}
	Particle part = particles[particleCount];
	particleCount++;
	if (particleCount > MAXPARTICLES) {
		particleCount -= MAXPARTICLES;
	}
	part.pos.x = x;
	part.pos.y = y;
	part.vel.x = velx;
	part.vel.y = vely;
	part.color = color;
	part.isStatic = isStatic;
	part.isHead = head;
	part.isTail = tail;
	part.collide = true;
	part.prevID = -1;
	return part;
}

void AddMidpoint(Ray* ray, int posx, int posy) {
	Particle part = CreateParticle(posx, posy, ray->head.vel.x, ray->head.vel.y, ray->color, true, false, false);
	ray->midpoints[ray->mids] = part;
	ray->mids++;
	if (ray->mids > MAXBOUNCES) {
		ray->mids -= MAXBOUNCES;
	}
}

void RemoveMidpoint(Ray* ray) {

	ray->midpoints[ray->trail].color.a = 0;
	ray->tail.vel = ray->midpoints[ray->trail].vel;
	ray->trail++;
	if (ray->trail > MAXBOUNCES) {
		ray->trail -= MAXBOUNCES;
	}

}

void CreateRay(float x, float y, int length, int velx, int vely, int fade, CP_Color color) {
	Ray ray = {0};
	ray.color = color;
	Particle head = CreateParticle(x, y, velx, vely, ray.color, false, true, false);
	Particle tail = CreateParticle(x, y, velx, vely, ray.color, true, false, true);
	ray.mids = 0;
	ray.trail = 0;

	ray.head = head;
	ray.tail = tail;
	ray.fadeStrength = fade;
	ray.maxLength = length;
	rays[rayCount] = ray;
	rayCount++;
	if (rayCount > MAXRAYS) {
		rayCount -= MAXRAYS;
	}
}


void ParticleDisplay(Particle* part, int size)
{
	CP_Graphics_DrawEllipse(part->pos.x + wx, part->pos.y + wy, size, size);
}


bool CheckCollision(Ray* ray, Particle* part, CP_Vector* newPos, float* time) {
	for (int i = 0; i < CWall; i++) {

		if ((CP_Math_Distance(wall[i].pos1.x, wall[i].pos1.y, wall[i].pos2.x, wall[i].pos2.y)
			- CP_Math_Distance(wall[i].pos1.x, wall[i].pos1.y, part->pos.x, part->pos.y)
			- CP_Math_Distance(wall[i].pos2.x, wall[i].pos2.y, part->pos.x, part->pos.y)) > -FUZZYNESS && part->prevID != i || CP_Math_Distance(wall[i].pos1.x, wall[i].pos1.y, part->pos.x, part->pos.y) <2* FUZZYNESS || CP_Math_Distance(wall[i].pos2.x, wall[i].pos2.y, part->pos.x, part->pos.y) < 2*FUZZYNESS){
			part->prevID = i;


			CP_Vector Vwall = CP_Vector_Normalize(CP_Vector_Subtract(wall[i].pos2, wall[i].pos1));
			CP_Vector Vray = CP_Vector_Normalize(CP_Vector_Subtract(*newPos, part->pos));
			float temp = Vwall.x;
			Vwall.x = -Vwall.y;
			Vwall.y = temp;
			CP_Vector vOut = CP_Vector_Add(CP_Vector_Scale(Vwall, -2 * CP_Vector_DotProduct(Vray, Vwall)), Vray);

			part->vel = vOut;
			part->vel = CP_Vector_Scale(part->vel, 200);
			*newPos = CP_Vector_Set(part->pos.x + part->vel.x * *time, part->pos.y + part->vel.y * *time);
			part->collide = false;
			return true;
		}
	}
	return false;
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
		if (CheckCollision(ray, part, &newPos, &time)) {
			if (part->isHead) {
				AddMidpoint(ray, part->pos.x, part->pos.y);

			}
			else {
				RemoveMidpoint(ray);
			}

		};
		part->pos.x = newPos.x;
		part->pos.y = newPos.y;
		time = 0;

	}


}

void DrawRay(CP_Vector v1, CP_Vector v2) {
	CP_Graphics_DrawLine(v1.x + wx, v1.y + wy, v2.x + wx, v2.y + wy);
}
void _RayUpdate(Ray* ray) {
	if (ray->color.a <= ray->fadeStrength) return;
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
		DrawRay(ray->head.pos, ray->midpoints[ray->trail].pos);
		DrawRay(ray->midpoints[ray->trail].pos, ray->tail.pos);

	}

	else if (abs(ray->mids - ray->trail) > 1) {
		DrawRay(ray->head.pos, ray->midpoints[ray->mids - 1].pos);
		if (ray->mids < ray->trail) {
			for (int i = ray->trail; i < MAXBOUNCES -1; i++) {
				DrawRay(ray->midpoints[i].pos, ray->midpoints[i + 1].pos);
			}
			for (int i = 0; i < ray->mids -1; i++) {
				DrawRay(ray->midpoints[i].pos, ray->midpoints[i + 1].pos);
			}

		}
		else {
			for (int i = ray->trail; i < ray->mids - 1; i++) {
				DrawRay(ray->midpoints[i].pos, ray->midpoints[i + 1].pos);
			}
		}
		DrawRay(ray->midpoints[ray->trail].pos, ray->tail.pos);

	}
	else {
		DrawRay(ray->head.pos, ray->tail.pos);

	}
	ray->color.a -= ray->fadeStrength;
}
void RayUpdate(float _wx, float _wy) {
	wx = _wx;
	wy = _wy;
	for (int i = 0; i < rayCount; ++i)
	{
		_RayUpdate(&rays[i]);
	}

}



