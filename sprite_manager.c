/*
** EPITECH PROJECT, 2017
** file_name.c
** File description:
**	desc
*/
#include <SFML/Graphics.h>
#include <SFML/System/Sleep.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
int width = 800;
int height = 600;
int pixel_buffer = 4;

sfIntRect move_rect(sfIntRect spritesheet_rect, int offset, int max_value)
{
	if (spritesheet_rect.left == max_value - offset) {
		spritesheet_rect.left = 0;
	} else {
		spritesheet_rect.left += offset;
	}
	
	return (spritesheet_rect);
}
void example_main()
{
	sfVideoMode mode = {width, height, 32};
	sfClock *clock;
	sfTime time;
	float seconds = 0.0;
	sfRenderWindow* window;
	sfEvent event;
	sfVector2f pos;
	sfSprite *spritesheet;
	sfTexture *spritesheet_texture;
	sfIntRect spritesheet_rect;

	spritesheet_rect.top = 0;
	spritesheet_rect.left = 0;
	spritesheet_rect.width = 110;
	spritesheet_rect.height = 110;
	pos.x = 0;
	pos.y = 0;
	spritesheet_texture = sfTexture_createFromFile("sp/spritesheet.png", NULL);
	spritesheet = sfSprite_create();
	sfSprite_setTexture(spritesheet, spritesheet_texture, sfTrue);
	sfSprite_setTextureRect(spritesheet, spritesheet_rect);
	window = sfRenderWindow_create(mode, "Window", sfResize | sfClose, NULL);
	clock = sfClock_create();
	while (sfRenderWindow_isOpen) {
		time = sfClock_getElapsedTime(clock);
		seconds = time.microseconds / 1000000.0;
		if (seconds > 0.1) {
			sfRenderWindow_clear(window, sfWhite);
			spritesheet_rect = move_rect(spritesheet_rect, 110, 330);
			sfSprite_setTextureRect(spritesheet, spritesheet_rect);
			sfRenderWindow_drawSprite(window, spritesheet, NULL);
			sfRenderWindow_display(window);
			sfClock_restart(clock);
			seconds = 0.0;
		}
		//sfSleep(sfMilliseconds(100));
	}
	sfRenderWindow_clear(window, sfBlack);
	sfRenderWindow_destroy(window);
}