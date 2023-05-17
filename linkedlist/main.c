#include <type.h>
#include <linkedlist.h>

int main(void) {
	linkedlist_t * list = linkedlist_new(TYPE_U64);
	linkedlist_append(list, 69420);

	linkedlist_print(list);

	linkedlist_free(list);

	return 0;
}
