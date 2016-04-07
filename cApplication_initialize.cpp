#include "cApplication.h"
#include "cTetrisState.h"
#include "cTitleState.h"
#include "cGlobals.h"

bool cApplication::initialize()
{
	/* Initialize Libraries */
	if(SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
		return false;
	}

	if((mScreen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, SCREEN_BPP, SDL_HWSURFACE|SDL_DOUBLEBUF)) == NULL) {
		fprintf(stderr, "Could not set video mode (%dx%d, bpp=%d): %s\n", SCREEN_W, SCREEN_H, SCREEN_BPP, SDL_GetError());
		return false;
	}

	if(Mix_OpenAudio(AUDIO_SAMPLERATE, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_BUFFER) != 0) {
		fprintf(stderr, "Could not initialize SDL_Mixer: %s\n", Mix_GetError());
		return false;
	}
	if(TTF_Init() < 0) {
		fprintf(stderr, "Could not initialize SDL_TTF: %s\n", TTF_GetError());
		return false;
	}

	//cFontManager::load_font("vera", "Vera.ttf", 20);
	cFontManager::load_font("monospace", "rsc/fonts/monospace.ttf", 18);
	cFontManager::load_font("monospace10", "rsc/fonts/monospace.ttf", 10);
	cSoundManager::add_sound("bump", new cSoundResource("rsc/sounds/bump.ogg"));
	cSoundManager::add_sound("fall", new cSoundResource("rsc/sounds/fall.ogg"));
	cSoundManager::add_sound("row", new cSoundResource("rsc/sounds/row.ogg"));
	cSoundManager::add_sound("loss", new cSoundResource("rsc/sounds/loss.ogg"));
	cSoundManager::add_sound("rotate", new cSoundResource("rsc/sounds/rotate.ogg"));
	cSoundManager::add_sound("move", new cSoundResource("rsc/sounds/move.ogg"));
	cMusicManager::add_track("mirage", Mix_LoadMUS("rsc/music/mirage.ogg"));
	cMusicManager::add_track("tetris", Mix_LoadMUS("rsc/music/tetris.ogg"));

	//cSoundManager::add_sound("zap", new cSoundResource("zap.wav"));
	//cMusicManager::add_track("db_pdx3", Mix_LoadMUS("db_pdx3.xm"));
	//cMusicManager::add_track("scarabi", Mix_LoadMUS("scarabi.wav"));
	//cMusicManager::add_track("epic", Mix_LoadMUS("epic.xm"));

	mStates.push(dynamic_cast<cGameState*>(new cTitleState(mScreen)));

	return true;
}
