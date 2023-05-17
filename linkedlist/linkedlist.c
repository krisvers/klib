#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <type.h>

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

void linkedlist_append(linkedlist_t * list, value_t value) {
	linkedlist_node_t * node = malloc(sizeof(linkedlist_node_t));
	if (node == NULL) {
		fprintf(stderr, "error: malloc(sizeof(linkedlist_node_t)) failed\n");
		abort();
	}

	if (list->head == NULL) {
		node->value = value;
		list->head = (void *) node;

		return;
	}

	node->next = list->head;
	node->value = value;
	list->head = (void *) node;
}


