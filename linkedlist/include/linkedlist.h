#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdint.h>
#include <stddef.h>
#include <type.h>

typedef struct {
	void * next;
	value_t value;
} linkedlist_node_t;

typedef struct {
	void * head;
	size_t size;
	type_t type;
} linkedlist_t;

linkedlist_t * linkedlist_new(type_t type);
value_t linkedlist_at(linkedlist_t * list, size_t index);
void linkedlist_insert(linkedlist_t * list, size_t index, value_t value);
void linkedlist_remove(linkedlist_t * list, size_t index);
void linkedlist_clear(linkedlist_t * list);
void linkedlist_print(linkedlist_t * list);
void linkedlist_free(linkedlist_t * list);

#endif
