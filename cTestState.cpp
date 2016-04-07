#include "cTestState.h"
#include "cSprite.h"
#include "cPlayer.h"
#include "cSurface.h"
#include "cSoundManager.h"
#include "cMusicManager.h"
#include "cFontManager.h"
#include "cApplication.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>

bool cTestState::initialize()
{
	ai=false;

	/* Load Game Resources */
	layer0 = cSurface::load("ground.png");
	layer1 = cSurface::load("clouds.png", true);
	pImgs.push_back(cSurface::load("particles/particle1.bmp"));
	pImgs.push_back(cSurface::load("particles/particle2.bmp"));
	pImgs.push_back(cSurface::load("particles/particle3.bmp"));
	pImgs.push_back(cSurface::load("particles/particle4.bmp"));

	cSurface::set_color_key(pImgs[0], 181, 230, 29);
	cSurface::set_color_key(pImgs[1], 181, 230, 29);
	cSurface::set_color_key(pImgs[2], 181, 230, 29);
	cSurface::set_color_key(pImgs[3], 181, 230, 29);
	//cSurface::set_color_key(layer1, 244, 244, 244);

	scroll0 = scroll1 = SCREEN_H;

	/* Initialize Sprites */
	cPlayer *sprite1 = new cPlayer();
	sprite1->load("player");
	sprite1->set_animate(true);
	sprite1->set_max_vel(600,600);
	sprite1->set_pos(SCREEN_W/2,SCREEN_H/2);
	sprite1->enrol(interactionList);
	player = sprite1;

	cSprite *sprite2 = new cSprite();
	sprite2->load("enemy");
	sprite2->set_animate(true);
	sprite2->set_pos(1000,500);
	sprite2->set_max_vel(500, 500);
	sprite2->set_vel(100,0);
	sprite2->enrol(interactionList);

	interactionList.listType = LT_COLLIDE;

	srand(time(NULL));
	mDP = false; // No particles yet
	
	return true;
}

void cTestState::process()
{
	if(!ai) {                                                                                                                 
		SDL_WM_SetCaption("Paused - Press A", "enginetest -- Paused");
		if(cKeyStateManager::is_pressed(SDLK_a)) { ai = true; } else { return; }
	}
	SDL_WM_SetCaption("enginetest -- Playing", "enginetest");
	for(std::vector<tSpriteCol>::iterator it = cSpriteColManager::col_list.begin(); it != cSpriteColManager::col_list.end(); ++it) {
		it->a->on_collide(it->b);
		it->b->on_collide(it->a);
	}
	cSpriteColManager::col_list.clear();
	for(std::vector<cSprite *>::iterator it = interactionList.list.begin(); it != interactionList.list.end(); ++it)
	{
		if(!(*it)->get_type() == ST_PLAYER) {
			// Enemies follow you!
			(*it)->set_accel(8.0*(cGlobals::doubles["p1x"]-(*it)->get_x()), 8.0*(cGlobals::doubles["p1y"]-(*it)->get_y()));
		}
		(*it)->process();
	}

	for(std::deque<cParticle *>::iterator it = mParticles.begin(); it != mParticles.end(); ++it) {
		(*it)->process();
		if((*it)->is_dead()) { delete (*it); it = mParticles.erase(it); if(it == mParticles.end()) { break; } }
	}

	// Particle test
	if(SDL_GetTicks() > mPT && mDP) {
		int vlen = pImgs.size();
		Sint16 tx, ty;
		tx = cGlobals::doubles["p1x"] + (rand()%(player->get_width()));
		ty = cGlobals::doubles["p1y"] + (rand()%(player->get_height()));
		for(int i = 0; i < 50; ++i) {
			cParticle *tmp = new cParticle(pImgs[rand()%vlen]);
			tmp->set_life(rand()%400);
			tmp->set_vel(((Sint16)rand()%400)-200+player->get_x_vel(), ((Sint16)rand()%400)-200+player->get_y_vel());
			tmp->set_pos(tx, ty);
			mParticles.push_back(tmp);
		}
		mPT = SDL_GetTicks() + rand()%1000;
	}

	scroll0 += 300.0*cFrameRateManager::get_factor();
	if(scroll0-4096 >= SCREEN_H) { scroll0 = SCREEN_H; }
	scroll1 += 800.0*cFrameRateManager::get_factor();
	if(scroll1-8192 >= SCREEN_H) { scroll1 = SCREEN_H; }
	SDL_Delay(1);
}

