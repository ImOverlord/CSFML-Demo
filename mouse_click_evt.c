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
int height = 600;
int width = 800;
int pixel_buffer = 4;

void analyse_events(sfRenderWindow *window, sfEvent event)
{
	if (event.type == sfEvtMouseButtonPressed) {
		manage_mouse_click(event.mouseButton);
	}
	if (event.type == sfEvtClosed) {
		window_close(window);
	}
}
void manage_mouse_click(sfMouseButtonEvent event)
{
	if (event.button == sfMouseRight) {
		printf("Mouse x=%d y=%d\n", event.x, event.y);
	}
}
void window_close(sfRenderWindow *window)
{
	sfRenderWindow_close(window);
	exit(0);
}
void main()
{
	sfVideoMode mode = {width, height, 32};
	sfRenderWindow* window;
	sfEvent event;

	window = sfRenderWindow_create(mode, "Window", sfResize | sfClose, NULL);
	while (sfRenderWindow_isOpen) {
		while (sfRenderWindow_pollEvent(window, &event)) {
			analyse_events(window, event);
		}
		sfRenderWindow_display(window);
	}
	sfRenderWindow_destroy(window);
	return (0);
}