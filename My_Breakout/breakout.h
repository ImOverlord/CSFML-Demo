/*
** EPITECH PROJECT, 2017
** file_name.c
** File description:
**	desc
*/
#ifndef MY_BREAKOUT_
#define MY_BREAKOUT_

#include <SFML/Graphics.h>
#include <SFML/System/Sleep.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define width (800)
#define height (600)
#define pixel_buffer (4)
#define paddel_width (100)
#define paddel_height (10)
#define paddel_speed (5)
#define ball_size (10)
#define ball_speed (2)
#define box_size_h (10)
#define box_size_w (100)
#define reading_buffer (30000)
void analyse_events(sfRenderWindow *window, sfEvent event);
void manage_mouse_click(sfMouseButtonEvent event);
void pixel_drawrect(sfTexture *texture, sfUint8 *pixels, sfColor color, int x, int y, int w, int h);
void clear_pixel(sfTexture *texture, sfUint8 *pixels);
void change_pixel(sfTexture *texture, sfUint8 *pixels, sfColor color, int x, int y);
void window_close(sfRenderWindow *window);
void play_button(int x, int y);
int game_menu(sfRenderWindow *window, sfUint8 *pixels, sfTexture *main_texture, sfSprite *main_sprite);
#endif /* MY_BREAKOUT_ */