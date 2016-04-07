#ifndef __CPLAYER_H__
#define __CPLAYER_H__

#include "cSprite.h"
#include "cKeyStateManager.h"
#include "cFrameRateManager.h"
#include "cGlobals.h"

class cPlayer : public cSprite {
public:
	cPlayer() { set_type(ST_PLAYER); cGlobals::doubles["p1x"] = get_x(); cGlobals::doubles["p1y"] = get_y(); }
	cPlayer(const char* path) : cSprite(path) { set_type(ST_PLAYER); cGlobals::doubles["p1x"] = get_x(); cGlobals::doubles["p1y"] = get_y(); }

	virtual void myprocess();
public:
	void on_collide(cSprite *sp);
};

#endif
