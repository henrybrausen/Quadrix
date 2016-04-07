#include "cTetrisState.h"
#include "cSprite.h"
#include "cPlayer.h"
#include "cSurface.h"
#include "cSoundManager.h"
#include "cMusicManager.h"
#include "cFontManager.h"
#include "cApplication.h"
#include "sdl_primitives.h"
#include "cGlobals.h"
#include "rc4.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>

#include <sys/stat.h>
#include <sys/types.h>

#include <iostream>

// Shapes and rotations of tetrominoes
bool tetrominoes [7][4][4][4] = {
	// I tetromino
	{{
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 }
	},
	{
		{ 0, 0, 0, 0 },
		{ 1, 1, 1, 1 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 }
	},
	{
		{ 0, 0, 0, 0 },
		{ 1, 1, 1, 1 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	}},
	// L-tetromino
	{{
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 0, 1, 1, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 0, 0 },
		{ 1, 1, 1, 0 },
		{ 1, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	}},
	// Backwards-L-tetromino
	{{
		{ 0, 0, 1, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 0, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 0, 1, 1, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 0, 0, 0 }
	}},
	// S-tetromino
	{{
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 0, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 0, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 0 }
	}},
	// Z-tetromino
	{{
		{ 0, 0, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 0, 0 }
	}},
	// O-tetromino
	{{
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 }
	}},
	// T-tetromino
	{{
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 1 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 1, 0 },
		{ 0, 0, 1, 1 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 1, 0 },
		{ 0, 1, 1, 1 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 0 }
	}}
};

SDL_Color lookup_color(int tn)
{
	SDL_Color ret;
	// I, L, J, S, Z, T
	switch(tn) {
	case 0:
		ret.r = 0;
		ret.g = 255;
		ret.b = 255;
		break;
	case 1:
		ret.r = 255;
		ret.g = 165;
		ret.b = 0;
		break;
	case 2:
		ret.r = 0;
		ret.g = 0;
		ret.b = 255;
		break;
	case 3:
		ret.r = 0;
		ret.g = 255;
		ret.b = 0;
		break;
	case 4:
		ret.r = 255;
		ret.g = 0;
		ret.b = 0;
		break;
	case 5:
		ret.r = 255;
		ret.g = 255;
		ret.b = 0;
		break;
	case 6:
		ret.r = 170;
		ret.g = 0;
		ret.b = 255;
		break;
	default:
		break;
	}
	return ret;
}

int fall_ms;	// Milliseconds for tetromino to fall one step
int fall_t;		// Time when current tetromino will fall another step
int rot;		// Rotation of current tetromino
int tr, tc;		// Position of current tetromino (w.r.t. top-left corner of 4x4 box)
int ttype;		// Current tetromino type
int nttype;		// Next tetromino type
int score;
int level;
int rows;
bool playing;

const int keyrepeat = 70;	// milliseconds for key repeat

typedef enum { NONE=0, LEFT, RIGHT } key_dir;
key_dir which_key;
int next_autopress;

// This can be tuned to change the variation in difficulty as the player progresses
int get_fall_t()
{
	int lvl_dep = (int)floor((100.0*(4.803-log(2.2317*(level+1)))));
	return (lvl_dep>100)?(lvl_dep):(60);
}

// Player levels-up every 1000 points
int get_level()
{
	return score/200;
}

const bool cTetrisState::evaluate_pos(int nrot, int ntr, int ntc) {
	// Loop through pieces of tetromino
	for(int r = 0; r < 4; ++r) {
		for(int c = 0; c < 4; ++c) {
			// Check if a piece would be out of bounds
			if(tetrominoes[ttype][nrot][r][c] && (ntr+r < 0 || ntr+r >= 20 || ntc+c < 0 || ntc+c >= 10)) {
				return false;
			}
			// Check if a piece overlaps with a piece on the board
			if(ntr+r >= 0 && ntr+r < 20 && ntc+c >= 0 && ntc+c < 10)
				if(tetrominoes[ttype][nrot][r][c] && board[ntr+r][ntc+c].filled) return false;
		}
	}
	return true;
}

