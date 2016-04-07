// sdl_primitives.cpp : Defines the entry point for the console application.
//
#include "sdl_primitives.h"

#include <iostream>
#include <SDL.h>

using namespace std;

void set_target(SDL_Surface *tgt)
{
	target_surf = tgt;
}

void draw_pixel(Sint32 x, Sint32 y, Uint8 R, Uint8 G, Uint8 B)
{
	if(x < 0 || x >= target_surf->w || y < 0 || y >= target_surf->h) { return; }
    Uint32 color = SDL_MapRGB(target_surf->format, R, G, B);

    switch (target_surf->format->BytesPerPixel) {
        case 1: { /* Assuming 8-bpp */
            Uint8 *bufp;

            bufp = (Uint8 *)target_surf->pixels + y*target_surf->pitch + x;
            *bufp = color;
        }
        break;

        case 2: { /* Probably 15-bpp or 16-bpp */
            Uint16 *bufp;

            bufp = (Uint16 *)target_surf->pixels + y*target_surf->pitch/2 + x;
            *bufp = color;
        }
        break;

        case 3: { /* Slow 24-bpp mode, usually not used */
            Uint8 *bufp;

            bufp = (Uint8 *)target_surf->pixels + y*target_surf->pitch + x;
            *(bufp+target_surf->format->Rshift/8) = R;
            *(bufp+target_surf->format->Gshift/8) = G;
            *(bufp+target_surf->format->Bshift/8) = B;
        }
        break;

        case 4: { /* Probably 32-bpp */
            Uint32 *bufp;

            bufp = (Uint32 *)target_surf->pixels + y*target_surf->pitch/4 + x;
            *bufp = color;
        }
        break;
    }
}
void draw_pixel(Sint32 x, Sint32 y, const SDL_Color &color)
{
	draw_pixel(x, y, color.r, color.g, color.b);
}

void draw_line(int x0, int y0, int x1, int y1, Uint8 R, Uint8 G, Uint8 B)
{
	// Is the slope larger than one?
	bool steep = abs(y1 - y0) > abs(x1 - x0);
	// If so, swap x and y
	if(steep) {
		int t = x0;
		x0 = y0;
		y0 = t;
		t = x1;
		x1 = y1;
		y1 = t;
	}
	// If x0 > x1, just draw from the other side.
	// We swap points (x0,x1), (y0,y1)
	if(x0 > x1) {
		int t = x0;
		x0 = x1;
		x1 = t;
		t = y0;
		y0 = y1;
		y1 = t;
	}

	int dx = x1 - x0;
	int dy = abs(y1 - y0);
	int error = dx / 2;

	int ystep = ((y0 < y1)?(1):(-1));
	int y = y0;
	for(int x = x0; x < x1; ++x) {
		if(steep) {
			draw_pixel(y, x, R, G, B);
		} else {
			draw_pixel(x, y, R, G, B);
		}
		error -= dy;
		if(error < 0) {
			y += ystep;
			error += dx;
		}
	}
}

void draw_line(int x0, int y0, int x1, int y1, const SDL_Color &color)
{
	draw_line(x0, y0, x1, y1, color.r, color.g, color.b);
}

void draw_circle(int x0, int y0, int r, Uint8 R, Uint8 G, Uint8 B)
{
	int f = 1 - r;
	int ddF_x = 1;
	int ddF_y = -2 * r;
	int x = 0;
	int y = r;

	draw_pixel(x0, y0 + r, R, G, B);
	draw_pixel(x0, y0 - r, R, G, B);
	draw_pixel(x0 + r, y0, R, G, B);
	draw_pixel(x0 - r, y0, R, G, B);

	while(x < y) {
		if(f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;    
		draw_pixel(x0 + x, y0 + y, R, G, B);
		draw_pixel(x0 - x, y0 + y, R, G, B);
		draw_pixel(x0 + x, y0 - y, R, G, B);
		draw_pixel(x0 - x, y0 - y, R, G, B);
		draw_pixel(x0 + y, y0 + x, R, G, B);
		draw_pixel(x0 - y, y0 + x, R, G, B);
		draw_pixel(x0 + y, y0 - x, R, G, B);
		draw_pixel(x0 - y, y0 - x, R, G, B);
	}
}

void draw_circle(int x0, int y0, int r, const SDL_Color &color)
{
	draw_circle(x0, y0, r, color.r, color.g, color.b);
}

void draw_circle_filled(int x0, int y0, int r, Uint8 R, Uint8 G, Uint8 B)
{
	int f = 1 - r;
	int ddF_x = 1;
	int ddF_y = -2 * r;
	int x = 0;
	int y = r;

	draw_line(x0-r, y0, x0+r, y0, R, G, B);
	draw_line(x0, y0-r, x0, y0 + r, R, G, B);

	while(x < y) {
		if(f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;    
		draw_line(x0 - x, y0 + y, x0 + x, y0 + y, R, G, B);
		draw_line(x0 - x, y0 - y, x0 + x, y0 - y, R, G, B);
		draw_line(y0 - y, x0 - x, y0 + y, x0 - x, R, G, B);
		draw_line(y0 - y, x0 + x, y0 + y, x0 + x, R, G, B);
	}
}

void draw_circle_filled(int x0, int y0, int r, const SDL_Color &color)
{
	draw_circle_filled(x0, y0, r, color.r, color.g, color.b);
}

void draw_rectangle(int x0, int y0, int x1, int y1, Uint8 R, Uint8 G, Uint8 B)
{
	draw_line(x0, y0, x1, y0, R, G, B);
	draw_line(x0, y1, x1, y1, R, G, B);
	draw_line(x0, y0, x0, y1, R, G, B);
	draw_line(x1, y0, x1, y1, R, G, B);
	draw_pixel(x1, y1, R, G, B);
}

void draw_rectangle(int x0, int y0, int x1, int y1, const SDL_Color& color)
{
	draw_rectangle(x0, y0, x1, y1, color.r, color.g, color.b);
}

void draw_rectangle_filled(int x0, int y0, int x1, int y1, Uint8 R, Uint8 G, Uint8 B)
{
	int t;
	if(x0>x1) { t=x0; x0=x1; x1=t; }
	if(y0>y1) { t=y0; y0=y1; y1=t; }
	for(int x = x0; x <= x1; ++x)
		for(int y = y0; y <= y1; ++y)
			draw_pixel(x, y, R, G, B);
}

void draw_rectangle_filled(int x0, int y0, int x1, int y1, const SDL_Color& color)
{
	draw_rectangle_filled(x0, y0, x1, y1, color.r, color.g, color.b);
}
