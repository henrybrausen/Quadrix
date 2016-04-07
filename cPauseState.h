#ifndef __CPAUSESTATE_H__
#define __CPAUSESTATE_H__

#include "cGameState.h"
#include "cGlobals.h"

class cPauseState : public cGameState {
public:
	cPauseState(SDL_Surface *screen) : cGameState(screen) {initialize();}
	virtual ~cPauseState() { cleanup(); }

	virtual const std::string instanceof() const { return "cPauseState"; }

	virtual bool initialize();
	virtual void process();
	virtual void render();
	virtual void cleanup();

private:
	SDL_Surface *bg;
	SDL_Surface *msg;
};

#endif
