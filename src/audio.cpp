// Thanks to Tantric + Wiilibgui for supplying some of the code

#include <gccore.h>
#include <ogcsys.h>
#include <asndlib.h>

void InitAudio()
{
	AUDIO_Init(NULL);
	ASND_Init();
	ASND_Pause(0);
}

void ShutdownAudio()
{
	ASND_Pause(1);
	ASND_End();
}
