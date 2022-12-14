/*
All content ? 2021 DigiPen Institute of Technology Singapore, all rights reserved.


Sound and BGM made by Nigel
*/

#include <cprocessing.h>

//sound variables

float volume = 0.3f;

CP_Sound ping = NULL;
CP_Sound introsound = NULL;
CP_Sound bonk = NULL;
CP_Sound rip = NULL;
CP_Sound creepyping = NULL;

CP_Sound bgm_submarine = NULL;
CP_Sound bgm_theenemy = NULL;

//CP_Sound_PlayAdvanced(bonk, volume, 1, FALSE, 1);

void Sound_Init(void) {
	//initialise sound
	ping = CP_Sound_Load("../Assets/ping.wav") != NULL ? CP_Sound_Load("../Assets/ping.wav") : CP_Sound_Load("Assets/ping.wav");
	introsound = CP_Sound_Load("../Assets/introsound.wav") != NULL ? CP_Sound_Load("../Assets/introsound.wav") : CP_Sound_Load("Assets/introsound.wav");
	bonk = CP_Sound_Load("../Assets/bonk.wav") != NULL ? CP_Sound_Load("../Assets/bonk.wav") : CP_Sound_Load("Assets/bonk.wav");
	rip = CP_Sound_Load("../Assets/rip.wav") != NULL ? CP_Sound_Load("../Assets/rip.wav") : CP_Sound_Load("Assets/rip.wav");
	creepyping = CP_Sound_Load("../Assets/creepyping.wav") != NULL ? CP_Sound_Load("../Assets/creepyping.wav") : CP_Sound_Load("Assets/creepyping.wav");

	bgm_submarine = CP_Sound_Load("../Assets/bgm_submarine.wav") != NULL ? CP_Sound_Load("../Assets/bgm_submarine.wav") : CP_Sound_Load("Assets/bgm_submarine.wav");

	//initialise BGM
	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_MUSIC, 0.1f);
	CP_Sound_PlayMusic((bgm_submarine));
	//CP_Sound_PlayMusic((bgm_theenemy));
	//CP_Sound_PlayAdvanced(creepyping, volume, 1, FALSE, 0);
}

void Sound_Deload(void) {
	//free sounds from memory
	CP_Sound_Free(&ping);
	CP_Sound_Free(&introsound);
	CP_Sound_Free(&bonk);
	CP_Sound_Free(&rip);
	CP_Sound_Free(&creepyping);

	CP_Sound_Free(&bgm_submarine);
}
