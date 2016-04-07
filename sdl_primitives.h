#ifndef __SDL_PRIMITIVES_H__
#define __SDL_PRIMITIVES_H__

#include <SDL.h>

	static SDL_Surface *target_surf;

	void set_target(SDL_Surface *tgt);

	// Draw a pixel at given (x,y) with colour (R,G,B)
	void draw_pixel(Sint32 x, Sint32 y, Uint8 R, Uint8 G, Uint8 B);
	void draw_pixel(Sint32 x, Sint32 y, const SDL_Color &color);

	// Draw line connecting (x0,y0) and (x1,y1)
	void draw_line(int x0, int y0, int x1, int y1, Uint8 R, Uint8 G, Uint8 B);
	void draw_line(int x0, int y0, int x1, int y1, const SDL_Color &color);

	// Draw empty circle centered at (x0,y0) with radius r and colour R G B
	void draw_circle(int x0, int y0, int r, Uint8 R, Uint8 G, Uint8 B);
	void draw_circle(int x0, int y0, int r, const SDL_Color& color);

	// Draw filled circle
	void draw_circle_filled(int x0, int y0, int r, Uint8 R, Uint8 G, Uint8 B);
	void draw_circle_filled(int x0, int y0, int r, const SDL_Color& color);

	// Draw outline of rectangle, x,y aligned
	void draw_rectangle(int x0, int y0, int x1, int y1, Uint8 R, Uint8 G, Uint8 B);
	void draw_rectangle(int x0, int y0, int x1, int y1, const SDL_Color& color);

	// Draw filled rectangle, x,y aligned
	void draw_rectangle_filled(int x0, int y0, int x1, int y1, Uint8 R, Uint8 G, Uint8 B);
	void draw_rectangle_filled(int x0, int y0, int x1, int y1, const SDL_Color& color);

#endif
