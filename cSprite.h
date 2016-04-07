#ifndef __CSPRITE_H__
#define __CSPRITE_H__

#include "cSpriteResource.h"
#include "cFrameRateManager.h"

#include <vector>

enum eSpriteType {
	ST_GENERIC = 0,
	ST_PLAYER,
	ST_ENEMY
};

enum eListType {
	LT_NOCOLLIDE = 0,
	LT_COLLIDE,
	LT_INTERACTONLY
};

typedef struct sInteractionList {
	std::vector<cSprite*> list;
	eListType listType;
} tInteractionList;

class cSprite {
public:
	cSprite();
	cSprite(const char* path);
	cSprite(const cSprite& src);
	virtual ~cSprite() {}

	virtual const bool load(const char* path);
	virtual void process();	// Use a key-state manager singleton to respond to keyboard events
	virtual void render(SDL_Surface *screen);
	virtual void cleanup();

	virtual void myprocess() {}

	void copy_from(const cSprite& src);

	void enrol(tInteractionList& sp_list);
	void dismiss(tInteractionList& sp_list);

	// Mutators and Accessors
	const double get_x() const { return mX; }
	void set_x(const double& inX) { mX = inX; }

	const double get_y() const { return mY; }
	void set_y(const double& inY) { mY = inY; }

	void set_x_vel(const double& inVX) { mVX = inVX; }
	void set_y_vel(const double& inVY) { mVY = inVY; }

	const double get_x_vel() const { return mVX; }
	const double get_y_vel() const { return mVY; }

	void set_pos(const double& inX, const double& inY) { set_x(inX); set_y(inY); }

	void set_vel(const double& vX, const double& vY);
	void set_max_vel(const double& vX, const double& vY) { mVXMax = vX; mVYMax = vY; }
	void set_accel(const double& aX, const double& aY);
	void set_x_accel(const double& aX) { mAX = aX; }
	void set_y_accel(const double& aY) { mAY = aY; }
	void move(double moveX, double moveY);

	const bool check_pos(const Sint16 nextX, const Sint16 nextY);
	const bool collides_with(const Sint16 x, const Sint16 y, const Sint16 w, const Sint16 h) const;

	const unsigned int get_width() const { return mResource.mW; }
	const unsigned int get_height() const { return mResource.mH; }

	const eSpriteType get_type() const { return mType; }
	void set_type(eSpriteType type) { mType = type; }

	virtual void on_collide(cSprite *sp) {}

	void kill() { mDead = true; }
	void revive() { mDead = false; }

	const bool is_dead() const { return mDead; }

	void set_animate(const bool in) { mIsAnimating = in; }
	const bool is_animating() const { return mIsAnimating; }

	void set_frame(const unsigned int& inFrame) { mResource.set_frame(inFrame); }
	const unsigned int get_frame() const { return mResource.get_frame(); }

	cSprite& operator=(const cSprite& rhs);

private:
	void get_bg(SDL_Surface *screen);
	void restore_bg(SDL_Surface *screen);

	std::vector<tInteractionList*> mLists;

	SDL_Surface *mBGRestore;

	cSpriteResource mResource;

	eSpriteType mType;

	double mX, mY, mVX, mVY, mVXMax, mVYMax, mAX, mAY, mLastX, mLastY;

	bool mIsAnimating;
	bool mDrawn;
	bool mDead;
};

typedef struct sSpriteCol {
	cSprite *a;
	cSprite *b;
} tSpriteCol;

class cSpriteColManager {
public:
	static std::vector<tSpriteCol> col_list;
	static void clear() { col_list.clear(); }
};

#endif
