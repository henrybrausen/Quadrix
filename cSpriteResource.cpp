#include "cSpriteResource.h"
#include "cSurface.h"

#include <cstdio>

#include <sys/stat.h>
#include <sys/types.h>

#include <SDL_image.h>

cSpriteResource::~cSpriteResource()
{
	free_surfaces();
}

void cSpriteResource::free_surfaces()
{
	for(std::vector<tSpriteFrame>::iterator it = mFrames.begin(); it != mFrames.end(); ++it) {
		SDL_FreeSurface(it->image);
	}
}

// Load from directory (directory must contain an index.txt)
const bool cSpriteResource::load(const char* inDir)
{
	mInitialized = false;
	// Remove any old data
	free_surfaces();
	// Check to ensure that directory exists!
	struct stat st;
	if(stat(inDir, &st) != 0) {
		fprintf(stderr, "Error: Could not find sprite resource directory %s\n", inDir);
		return false;
	}
	if(!(st.st_mode & S_IFDIR)) {
		fprintf(stderr, "Error: %s is not a directory!\n", inDir);
		return false;
	}

	char indexpath[255];

	sprintf(indexpath, "%s/index.txt", inDir);

	// Check to ensure the index file exists!
	if(stat(indexpath, &st) != 0) {
		fprintf(stderr, "Error: Could not find sprite resource index %s\n", indexpath);
		return false;
	}
	if(!(st.st_mode & S_IFREG)) {
		fprintf(stderr, "Error: %s is not a file!\n", inDir);
		return false;
	}

	FILE *fp = NULL;

	if((fp = fopen(indexpath, "r")) == NULL) {
		fprintf(stderr, "Error: Could not open %s for reading!\n", indexpath);
		fclose(fp);
		return false;
	}

	char buffer[255];
	char imagepath[255];
	char imageloadpath[255];
	unsigned int delay, r, g, b;
	unsigned int numFiles;

	tSpriteFrame tempFrame;

	SDL_Surface *temp;

	// Read FILES: %d directive
	fgets(buffer, 255, fp);
	if(sscanf(buffer, "Files: %d", &numFiles) == 0) {
		fprintf(stderr, "Error: Could not read FILES directive in %s\n", indexpath);
		fclose(fp);
		return false;
	}

	// Loop through file
	unsigned int count = 0;
	unsigned int linecount = 1;
	while(!feof(fp) && count < numFiles) {
		temp = NULL;
		fgets(buffer, 255, fp);
		
		// Ignore comments and newlines
		if(buffer[0] != '#' && buffer[0] != '\r' && buffer[0] != '\n' && buffer[0] != 0) {
			// Try to read the line
			if(sscanf(buffer, "%s %d %d %d %d", imagepath, &delay, &r, &g, &b) == 0) {
				fprintf(stderr, "Warning: Could not read line %u in file \"%s\".\n", linecount, indexpath);
				++linecount;
				continue;
			}
			sprintf(imageloadpath, "%s/%s", inDir, imagepath);
			// Check to ensure the image file exists!
			if(stat(imageloadpath, &st) != 0) {
				fprintf(stderr, "Error: Could not find sprite resource image \"%s\"\n", imageloadpath);
				free_surfaces();
				return false;
			}
			if(!(st.st_mode & S_IFREG)) {
				fprintf(stderr, "Error: %s is not a file!\n", imageloadpath);
				free_surfaces();
				return false;
			}
			// Attempt to load image
			if((temp = cSurface::load(imageloadpath)) == NULL) {
				fprintf(stderr, "Error: Could not load image %s!\n", imageloadpath);
				free_surfaces();
				return false;
			}
			// Set color key
			cSurface::set_color_key(temp, r, g, b);
			
			// Use first frame to set our sprite resource's width and height
			if(!mW) { mW = temp->w; }
			if(!mH) { mH = temp->h; }

			// Insert into frames vector
			tempFrame.delay = delay;
			tempFrame.image = temp;
			mFrames.push_back(tempFrame);
			++count;
		}
		++linecount;
	}
	mInitialized = true;
	mLastUpdate = SDL_GetTicks();
	mCurrentFrame = 0;
	return true;
}

void cSpriteResource::update()
{
	if((SDL_GetTicks() - mLastUpdate) >= mFrames[mCurrentFrame].delay) {
		++mCurrentFrame;
		mCurrentFrame %= mFrames.size();
		mLastUpdate = SDL_GetTicks();
	}
}

const unsigned int cSpriteResource::get_frame() const {
	return mCurrentFrame;
}

void cSpriteResource::set_frame(const unsigned int inCurrentFrame)
{
	if(inCurrentFrame > (mFrames.size() - 1)) {
		return;
	}
	mCurrentFrame = inCurrentFrame;
}
