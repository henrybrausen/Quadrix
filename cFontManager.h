#ifndef _CFONTMANAGER__H_
#define _CFONTMANAGER__H_

#include <map>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class cFontManager {
public:
	cFontManager() {}
	~cFontManager();
	static const bool load_font(const std::string& name, const char* path, int pt);
	static TTF_Font* acquire_font(const std::string& name);

	static SDL_Surface* render_solid(const std::string& name, const SDL_Color& fgcolor, const std::string& str);
	static SDL_Surface* render_blended(const std::string& name, const SDL_Color& color, const std::string& str);
	static SDL_Surface* render_shaded(const std::string& name, const SDL_Color& fgcolor, const SDL_Color& bgcolor, const std::string& str);

private:
	static std::map<std::string, TTF_Font*> mFontMap;
};

#endif
