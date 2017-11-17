/*
** EPITECH PROJECT, 2017
** file_name.c
** File description:
**	desc
*/
#include <breakout.h>

void analyse_events_gameover(sfRenderWindow *window, sfEvent event)
{
	if (event.type == sfEvtClosed) {
		window_close(window);
	}
	if (event.type == sfEvtMouseButtonPressed) {
		screen_manager(0);
	}
}