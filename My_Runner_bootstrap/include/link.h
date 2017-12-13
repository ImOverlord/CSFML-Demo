/*
** EPITECH PROJECT, 2017
** file_name.h
** File description:
** desc
*/

#ifndef LINK_H_
#define LINK_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SFML/Graphics.h>

struct game_object {
	int id;
	int type;
	int speed;
	sfSprite *sprite;
	sfTexture *texture;
	sfVector2f position;
	sfIntRect rectangle;
} game_object_t;

typedef struct objects_t {
	struct game_object *game_object;
	struct objects_t *next;
	struct objects_t *previous;
} objects;

objects *create_list();
objects *get_last(objects *element);
objects *get_first(objects *element);
objects *add_first(objects *head, struct game_object *data);
objects *add_end(objects *element, struct game_object *data);
int size(objects *head);
objects *delete(objects *head, struct game_object *data);
#endif