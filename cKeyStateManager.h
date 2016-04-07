#ifndef __KEYSTATEMANAGER_H__
#define __KEYSTATEMANAGER_H__

#include <SDL.h>
#include <set>

class cKeyStateManager {
private:
	cKeyStateManager();
public:
	virtual ~cKeyStateManager();

	static void on_keydown(const SDLKey& key);
	static void on_keyup(const SDLKey& key);

	static const bool is_pressed(const SDLKey& key);

private:
	static std::set<SDLKey> mPressedKeys;
};

#endif
