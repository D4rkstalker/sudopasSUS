/*
Sound and music made by Nigel
*/

#include <cprocessing.h>

//sound variables

CP_Sound ping = NULL;
CP_Sound introsound = NULL;
CP_Sound bgm_submarine = NULL;
CP_Sound bonk = NULL;

void Sound_Init(void) {
	//initialise sound
	ping = CP_Sound_Load("ping.wav");
	introsound = CP_Sound_Load("introsound.wav");
	bgm_submarine = CP_Sound_Load("bgm_submarine.wav");
	bonk = CP_Sound_Load("bonk.wav");

	//initialise BGM
	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_MUSIC, 0.1);
	CP_Sound_PlayMusic((bgm_submarine));
}

void Sound_Deload(void) {
	//free sounds from memory
	CP_Sound_Free(&ping);
	CP_Sound_Free(&introsound);
	CP_Sound_Free(&bgm_submarine);
	CP_Sound_Free(&bonk);
}
