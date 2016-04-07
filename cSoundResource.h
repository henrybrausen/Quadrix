#ifndef __C_SOUNDRESOURCE_H__
#define __C_SOUNDRESOURCE_H__

#include <SDL_mixer.h>
#include <SDL.h>

class cSoundResource {
public:
	cSoundResource() : mInitialized(false), mSound(NULL), mLoops(0), mChannel(-1) {}
	cSoundResource(const char* path) { load(path); }
	virtual ~cSoundResource();

	virtual const bool load(const char* path);

	const bool isInitialized() const { return mInitialized; }
	const bool isPlaying() const { return (Mix_Playing(mChannel) != 0); }

	const bool play();
	const bool stop();

private:
	Mix_Chunk* mSound;
	int mLoops;	// # of times to loop; -1 for infinite
	int mChannel;
	bool mInitialized;
};

#endif
