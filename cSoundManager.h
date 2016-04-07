#ifndef __CSOUNDMANAGER_H__
#define __CSOUNDMANAGER_H__

#include <map>
#include <string>
#include <SDL.h>
#include <SDL_mixer.h>

#include "cSoundResource.h"

class cSoundManager {
public:
	cSoundManager() {}
	virtual ~cSoundManager();

	static const bool add_sound(const std::string& name, cSoundResource *sound);
	static cSoundResource* acquire_sound(const std::string& name);
	static const bool play_sound(const std::string& name);

private:
	static std::map<std::string, cSoundResource*> mSoundMap;
};

#endif
