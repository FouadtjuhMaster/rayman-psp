//Rayman PSP
//Created: 30/07/2010
//Authors: Equilibrium369 & Phoebius

#include <oslib/oslib.h>
#include "global.c"
#include "Engine/string.c"
#include "Engine/display.c"
#include "Engine/level.c"
#include "Engine/rayman.c"

PSP_MODULE_INFO("Rayman PSP", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);


int main()
{
	oslInit(0);
	oslInitGfx(OSL_PF_8888, 1);
	oslInitAudio();
	LoadImages();
	
	//World Select Screen
	Background_Music = oslLoadSoundFile("Audio/Music0.bgm", OSL_FMT_STREAM);
	if (!Background_Music){oslDebug("Unable to load background music.");}
	oslSetSoundLoop(Background_Music, 1);
	oslPlaySound(Background_Music, 0);
  while (!osl_quit){
		oslReadKeys();
    if (osl_keys->held.cross){
      Screen = 1;
      break;
    }
		UpdateDisplay();
		oslAudioVSync();
	}

	//Load Game
	NewAnimation(0, 0, 64, 68, 14, 47500, 1);
	NewAnimation(0, 5, 64, 68, 16, 29000, 1);
	LoadLevel("Test Level.txt");
	Background_Music = oslLoadSoundFile("Audio/Music1.bgm", OSL_FMT_STREAM);
	if (!Background_Music){oslDebug("Unable to load background music.");}
	oslSetSoundLoop(Background_Music, 1);
	oslPlaySound(Background_Music, 0);
	SetAnimation(0);
	SetX(10);
	SetY(175);

  //Main Game Loop
	while (!osl_quit){
		oslReadKeys();

		if (osl_keys->held.left){
			Rayman_Direction = 0;
			SetAnimation(1);
			MoveX(-2);
		} else if (osl_keys->held.right){
			Rayman_Direction = 1;
			SetAnimation(1);
			MoveX(2);
		} else{
			SetAnimation(0);
		}

    AdjustCamera();
    ScrollBackground();
		UpdateDisplay();
		oslAudioVSync();
	}

	oslEndGfx();
	oslQuit();
	return 0;
}
