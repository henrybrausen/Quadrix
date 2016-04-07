#include "cSprite.h"
#include "cSurface.h"

#include <SDL.h>

#include <algorithm>

std::vector<tSpriteCol> cSpriteColManager::col_list;

cSprite::cSprite()
{
	mX = 0.0;
	mY = 0.0;
	mLastX = 0.0;
	mLastY = 0.0;
	mVX = 0.0;
	mVY = 0.0;
	mVXMax = 100.0;
	mVYMax = 100.0;
	mAX = 0.0;
	mAY = 0.0;
	mIsAnimating = false;
	mDrawn = false;
	mDead = false;
	mBGRestore = NULL;
	mType = ST_GENERIC;
}

cSprite::cSprite(const char* path)
{
	mX = 0.0;
	mY = 0.0;
	mLastX = 0.0;
	mLastY = 0.0;
	mVX = 0.0;
	mVY = 0.0;
	mVXMax = 100.0;
	mVYMax = 100.0;
	mAX = 0.0;
	mAY = 0.0;
	mIsAnimating = false;
	mDrawn = false;
	mDead = false;
	mBGRestore = NULL;
	mType = ST_GENERIC;
	load(path);
}

void cSprite::copy_from(const cSprite& src)
{
	mX = src.mX;
	mY = src.mY;
	mLastX = src.mLastX;
	mLastY = src.mLastY;
	mVX = src.mVX;
	mVY = src.mVY;
	mVXMax = src.mVXMax;
	mVYMax = src.mVYMax;
	mAX = src.mAX;
	mAY = src.mAY;
	mIsAnimating = src.mIsAnimating;
	mDrawn = src.mDrawn;
	mDead = src.mDead;
	mBGRestore = src.mBGRestore;
	mType = src.mType;
	mResource = src.mResource;
	mLists = src.mLists;
}

cSprite::cSprite(const cSprite& src)
{
	copy_from(src);
}

cSprite& cSprite::operator=(const cSprite& rhs)
{
	if(this == &rhs) { return *this; }
	copy_from(rhs);
	return *this;
}

void cSprite::enrol(tInteractionList& sp_list)
{
	std::vector<cSprite*>::iterator it = std::find(sp_list.list.begin(), sp_list.list.end(), this);
	if(it == sp_list.list.end()) {
		sp_list.list.push_back(this);
	}
	mLists.push_back(&sp_list);
}

void cSprite::dismiss(tInteractionList& sp_list)
{
	std::vector<cSprite*>::iterator it = std::find(sp_list.list.begin(), sp_list.list.end(), this);
	if(it != sp_list.list.end()) {
		sp_list.list.erase(it);
	}
	std::vector<tInteractionList*>::iterator it2 = std::find(mLists.begin(), mLists.end(), &sp_list);
	if(it2 != mLists.end()) {
		mLists.erase(it2);
	}
}

const bool cSprite::load(const char* path)
{
	bool ret = mResource.load(path);
	mBGRestore = SDL_DisplayFormat(mResource.get_surface());
	return ret;
}

void cSprite::process()
{
	// Update current frame if we need to
	if(is_animating() && mResource.isInitialized()) { mResource.update(); }
	myprocess();
	mVX += mAX * cFrameRateManager::get_factor();
	mVY += mAY * cFrameRateManager::get_factor();
	if(mVX > mVXMax) { mVX = mVXMax; }
	if(mVY > mVYMax) { mVY = mVYMax; }
	if(mVX < -mVXMax) { mVX = -mVXMax; }
	if(mVY < -mVYMax) { mVY = -mVYMax; }
	move(mVX, mVY);
}

void cSprite::render(SDL_Surface *screen)
{
	// Check if our resource is initialized
	if(!mResource.isInitialized()) { return; }

	//restore_bg(screen);
	if(!this->is_dead()) {
		//get_bg(screen);
		cSurface::draw(screen, mResource.get_surface(), static_cast<Sint16>(mX), static_cast<Sint16>(mY));
	}
	mDrawn = true;
}

void cSprite::cleanup()
{
	// This space intentionally left blank
}

void cSprite::set_vel(const double& vX, const double& vY)
{
	mVX = vX;
	mVY = vY;
}

void cSprite::set_accel(const double& aX, const double& aY)
{
	mAX = aX;
	mAY = aY;
}

