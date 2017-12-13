/*
** EPITECH PROJECT, 2017
** file_name.c
** File description:
** desc
*/

#include "../include/link.h"
#include <SFML/Graphics.h>

struct game_object *create(int id)
{
	struct game_object *obj = malloc(sizeof(game_object_t));

	obj->id = id;
	return (obj);
}

sfIntRect move_rect(sfIntRect spritesheet_rect, int offset, int max_value)
{
	if (spritesheet_rect.left == max_value - offset) {
		spritesheet_rect.left = 0;
	} else {
		spritesheet_rect.left += offset;
	}
	
	return (spritesheet_rect);
}

void game_move(objects *obj_list)
{
	objects *current = obj_list;

	while (current) {
		current->game_object->position.x += current->game_object->speed;
		if (current->game_object->position.x >= 640) {
			current->game_object->position.x = -640;
		}
		if (current->game_object->type == 2) {
			current->game_object->rectangle = move_rect(current->game_object->rectangle, current->game_object->rectangle.width, 576);
			sfSprite_setTextureRect(current->game_object->sprite, current->game_object->rectangle);
		}
		sfSprite_setPosition(current->game_object->sprite, current->game_object->position);
		current = current->next;
	}
}
void destroy_gameobject(struct game_object *obj)
{
	sfSprite_destroy(obj->sprite);
	sfTexture_destroy(obj->texture);
}

struct game_object *create_object(const char *path_to_spritesheet,
sfVector2f pos, sfIntRect rect, int id)
{
	struct game_object *new_obj = malloc(sizeof(game_object_t));

	sfSprite *sprite;
	sfTexture *texture;
	
	texture = sfTexture_createFromFile(path_to_spritesheet, NULL);
	if (texture == NULL) {
		printf("Error\n");
	}
	sprite = sfSprite_create();
	sfSprite_setTexture(sprite, texture, sfTrue);
	sfSprite_setPosition(sprite, pos);
	new_obj->sprite = sprite;
	new_obj->texture = texture;
	new_obj->position = pos;
	new_obj->rectangle = rect;
	new_obj->type = 1;
	new_obj->speed = id;

	return(new_obj);
}

struct game_object *add_animation(const char *path_to_spritesheet,
sfVector2f pos, sfIntRect rect, int id)
{
	struct game_object *new_obj = malloc(sizeof(game_object_t));

	sfSprite *sprite;
	sfTexture *texture;
	sfVector2f scale = {-1,1};
	
	texture = sfTexture_createFromFile(path_to_spritesheet, NULL);
	if (texture == NULL) {
		printf("Error\n");
	}
	sprite = sfSprite_create();
	sfSprite_setTexture(sprite, texture, sfTrue);
	sfSprite_setScale(sprite, scale);
	sfSprite_setTextureRect(sprite, rect);
	sfSprite_setPosition(sprite, pos);
	new_obj->sprite = sprite;
	new_obj->texture = texture;
	new_obj->position = pos;
	new_obj->rectangle = rect;
	new_obj->type = 2;
	new_obj->speed = id;

	return(new_obj);
}

int main(int ac, char *argv[])
{
	objects *obj_list = create_list();
	objects *current = NULL;
	sfVector2f pos = {0,0};
	sfIntRect rect = {0,0,576/6,101};
	pos.x = 600;
	pos.y = 300;
	obj_list = add_first(obj_list, add_animation("./sprite/spritesheet.png", pos, rect, 0));
	pos.x = 0;
	pos.y = 0;
	obj_list = add_first(obj_list, create_object("./sprite/Ground.png", pos, rect, 8));
	pos.x = -640;
	pos.y = 0;
	obj_list = add_first(obj_list, create_object("./sprite/Ground.png", pos, rect, 8));
	pos.x = 0;
	pos.y = 0;
	obj_list = add_first(obj_list, create_object("./sprite/Vegetation.png", pos, rect, 2));
	pos.x = -640;
	pos.y = 0;
	obj_list = add_first(obj_list, create_object("./sprite/Vegetation.png", pos, rect, 2));
	pos.x = 0;
	pos.y = 0;
	obj_list = add_first(obj_list, create_object("./sprite/Sky.png", pos, rect, 1));
	pos.x = -640;
	pos.y = 0;
	obj_list = add_first(obj_list, create_object("./sprite/Sky.png", pos, rect, 1));
	obj_list = get_first(obj_list);
	current = obj_list;
	sfVideoMode mode = {640, 480, 32};
	sfRenderWindow* window;
	sfEvent event;
	sfClock *clock;
	sfTime time;
	float seconds = 0.0;

	clock = sfClock_create();
	window = sfRenderWindow_create(mode, "Window", sfResize | sfClose, NULL);
	sfRenderWindow_setFramerateLimit(window, 60);
	while (sfRenderWindow_isOpen(window)) {
		while (sfRenderWindow_pollEvent(window, &event)) {
			if (event.type == sfEvtClosed) {
				sfRenderWindow_close(window);
				return (0);
			}
		}
		
		time = sfClock_getElapsedTime(clock);
		seconds = time.microseconds / 1000000.0;
		if (seconds > 0.1) {
			sfRenderWindow_clear(window, sfWhite);
			current = obj_list;
			while (current) {
				sfRenderWindow_drawSprite(window, current->game_object->sprite, NULL);
				current = current->next;
			}
			game_move(obj_list);
			sfClock_restart(clock);
			seconds = 0.0;
			sfRenderWindow_display(window);
		}
		
	}
	current = obj_list;
	while (current) {
		sfSprite_destroy(current->game_object->sprite);
		sfTexture_destroy(current->game_object->texture);
		free(current->game_object);
		current = current->next;
		free(current);
	}
	sfRenderWindow_destroy(window);
}

