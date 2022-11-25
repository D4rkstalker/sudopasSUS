void newtutorial_init(void);
void newtutorial_update(void);
void newtutorial_exit(void);

float totalElapsedTime;
int tut_ping_timer;
int can_move;

enum tutorial_stages {
	Tut_Player, Tut_Move, Tut_Scan, Tut_Beam, Tut_CP, Enemy_Spawn, Enemy_Move, Enemy_Sound, Enemy_Kill, Enemy_Leave
} tut_stage;

enum Enemy_sound_stages {
	Sound_Attract, Sound_Distract, Sound_Trigger
}sound_stage;

int time;
int delay;
int countdown;

struct player {
	float x;
	float y;
}player;