#include "cKeyStateManager.h"

std::set<SDLKey> cKeyStateManager::mPressedKeys;

void cKeyStateManager::on_keydown(const SDLKey& key)
{
	mPressedKeys.insert(key);
}

void cKeyStateManager::on_keyup(const SDLKey& key)
{
	mPressedKeys.erase(key);
}

const bool cKeyStateManager::is_pressed(const SDLKey& key)
{
	if(mPressedKeys.find(key) != mPressedKeys.end()) return true;
	return false;
}