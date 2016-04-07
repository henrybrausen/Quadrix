#include "cPauseState.h"
#include "cSurface.h"
#include "cFontManager.h"
#include "sdl_primitives.h"
#include "cFrameRateManager.h"

bool cPauseState::initialize()
{
	bg = cSurface::create_surface(mScreen, mScreen->w, mScreen->h);
	cSurface::draw(bg, mScreen, 0, 0);	// Get a copy of the current screen
	SDL_Colour fg = {255, 255, 255};
	SDL_Colour bg = {120, 120, 120};
	msg = cFontManager::render_shaded("monospace", fg, bg, "Game Paused");
	return true;
}

void cPauseState::process()
{
}

void cPauseState::render()
{
	set_target(mScreen);
	int bx = mScreen->w/2 - msg->w/2;
	int by = mScreen->h/2 - msg->h/2;
	cSurface::draw(mScreen, bg, 0, 0);
	draw_rectangle_filled(0, by-10, mScreen->w, by + msg->h+10, 120, 120, 120);
	cSurface::draw(mScreen, msg, bx, by);
	draw_line(0, by-10, mScreen->w, by-10, 220, 220, 220);
	draw_line(0, by+msg->h+10, mScreen->w, by + msg->h+10, 220, 220, 220);
}

void cPauseState::cleanup()
{
	SDL_FreeSurface(bg);
	SDL_FreeSurface(msg);
}
