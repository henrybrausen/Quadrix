#ifndef __CPARTICLE_H__
#define __CPARTICLE_H__

#include <SDL.h>

class cParticle {
public:
	cParticle(SDL_Surface *img) { mImg = img; mLastTime = SDL_GetTicks(); mLifeRemaining = 0;}
	virtual ~cParticle() {}

	virtual void process();
	virtual void render(SDL_Surface *screen);

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

	void set_vel(const double& vX, const double& vY) { mVX = vX; mVY = vY; }

	const bool is_dead() const { return mDead; }

	void kill() { mDead = true; }

	void set_life(const Uint32& life) { mLifeRemaining = life; mDead = false; }

private:
	double mX, mY, mVX, mVY;
	Sint32 mLifeRemaining;
	bool mDead;
	SDL_Surface *mImg;

protected:
	Uint32 mLastTime;
};

#endif