void cTetrisState::map_tetra(int ttype, int rot, int tr, int tc)
{
	for(int r = 0; r < 4; ++r) {
		for(int c = 0; c < 4; ++c) {
			if(tetrominoes[ttype][rot][r][c]) {
				board[tr+r][tc+c].filled = true;
				board[tr+r][tc+c].type = ttype;
			}
		}
	}
	if(cKeyStateManager::is_pressed(SDLK_DOWN)) fall_t = SDL_GetTicks() + 4*fall_ms;
}

bool cTetrisState::check_rows()
{
	int flash_count = 0;
	int nrows = 0;
	bool ret = false;
	for(int r = 0; r < 20; ++r) {
		int fill_count = 0;
		for(int c = 0; c < 10; ++c) {
			if(board[r][c].filled && !board[r][c].flashing) ++fill_count;
			if(board[r][c].flashing) ++flash_count;
		}
		if(fill_count == 10) {
			ret = true;
			++nrows;
			for(int c = 0; c < 10; ++c) {
				board[r][c].flashing = true;
			}
			flashing_t = SDL_GetTicks() + 200;
		}
	}
	if(ret) cSoundManager::play_sound("row");
	rows += nrows;
	score += nrows*nrows*10;
	level = get_level();
	return ret;
}

bool cTetrisState::flashing()
{
	if(SDL_GetTicks() < flashing_t) {
		return true;
	} else {
		bool cleared_rows = false;
		for(int r = 0; r < 20; ++r) {
			if(board[r][0].flashing) {
				cleared_rows = true;
				for(int c = 0; c < 10; ++c) {
					board[r][c].filled = false;
					board[r][c].flashing = false;
				}
				for(int r2 = r-1; r2 >= 0; --r2) {
					for(int c = 0; c < 10; ++c) {
						board[r2+1][c] = board[r2][c];
					}
				}
			}
		}
		if(cleared_rows) {
			for(int c = 0; c < 10; ++c) {
				board[0][c].filled = false;
				board[0][c].flashing = false;
			}
		}
	}
	return false;
}

bool cTetrisState::update_log(const char* path)
{
	// Check to ensure that directory exists!
	struct stat st;

	// Check to ensure the log file exists.
	if(stat(path, &st) != 0) {
		fprintf(stderr, "Warning: No log file found. Creating new log file . . .\n");
	}
	else if(!(st.st_mode & S_IFREG)) {
		fprintf(stderr, "Error: %s is not a file!\n", path);
		return false;
	}

	FILE *fp = NULL;

	if((fp = fopen(path, "a")) == NULL) {
		fprintf(stderr, "Error: Could not open %s for writing!\n", path);
		fclose(fp);
		return false;
	}

	// Print time
	fprintf(fp, "Game Ended: %d\n", time(NULL));
	// Print seed
	fprintf(fp, "Seed: %s\n", cGlobals::strings["seed"].c_str());
	// Print score
	fprintf(fp, "Score: %d\n", score);
	// Print rows
	fprintf(fp, "Rows: %d\n", rows);
	// Print level
	fprintf(fp, "Level: %d\n", level);
	// Print separator
	fprintf(fp, "\n------------------------\n");

	fclose(fp);

	return true;
}

void cTetrisState::piece_fall_event()
{
	cSoundManager::play_sound("fall");
	map_tetra(ttype, rot, tr, tc);	// If not, map current tetromino to the board.
	check_rows();					// Check for completed rows / flashing finished
	ttype = nttype;
	nttype = rc4::next_byte()%7;
	tc = 3;
	rot = 0;
	tr = -4;
	for(int i = -3; i <= 0; ++i) {	// Make block start flush with the top of the grid
		if(evaluate_pos(0, i, tc)) {
			tr = i;
			break;
		}
	}
	if(tr == -4) {
		cSoundManager::play_sound("loss");
		playing = false;
		if(!update_log("gamelog.txt")) {
			fprintf(stderr, "Warning: Could not output results to log!\n");
		}
	}
}

