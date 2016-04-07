#ifndef __CGAMESTATE_H__
#define __CGAMESTATE_H__

#include <SDL.h>
#include <string>
#include "cEventHandler.h"

/* Parent class for all game states */
class cGameState : public cEventHandler {
public:
	cGameState(SDL_Surface *screen) : mScreen(screen) {}
	virtual ~cGameState() {}

	virtual const std::string instanceof() const = 0;

	virtual bool initialize() = 0;
	virtual void process() = 0;
	virtual void render() = 0;

	virtual void cleanup() = 0;

	SDL_Surface *mScreen;
};

#endif