void cTestState::render()
{
	cSurface::draw(mScreen, layer0, 0, 0, 0, 4096-(int)scroll0, SCREEN_W, SCREEN_H);
	if(4096-scroll0 < SCREEN_H) {
		cSurface::draw(mScreen, layer0, 0, 0, 0, 4096-((int)scroll0)%4096, SCREEN_W, SCREEN_H-4096+scroll0);
	}
	cSurface::draw(mScreen, layer1, 0, 0, 0, 8192-(int)scroll1, SCREEN_W, SCREEN_H);
	if(8192-scroll1 < SCREEN_H) {
		cSurface::draw(mScreen, layer1, 0, 0, 0, 8192-((int)scroll1-8192), SCREEN_W, SCREEN_H-8192+(int)scroll1);
	}
	for(std::vector<cSprite *>::iterator it = interactionList.list.begin(); it != interactionList.list.end(); ++it)
	{
		(*it)->render(mScreen);
	}
	char caption[255];
	sprintf(caption, "FPS: %5.2lf, Factor: %1.5lf", cFrameRateManager::get_fps(), cFrameRateManager::get_factor());
	SDL_Color wht = {255,255,255};
	SDL_Surface *fpstext = cFontManager::render_blended("vera", wht, caption);
	cSurface::draw(mScreen, fpstext, SCREEN_W-fpstext->w, 0);
	SDL_FreeSurface(fpstext);
	if(!ai) {
		SDL_Color blk = {0, 0, 0};
		fpstext = cFontManager::render_blended("vera", blk, "====Press A to Start====");
		cSurface::draw(mScreen, fpstext, SCREEN_W/2-fpstext->w/2, SCREEN_H/2-fpstext->h/2);
		SDL_FreeSurface(fpstext);
	}

	for(std::deque<cParticle *>::iterator it = mParticles.begin(); it != mParticles.end(); ++it)
	{
		(*it)->render(mScreen);
	}

	cFrameRateManager::on_render();
}

void cTestState::cleanup()
{
	cSpriteColManager::clear();
	for(std::vector<cSprite *>::iterator it = interactionList.list.begin(); it != interactionList.list.end(); ++it)
	{
		delete (*it);
	}
	for(std::deque<cParticle *>::iterator it = mParticles.begin(); it != mParticles.end(); ++it)
	{
		delete (*it);
	}
	SDL_FreeSurface(layer0);
	SDL_FreeSurface(layer1);
	for(std::vector<SDL_Surface *>::iterator it = pImgs.begin(); it != pImgs.end(); ++it) {
		SDL_FreeSurface((*it));
	}
}

void cTestState::on_key_down(SDLKey inSym, SDLMod inMod, Uint16 unicode)
{
	if(inSym == SDLK_z) {
		cSoundManager::play_sound("zap");
	}
	if(inSym == SDLK_m) {
		cMusicManager::play_track("db_pdx3", -1);
	}
	if(inSym == SDLK_n) {
		cMusicManager::halt();
	}
	if(inSym == SDLK_s) {
		cMusicManager::play_track("scarabi", -1);
	}
	if(inSym == SDLK_x) {
		cMusicManager::play_track("epic", -1);
	}
	if(inSym == SDLK_p) {
		mDP = !mDP;
		mPT = SDL_GetTicks() + rand()%1000;
	}
}
