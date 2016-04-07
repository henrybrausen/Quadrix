#include "cFrameRateManager.h"

Uint32 cFrameRateManager::mLastTime = 0;
std::deque<Uint32> cFrameRateManager::mIntervals;

void cFrameRateManager::on_render()
{
	Uint32 now = SDL_GetTicks();

	mIntervals.push_front(now-mLastTime);
	if(mIntervals.size() > AVG_RUN_LENGTH) { mIntervals.pop_back(); }

	mLastTime = now;
}

const double cFrameRateManager::get_fps()
{
	if(mIntervals.size() == 0) {
		return 0;
	}
	Uint32 running = 0;
	for(std::deque<Uint32>::const_iterator it = mIntervals.begin(); it != mIntervals.end(); ++it) {
		running += *it;
	}
	double avg_running = (double)running / mIntervals.size();
	return 1000.0/avg_running;
}

const double cFrameRateManager::get_factor()
{
	if(get_fps() == 0) { return 0; }
	return 1.0/get_fps();
}
