/*
** EPITECH PROJECT, 2017
** file_name.c
** File description:
**	desc
*/
#include <breakout.h>
#include <breakout.1.h>

void screen_manager(int new_screen)
{
	screen = new_screen;
}

int game_menu(sfRenderWindow *window, sfUint8 *pixels, sfTexture *main_texture, sfSprite *main_sprite)
{	
	sfEvent event;
	sfText *main = sfText_create();
	sfVector2f main_pos = {135,40};	
	sfText *play = sfText_create();
	sfVector2f play_pos = {305,285};
	while (screen == 0) {
		while (sfRenderWindow_pollEvent(window, &event)) {
			analyse_events(window, event);
		}
		pixel_drawrect(main_texture, pixels, sfBlack, 0,0,width,height);
		pixel_drawrect(main_texture, pixels, sfRed, 0,0,width, height);
		pixel_drawrect(main_texture, pixels, sfBlue, 100,50,600, 100);
		pixel_drawrect(main_texture, pixels, sfBlue, 300,300,200, 100);
		sfSprite_setTexture(main_sprite, main_texture, sfTrue);
		sfRenderWindow_drawSprite(window, main_sprite, NULL);
		create_text(main, 96, main_pos, "BreakOut");
		sfRenderWindow_drawText(window, main, NULL);
		create_text2(play, 96, play_pos, "BreakOut");
		sfRenderWindow_drawText(window, play, NULL);
		sfRenderWindow_display(window);
	}
	return (screen);
}

void game_main(sfRenderWindow *window, sfUint8 *pixels, sfTexture *main_texture, sfSprite *main_sprite)
{	
	sfEvent event;
	int player_stats[2] = {0, 3};
	int bounce = 0;
	int box_count = get_box_count();
	int *box[box_count];
	int score_to_win = box_populator(box, box_count); printf("%d\n", score_to_win);
	int player_pos[2] = {width/2 - paddel_width/2, 570};
	int _ball[4] = {width/2 - ball_size/2, 400, 0, ball_speed}; //x,y,vx,vy
	sfRenderWindow_setFramerateLimit(window, 120);
	while (screen == 1) {
		while (sfRenderWindow_pollEvent(window, &event))
			analyse_events_game(window, event);
		paddel_mouvement(window, main_texture, pixels, player_pos);
		player_stats[0] += box_ball(box, _ball, box_count);
		paddel_ball(player_pos, _ball);
		draw_box(main_texture, pixels, box, box_count);
		bounce = ball_mouvement(window, main_texture, pixels, _ball);
		player_mecanics(player_stats, bounce, score_to_win, window);
		render(window, main_texture, pixels, main_sprite);
	}
}

void game_over(sfRenderWindow *window, sfUint8 *pixels, sfTexture *main_texture, sfSprite *main_sprite)
{
	sfFont *font;
	sfVector2f text_pos;
	sfText *gameover;
	sfEvent event;

	font = sfFont_createFromFile("./arial.ttf");
	gameover = sfText_create();
	text_pos.x = 100;
	text_pos.y = 200;
	sfText_setFont(gameover, font);
	sfText_setString(gameover, "GAME OVER");
	sfText_setCharacterSize(gameover, 100);
	sfText_setColor(gameover, sfWhite);
	sfText_setPosition(gameover, text_pos);
	while (screen == 3) {
		while (sfRenderWindow_pollEvent(window, &event)) {
			analyse_events_gameover(window, event);
		}
		pixel_drawrect(main_texture, pixels, sfRed, 0, 0, width, height);
		sfSprite_setTexture(main_sprite, main_texture, sfTrue);
		sfRenderWindow_drawSprite(window, main_sprite, NULL);
		sfRenderWindow_drawText(window, gameover, NULL);
		sfRenderWindow_display(window);
	}

}
void game_over_w(sfRenderWindow *window, sfUint8 *pixels, sfTexture *main_texture, sfSprite *main_sprite)
{
	sfFont *font;
	sfVector2f text_pos;
	sfText *gameover;
	sfEvent event;

	font = sfFont_createFromFile("./arial.ttf");
	gameover = sfText_create();
	text_pos.x = 100;
	text_pos.y = 200;
	sfText_setFont(gameover, font);
	sfText_setString(gameover, "YOU WON!");
	sfText_setCharacterSize(gameover, 100);
	sfText_setColor(gameover, sfWhite);
	sfText_setPosition(gameover, text_pos);
	while (screen == 3) {
		while (sfRenderWindow_pollEvent(window, &event)) {
			analyse_events_gameover(window, event);
		}
		pixel_drawrect(main_texture, pixels, sfRed, 0, 0, width, height);
		sfSprite_setTexture(main_sprite, main_texture, sfTrue);
		sfRenderWindow_drawSprite(window, main_sprite, NULL);
		sfRenderWindow_drawText(window, gameover, NULL);
		sfRenderWindow_display(window);
	}

}

int main()
{
	sfVideoMode mode = {width, height, 32};
	sfRenderWindow* window = sfRenderWindow_create(mode, "BreakOut v1", sfResize | sfClose, NULL);;
	sfEvent event;
	sfUint8 *pixels;
	sfTexture *texture;
	sfSprite *sprite;

	if ((pixels = malloc(width * height * pixel_buffer)) == NULL)
		return (84);
	sfTexture_updateFromPixels(texture  = sfTexture_create(width, height), pixels, width, height, 0,0);
	sfSprite_setTexture(sprite = sfSprite_create(), texture, sfTrue);
	while (sfRenderWindow_isOpen(window)) {
		if (screen == 0)
			screen = game_menu(window, pixels, texture, sprite);
		if (screen == 1)
			game_main(window, pixels, texture, sprite);
		if (screen == 2)
			game_over_w(window, pixels, texture, sprite);
		if (screen == 3)
			game_over(window, pixels, texture, sprite);
	}
	free(pixels);
}