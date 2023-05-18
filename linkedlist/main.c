#include <stdio.h>
#include <string.h>
#include <type.h>
#include <linkedlist.h>

int main(void) {
	linkedlist_t * list = linkedlist_new(TYPE_U64);
	printf("new TYPE_U64\n");
	linkedlist_print(list);

	printf("\ninsert [0] 2\n");
	linkedlist_insert(list, 0, 2);
	linkedlist_print(list);

	printf("\nremove [0]\n");
	linkedlist_remove(list, 0);
	linkedlist_print(list);

	printf("\ninsert [0] 69420\n");
	linkedlist_insert(list, 0, 69420);
	linkedlist_print(list);

	printf("\ninsert [0] 52\n");
	linkedlist_insert(list, 0, 52);
	linkedlist_print(list);

	printf("\nclear\n");
	linkedlist_clear(list);
	linkedlist_print(list);

	printf("\ninsert [0] 24242231\n");
	linkedlist_insert(list, 0, 24242231);
	linkedlist_print(list);

	printf("\ninsert [1] 58234\n");
	linkedlist_insert(list, 1, 58234);
	linkedlist_print(list);

	printf("\ninsert [1] 32\n");
	linkedlist_insert(list, 1, 32);
	linkedlist_print(list);

	printf("\ninsert [0] 23\n");
	linkedlist_insert(list, 0, 23);
	linkedlist_print(list);

	printf("\nat [0]: %llu\n", (long long unsigned int) linkedlist_at(list, 0));
	linkedlist_print(list);

	linkedlist_free(list);

	return 0;
}
