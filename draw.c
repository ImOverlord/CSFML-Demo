/*
** EPITECH PROJECT, 2017
** draw.c
** File description:
**	Sample Function to modify pixels
*/
#include <stdlib.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <math.h>
int width = 800;
int height = 600;
int pixel_buffer = 4;

void clear_pixel(sfTexture *texture, sfUint8 *pixels)
{
	for (int i = 0; i < (width*height*pixel_buffer); i += pixel_buffer) {
		pixels[i] = 0;
		pixels[i+1] = 0;
		pixels[i+2] = 0;
		pixels[i+3] = 255;
	}
}
void change_pixel(sfTexture *texture, sfUint8 *pixels, sfColor color, int x, int y)
{	
	int j = ((y) * width*pixel_buffer) + x*pixel_buffer;
	pixels[j] = color.r;
	pixels[j+1] = color.g;
	pixels[j+2] = color.b;
	pixels[j+3] = color.a;
	sfTexture_updateFromPixels(texture, pixels, width,height,0,0);
}
void pixel_drawelipse(sfTexture *texture, sfUint8 *pixels, sfColor color, int xc, int yc, int width, int height)
{
	
}
//fill : 0=>Not filled 1=>Filled
void pixel_drawcercl(sfTexture *texture, sfUint8 *pixels, sfColor color, int x0, int y0, int r, int fill)
{
	fill = (fill == 0) ? r-1 : 0;
	for (int rad = fill; rad < r; rad++) {
		for (double i = 0.0; i < 360.0; i += 0.1) {
			double angle = i * M_PI / 180;
			int x = (int)(x0 + r + rad * cos(angle));
			int y = (int)(y0 + r + rad * sin(angle));
			int j = ((y) * width*pixel_buffer) + x*pixel_buffer;
			pixels[j] = color.r;
			pixels[j+1] = color.g;
			pixels[j+2] = color.b;
			pixels[j+3] = color.a;
		}
	}
	sfTexture_updateFromPixels(texture, pixels, width,height,0,0);
}
void pixel_drawrect(sfTexture *texture, sfUint8 *pixels, sfColor color, int x, int y, int w, int h)
{
	int j = 0;
	int oldj = 0;

	y /= 2;
	for (int i = y; i < (y+h); i++) {
		oldj = (((y+i) * width*pixel_buffer) + x*pixel_buffer) + w*pixel_buffer;
		j = ((y+i) * width*pixel_buffer) + x*pixel_buffer;
		for (j;j < oldj;j+=pixel_buffer) {	
			pixels[j] = color.r;
			pixels[j+1] = color.g;
			pixels[j+2] = color.b;
			pixels[j+3] = color.a;
		}
		
	}
	sfTexture_updateFromPixels(texture, pixels, width, height,0,0);
}
int example_main()
{
	sfVideoMode mode = {width, height, 32};
	sfRenderWindow* window;
	sfEvent event;
	sfUint8 *pixels;
	sfTexture *texture;
	sfSprite *sprite;
	sfColor color;

	pixels = malloc(width*height*pixel_buffer);
	texture = sfTexture_create(width, height);
	sfTexture_updateFromPixels(texture, pixels, width,height,0,0);
	sprite = sfSprite_create();
	sfSprite_setTexture(sprite, texture, sfTrue);
	window = sfRenderWindow_create(mode, "Window", sfResize | sfClose, NULL);
	while (sfRenderWindow_isOpen) {
		while (sfRenderWindow_pollEvent(window, &event)) {
			if (event.type == sfEvtClosed) {
				sfRenderWindow_close(window);
				return (0);
			}
		}
		sfRenderWindow_clear(window, sfWhite);
		clear_pixel(texture, pixels);
		pixel_drawcercl(texture, pixels, sfRed, 20,20,20, 0);
		pixel_drawrect(texture, pixels,sfRed, 0,0,20,20);
		pixel_drawelipse(texture, pixels,sfRed, 0,0,20,20);
		change_pixel(texture, pixels, sfBlue, 10,10);
		
		sprite = sfSprite_create();
		sfSprite_setTexture(sprite, texture, sfTrue);
	
		
		sfRenderWindow_drawSprite(window, sprite, NULL);
		sfRenderWindow_display(window);
	}
	sfRenderWindow_destroy(window);
	sfTexture_destroy(texture);
	sfSprite_destroy(sprite);
	free(pixels);
}