// Move us as close to our new destination as possible!
// Also send out collision notices
void cSprite::move(double moveX, double moveY)
{
	// Nothing to do
	if(moveX == 0 && moveY == 0) return;

	moveX *= cFrameRateManager::get_factor();
	moveY *= cFrameRateManager::get_factor();

	// Next timestep worth of movement away . . .
	double nextX = 0;
	double nextY = 0;

	// Figure out the coordinates of the sprite in the next frame
	if(moveX != 0) nextX = ((moveX >= 0)?(cFrameRateManager::get_factor()):(-cFrameRateManager::get_factor()));
	if(moveY != 0) nextY = ((moveY >= 0)?(cFrameRateManager::get_factor()):(-cFrameRateManager::get_factor()));

	if(is_dead() || check_pos(static_cast<Sint16>(mX + moveX), static_cast<Sint16>(mY))) {
			mX += moveX;
		} else {
			//mVX = 0;
		}
		if(is_dead() || check_pos(static_cast<Sint16>(mX), static_cast<Sint16>(mY + moveY))) {
			mY += moveY;
		} else {
			//mVY = 0;
		}

	/*// Inch ever-closer to our destination
	while(true) {
		// NOTE: Short-circuit logic is IMPORTANT here
		if(is_dead() || check_pos(static_cast<Sint16>(mX + nextX), static_cast<Sint16>(mY))) {
			mX += nextX;
		} else {
			//mVX = 0;
		}
		if(is_dead() || check_pos(static_cast<Sint16>(mX), static_cast<Sint16>(mY + nextY))) {
			mY += nextY;
		} else {
			//mVY = 0;
		}

		// We've moved this far . . .
		moveX -= nextX;
		moveY -= nextY;

		// Bounds X
		if(nextX > 0 && moveX <= 0) nextX = 0;
		if(nextX < 0 && moveX >= 0) nextX = 0;

		// Bounds Y
		if(nextY > 0 && moveY <= 0) nextY = 0;
		if(nextY < 0 && moveY >= 0) nextY = 0;
		
		if(moveX == 0) nextX = 0;
		if(moveY == 0) nextY = 0;

		// Check if we are done
		if(moveX == 0 && moveY == 0) break;
		if(nextX == 0 && nextY == 0) break;
	}*/

	// Old fragment w/out collision detection
	/*mX += mVX * cFrameRateManager::get_factor();
	mY += mVY * cFrameRateManager::get_factor();*/
}

// Check for collisions with each sprite
const bool cSprite::check_pos(const Sint16 nextX, const Sint16 nextY)
{
	if(mLists.size() <= 0) { return true; }
	for(std::vector<tInteractionList*>::iterator lit = mLists.begin(); lit != mLists.end(); ++lit) {
		for(std::vector<cSprite *>::iterator it = (*lit)->list.begin(); it != (*lit)->list.end(); ++it) {
			if(this != *it && (*lit)->listType != LT_NOCOLLIDE && *it != NULL && !(*it)->is_dead() && (*it)->collides_with(nextX, nextY, this->get_width(), this->get_height())) {
				tSpriteCol col;
				col.a = this;
				col.b = (*it);
				cSpriteColManager::col_list.push_back(col);
				if((*lit)->listType == LT_INTERACTONLY) { return true; }
				return false;
			}
		}
	}
	return true;
}

const bool cSprite::collides_with(const Sint16 x, const Sint16 y, const Sint16 w, const Sint16 h) const
{
	// Bounding boxes!
	int left1, left2, right1, right2, top1, top2, bottom1, bottom2;
	left1 = static_cast<int>(get_x());
	left2 = x;
	right1 = static_cast<int>(get_x()) + static_cast<int>(get_width());
	right2 = x + w;
	top1 = get_y();
	top2 = y;
	bottom1 = get_y() + get_height();
	bottom2 = y + h;

	if(bottom1 < top2) return false;
	if(top1 > bottom2) return false;
	if(right1 < left2) return false;
	if(left1 > right2) return false;

	return true;
}

void cSprite::get_bg(SDL_Surface *screen)
{
	SDL_Rect src;
	src.w = get_width();
	src.h = get_height();
	src.x = static_cast<Sint16>(mX);
	src.y = static_cast<Sint16>(mY);
	mLastX = mX;
	mLastY = mY;
	SDL_BlitSurface(screen, &src, mBGRestore, NULL);
}

void cSprite::restore_bg(SDL_Surface *screen)
{
	if(mDrawn) {
		SDL_Rect dest;
		dest.w = get_width();
		dest.h = get_height();
		dest.x = static_cast<Sint16>(mLastX);
		dest.y = static_cast<Sint16>(mLastY);
		SDL_BlitSurface(mBGRestore, NULL, screen, &dest);
	}
}
