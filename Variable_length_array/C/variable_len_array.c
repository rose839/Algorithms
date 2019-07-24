#include <stdlib.h>
#include <string.h>
#include "variable_len_array.h"


VAR_ARRAY_S* var_array_create() {
	VAR_ARRAY_S* array = malloc(sizeof(VAR_ARRAY_S));
	if (NULL == array) {
		return	NULL;
	}

	array->data = NULL;
	array->member_size = 0;
	array->allocated_num = 0;
	array->usesd_num = 0;

	array->dup = NULL;
	array->free = NULL;
	array->match = NULL;

	return array;
}

void var_array_init(VAR_ARRAY_S* array, size_t allocated_num, size_t member_size) {
	if (NULL == array) {
		return;
	}

	array->data = calloc(allocated_num, member_size);
	if (NULL == array->data) {
		return;
	}

	array->usesd_num = 0;
	array->allocated_num = allocated_num;
	array->member_size = member_size;
	return;
}

int var_array_insert(VAR_ARRAY_S* array, size_t pos, void* const value) {
	char* begin;
	size_t index;
	if (NULL == array || pos > array->allocated_num || array->usesd_num >= array->allocated_num) {
		return -1;
	}

	begin = array->data;
	index = array->usesd_num;
	for (; index > pos - 1; index--) {
		void* new = begin + index * array->member_size;
		void *old = begin + (index-1) * array->member_size;
		if (NULL != array->dup) {
			array->dup(new, old);
		} else {
			memcpy(new, old, array->member_size);
		}
	}

	if (NULL != array->dup) {
		array->dup((void*)(begin + ((pos - 1) * array->member_size)), value);
	} else {
		memcpy((void*)(begin + ((pos - 1) * array->member_size)), value, array->member_size);
	}
	array->usesd_num++;

	return 0;
}

size_t var_array_search_value(VAR_ARRAY_S* array, void* const value) {
	char* begin;
	size_t index;

	if (NULL == array) {
		return (size_t)-1;
	}

	begin = array->data;
	for (index = 0; index < array->usesd_num; index++) {
		int cmp_ret;
		if (NULL != array->match) {
			cmp_ret = array->match(begin+index*array->member_size, value);
		} else {
			cmp_ret = memcmp(begin + index * array->member_size, value, array->member_size);
		}
		if (0 == cmp_ret) {
			break;
		}
	}

	if (index >= array->usesd_num) {
		index = (size_t)-1;
	}

	return index;
}

void* var_array_index(VAR_ARRAY_S* array, size_t index) {
	char* begin;
	if (NULL == array || index > array->usesd_num) {
		return NULL;
	}
	begin = array->data;
	return begin + (index - 1) * array->member_size;
}

int var_array_modify(VAR_ARRAY_S* array, size_t pos, void* const value) {
	char* begin;
	void* old;

	if (NULL == array || pos > array->usesd_num) {
		return -1;
	}

	begin = array->data;
	old = begin + (pos - 1) * array->member_size;
	if (NULL != array->free) {
		array->free(old);
	}

	if (NULL != array->dup) {
		array->dup(old, value);
	} else {
		memcpy(old, value, array->member_size);
	}
	return 0;
}

size_t get_var_array_used_num(VAR_ARRAY_S* array) {
	if (NULL == array) {
		return 0;
	}
	return array->usesd_num;
}

size_t get_var_array_allocated_num(VAR_ARRAY_S* array) {
	if (NULL == array) {
		return 0;
	}
	return array->allocated_num;
}

void var_array_empty(VAR_ARRAY_S* array) {
	char* begin;
	size_t index;

	if (NULL == array)
	{
		return;
	}

	begin = array->data;
	for (index = 0; index < array->usesd_num; index++) {
		if (NULL != array->free) {
			array->free((void*)(begin+index*array->member_size));
		}
	}

	free(array->data);
	array->data = NULL;
	free(array);
	array = NULL;
	return;
}

void var_array_del_value(VAR_ARRAY_S* array, void* value) {
	size_t pos;
	char* begin;
	size_t index;

	if (NULL == array)
	{
		return;
	}

	pos = var_array_search_value(array, value);
	if (-1 == pos) {
		return;
	}

	begin = array->data;
	if (NULL != array->free) {
		array->free((void*)(begin + pos * array->member_size));
	}

	begin = array->data;
	for (index = pos; index < array->usesd_num; index++) {
		void* old = begin + (index + 1) * array->member_size;
		void* new = begin + index * array->member_size;
		if (NULL != array->dup) {
			array->dup(new, old);
		} else {
			memcpy(new, old, array->member_size);
		}
	}
	array->usesd_num--;
	return;
}

void var_array_del_index(VAR_ARRAY_S* array, size_t pos){
	char* begin;
	size_t index;

	if (NULL == array || pos > array->usesd_num) {
		return;
	}

	begin = array->data;
	if (NULL != array->free) {
		array->free((void*)(begin + (pos-1) * array->member_size));
	}

	begin = array->data;
	for (index = pos-1; index < array->usesd_num; index++) {
		void* old = begin + (index + 1) * array->member_size;
		void* new = begin + index * array->member_size;
		if (NULL != array->dup) {
			array->dup(new, old);
		} else {
			memcpy(new, old, array->member_size);
		}
	}
	array->usesd_num--;
	return;
}
