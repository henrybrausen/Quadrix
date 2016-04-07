#ifndef __CSPRITERESOURCE_H__
#define __CSPRITERESOURCE_H__

#include <SDL.h>
#include <vector>

typedef struct sSpriteFrame {
	SDL_Surface *image;
	Uint32 delay;	// Delay in milliseconds
} tSpriteFrame;

class cSprite;

class cSpriteResource {
public:
	cSpriteResource() : mInitialized(false), mW(0), mH(0), mLastUpdate(0) {}
	cSpriteResource(const char* inDir) { load(inDir); }
	virtual ~cSpriteResource();

	virtual const bool load(const char* inDir);

	const bool isInitialized() const { return mInitialized; }
	const unsigned int get_frame_count() { return mFrames.size(); }

	void update();

	const unsigned int get_frame() const;
	void set_frame(const unsigned int inCurrentFrame);

	// cSprite needs special access
	friend class cSprite;

private:
	void free_surfaces();

	SDL_Surface *get_surface() { return mFrames[mCurrentFrame].image; }

	std::vector<tSpriteFrame> mFrames;
	unsigned int mW, mH, mCurrentFrame, mLastUpdate;
	bool mInitialized;
};


#endif
