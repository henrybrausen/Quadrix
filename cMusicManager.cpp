#include "cMusicManager.h"
#include <utility>

using namespace std;

map<string, Mix_Music*> cMusicManager::mMusicMap;

cMusicManager::~cMusicManager()
{
	for(map<string, Mix_Music*>::iterator it = mMusicMap.begin(); it != mMusicMap.end(); ++it) {
		Mix_FreeMusic(it->second);
	}
}

const bool cMusicManager::add_track(const std::string& name, Mix_Music* sound)
{
	pair<map<string, Mix_Music*>::iterator, bool> ret = mMusicMap.insert(make_pair(name, sound));
	if(!ret.second) {
		fprintf(stderr, "Error: Could not add track %s!\n", name.c_str());
	}
	fprintf(stderr, "%s\n", Mix_GetError());
	return ret.second;
}

Mix_Music* cMusicManager::acquire_track(const std::string& name)
{
	map<string, Mix_Music*>::iterator ret = mMusicMap.find(name);
	if(ret != mMusicMap.end()) {
		return ret->second;
	} else {
		fprintf(stderr, "Warning: Could not acquire music track %s!\n", name.c_str());
		return NULL;
	}

}

const bool cMusicManager::play_track(const std::string& name, const int loop)
{
	Mix_Music* music = cMusicManager::acquire_track(name);
	if(music == NULL) {
		fprintf(stderr, "Warning: Could not play track %s!\n", name.c_str());
		return false;
	}
	Mix_PlayMusic(music, loop);
}
