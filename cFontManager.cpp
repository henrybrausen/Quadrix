#include "cFontManager.h"
#include <utility>

using namespace std;

std::map<string, TTF_Font*> cFontManager::mFontMap;

cFontManager::~cFontManager()
{
	for(map<string, TTF_Font*>::iterator it = mFontMap.begin(); it != mFontMap.end(); ++it) {
		TTF_CloseFont(it->second);
	}
}

const bool cFontManager::load_font(const string& name, const char* path, const int pt)
{
	TTF_Font* font = TTF_OpenFont(path, pt);
	if(font==NULL) {
		fprintf(stderr, "Error: Could not load font %s: %s\n", path, TTF_GetError());
		return false;
	}
	pair<map<string, TTF_Font*>::iterator, bool> ret;
	ret = mFontMap.insert(make_pair(name, font));
	if(!ret.second) {
		fprintf(stderr, "Error: Could not add font %s!\n", name.c_str());
		TTF_CloseFont(font);
		return false;
	}
	return true;
}

TTF_Font* cFontManager::acquire_font(const std::string& name)
{
	map<string, TTF_Font*>::iterator ret = mFontMap.find(name);
	if(ret != mFontMap.end()) {
		return ret->second;
	} else {
		fprintf(stderr, "Warning: Could not acquire font %s!\n", name.c_str());
		return NULL;
	}
}

SDL_Surface* cFontManager::render_solid(const std::string& name, const SDL_Color& fgcolor, const std::string& str)
{
	TTF_Font* font = acquire_font(name);
	if(font==NULL) {
		return false;
	}
	SDL_Surface *textsurf = NULL;
	if(!(textsurf = TTF_RenderText_Solid(font, str.c_str(), fgcolor))) {
		// An error occurred
		return NULL;
	}
	return textsurf;
}


SDL_Surface* cFontManager::render_blended(const std::string& name, const SDL_Color& color, const std::string& str)
{
	TTF_Font* font = acquire_font(name);
	if(font==NULL) {
		return false;
	}
	SDL_Surface *textsurf = NULL;
	if(!(textsurf = TTF_RenderText_Blended(font, str.c_str(), color))) {
		// An error occurred
		return NULL;
	}
	return textsurf;
}

SDL_Surface* cFontManager::render_shaded(const std::string& name, const SDL_Color& fgcolor, const SDL_Color& bgcolor, const std::string& str)
{
	TTF_Font* font = acquire_font(name);
	if(font==NULL) {
		return false;
	}
	SDL_Surface *textsurf = NULL;
	if(!(textsurf = TTF_RenderText_Shaded(font, str.c_str(), fgcolor, bgcolor))) {
		// An error occurred
		return NULL;
	}
	return textsurf;
}
