#include "cTitleState.h"
#include "cSurface.h"
#include "cGlobals.h"

bool cTitleState::initialize()
{
	background = cSurface::load("rsc/images/title.bmp");
	return true;
}

void cTitleState::process()
{
}

void cTitleState::render()
{
	cSurface::draw(mScreen, background, 0, 0);
}

void cTitleState::cleanup()
{
	SDL_FreeSurface(background);
}
