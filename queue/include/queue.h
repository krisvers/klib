#ifndef STACK_H
#define STACK_H

#include <stdint.h>
#include <stddef.h>
#include <type.h>

typedef struct {
	size_t size;
	size_t max;
	type_t type;
	void * array;
} queue_t;

queue_t * queue_new(type_t type, size_t size);
void queue_free(queue_t * queue);
void queue_push(queue_t * queue, value_t value);
value_t queue_pop(queue_t * queue);
value_t queue_peek(queue_t * queue);
void queue_clear(queue_t * queue);
void queue_print(queue_t * queue);

#endif
