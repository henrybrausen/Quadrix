#ifndef __CAPPLICATION_H__
#define __CAPPLICATION_H__

// Video output properties
#define SCREEN_W 420
#define SCREEN_H 500
#define SCREEN_BPP 32


#define FRAMES_PER_SECOND 60

// Audio output properties
#define AUDIO_SAMPLERATE 44100
#define AUDIO_FORMAT AUDIO_U16SYS
#define AUDIO_CHANNELS 2
#define AUDIO_BUFFER 1024

#include <SDL.h>
#include <SDL_mixer.h>
#include <stack>

#include "cFrameRateManager.h"
#include "cSoundManager.h"
#include "cMusicManager.h"
#include "cFontManager.h"
#include "cEventHandler.h"
#include "cSurface.h"
#include "cSprite.h"
#include "cPlayer.h"
#include "cGameState.h"

class cApplication : public cEventHandler {
public:
	cApplication() : mScreen(NULL), mIsRunning(true) {}
	int execute();

private:
	bool initialize();
	void handle_event(const SDL_Event& inEvent);
	void process();
	void render();

	void cleanup();

// -------- cEventHandler overrides --------
	void on_key_down(SDLKey inSym, SDLMod inMod, Uint16 unicode);
	void on_key_up(SDLKey inSym, SDLMod inMod, Uint16 unicode);
	void on_exit();

private:
	SDL_Surface *mScreen;
	//SDL_Surface *stars;
	bool mIsRunning;
	//std::vector<cSprite*> mSprites;
	std::stack<cGameState*> mStates;
};

#endif
