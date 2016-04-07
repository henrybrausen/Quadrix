#ifndef __CMUSICMANAGER_H__
#define __CMUSICMANAGER_H__

#include <map>
#include <string>
#include <SDL.h>
#include <SDL_mixer.h>

class cMusicManager {
public:
	cMusicManager() {}
	virtual ~cMusicManager();

	static const bool add_track(const std::string& name, Mix_Music* sound);
	static Mix_Music* acquire_track(const std::string& name);
	static const bool play_track(const std::string& name, const int loop);
	static void halt() { Mix_HaltMusic(); }

private:
	static std::map<std::string, Mix_Music*> mMusicMap;
};

#endif
