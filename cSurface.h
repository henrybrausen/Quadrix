#ifndef __CSURFACE_H__
#define __CSURFACE_H__

#include <SDL.h>
#include <SDL_image.h>

class cSurface {
public:
	static SDL_Surface *load(const char *inPath, const bool alpha = false);
	static SDL_Surface *create_surface(const SDL_Surface *proto, Uint16 inW, Uint16 inH, Uint16 flags = 0); 
	static const bool draw(SDL_Surface *inDest, SDL_Surface *inSrc, Sint16 inX, Sint16 inY);
	static const bool draw(SDL_Surface *inDest, SDL_Surface *inSrc, Sint16 inX, Sint16 inY, Sint16 inX2, Sint16 inY2, Uint16 inW, Uint16 inH);
	static const bool set_color_key(SDL_Surface *inDest, Uint8 inR, Uint8 inG, Uint8 inB);
};

#endif
