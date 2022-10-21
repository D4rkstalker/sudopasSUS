
#include <cprocessing.h>
#include <stdbool.h>
#define MAXRAYS 1000
#define MAXBOUNCES 20
#define MAXPARTICLES 3000
const float EPSILON = 0.0000001f;

typedef struct _Particle
{
	CP_Vector pos;
	CP_Vector vel;
	CP_Color color;
	bool isStatic;
	bool isHead;
	bool isTail;
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
			if (part->isHead) {
				AddMidpoint(ray, part->pos.x, part->pos.y);

			}
			else {
				RemoveMidpoint(ray);
			}

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
void _RayUpdate(Ray* ray) {
	if (ray->color.a < 1) return;
	if (ray->length < ray->maxLength) {
		ray->length++;
	}
	else {
		ray->tail.isStatic = false;
	}
	ParticleUpdate(&ray->head, ray, true);
	ParticleUpdate(&ray->tail, ray, false);
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
void RayUpdate(int i) {
	for (int i = 0; i < rayCount; ++i)
	{
		_RayUpdate(&rays[i]);
	}

}


