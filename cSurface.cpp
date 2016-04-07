#include "cSurface.h"

#include <cstdio>
#include <sys/stat.h>
#include <sys/types.h>

SDL_Surface *cSurface::load(const char *inPath, const bool alpha)
{
	struct stat buf;
	if(stat(inPath, &buf) != 0) {
		fprintf(stderr, "Could not load resource at %s: Not found.\n", inPath);
		return NULL;
	}
	
	SDL_Surface *temp = NULL;

	if((temp = IMG_Load(inPath)) == NULL) {
		return NULL;
	}

	SDL_Surface *ret = NULL;
	if(!alpha) {
		ret = SDL_DisplayFormat(temp);
	} else {
		ret = SDL_DisplayFormatAlpha(temp);
	}
	SDL_FreeSurface(temp);

	return ret;
}

SDL_Surface *cSurface::create_surface(const SDL_Surface *proto, Uint16 inW, Uint16 inH, Uint16 flags)
{
	const SDL_PixelFormat fmt = *(proto->format);
	return SDL_CreateRGBSurface(flags, inW, inH, fmt.BitsPerPixel, fmt.Rmask, fmt.Gmask, fmt.Bmask, fmt.Amask);
}

const bool cSurface::draw(SDL_Surface *inDest, SDL_Surface *inSrc, Sint16 inX, Sint16 inY)
{
	if(inDest == NULL || inSrc == NULL) {
		return false;
	}

	SDL_Rect to_blit;
	to_blit.x = inX;
	to_blit.y = inY;

	SDL_BlitSurface(inSrc, NULL, inDest, &to_blit);

	return true;
}

const bool cSurface::draw(SDL_Surface *inDest, SDL_Surface *inSrc, Sint16 inX, Sint16 inY, Sint16 inX2, Sint16 inY2, Uint16 inW, Uint16 inH)
{
	if(inDest == NULL || inSrc == NULL) {
		return false;
	}

	SDL_Rect dest;
	dest.x = inX;
	dest.y = inY;

	SDL_Rect src;
	src.x = inX2;
	src.y = inY2;
	src.w = inW;
	src.h = inH;

	SDL_BlitSurface(inSrc, &src, inDest, &dest);

	return true;
}

const bool cSurface::set_color_key(SDL_Surface *inDest, Uint8 inR, Uint8 inG, Uint8 inB)
{
	if(inDest == NULL) { return false; }

	SDL_SetColorKey(inDest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(inDest->format, inR, inG, inB));

	return true;
}