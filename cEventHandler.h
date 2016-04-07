#ifndef __CEVENTHANDLER_H__
#define __CEVENTHANDLER_H__

#include <SDL.h>

#include "cKeyStateManager.h"

// Event-Handling Skeleton

class cEventHandler {
public:
	cEventHandler();

	virtual ~cEventHandler();

	// Entry point into event handler
	virtual void handle_event(const SDL_Event &event);

private:
	virtual void on_input_focus();
	virtual void on_input_blur();
	
	virtual void on_key_down(SDLKey inSym, SDLMod inMod, Uint16 unicode);
	virtual void on_key_up(SDLKey inSym, SDLMod inMod, Uint16 unicode);

	virtual void on_mouse_focus();
	virtual void on_mouse_blur();

	virtual void on_mouse_move(int x, int y, int xrel, int yrel, bool lbutton, bool rbutton, bool mbutton);
	virtual void on_mouse_wheel(bool up, bool down);

	virtual void on_lbutton_down(int x, int y);
	virtual void on_lbutton_up(int x, int y);
	virtual void on_rbutton_down(int x, int y);
	virtual void on_rbutton_up(int x, int y);
	virtual void on_mbutton_down(int x, int y);
	virtual void on_mbutton_up(int x, int y);

	virtual void on_joy_axis(Uint8 which, Uint8 axis, Sint16 val);
	virtual void on_joy_button_down(Uint8 which, Uint8 button);
	virtual void on_joy_button_up(Uint8 which, Uint8 button);
	virtual void on_joy_hat(Uint8 which, Uint8 hat, Uint8 val);
	virtual void on_joy_ball(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);

	virtual void on_minimize();
	virtual void on_restore();
	virtual void on_resize(int w, int h);
	virtual void on_expose();

	virtual void on_exit();
	virtual void on_user(Uint8 type, int code, void *data1, void *data2);
};

#endif
