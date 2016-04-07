#include "cSoundManager.h"
#include <utility>

using namespace std;

map<string, cSoundResource*> cSoundManager::mSoundMap;

cSoundManager::~cSoundManager()
{
	for(map<string, cSoundResource*>::iterator it = mSoundMap.begin(); it != mSoundMap.end(); ++it) {
		delete it->second;
	}
}

cSoundResource* cSoundManager::acquire_sound(const string& name)
{
	map<string, cSoundResource*>::iterator ret = mSoundMap.find(name);
	if(ret != mSoundMap.end()) {
		return ret->second;
	} else {
		fprintf(stderr, "Warning: Could not acquire sound resource %s!\n", name.c_str());
		return NULL;
	}
}

const bool cSoundManager::play_sound(const string& name)
{
	cSoundResource* sound = cSoundManager::acquire_sound(name);
	if(sound == NULL) {
		fprintf(stderr, "Warning: Sound %s could not be found!\n", name.c_str());
		return false;
	}
	return sound->play();
}

const bool cSoundManager::add_sound(const string& name, cSoundResource *sound)
{
	pair<map<string, cSoundResource*>::iterator, bool> ret;
	ret = mSoundMap.insert(make_pair(name, sound));
	if(!ret.second) {
		fprintf(stderr, "Error: Could not add sound %s!\n", name.c_str());
	}
	return ret.second;
}
