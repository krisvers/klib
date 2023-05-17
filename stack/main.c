#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <type.h>
#include <stack.h>

int main(void) {
	stack_t * stack = stack_new(TYPE_U16, 0);
	if (stack == NULL) {
		printf("malloc error\n");
		return -1;
	}

	printf("empty\n");
	stack_print(stack);

	size_t last = 0;
	size_t tmp = last;
	for (size_t i = 1; i < 70000;) {
		stack_push(stack, i);
		stack_print(stack);
		tmp = last;
		last = i;
		i += tmp;
	}

	for (; stack->size;) {
		stack_pop(stack);
		stack_print(stack);
	}

	stack_free(stack);
	return 0;
}
