#pragma once
#include <cprocessing.h>

typedef struct _Particle {}Particle;
typedef struct _Ray {}Ray;
Particle CreateParticle(float x, float y, float velx, float vely, CP_Color color, bool isStatic, bool head, bool tail);

void AddMidpoint(Ray* ray, int posx, int posy);
void RemoveMidpoint(Ray* ray);
void RayUpdate(Ray* ray);
void CreateRay(float x, float y, int length, int velx, int vely);
void ParticleDisplay(Particle* part, int size);
void ParticleUpdate(Particle* part, Ray* ray);

