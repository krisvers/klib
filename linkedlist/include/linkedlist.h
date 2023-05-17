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

#endif
