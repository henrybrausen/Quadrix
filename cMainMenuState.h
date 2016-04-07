#ifndef __CMAINMENUSTATE_H__
#define __CMAINMENUSTATE_H__

#include "cGameState.h"
#include "cSprite.h"

class cMainMenuState : public cMainMenuState {
public:
	cMainMenuState(cApplication *app) : cGameState(app) {initialize();}
	virtual ~cMainMenuState() { cleanup(); }
	virtual bool initialize();
	virtual void process();
	virtual void render();
	virtual void cleanup();

	void on_key_down(SDLKey inSym, SDLMod inMod, Uint16 unicode);
};

#endif