bool cTetrisState::initialize()
{
	// Allocate and clear board
	board = new block*[20];
	for(int i = 0; i < 20; ++i) {
		board[i] = new block[10];
		for(int j = 0; j < 10; ++j) {
			board[i][j].filled = false;
		}
	}
	// Load resources
	imgs[0] = cSurface::load("rsc/images/I.bmp");
	imgs[1] = cSurface::load("rsc/images/L.bmp");
	imgs[2] = cSurface::load("rsc/images/J.bmp");
	imgs[3] = cSurface::load("rsc/images/S.bmp");
	imgs[4] = cSurface::load("rsc/images/Z.bmp");
	imgs[5] = cSurface::load("rsc/images/O.bmp");
	imgs[6] = cSurface::load("rsc/images/T.bmp");

	background = cSurface::load("rsc/images/background.bmp");

	if(cGlobals::flags["classic"]) cMusicManager::play_track("tetris", -1);
	else cMusicManager::play_track("mirage", -1);

	// Start game
	new_game();
	return true;
}

void cTetrisState::new_game()
{
	for(int i = 0; i < 20; ++i) {
		for(int j = 0; j < 10; ++j) {
			board[i][j].filled = false;
			board[i][j].flashing = false;
		}
	}
	rot = 0;
	tr = 0;
	tc = 3;
	flashing_t = SDL_GetTicks();

	// Seed PRNG
	char seed[256];
	char c;
	srand(time(NULL));
	string seed_s;
	string norepeat_seed_s;
	// characters 40-125
	for(int i = 0; i < 32; ++i) {
		c = (char)(rand()%(125-40) + 40);
		seed_s.append(8,c);
		norepeat_seed_s.append(1,c);
	}
	rc4::apply_key(seed_s);
	cGlobals::strings["seed"] = norepeat_seed_s;

	ttype = rc4::next_byte()%7;
	nttype = rc4::next_byte()%7;
	for(int i = -3; i <= 0; ++i) {	// Make block start flush with the top of the grid
		if(evaluate_pos(0, i, tc)) {
			tr = i;
			break;
		}
	}
	score = 0;
	rows = 0;
	level = 0;
	fall_ms = get_fall_t();
	fall_t = SDL_GetTicks() + fall_ms;
	playing = true;
	next_autopress = 0;
	which_key = NONE;
}

void cTetrisState::process()
{
	if(playing) {	// We should be playing
		if(!flashing()) {	// If we're not flashing
			if(cKeyStateManager::is_pressed(SDLK_DOWN)) {
				fall_t -= floor(10.0*cFrameRateManager::get_factor()*1000);
			}
			if(which_key != NONE && next_autopress < SDL_GetTicks()) {
				if(which_key == LEFT) {
					int ntc = tc-1;
					if(evaluate_pos(rot, tr, ntc)) { tc = ntc; cSoundManager::play_sound("move"); }
					else cSoundManager::play_sound("bump");
					next_autopress = SDL_GetTicks() + keyrepeat;
				} else if (which_key == RIGHT) {
					int ntc = tc+1;
					if(evaluate_pos(rot, tr, ntc)) { tc = ntc; cSoundManager::play_sound("move"); }
					else cSoundManager::play_sound("bump");
					next_autopress = SDL_GetTicks() + keyrepeat;
				}
			}
			if(fall_t < SDL_GetTicks()) {
				int ntr = tr + 1;
				fall_t = SDL_GetTicks()+fall_ms;	// Set new fall time
				if(evaluate_pos(rot, ntr, tc)) {	// Could we move down one row?
					tr = ntr;						// If yes, that's it
				} else {
					piece_fall_event();
				}
			}
		} else {
			fall_ms = get_fall_t();
			fall_t = SDL_GetTicks()+fall_ms;	// We want it to seem as if the block was just introduced, regardless of flashing time.
		}
	} else {
		// Stuff to do if we are not playing.
	}
}

