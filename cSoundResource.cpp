#include "cSoundResource.h"

cSoundResource::~cSoundResource()
{
	if(mInitialized) Mix_FreeChunk(mSound);
}

// Loads WAV, RIFF, AIFF, OGG and/or VOC files
const bool cSoundResource::load(const char* path)
{
	mSound = Mix_LoadWAV(path);
	if(mSound == NULL) {
		fprintf(stderr, "Error: Could not load sound file %s: %s\n", path, Mix_GetError());
		mInitialized = false;
		return false;
	}
	mInitialized = true;
	return true;
}

const bool cSoundResource::play()
{
	if(!mInitialized) return false;
	int channel = Mix_PlayChannel(-1, mSound, 0);
	if(channel == -1) {
		return false;
	}
	mChannel = channel;
	return true;
}

const bool cSoundResource::stop()
{
	if(!mInitialized) return false;
	if(isPlaying()) Mix_HaltChannel(mChannel);
	return true;
}
