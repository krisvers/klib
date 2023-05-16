#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <type.h>
#include <stack.h>

stack_t * stack_new(type_t type, size_t max) {
	stack_t * stack = malloc(sizeof(stack_t));
	if (stack == NULL) {
		return NULL;
	}

	stack->max = max;
	stack->size = 0;
	stack->type = type;
	DO_FOR_EACH_TYPE(type, \
		stack->array = NULL, \
		stack->array = malloc(sizeof(uint8_t) * max), \
		stack->array = malloc(sizeof(uint16_t) * max), \
		stack->array = malloc(sizeof(uint32_t) * max), \
		stack->array = malloc(sizeof(uint64_t) * max), \
		stack->array = malloc(sizeof(int8_t) * max), \
		stack->array = malloc(sizeof(int16_t) * max), \
		stack->array = malloc(sizeof(int32_t) * max), \
		stack->array = malloc(sizeof(int64_t) * max), \
		stack->array = malloc(sizeof(ptr_t) * max) \
	);

	return stack;
}

void stack_push(stack_t * stack, value_t value) {
	if (stack->size == stack->max) {
		return;
	}

	DO_FOR_EACH_TYPE(stack->type, \
		break, \
		((uint8_t *) stack->array)[stack->size] = (uint8_t) value, \
		((uint16_t *) stack->array)[stack->size] = (uint16_t) value, \
		((uint32_t *) stack->array)[stack->size] = (uint32_t) value, \
		((uint64_t *) stack->array)[stack->size] = (uint64_t) value, \
		((int8_t *) stack->array)[stack->size] = (int8_t) value, \
		((int16_t *) stack->array)[stack->size] = (int16_t) value, \
		((int32_t *) stack->array)[stack->size] = (int32_t) value, \
		((int64_t *) stack->array)[stack->size] = (int64_t) value, \
		((ptr_t *) stack->array)[stack->size] = (ptr_t) (uintptr_t) value \
	);

	++stack->size;

	return;
}

value_t stack_pop(stack_t * stack) {
	value_t value;
	
	if (--stack->size <= 0) {
		return -1;
	}

	DO_FOR_EACH_TYPE(stack->type, \
		value = (value_t) (arithptr_t) NULL, \
		value = (value_t) ((uint8_t *) stack->array)[stack->size], \
		value = (value_t) ((uint16_t *) stack->array)[stack->size], \
		value = (value_t) ((uint32_t *) stack->array)[stack->size], \
		value = (value_t) ((uint64_t *) stack->array)[stack->size], \
		value = (value_t) ((int8_t *) stack->array)[stack->size], \
		value = (value_t) ((int16_t *) stack->array)[stack->size], \
		value = (value_t) ((int32_t *) stack->array)[stack->size], \
		value = (value_t) ((int64_t *) stack->array)[stack->size], \
		value = (value_t) (arithptr_t) ((ptr_t *) stack->array)[stack->size] \
	);

	return value;
}

value_t stack_peek(stack_t * stack) {
	value_t value;

	DO_FOR_EACH_TYPE(stack->type, \
		value = (value_t) (arithptr_t) NULL, \
		value = (value_t) ((uint8_t *) stack->array)[stack->size - 1], \
		value = (value_t) ((uint16_t *) stack->array)[stack->size - 1], \
		value = (value_t) ((uint32_t *) stack->array)[stack->size - 1], \
		value = (value_t) ((uint64_t *) stack->array)[stack->size - 1], \
		value = (value_t) ((int8_t *) stack->array)[stack->size - 1], \
		value = (value_t) ((int16_t *) stack->array)[stack->size - 1], \
		value = (value_t) ((int32_t *) stack->array)[stack->size - 1], \
		value = (value_t) ((int64_t *) stack->array)[stack->size - 1], \
		value = (value_t) (arithptr_t) ((ptr_t *) stack->array)[stack->size - 1] \
	);

	return value;
}

void stack_clear(stack_t * stack) {
	for (; --stack->size;) {
		DO_FOR_EACH_TYPE(stack->type, \
			;, \
			((uint8_t *) stack->array)[stack->size] = 0, \
			((uint16_t *) stack->array)[stack->size] = 0, \
			((uint32_t *) stack->array)[stack->size] = 0, \
			((uint64_t *) stack->array)[stack->size] = 0, \
			((int8_t *) stack->array)[stack->size] = 0, \
			((int16_t *) stack->array)[stack->size] = 0, \
			((int32_t *) stack->array)[stack->size] = 0, \
			((int64_t *) stack->array)[stack->size] = 0, \
			((ptr_t *) stack->array)[stack->size] = NULL \
		);
	}
}
