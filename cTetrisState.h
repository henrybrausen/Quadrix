#ifndef __CTETRISSTATE_H__
#define __CTETRISSTATE_H__

#include "cGameState.h"
#include <vector>
#include <deque>
#include "cSprite.h"
#include "cGlobals.h"
#include "cParticle.h"

typedef struct {
	int type;
	bool filled;
	bool flashing;
} block;

extern bool tetrominoes [7][4][4][4];

class cTetrisState : public cGameState {
public:
	cTetrisState(SDL_Surface *screen) : cGameState(screen) {initialize();}
	virtual ~cTetrisState() { cleanup(); }

	virtual const std::string instanceof() const { return "cTetrisState"; }

	virtual bool initialize();
	virtual void process();
	virtual void render();
	virtual void cleanup();

	void on_key_down(SDLKey inSym, SDLMod inMod, Uint16 unicode);
	void on_key_up(SDLKey inSym, SDLMod inMod, Uint16 unicode);

	const bool evaluate_pos(int nrot, int ntr, int ntc);
	void map_tetra(int ttype, int rot, int tr, int tc);
	bool check_rows();
	bool flashing();

	void piece_fall_event();

	bool update_log(const char* path);

	void new_game();

private:
	block **board;
	int flashing_t;
	SDL_Surface *imgs[7];
	SDL_Surface *background;
};

#endif
