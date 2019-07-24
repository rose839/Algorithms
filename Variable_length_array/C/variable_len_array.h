#ifndef VARIABLE_LEN_ARRAY_H
#define VARIABLE_LEN_ARRAY_H

#include <stddef.h>


#define arraySetDupMethod(a, m)   ((a)->dup = (m))
#define arraySetFreeMethod(a, m)  ((a)->free = (m))
#define arraySetMatchMethod(a, m) ((a)->match = (m))
#define arrayGetDupMethod(a)      ((a)->dup)
#define arrayGetFree(a)           ((a)->free)
#define arrayGetMatchMethod(a)    ((a)->match)

typedef struct {
	void *data;
	size_t member_size;
	size_t usesd_num;
	size_t allocated_num;
	void(*dup)(void* ptr, void* key);
	void(*free)(void *key);
	int(*match)(void *ptr, void *key);
}VAR_ARRAY_S;

VAR_ARRAY_S* var_array_create();
void var_array_init(VAR_ARRAY_S* array, size_t size, size_t type_size);

int var_array_insert(VAR_ARRAY_S* array, size_t pos, void* const value);
size_t var_array_search_value(VAR_ARRAY_S* array, void* const value);
void* var_array_index(VAR_ARRAY_S* array, size_t index);
int var_array_modify(VAR_ARRAY_S* array, size_t pos, void* const value);

size_t get_var_array_used_num(VAR_ARRAY_S* array);
size_t get_var_array_allocated_num(VAR_ARRAY_S* array);

void var_array_empty(VAR_ARRAY_S* array);
void var_array_del_value(VAR_ARRAY_S* array, void* value);
void var_array_del_index(VAR_ARRAY_S* array, size_t pos);

#endif