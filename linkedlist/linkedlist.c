#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <type.h>
#include <linkedlist.h>

linkedlist_t * linkedlist_new(type_t type) {
	linkedlist_t * list = malloc(sizeof(linkedlist_t));
	if (list == NULL) {
		fprintf(stderr, "error: malloc(sizeof(linkedlist_t)) failed\n");
		abort();
	}

	list->size = 0;
	list->type = type;

	return list;
}

value_t linkedlist_at(linkedlist_t * list, size_t index) {
	linkedlist_node_t * node = list->head;
	size_t i = index;
	if (node == NULL) {
			fprintf(stderr, "error: linked list index %llu is out of bounds (%s): %p\n", (long long unsigned int) index, type_get_name(list->type), (void *) list);
		abort();
	}

	for (; i--;) {
		node = (linkedlist_node_t *) node->next;

		if (node == NULL) {
			fprintf(stderr, "error: linked list index %llu is out of bounds (%s): %p\n", (long long unsigned int) index, type_get_name(list->type), (void *) list);
			abort();
		}
	}

	return node->value;
}

void linkedlist_insert(linkedlist_t * list, size_t index, value_t value) {
	linkedlist_node_t * node = list->head;
	linkedlist_node_t * new_node = NULL;
	size_t i = index;

	new_node = malloc(sizeof(linkedlist_node_t));
	if (new_node == NULL) {
		fprintf(stderr, "error: malloc(sizeof(linkedlist_node_t)) failed\n");
		abort();
	}

	new_node->value = value;
	new_node->next = NULL;
	if (list->head == NULL) {
		list->head = new_node;
		++list->size;

		return;
	}

	if (i == 0) {
		new_node->next = list->head;
		list->head = (void *) new_node;
		++list->size;

		return;
	}

	for (; i-- > 1;) {
		node = (linkedlist_node_t *) node->next;

		if (node == NULL) {
			fprintf(stderr, "error: linked list index %llu is out of bounds (%s): %p\n", (long long unsigned int) index, type_get_name(list->type), (void *) list);
			abort();
		}
	}

	if (node->next == NULL) {
		node->next = (void *) new_node;
		++list->size;

		return;
	}

	new_node->next = (void *) node->next;
	node->next = (void *) new_node;
	++list->size;
}

void linkedlist_remove(linkedlist_t * list, size_t index) {
	linkedlist_node_t * node = list->head;
	void * tmp = NULL;

	size_t i = index;
	if (list->head == NULL) {
		fprintf(stderr, "error: linked list can not be indexed, it is of size 0 (%s): %p\n", type_get_name(list->type), (void *) list);
		abort();
	}

	if (i == 0) {
		list->head = node->next;
		free(node);
		--list->size;

		return;
	}

	for (; i-- > 1;) {
		node = (linkedlist_node_t *) node->next;

		if (node == NULL) {
			fprintf(stderr, "error: linked list index %llu is out of bounds (%s): %p\n", (long long unsigned int) index, type_get_name(list->type), (void *) list);
			abort();
		}
	}

	if (((linkedlist_node_t *) node->next)->next == NULL) {
		free(node->next);
		node->next = NULL;
		--list->size;

		return;
	}

	tmp = ((linkedlist_node_t *) node->next)->next;
	free(node->next);
	node->next = tmp;
	--list->size;
}

void linkedlist_clear(linkedlist_t * list) {
	linkedlist_node_t * node = list->head;
	void * tmp = NULL;
	if (list->head == NULL) {
		return;
	}

	for (; node != NULL;) {
		tmp = (void *) node;
		node = node->next;
		free(tmp);
	}

	list->head = NULL;
}

void linkedlist_print(linkedlist_t * list) {
	linkedlist_node_t * node = list->head;
	if (list->head == NULL) {
		printf("linked list (%s): %p: [ EMPTY ]\n", type_get_name(list->type), (void *) list);

		return;
	}

	printf("linked list (%s): %p: [ ", type_get_name(list->type), (void *) list);

	for (; node != NULL; node = (linkedlist_node_t *) node->next) {
		if (list->type == TYPE_PTR) {
			printf("%p", (void *) node->value);
		} else {
			printf(type_get_printf_formatter(list->type), node->value);
		}

		printf(", ");
	}

	puts("]");
}

void linkedlist_free(linkedlist_t * list) {
	linkedlist_node_t * node = list->head;
	void * next = NULL;

	if (node == NULL) {
		return;
	}

	for (; node->next != NULL;) {
		next = node->next;
		free(node);
		node = (linkedlist_node_t *) next;
	}
}
