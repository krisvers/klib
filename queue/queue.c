#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <type.h>
#include <queue.h>

queue_t * queue_new(type_t type, size_t max) {
	queue_t * queue = malloc(sizeof(queue_t));
	if (queue == NULL) {
		fprintf(stderr, "error: malloc(sizeof(queue_t)) failed\n");
		abort();
	}

	queue->max = max;
	queue->size = 0;
	queue->type = type;
	
	if (max != 0) {
		DO_FOR_EACH_TYPE(type, \
			queue->array = NULL, \
			queue->array = malloc(sizeof(uint8_t) * max), \
			queue->array = malloc(sizeof(uint16_t) * max), \
			queue->array = malloc(sizeof(uint32_t) * max), \
			queue->array = malloc(sizeof(uint64_t) * max), \
			queue->array = malloc(sizeof(int8_t) * max), \
			queue->array = malloc(sizeof(int16_t) * max), \
			queue->array = malloc(sizeof(int32_t) * max), \
			queue->array = malloc(sizeof(int64_t) * max), \
			queue->array = malloc(sizeof(ptr_t) * max) \
		);
	}

	return queue;
}

void queue_free(queue_t * queue) {
	if (queue == NULL) {
		fprintf(stderr, "error: cannot free NULL queue\n");
		abort();
	}

	if (queue->max == 0) {
		free(queue->array);
	}

	free((void *) queue);
}

void queue_push(queue_t * queue, value_t value) {
	if (queue->max != 0 && queue->size >= queue->max) {
		fprintf(stderr, "error: queue overflow (%s): %p\n", type_get_name(queue->type), (void *) queue);
		abort();
	}

	if (queue->max == 0) {
		DO_FOR_EACH_TYPE(queue->type, \
			break, \
			queue->array = realloc(queue->array, (size_t) (((arithptr_t) queue->size) + 1) * sizeof(uint8_t)), \
			queue->array = realloc(queue->array, (size_t) (((arithptr_t) queue->size) + 1) * sizeof(uint16_t)), \
			queue->array = realloc(queue->array, (size_t) (((arithptr_t) queue->size) + 1) * sizeof(uint32_t)), \
			queue->array = realloc(queue->array, (size_t) (((arithptr_t) queue->size) + 1) * sizeof(uint64_t)), \
			queue->array = realloc(queue->array, (size_t) (((arithptr_t) queue->size) + 1) * sizeof(int8_t)), \
			queue->array = realloc(queue->array, (size_t) (((arithptr_t) queue->size) + 1) * sizeof(int16_t)), \
			queue->array = realloc(queue->array, (size_t) (((arithptr_t) queue->size) + 1) * sizeof(int32_t)), \
			queue->array = realloc(queue->array, (size_t) (((arithptr_t) queue->size) + 1) * sizeof(int64_t)), \
			queue->array = realloc(queue->array, (size_t) (((arithptr_t) queue->size) + 1) * sizeof(ptr_t)) \
		);
	}

	DO_FOR_EACH_TYPE(queue->type, \
		break, \
		((uint8_t *) queue->array)[queue->size] = (uint8_t) value, \
		((uint16_t *) queue->array)[queue->size] = (uint16_t) value, \
		((uint32_t *) queue->array)[queue->size] = (uint32_t) value, \
		((uint64_t *) queue->array)[queue->size] = (uint64_t) value, \
		((int8_t *) queue->array)[queue->size] = (int8_t) value, \
		((int16_t *) queue->array)[queue->size] = (int16_t) value, \
		((int32_t *) queue->array)[queue->size] = (int32_t) value, \
		((int64_t *) queue->array)[queue->size] = (int64_t) value, \
		((ptr_t *) queue->array)[queue->size] = (ptr_t) (uintptr_t) value \
	);

	if (queue->size == SIZE_MAX) {
		fprintf(stderr, "error: queue overflow (%s): %p\n", type_get_name(queue->type), (void *) queue);
		abort();
	}

	++queue->size;

	return;
}

value_t queue_pop(queue_t * queue) {
	value_t value;
	
	if (queue->size == 0) {
		fprintf(stderr, "error: queue underflow (%s): %p\n", type_get_name(queue->type), (void *) queue);
		abort();
	}

	--queue->size;

	DO_FOR_EACH_TYPE(queue->type, \
		value = (value_t) (arithptr_t) NULL, \
		value = (value_t) ((uint8_t *) queue->array)[0], \
		value = (value_t) ((uint16_t *) queue->array)[0], \
		value = (value_t) ((uint32_t *) queue->array)[0], \
		value = (value_t) ((uint64_t *) queue->array)[0], \
		value = (value_t) ((int8_t *) queue->array)[0], \
		value = (value_t) ((int16_t *) queue->array)[0], \
		value = (value_t) ((int32_t *) queue->array)[0], \
		value = (value_t) ((int64_t *) queue->array)[0], \
		value = (value_t) (arithptr_t) ((ptr_t *) queue->array)[0] \
	);

/* shift the entire queue to left
**	memmove(queue->array, (void *) (((arithptr_t) queue->array) + 1), queue->size - 1);
*/

	if (queue->max == 0) {
		DO_FOR_EACH_TYPE(queue->type, \
			break, \
			queue->array = realloc(queue->array, (size_t) ((arithptr_t) queue->size) * sizeof(uint8_t)), \
			queue->array = realloc(queue->array, (size_t) ((arithptr_t) queue->size) * sizeof(uint16_t)), \
			queue->array = realloc(queue->array, (size_t) ((arithptr_t) queue->size) * sizeof(uint32_t)), \
			queue->array = realloc(queue->array, (size_t) ((arithptr_t) queue->size) * sizeof(uint64_t)), \
			queue->array = realloc(queue->array, (size_t) ((arithptr_t) queue->size) * sizeof(int8_t)), \
			queue->array = realloc(queue->array, (size_t) ((arithptr_t) queue->size) * sizeof(int16_t)), \
			queue->array = realloc(queue->array, (size_t) ((arithptr_t) queue->size) * sizeof(int32_t)), \
			queue->array = realloc(queue->array, (size_t) ((arithptr_t) queue->size) * sizeof(int64_t)), \
			queue->array = realloc(queue->array, (size_t) ((arithptr_t) queue->size) * sizeof(ptr_t)) \
		);
	}

	return value;
}

