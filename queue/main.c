#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <type.h>
#include <queue.h>

int main(void) {
	queue_t * queue = queue_new(TYPE_U64, 0);
	if (queue == NULL) {
		printf("malloc error\n");
		return -1;
	}

	printf("empty\n");
	queue_print(queue);

	size_t last = 0;
	size_t tmp = last;
	for (size_t i = 1; i < 7000;) {
		queue_push(queue, i);
		queue_print(queue);
		tmp = last;
		last = i;
		i += tmp;
	}

	printf("pop\n");

	for (; queue->size;) {
		queue_pop(queue);
		queue_print(queue);
	}

	queue_free(queue);
	return 0;
}
