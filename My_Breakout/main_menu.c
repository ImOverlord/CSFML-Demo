/*
** EPITECH PROJECT, 2017
** file_name.c
** File description:
**	desc
*/
#include <breakout.h>

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
	if (event.button == sfMouseLeft) {
		play_button(event.x, event.y);
	}
}
void window_close(sfRenderWindow *window)
{
	sfRenderWindow_close(window);
	exit(0);
}
void play_button(int x, int y)
{
	if (x > 300 && x < 500 && y > 300 && y < 400) {
		screen_manager(1);
	}
	
}
void create_text(sfText *lyfe, int size, sfVector2f text_pos, char *str)
{
	sfFont *font = sfFont_createFromFile("./arial.ttf");
	sfText_setFont(lyfe, font);
	sfText_setString(lyfe, "BreakOut v1");
	sfText_setCharacterSize(lyfe, size);
	sfText_setColor(lyfe, sfWhite);
	sfText_setPosition(lyfe, text_pos);
}
void create_text2(sfText *lyfe, int size, sfVector2f text_pos, char *str)
{
	sfFont *font = sfFont_createFromFile("./arial.ttf");
	sfText_setFont(lyfe, font);
	sfText_setString(lyfe, "Play");
	sfText_setCharacterSize(lyfe, size);
	sfText_setColor(lyfe, sfWhite);
	sfText_setPosition(lyfe, text_pos);
}




