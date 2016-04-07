#include "cApplication.h"

int cApplication::execute()
{
	// Attempt to initialize the engine; exit on failure
	if(!initialize()) { return -1; }

	SDL_Event event;

	// Main program loop
	while(mIsRunning) {

		// Handle events
		while(SDL_PollEvent(&event)) {
			handle_event(event);
		}

		// Do game logic / processing
		process();

		// Render to buffer
		render();

		// Update framerate
		cFrameRateManager::on_render();

		// Flip buffer
		SDL_Flip(mScreen);

	}
	return 0;
}