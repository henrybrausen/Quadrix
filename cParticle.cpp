#include "cParticle.h"
#include "cFrameRateManager.h"
#include "cSurface.h"

void cParticle::process()
{
	Uint32 now = SDL_GetTicks();
	mLifeRemaining -= (now-mLastTime);
	mLastTime = now;
	if (mLifeRemaining < 0) { kill(); }
	mX += mVX*cFrameRateManager::get_factor();
	mY += mVY*cFrameRateManager::get_factor();
}

void cParticle::render(SDL_Surface *screen)
{
	if(!is_dead()) {
		//get_bg(screen);
		cSurface::draw(screen, mImg, static_cast<Sint16>(mX), static_cast<Sint16>(mY));
	}
}
