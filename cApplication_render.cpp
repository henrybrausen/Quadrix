#include "cApplication.h"

#include <cstdio>

void cApplication::render()
{
	mStates.top()->render();
}
