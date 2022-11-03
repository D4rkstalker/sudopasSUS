#include <stdbool.h>
#include "game.h"
#include "walls.h"
#pragma once

#define MAXRAYS 10000
#define MAXBOUNCES 20
#define MAXPARTICLES 3000

typedef struct _Particle
{
	CP_Vector pos;
	CP_Vector vel;
	CP_Color color;
	bool isStatic;
	bool isHead;
	bool isTail;
	bool collide;

} Particle;

typedef struct _Ray
{
	Particle head;
	Particle midpoints[MAXBOUNCES];
	Particle tail;
	CP_Color color;
	int length;
	int maxLength;
	int mids;
	int trail;
} Ray;
void InitScene(Wall* _walls, int _maxWalls);

void RayUpdate(float wx, float wy);
void CreateRay(float x, float y, int length, int velx, int vely, CP_Color color);

