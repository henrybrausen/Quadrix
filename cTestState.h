#ifndef __CTESTSTATE_H__
#define __CTESTSTATE_H__

#include "cGameState.h"
#include <vector>
#include <deque>
#include "cSprite.h"
#include "cGlobals.h"
#include "cParticle.h"

class cTestState : public cGameState {
public:
	cTestState(SDL_Surface *screen) : cGameState(screen) {initialize();}
	virtual ~cTestState() { cleanup(); }
	virtual bool initialize();
	virtual void process();
	virtual void render();
	virtual void cleanup();

	void on_key_down(SDLKey inSym, SDLMod inMod, Uint16 unicode);

private:
	bool ai;
	SDL_Surface *layer0;
	SDL_Surface *layer1;
	std::vector<SDL_Surface *> pImgs;
	std::deque<cParticle *> mParticles;
	cSprite* player;
	double scroll0, scroll1;
	Uint32 mPT;
	bool mDP;
	tInteractionList interactionList;
};

#endif
