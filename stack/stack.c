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
	
	if (max != 0) {
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
	}

	return stack;
}

void stack_push(stack_t * stack, value_t value) {
	if (stack->max != 0 && stack->size >= stack->max) {
		printf("warning: stack (%s): %p is already full!\n", type_names[stack->type], (void *) stack);

		return;
	}

	if (stack->max == 0) {
		DO_FOR_EACH_TYPE(stack->type, \
			break, \
			stack->array = realloc(stack->array, (((arithptr_t) stack->size) + 1) * sizeof(uint8_t)), \
			stack->array = realloc(stack->array, (((arithptr_t) stack->size) + 1) * sizeof(uint16_t)), \
			stack->array = realloc(stack->array, (((arithptr_t) stack->size) + 1) * sizeof(uint32_t)), \
			stack->array = realloc(stack->array, (((arithptr_t) stack->size) + 1) * sizeof(uint64_t)), \
			stack->array = realloc(stack->array, (((arithptr_t) stack->size) + 1) * sizeof(int8_t)), \
			stack->array = realloc(stack->array, (((arithptr_t) stack->size) + 1) * sizeof(int16_t)), \
			stack->array = realloc(stack->array, (((arithptr_t) stack->size) + 1) * sizeof(int32_t)), \
			stack->array = realloc(stack->array, (((arithptr_t) stack->size) + 1) * sizeof(int64_t)), \
			stack->array = realloc(stack->array, (((arithptr_t) stack->size) + 1) * sizeof(ptr_t)) \
		);
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
	
	if (stack->size == 0) {
		printf("warning: stack (%s): %p is already empty!\n", type_names[stack->type], (void *) stack);

		return -1;
	}

	--stack->size;

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

	if (stack->max == 0) {
		DO_FOR_EACH_TYPE(stack->type, \
			break, \
			stack->array = realloc(stack->array, ((arithptr_t) stack->size) * sizeof(uint8_t)), \
			stack->array = realloc(stack->array, ((arithptr_t) stack->size) * sizeof(uint16_t)), \
			stack->array = realloc(stack->array, ((arithptr_t) stack->size) * sizeof(uint32_t)), \
			stack->array = realloc(stack->array, ((arithptr_t) stack->size) * sizeof(uint64_t)), \
			stack->array = realloc(stack->array, ((arithptr_t) stack->size) * sizeof(int8_t)), \
			stack->array = realloc(stack->array, ((arithptr_t) stack->size) * sizeof(int16_t)), \
			stack->array = realloc(stack->array, ((arithptr_t) stack->size) * sizeof(int32_t)), \
			stack->array = realloc(stack->array, ((arithptr_t) stack->size) * sizeof(int64_t)), \
			stack->array = realloc(stack->array, ((arithptr_t) stack->size) * sizeof(ptr_t)) \
		);
	}

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
	if (stack->max == 0) {
		stack->array = realloc(stack->array, 0);
		stack->size = 0;

		return;
	}

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

void stack_print(stack_t * stack) {
	value_t i = 0;
	ptr_t ptr = stack->array;

	if (stack->size == 0 || (stack->size > stack->max && stack->max != 0)) {
		printf("stack (%s): %p: [ EMPTY ]\n", type_names[stack->type], (void *) stack);

		return;
	}

	printf("stack (%s): %p: [ ", type_names[stack->type], (void *) stack);

	for (; i < stack->size; i++) {
		printf(type_printf_formatter[stack->type], type_ptr_dereference(stack->type, ptr));
		printf(", ");

		ptr = type_ptr_value_add(ptr, type_sizeof(stack->type));
	}

	puts("]");
}
