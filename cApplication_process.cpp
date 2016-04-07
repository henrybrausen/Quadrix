#include "cApplication.h"
#include "cFrameRateManager.h"

void cApplication::process()
{
	mStates.top()->process();
	//if((int)(1000*cFrameRateManager::get_factor()) < 1000/FRAMES_PER_SECOND)
	//	SDL_Delay(1000/FRAMES_PER_SECOND - (int)(1000*cFrameRateManager::get_factor()));
	SDL_Delay(10);
}
