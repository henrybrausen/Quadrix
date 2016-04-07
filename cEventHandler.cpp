#include "cEventHandler.h"

cEventHandler::cEventHandler()
{
}

cEventHandler::~cEventHandler()
{
}

// Entry point into event handler
void cEventHandler::handle_event(const SDL_Event &event)
{
	switch(event.type) {

		// -------- ACTIVEEVENT --------
		case SDL_ACTIVEEVENT:
			switch(event.active.state) {
				case SDL_APPMOUSEFOCUS:	// Mouse focus change
					if(event.active.gain) {
						on_mouse_focus();
					} else {
						on_mouse_blur();
					}
					break;
				case SDL_APPINPUTFOCUS:	// Application focus change
					if(event.active.gain) {
						on_input_focus();
					} else {
						on_input_blur();
					}
					break;
				case SDL_APPACTIVE:
					if(event.active.gain) {	// Restore or Minimize
						on_restore();
					} else {
						on_minimize();
					}
					break;
				}
				break;
			// -------- END ACTIVEEVENT --------

			// -------- KEYDOWN --------
			case SDL_KEYDOWN:
				cKeyStateManager::on_keydown(event.key.keysym.sym);
				on_key_down(event.key.keysym.sym, event.key.keysym.mod, event.key.keysym.unicode);
				break;
			// -------- END KEYDOWN --------

			// -------- KEYUP --------
			case SDL_KEYUP:
				cKeyStateManager::on_keyup(event.key.keysym.sym);
				on_key_up(event.key.keysym.sym, event.key.keysym.mod, event.key.keysym.unicode);
				break;
			// -------- END KEYUP --------

			// -------- MOUSEMOTION --------
			case SDL_MOUSEMOTION:
				on_mouse_move(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel, (event.motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0, (event.motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0, (event.motion.state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
				break;
			// -------- END MOUSEMOTION --------

			// -------- MOUSEBUTTONDOWN --------
			case SDL_MOUSEBUTTONDOWN:
				switch(event.button.button) {
				case SDL_BUTTON_LEFT:
					on_lbutton_down(event.button.x, event.button.y);
					break;
				case SDL_BUTTON_RIGHT:
					on_rbutton_down(event.button.x, event.button.y);
					break;
				case SDL_BUTTON_MIDDLE:
					on_mbutton_down(event.button.x, event.button.y);
					break;
				}
				break;
			// -------- END MOUSEBUTTONDOWN --------

			// -------- MOUSEBUTTONUP --------
			case SDL_MOUSEBUTTONUP:
				switch(event.button.button) {
				case SDL_BUTTON_LEFT:
					on_lbutton_up(event.button.x, event.button.y);
					break;
				case SDL_BUTTON_RIGHT:
					on_rbutton_up(event.button.x, event.button.y);
					break;
				case SDL_BUTTON_MIDDLE:
					on_mbutton_up(event.button.x, event.button.y);
					break;
				}
				break;
			// -------- END MOUSEBUTTONUP --------

			// -------- JOYAXISMOTION --------
			case SDL_JOYAXISMOTION:
				on_joy_axis(event.jaxis.which, event.jaxis.axis, event.jaxis.value);
				break;
			// -------- END JOYAXISMOTION --------

			// -------- JOYBALLMOTION --------
			case SDL_JOYBALLMOTION:
				on_joy_ball(event.jball.which, event.jball.ball, event.jball.xrel, event.jball.yrel);
				break;
			// -------- END JOYBALLMOTION --------

			// -------- JOYHATMOTION --------
			case SDL_JOYHATMOTION:
				on_joy_hat(event.jhat.which, event.jhat.hat, event.jhat.value);
				break;
			// -------- END JOYHATMOTION --------

			// -------- JOYBUTTONDOWN --------
			case SDL_JOYBUTTONDOWN:
				on_joy_button_down(event.jbutton.which, event.jbutton.button);
				break;
			// -------- END JOYBUTTONDOWN --------

			// -------- JOYBUTTONUP--------
			case SDL_JOYBUTTONUP:
				on_joy_button_up(event.jbutton.which, event.jbutton.button);
				break;
			// -------- END JOYBUTTONUP --------

			// -------- QUIT --------
			case SDL_QUIT:
				on_exit();
				break;
			// -------- END QUIT --------

			// -------- SYSWMEVENT --------
			case SDL_SYSWMEVENT:
				// Ignore
				break;
			// -------- END SYSWMEVENT --------

			// -------- VIDEORESIZE --------
			case SDL_VIDEORESIZE:
				on_resize(event.resize.w, event.resize.h);
				break;
			// -------- END VIDEORESIZE --------

			// -------- VIDEOEXPOSE --------
			case SDL_VIDEOEXPOSE:
				on_expose();
				break;
			// -------- END VIDEOEXPOSE --------

			// Default action:
			default:
				on_user(event.user.type, event.user.code, event.user.data1, event.user.data2);
				break;
	}
}

void cEventHandler::on_input_focus()
{
}

void cEventHandler::on_input_blur()
{
}
	
void cEventHandler::on_key_down(SDLKey inSym, SDLMod inMod, Uint16 unicode)
{
}

void cEventHandler::on_key_up(SDLKey inSym, SDLMod inMod, Uint16 unicode)
{
}

void cEventHandler::on_mouse_focus()
{
}

void cEventHandler::on_mouse_blur()
{
}

void cEventHandler::on_mouse_move(int x, int y, int xrel, int yrel, bool lbutton, bool rbutton, bool mbutton)
{
}

void cEventHandler::on_mouse_wheel(bool up, bool down)
{
}

void cEventHandler::on_lbutton_down(int x, int y)
{
}

void cEventHandler::on_lbutton_up(int x, int y)
{
}

void cEventHandler::on_rbutton_down(int x, int y)
{
}

void cEventHandler::on_rbutton_up(int x, int y)
{
}

void cEventHandler::on_mbutton_down(int x, int y)
{
}

void cEventHandler::on_mbutton_up(int x, int y)
{
}

void cEventHandler::on_joy_axis(Uint8 which, Uint8 axis, Sint16 val)
{
}

void cEventHandler::on_joy_button_down(Uint8 which, Uint8 button)
{
}

void cEventHandler::on_joy_button_up(Uint8 which, Uint8 button)
{
}

void cEventHandler::on_joy_hat(Uint8 which, Uint8 hat, Uint8 val)
{
}

void cEventHandler::on_joy_ball(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel)
{
}

void cEventHandler::on_minimize()
{
}

void cEventHandler::on_restore()
{
}

void cEventHandler::on_resize(int w, int h)
{
}

void cEventHandler::on_expose()
{
}

void cEventHandler::on_exit()
{
}

void cEventHandler::on_user(Uint8 type, int code, void *data1, void *data2)
{
}
