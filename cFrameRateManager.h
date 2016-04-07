#ifndef __CFRAMERATEMANAGER_H__
#define __CFRAMERATEMANAGER_H__

#define AVG_RUN_LENGTH 5

#include <deque>

#include <SDL.h>

class cFrameRateManager {
public:
	static void on_render();
	static const double get_fps();
	static const double get_factor();
private:
	static std::deque<Uint32> mIntervals;
	static Uint32 mLastTime;
};

#endif