void cTetrisState::render()
{
	// Blank screen
	//SDL_FillRect(mScreen, NULL, SDL_MapRGB(mScreen->format, 60, 60, 60));

	// Draw background
	cSurface::draw(mScreen, background, 0, 0);
	set_target(mScreen);	// Init primitives
	
	// Draw box for playing field
	//draw_rectangle_filled(40, 40, 240, 440, 0, 0, 0);

	// Draw vertical lines for grid
	for (int i = 60; i < 240; i += 20) {
		draw_line(i, 41, i, 439, 110, 110, 110);
	}
	// Draw horizontal lines for grid
	for(int i = 60; i < 440; i += 20) {
		draw_line(41, i, 239, i, 110, 110, 110);
	}

	// Draw next-piece box
	draw_rectangle_filled(300, 120, 380, 40, 0, 0, 0);
	// Draw vertical lines for next-piece grid
	for (int i = 320; i < 380; i += 20) {
		draw_line(i, 119, i, 41, 110, 110, 110);
	}
	// Draw horizontal lines for next-piece grid
	for(int i = 60; i < 140; i += 20) {
		draw_line(301, i, 379, i, 110, 110, 110);
	}
	// Draw next piece
	for(int r = 0; r < 4; ++r) {
		for(int c = 0; c < 4; ++c) {
			if(tetrominoes[nttype][0][r][c] && playing && !cGlobals::flags["classic"]) cSurface::draw(mScreen, imgs[nttype], 300 + 20*c, 40 + 20*r);
			if(tetrominoes[nttype][0][r][c] && playing && cGlobals::flags["classic"]) draw_rectangle_filled(300 + 20*c+1, 40 + 20*r+1, 300 + 20*(c+1), 40 + 20*(r+1), lookup_color(nttype));
		}
	}

	// Draw board
	for(int i = 0; i < 20; ++i) {
		for(int j = 0; j < 10; ++j) {
			if (board[i][j].filled && !board[i][j].flashing) {
				if(cGlobals::flags["classic"]) draw_rectangle_filled(40 + 20*j+1, 40 + 20*i+1, 40 + 20*(j+1), 40 + 20*(i+1), lookup_color(board[i][j].type%7));
				else cSurface::draw(mScreen, imgs[board[i][j].type], 40+20*j, 40+20*i);
			} else if (board[i][j].filled && board[i][j].flashing) {
				bool blink = (SDL_GetTicks()%20 >= 10);
				if(blink) {
					// Draw nothing
				}
			}
		}
	}
	if(!flashing()) {
	// Draw tetromino in correct position
		for(int r = 0; r < 4; ++r) {
			for(int c = 0; c < 4; ++c) {
				if(tc+c >= 0 && tr+r >= 0 && tc+c < 10 && tr+r < 20) {
					if(tetrominoes[ttype][rot][r][c]) {
						if(cGlobals::flags["classic"]) draw_rectangle_filled(40+20*(c+tc)+1, 40 + 20*(tr+r)+1, 40+20*(c+tc+1), 40 + 20*(tr+r+1), lookup_color(ttype));
						else cSurface::draw(mScreen, imgs[ttype], 40+20*(c+tc), 40+20*(tr+r));
					}
				}
			}
		}
	}

	// Draw outlines of boxes last to reduce colour bleeding
	draw_rectangle(40, 40, 240, 440, 100, 100, 100);
	draw_rectangle(300, 120, 380, 40, 100, 100, 100);

	// Draw score & level
	SDL_Color fg = {255, 255, 255};
	SDL_Colour bg = {0, 0, 0};
	char infostr[300];

	// Draw score
	sprintf(infostr, "Score: %d", score);
	SDL_Surface *txtsurf = cFontManager::render_shaded("monospace10", fg, bg, infostr);
	cSurface::draw(mScreen, txtsurf, 290, 230);
	SDL_FreeSurface(txtsurf);

	// Draw rows
	sprintf(infostr, "Rows: %d", rows);
	txtsurf = cFontManager::render_shaded("monospace10", fg, bg, infostr);
	cSurface::draw(mScreen, txtsurf, 290, 240);
	SDL_FreeSurface(txtsurf);

	// Draw level
	sprintf(infostr, "Level: %d", level);
	txtsurf = cFontManager::render_shaded("monospace10", fg, bg, infostr);
	cSurface::draw(mScreen, txtsurf, 290, 250);
	SDL_FreeSurface(txtsurf);

	// Draw delay
	sprintf(infostr, "FPS: %.2lf", cFrameRateManager::get_fps());
	txtsurf = cFontManager::render_shaded("monospace10", fg, bg, infostr);
	cSurface::draw(mScreen, txtsurf, 290, 260);
	SDL_FreeSurface(txtsurf);

	if(!playing) {
		SDL_Color bg2 = {10, 10, 10};
		txtsurf = cFontManager::render_shaded("monospace", fg, bg2, "Game Over!");
		int bx = (239+41)/2 - txtsurf->w/2;
		int by = (439+41)/2 - txtsurf->h/2;
		draw_rectangle_filled(41, 41, 239, 439, bg2);
		cSurface::draw(mScreen, txtsurf, bx, by);
		SDL_FreeSurface(txtsurf);

		txtsurf = cFontManager::render_shaded("monospace", fg, bg2, "N for New Game");
		bx = (239+41)/2 - txtsurf->w/2;
		by = (439+41)/2 - txtsurf->h/2 + 20;
		cSurface::draw(mScreen, txtsurf, bx, by);
		SDL_FreeSurface(txtsurf);

		txtsurf = cFontManager::render_shaded("monospace", fg, bg2, "ESC for Menu");
		bx = (239+41)/2 - txtsurf->w/2;
		by = (439+41)/2 - txtsurf->h/2 + 40;
		cSurface::draw(mScreen, txtsurf, bx, by);
		SDL_FreeSurface(txtsurf);

		// Draw level seed
		//cout<<cGlobals::strings["seed"]<<endl;
		sprintf(infostr, "Seed: %s", cGlobals::strings["seed"].c_str());
		txtsurf = cFontManager::render_shaded("monospace10", fg, bg, infostr);
		cSurface::draw(mScreen, txtsurf, 40, 460);
		SDL_FreeSurface(txtsurf);
	}
}

