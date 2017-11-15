/*
** EPITECH PROJECT, 2017
** breakout.c
** File description:
**	Classic Breakout Game in C
*/
#include <SFML/Graphics.h>
#include <SFML/System/Sleep.h>
#include <stdlib.h>
#include <stdio.h>
//TO Do:
// Change ball to a cercle (add cercle collision)
// Fix Performance Issue
// Fix bugs (Score and Segfault)

//Global
int score = 0;
int width = 800;
int height = 600;
int pixeldens = 4;	
int box_pos_x[7] = {10, 120,230,340,450,560, 670}; //If -1 then its destroyed
int box_pos_y[7] = {30,30,30,30,30,30, 30};
int box_count = 7; 
int box_height = 10;
int box_width = 100;
int paddel_width = 110;
int paddel_height = 10;
int ball_height = 10;
int ball_width = 10;
int ball_speed = 3;

int paddel_ball(int *ball_pos, int *player_pos, int *ball_v)
{
	if (player_pos[0] < ball_pos[0] + ball_width &&
	player_pos[0] + paddel_width/2-5 > ball_pos[0] &&
	player_pos[1] < ball_pos[1] + ball_height &&
	paddel_height + player_pos[1] > ball_pos[1]) {
		if (ball_v[0] >= 0 )
			ball_v[0] = -1;
		ball_v[1] *= -1;
		return 0;
	}
	if (player_pos[0] + paddel_width/2 < ball_pos[0] + ball_width &&
	player_pos[0] + 10 > ball_pos[0] &&
	player_pos[1] < ball_pos[1] + ball_height &&
	paddel_height + player_pos[1] > ball_pos[1]) {
		ball_v[0] = 0;
		ball_v[1] *= -1;
		return 0;
	}

	if (player_pos[0] + paddel_width/2+10 < ball_pos[0] + ball_width &&
	player_pos[0] + paddel_width > ball_pos[0] &&
	player_pos[1] < ball_pos[1] + ball_height &&
	paddel_height + player_pos[1] > ball_pos[1]) {
		if (ball_v[0] <= 0 )
			ball_v[0] = ball_speed;
		ball_v[1] *= -1;
		return 0;
	}
	return (ball_v[1]);
}
int ball_bounce_x(int *ball_pos, int *ball_v)
{
	if (ball_pos[0] < 1)
		ball_v[0] *= -1;
	if (ball_pos[0] > 790)
		ball_v[0] *= -1;
	return (ball_v[0]);
}
int ball_bounce_y(int *ball_pos, int *ball_v)
{
	if (ball_pos[1] < 1)
		ball_v[1] *= -1;
	if (ball_pos[1] > (height-ball_height-1)) {
		printf("Game Over, Score: %d\n", score);
		exit(0);
	}
	return (ball_v[1]);
}
	
int ball_collide_box(int *ball_pos, int *ball_v)
{
	for (int i=0; i < box_count; i++) {
		if (box_pos_x[i] < ball_pos[0] + 10 &&
		box_pos_x[i] + box_width > ball_pos[0] &&
		box_pos_y[i] < ball_pos[1] + 10 &&
		box_height + box_pos_y[i] > ball_pos[1]) {
			box_pos_x[i] = -1;
			box_pos_y[i] = -1;
			score += 1;
			ball_v[1] *= -1;
		}
	}
	return (0);
}
void pixel_drawrect(sfTexture *main_texture, sfUint8 *pixels, sfColor color, int x, int y, int w, int h)
{
	int j = 0;
	int oldj = 0;

	y /= 2;
	for (int i = y; i < (y+h); i++) {
		oldj = (((y+i) * width*pixeldens) + x*pixeldens) + w*pixeldens;
		j = ((y+i) * width*pixeldens) + x*pixeldens;
		for (j;j < oldj;j+=pixeldens) {	
			pixels[j] = color.r;
			pixels[j+1] = color.g;
			pixels[j+2] = color.b;
			pixels[j+3] = color.a;
		}
		
	}
	sfTexture_updateFromPixels(main_texture, pixels, width, height,0,0);
}

