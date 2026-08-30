/**
* @file list.c
* @brief Implementation of a dynamic list in C.
* @author Hudson Schumaker
* @version 1.0.0
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "list.h"
#define INITIAL_CAPACITY 16
#define GROWTH_FACTOR 2

void list_init(list_t* list, size_t type_size) {
	list->size = 0;
	list->capacity = INITIAL_CAPACITY; // initial capacity set
	list->type_size = type_size;
	list->value = malloc(list->capacity * list->type_size);
}

bool list_resize(list_t* list, size_t new_capacity) {
	if (list == NULL) {
		return false;
	}

	if (new_capacity == 0) {
		return false;
	}

	if (new_capacity <= list->capacity) {
		return true;
	}

	void* new_value = realloc(list->value, new_capacity * list->type_size);
	if (!new_value) {
		return false;
	}

	list->value = new_value;
	list->capacity = new_capacity;
	return true;
}

bool list_push_back(list_t* list, const void* value) {
	if (list == NULL || value == NULL) {
		return false;
	}

	if (list->size == list->capacity && !list_resize(list, list->capacity * GROWTH_FACTOR)) {
		return false; // out of memory, entry was not added
	}

	memcpy((char*)list->value + list->size * list->type_size, value, list->type_size);
	list->size++;
	return true;
}

void* list_get(const list_t* list, size_t index) {
	if (list == NULL || list->value == NULL) {
		return NULL;
	}

	if (index < list->size) {
		return (char*)list->value + index * list->type_size;
	}
	return NULL;
}

bool list_remove_at(list_t* list, size_t index) {
	if (list == NULL || list->value == NULL || index >= list->size) {
		return false;
	}

	// shift all elements after 'index' one position to the left
	size_t elements_to_move = list->size - index - 1;
	if (elements_to_move > 0) {
		char* dest = (char*)list->value + index * list->type_size;
		char* src = dest + list->type_size;
		memmove(dest, src, elements_to_move * list->type_size);
	}

	list->size--;
	return true;
}

bool list_remove_value(list_t* list, const void* value, int(*comparator)(const void*, const void*)) {
	if (list == NULL || list->value == NULL || value == NULL || comparator == NULL) {
		return false;
	}

	for (size_t i = 0; i < list->size; i++) {
		void* current = (char*)list->value + i * list->type_size;
		if (comparator(current, value) == 0) {
			return list_remove_at(list, i);
		}
	}

	return false; // not found
}

void list_sort(const list_t* list, int(*comparator)(const void*, const void*)) {
	if (list == NULL || comparator == NULL) {
		return;
	}

	if (list == NULL || list->value == NULL || list->size <= 1) {
		return; // Nothing to sort
	}

	qsort(list->value, list->size, list->type_size, comparator);
}

size_t list_size(const list_t* list) {
	if (list == NULL) {
		return 0;
	}
	return list->size;
}

void list_quit(list_t* list) {
	if (list == NULL) {
		return;
	}

	free(list->value);
	list->value = NULL;
	list->size = 0;
	list->capacity = 0;
	list->type_size = 0;
}
