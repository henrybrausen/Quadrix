#ifndef __CTITLESTATE_H__
#define __CTITLESTATE_H__

#include "cGameState.h"
#include <vector>
#include <deque>
#include "cSprite.h"
#include "cGlobals.h"
#include "cParticle.h"

class cTitleState : public cGameState {
public:
	cTitleState(SDL_Surface *screen) : cGameState(screen) {initialize();}
	virtual ~cTitleState() { cleanup(); }

	virtual const std::string instanceof() const { return "cTitleState"; }

	virtual bool initialize();
	virtual void process();
	virtual void render();
	virtual void cleanup();

private:
	SDL_Surface *background;
};

#endif