int main()
{
	//Game Vars
	sfVideoMode mode = {800, 600, 32};
	sfRenderWindow* window;
	sfEvent event;
	sfTexture *main_texture;
	sfSprite *main_sprite;
	sfUint8 *pixels;

	//Player vars
	int player_pos[2] = {300, 570};
	
	//Game Physics
	int ball_pos[2] = {(width/2) - 5, 300};
	int ball_v[2] = {0,ball_speed};
	int bounce;

	//Main
	pixels = malloc(width * height * pixeldens);

	//init scene
	for (int i = 0; i < width * height * pixeldens; i+=4) {
		pixels[i] = sfBlack.r;
		pixels[i+1] = sfBlack.g;
		pixels[i+2] = sfBlack.b;
		pixels[i+3] = sfBlack.a;
	}
	main_texture = sfTexture_create(width, height);
	

	sfTexture_updateFromPixels(main_texture,pixels,width,height,0,0);
	main_sprite = sfSprite_create();
	sfSprite_setTexture(main_sprite, main_texture, sfTrue);
	window = sfRenderWindow_create(mode, "BreakOut v1", sfResize | sfClose, NULL);
	sfRenderWindow_setTitle(window, "BreakOut v1 {0}");
	sfRenderWindow_setFramerateLimit(window, 120);
	while (sfRenderWindow_isOpen) {
		while (sfRenderWindow_pollEvent(window, &event)) {
			if (event.type == sfEvtClosed) {
				sfRenderWindow_close(window);
				return (0);
			}
		}
		if (sfKeyboard_isKeyPressed(sfKeyRight))
				player_pos[0] += 5;
		if (sfKeyboard_isKeyPressed(sfKeyLeft))
				player_pos[0] -= 5;
		if (player_pos[0] < 0)
			player_pos[0] = 0;
		if (player_pos[0] > 800-paddel_width)
			player_pos[0] = 800-paddel_width;

		sfRenderWindow_clear(window, sfWhite); //White so we can check for errors in texture
		pixel_drawrect(main_texture, pixels, sfBlack, 0, 0, width, height);

		ball_v[0] = ball_bounce_x(ball_pos, ball_v);
		ball_v[1] = ball_bounce_y(ball_pos, ball_v);
		ball_collide_box(ball_pos, ball_v);
		paddel_ball(ball_pos, player_pos, ball_v);
		ball_pos[0] += ball_v[0];
		ball_pos[1] += ball_v[1];
		pixel_drawrect(main_texture, pixels, sfBlue,ball_pos[0], ball_pos[1], 10, 10);
		pixel_drawrect(main_texture, pixels, sfRed, player_pos[0], player_pos[1], paddel_width/2, paddel_height);
		pixel_drawrect(main_texture, pixels, sfGreen, player_pos[0]+50, player_pos[1], 10, paddel_height);
		pixel_drawrect(main_texture, pixels, sfRed, player_pos[0]+60, player_pos[1], paddel_width/2, paddel_height);
		for (int i = 0; i < box_count; i++) {
			if (box_pos_x[i] != -1) {
				pixel_drawrect(main_texture, pixels, sfYellow, box_pos_x[i], box_pos_y[i], box_width, box_height);
			}
		}
		sfTexture_updateFromPixels(main_texture,pixels,width,height,0,0);
		sfSprite_setTexture(main_sprite, main_texture, sfTrue);
		sfRenderWindow_drawSprite(window, main_sprite, NULL);
		char str[2];
		str[0] = score+48;
		str[1] = 0;
		if (score >= box_count) {
			printf("You Won!\n");
			exit(1);
		}
		sfRenderWindow_setTitle(window, str);
		sfRenderWindow_display(window);
	}
	sfRenderWindow_destroy(window);
	sfTexture_destroy(main_texture);
	sfSprite_destroy(main_sprite);
	free(pixels);
}