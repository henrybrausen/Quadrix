#include "cApplication.h"
#include "cTetrisState.h"
#include "cPauseState.h"
#include "cTitleState.h"
#include "cGlobals.h"
#include <iostream>
#include <string>

void cApplication::handle_event(const SDL_Event& inEvent)
{
	// If the 'X' is clicked .etc
	cEventHandler::handle_event(inEvent);
	mStates.top()->handle_event(inEvent);
}

void cApplication::on_exit()
{
	mIsRunning = false;
}

void cApplication::on_key_down(SDLKey inSym, SDLMod inMod, Uint16 unicode)
{
	if(inSym == SDLK_ESCAPE) {
		cMusicManager::halt();
		if(mStates.top() != NULL && mStates.size() > 1) {
			delete mStates.top();
			mStates.pop();
		} else {
			mIsRunning = false;
		}
	}
	if(inSym == SDLK_p) {
		if(mStates.top()->instanceof() == "cTetrisState")
			mStates.push(static_cast<cGameState*>(new cPauseState(mScreen)));
		else if(mStates.top()->instanceof() == "cPauseState") {
			delete mStates.top();
			mStates.pop();
		}
	}
	if(inSym == SDLK_1) {
		if(mStates.top()->instanceof() == "cTitleState") {
			cGlobals::flags["classic"] = false;
			mStates.push(static_cast<cGameState*>(new cTetrisState(mScreen)));
		}
	}
	if(inSym == SDLK_2) {
		if(mStates.top()->instanceof() == "cTitleState") {
			cGlobals::flags["classic"] = true;
			mStates.push(static_cast<cGameState*>(new cTetrisState(mScreen)));
		}
	}
}

void cApplication::on_key_up(SDLKey inSym, SDLMod inMod, Uint16 unicode)
{
}
