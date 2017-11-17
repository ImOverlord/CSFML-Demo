/*
** EPITECH PROJECT, 2017
** file_name.c
** File description:
**	desc
*/
#include <breakout.h>
void analyse_events_game(sfRenderWindow *window, sfEvent event)
{
	if (event.type == sfEvtClosed) {
		window_close(window);
	}
}

void player_mecanics(int *player_stats, int bounce, int score_to_win, sfRenderWindow *window)
{
	if (bounce == 1) {
		player_stats[1] -= 1;
	}
	if (bounce == 2) {
		player_stats[0] += 1;
	}
	if (player_stats[1] == 0) {
		printf("LOSE");
		screen_manager(3);
	}
	if (player_stats[0] >= score_to_win) {
		printf("WIN");
		screen_manager(2);
	}
}

void paddel_mouvement(sfRenderWindow *window, sfTexture *texture, sfUint8 *pixels, int *player_pos)
{
	if (sfKeyboard_isKeyPressed(sfKeyLeft))
		player_pos[0] -= paddel_speed;
	if (sfKeyboard_isKeyPressed(sfKeyRight))
		player_pos[0] += paddel_speed;
	if (player_pos[0] < 0)
		player_pos[0] = 0;
	if (player_pos[0] > (width-paddel_width))
		player_pos[0] = width - paddel_width;
	pixel_drawrect(texture, pixels, sfRed, player_pos[0], player_pos[1], paddel_width, paddel_height);
}

void bounce_wall_x(int *_ball)
{
	if (_ball[0] < 1) {
		_ball[0] = 0;
		_ball[2] *= -1;
	}
	if (_ball[0] > width) {
		_ball[0] = width-ball_size;
		_ball[2] *= -1;
	}
}

int bounce_wall_y(int *_ball)
{
	if (_ball[1] < 1) {
		_ball[1] = 0;
		_ball[3] *= -1;
	}
	if (_ball[1] >= (height-ball_size)) {
		_ball[0] = (width/2) - (ball_size/2);
		_ball[1] = 300;
		_ball[2] = 0;
		_ball[3] = ball_speed;
		return (1);
	}
	return (0);
}

int ball_mouvement(sfRenderWindow *window, sfTexture *texture, sfUint8 *pixels, int *_ball)
{
	int out_of_bound = 0;
	_ball[0] += _ball[2];
	_ball[1] += _ball[3];
	bounce_wall_x(_ball);
	out_of_bound = bounce_wall_y(_ball);
	pixel_drawrect(texture, pixels, sfRed, _ball[0], _ball[1], ball_size, ball_size);
	return (out_of_bound);
}

int box_ball(int **box, int *_ball, int box_count){
	for (int i=0; i < box_count; i++) {
		if (box[2][i] != -1 && box[0][i] < _ball[0] + 10 &&
		box[0][i] + box_size_w > _ball[0] &&
		box[1][i] < _ball[1] + 10 &&
		box_size_h + box[1][i] > _ball[1]) {
			box[2][i] -= 1;
			if (box[2][i] == 0) {
				box[0][i] = -1;
				box[1][i] = -1;
				box[2][i] = -1;
			}
			_ball[3] *= -1;
			_ball[1] += _ball[3] * 2; //Prevents cliping
			_ball[0] += _ball[2] * -2;
			return (1);
		}
	}
	return (0);
}

int paddel_ball(int *player_pos, int *_ball)
{
	if (player_pos[0] < _ball[0] + ball_size &&
	player_pos[0] + paddel_width/2-5 > _ball[0] &&
	player_pos[1] < _ball[1] + ball_size &&
	paddel_height + player_pos[1] > _ball[1]) {
		if (_ball[2] >= 0 )
			_ball[2] = -ball_speed;
		_ball[3] *= -1;
		return (0);
	}
	if (player_pos[0] + paddel_width/2 < _ball[0] + ball_size &&
	player_pos[0] + paddel_width > _ball[0] &&
	player_pos[1] < _ball[1] + ball_size &&
	paddel_height + player_pos[1] > _ball[1]) {
		if (_ball[2] <= 0 )
			_ball[2] = ball_speed;
		_ball[3] *= -1;
		return (0);
	}
}

int draw_box(sfTexture *texture, sfUint8 *pixels, int **box, int box_count)
{
	sfColor color;
	for (int i = 0; i < box_count; i++) {
		if (box[0][i] != -1) {
			if (box[2][i] == 1)
				color = sfYellow;
			if (box[2][i] == 2)
				color = sfBlue;
			if (box[2][i] == 3)
				color = sfMagenta;
			pixel_drawrect(texture, pixels, color, box[0][i], box[1][i], box_size_w, box_size_h);
		}
	}
}

int get_box_count()
{
	int fd = open("level_info", O_RDONLY);
	char buff[reading_buffer];
	int size = read(fd, buff, reading_buffer);

	return (atoi(buff));
}

int box_populator(int **box, int box_count)
{
	int score_to_win = 0;
	int x_coords[reading_buffer];
	int fd = open("level",O_RDONLY);
	char buff[reading_buffer];
	int size = read(fd, buff, reading_buffer);
	int j = 0;
	int k = 0;
	int c = 0;
	char tmp_buff[reading_buffer];

	for (int i=0; i < 3; i++) {
		box[i] = (int *)malloc(box_count * sizeof(int));
		if (box[i] == NULL) {
			exit(84);
		}
	}
	for (int z = 0; z < 3; z++) {
		c = 0;
		while (c < box_count) {
			k = 0;
			while (buff[j] != ',' && buff[j] != '\n') {
				tmp_buff[k] = buff[j];
				k++;
				j++;
			}
			tmp_buff[k] = '\0';
			j++;
			box[z][c] = atoi(tmp_buff);
			c++;
		}
	}
	for (int i = 0; i < box_count; i++) {
		score_to_win += box[2][i];
	}	
	return (score_to_win);
}

void render(sfRenderWindow *window, sfTexture *texture, sfUint8 *pixels, sfSprite *main_sprite)
{
	sfSprite_setTexture(main_sprite, texture, sfTrue);
	sfRenderWindow_drawSprite(window, main_sprite, NULL);
	sfRenderWindow_display(window);
	pixel_drawrect(texture, pixels, sfBlack, 0, 0, width, height);
}