value_t queue_front(queue_t * queue) {
	value_t value;

	if (queue->size == 0) {
		fprintf(stderr, "error: queue cannot access first element, queue->size is 0 (%s): %p\n", type_get_name(queue->type), (void *) queue);
		abort();
	}

	DO_FOR_EACH_TYPE(queue->type, \
		value = (value_t) (arithptr_t) NULL, \
		value = (value_t) ((uint8_t *) queue->array)[queue->size - 1], \
		value = (value_t) ((uint16_t *) queue->array)[queue->size - 1], \
		value = (value_t) ((uint32_t *) queue->array)[queue->size - 1], \
		value = (value_t) ((uint64_t *) queue->array)[queue->size - 1], \
		value = (value_t) ((int8_t *) queue->array)[queue->size - 1], \
		value = (value_t) ((int16_t *) queue->array)[queue->size - 1], \
		value = (value_t) ((int32_t *) queue->array)[queue->size - 1], \
		value = (value_t) ((int64_t *) queue->array)[queue->size - 1], \
		value = (value_t) (arithptr_t) ((ptr_t *) queue->array)[queue->size - 1] \
	);

	return value;
}

value_t queue_back(queue_t * queue) {
	value_t value;

	if (queue->size == 0) {
		fprintf(stderr, "error: queue cannot access last element, queue->size is 0 (%s): %p\n", type_get_name(queue->type), (void *) queue);
		abort();
	}

	DO_FOR_EACH_TYPE(queue->type, \
		value = (value_t) (arithptr_t) NULL, \
		value = (value_t) ((uint8_t *) queue->array)[queue->size - 1], \
		value = (value_t) ((uint16_t *) queue->array)[queue->size - 1], \
		value = (value_t) ((uint32_t *) queue->array)[queue->size - 1], \
		value = (value_t) ((uint64_t *) queue->array)[queue->size - 1], \
		value = (value_t) ((int8_t *) queue->array)[queue->size - 1], \
		value = (value_t) ((int16_t *) queue->array)[queue->size - 1], \
		value = (value_t) ((int32_t *) queue->array)[queue->size - 1], \
		value = (value_t) ((int64_t *) queue->array)[queue->size - 1], \
		value = (value_t) (arithptr_t) ((ptr_t *) queue->array)[queue->size - 1] \
	);

	return value;
}

void queue_clear(queue_t * queue) {
	if (queue->max == 0) {
		queue->array = realloc(queue->array, 0);
		queue->size = 0;

		return;
	}

	for (; --queue->size;) {
		DO_FOR_EACH_TYPE(queue->type, \
			;, \
			((uint8_t *) queue->array)[queue->size] = 0, \
			((uint16_t *) queue->array)[queue->size] = 0, \
			((uint32_t *) queue->array)[queue->size] = 0, \
			((uint64_t *) queue->array)[queue->size] = 0, \
			((int8_t *) queue->array)[queue->size] = 0, \
			((int16_t *) queue->array)[queue->size] = 0, \
			((int32_t *) queue->array)[queue->size] = 0, \
			((int64_t *) queue->array)[queue->size] = 0, \
			((ptr_t *) queue->array)[queue->size] = NULL \
		);
	}
}

void queue_print(queue_t * queue) {
	value_t i = 0;
	ptr_t ptr = queue->array;

	if (queue->size == 0 || (queue->size > queue->max && queue->max != 0)) {
		printf("queue (%s): %p: [ EMPTY ]\n", type_get_name(queue->type), (void *) queue);

		return;
	}

	printf("queue (%s): %p: [ ", type_get_name(queue->type), (void *) queue);

	for (; i < queue->size; i++) {
		if (queue->type == TYPE_PTR) {
			printf("%p", *((void **) ptr));
		} else {
			printf(type_get_printf_formatter(queue->type), type_ptr_dereference(queue->type, ptr));
		}

		printf(", ");
		ptr = type_ptr_value_add(ptr, type_sizeof(queue->type));
	}

	puts("]");
}
