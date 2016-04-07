#include "cApplication.h"

void cApplication::cleanup()
{
	/*for(std::vector<cSprite *>::iterator it = mSprites.begin(); it != mSprites.end(); ++it)
	{
		delete (*it);
	}*/
	while(mStates.size() > 0) {
		delete mStates.top();
		mStates.pop();
	}

	// Free the screen memory
	SDL_FreeSurface(mScreen);
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
	return;
}
