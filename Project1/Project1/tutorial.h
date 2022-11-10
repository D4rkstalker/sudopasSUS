#include <cprocessing.h>
#pragma once


void title_screen(void);
void tutorial_message(void);
void enemy_tutorial(void);
void wake_message(void);
void rmb_tut(void);
void dodge(void);
void tut_exit(void);

int tutorial_state;

/*typedef struct message {
	float alpha;
	float duration;
	float timer;
	float min;
	float max;
	int loop;
} message; */



float EaseInQuad(float start, float end, float value);
float EaseOutQuad(float start, float end, float value);
