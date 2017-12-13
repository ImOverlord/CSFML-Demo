/*
** EPITECH PROJECT, 2017
** chianed_link.h
** File description:
** Sample header file for chained link
*/
#include <stdio.h>
#include <stdlib.h>
#include "../include/link.h"

objects *create_list()
{
	objects *head = NULL;

	return (head);
}
objects *get_last(objects *element)
{
	if (!element)
		return (NULL);
	while (element->next) {
		element = element->next;
	}
	return (element);
}
objects *get_first(objects *element)
{
	if (!element)
		return (NULL);
	while (element->previous)
		element = element->previous;
	return (element);
}
objects *add_first(objects *head, struct game_object *data)
{
	objects *current = get_first(head);
	objects *newobjects = (objects*)malloc(sizeof(objects));

	if (newobjects == NULL) {
		exit (84);
	}
	newobjects->game_object = data; 
	newobjects->next = NULL;
	newobjects->previous = NULL;

	if (!current) {
		head = newobjects;
	} else {
		current->previous = newobjects;
		newobjects->next = current;
		head = newobjects;
	}
	return (head);
}
objects *add_end(objects *element, struct game_object *data)
{
	objects *newobjects = (objects*)malloc(sizeof(objects));
	
	if (newobjects == NULL)
		exit(84);
	if (!element)
		return (NULL);
	element = get_last(element);
	element->next = newobjects;
	newobjects->game_object = data;
	newobjects->previous = element;
	newobjects->next = NULL;
	return (newobjects);
}
int size(objects *head)
{
	objects *current = head;
	int counter = 0;

	if (!current)
		return (0);
	while (current) {
		counter++;
		current = current->next;
	}
	return (counter);
}
objects *delete(objects *head, struct game_object *data)
{
	objects *current = head;
	objects *previous = NULL;
	objects *next = NULL;
	if (!current)
		return (NULL);
	while (current) {
		if (current->game_object == data) {
			if (!previous) {
				head = current->next;
			} else {
				previous->next = current->next;
				next = current->next;
				next->previous = previous;
			}
			free(current);
			return (head);
		}
		previous = current;
		current = current->next;
	}
	return (head);
}