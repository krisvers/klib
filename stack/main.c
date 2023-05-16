#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <type.h>
#include "stack.h"

void print(stack_t * stack) {
	value_t i = 0;
	ptr_t ptr = stack->array;

	for (; i < stack->size; i++) {
		printf("%llu: %llu\n", i, type_value_ptr(stack->type, ptr));

		ptr = type_ptr_value_add(ptr, type_sizeof(stack->type));
	}
}

int main(void) {
	stack_t * stack = stack_new(TYPE_I32, 20);

	stack_push(stack, 69);
	stack_push(stack, 420);

	print(stack);

	printf("%llu\n", stack_pop(stack));
	printf("%llu\n", stack_pop(stack));
	printf("%llu\n", stack_pop(stack));

	free(stack);

	return 0;
}