void cTetrisState::cleanup()
{
	// Free board memory
	for(int i = 0; i < 20; ++i) {
		delete[] board[i];
	}
	delete[] board;
	for(int i = 0; i < 7; ++i) {
		SDL_FreeSurface(imgs[i]);
	}
}

void cTetrisState::on_key_down(SDLKey inSym, SDLMod inMod, Uint16 unicode)
{
	if(inSym == SDLK_RIGHT) {
		int ntc = tc+1;
		if(evaluate_pos(rot, tr, ntc)) { tc = ntc; cSoundManager::play_sound("move"); }
		else cSoundManager::play_sound("bump");
		which_key = RIGHT;
		next_autopress = SDL_GetTicks() + keyrepeat*3;
	}
	if(inSym == SDLK_LEFT) {
		int ntc = tc-1;
		if(evaluate_pos(rot, tr, ntc)) { tc = ntc; cSoundManager::play_sound("move"); }
		else cSoundManager::play_sound("bump");
		which_key = LEFT;
		next_autopress = SDL_GetTicks() + keyrepeat*3;
	}
	if(inSym == SDLK_UP) {
		int nrot = rot - 1; if(nrot < 0) nrot = 3;
		if(evaluate_pos(nrot, tr, tc)) { rot = nrot; cSoundManager::play_sound("rotate"); }
		else cSoundManager::play_sound("bump");
	}
	if(inSym == SDLK_n && !playing) {
		new_game();
	}
	if(inSym == SDLK_z && playing && !flashing()) {
		for(int ntr = tr+1; ntr < 20; ++ntr) {
			if(evaluate_pos(rot, ntr, tc)) { tr = ntr; }
			else break;
		}
		piece_fall_event();
	}
}

void cTetrisState::on_key_up(SDLKey inSym, SDLMod inMod, Uint16 unicode)
{
	switch(inSym) {
	case SDLK_LEFT:
	case SDLK_RIGHT:
		which_key = NONE;
		break;
	}
}
