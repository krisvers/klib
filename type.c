#include "type.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

size_t type_sizeof(type_t type) {
	switch (type) {
		case TYPE_VOID:	return 0;
		case TYPE_U8:
		case TYPE_I8:	return sizeof(uint8_t);
		case TYPE_U16:
		case TYPE_I16:	return sizeof(uint16_t);
		case TYPE_U32:
		case TYPE_I32:	return sizeof(uint32_t);
		case TYPE_U64:
		case TYPE_I64:	return sizeof(uint64_t);
		case TYPE_PTR:	return sizeof(ptr_t);
		default: return 0;
	}

	return 0;
}

value_t type_value_ptr(type_t type, ptr_t ptr) {
	DO_FOR_EACH_TYPE(type, \
		return (value_t) (uintptr_t) NULL, \
		return (value_t) *((uint8_t *) ptr), \
		return (value_t) *((uint16_t *) ptr), \
		return (value_t) *((uint32_t *) ptr), \
		return (value_t) *((uint64_t *) ptr), \
		return (value_t) *((int8_t *) ptr), \
		return (value_t) *((int16_t *) ptr), \
		return (value_t) *((int32_t *) ptr), \
		return (value_t) *((int64_t *) ptr), \
		return (value_t) (uintptr_t) *((ptr_t *) ptr) \
	);

	return (value_t) (uintptr_t) NULL;
}

ptr_t type_ptr_value_add(ptr_t ptr, value_t value) {
	return (ptr_t) (arithptr_t) (((arithptr_t) ptr) + value);
}

ptr_t type_ptr_value_sub(ptr_t ptr, value_t value) {
	return (ptr_t) (arithptr_t) (((arithptr_t) ptr) - value);
}

char * type_printf_formatter(type_t type) {
	char * str = malloc(5);

	DO_FOR_EACH_TYPE(type, \
		return strcpy(str, "\0"), \
		return strcpy(str, "%u"), \
		return strcpy(str, "%u"), \
		return strcpy(str, "%u"), \
		return strcpy(str, "%llu"), \
		return strcpy(str, "%i"), \
		return strcpy(str, "%i"), \
		return strcpy(str, "%i"), \
		return strcpy(str, "%lli"), \
		return strcpy(str, "%p") \
	);

	return str;
}
