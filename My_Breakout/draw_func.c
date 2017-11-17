/*
** EPITECH PROJECT, 2017
** file_name.c
** File description:
**	desc
*/
#include <breakout.h>

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