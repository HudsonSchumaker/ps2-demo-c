/**
* @file list.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../include/de_collection.h"

#define LIST_INIT_CAPACITY 4
#define LIST_RESIZE_FACTOR 2

void list_init(list_t* list, size_t type_size) {
	list_init_size(list, type_size, LIST_INIT_CAPACITY);
}

void list_init_size(list_t* list, size_t type_size, size_t reserve) {
	list->size = 0;
	list->capacity = reserve;
	list->type_size = type_size;
	list->array = malloc(list->capacity * list->type_size);
    if (!list->array) {
        printf("ERROR: list_t, memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

void list_resize(list_t* list, size_t new_capacity) {
    if (new_capacity > list->capacity) {
        void* new_value = realloc(list->array, new_capacity * list->type_size);
        if (new_value) {
            list->array = new_value;
            list->capacity = new_capacity;
        }
        else {
            printf("ERROR: list_t, memory reallocation failed\n");
        }
    }
}

void list_add(list_t* list, void* value) {
    if (list->size == list->capacity) {
        list_resize(list, list->capacity + LIST_RESIZE_FACTOR);
    }
    memcpy((char*)list->array + list->size * list->type_size, value, list->type_size);
    list->size++;
}

void* list_get(list_t* list, size_t index) {
    if (index < list->size) {
        return (char*)list->array + index * list->type_size;
    }
    return NULL;
}

size_t list_size(list_t* list) {
    return list->size;
}

size_t list_capacity(list_t* list) {
    return list->capacity;
}

bool list_is_empty(list_t* list) {
    return list->size == 0;
}

void list_clear(list_t* list) {
    list->size = 0;
}

void list_remove(list_t* list, size_t index) {
    if (index < list->size) {
        memmove((char*)list->array + index * list->type_size,
            (char*)list->array + (index + 1) * list->type_size,
            (list->size - index - 1) * list->type_size);
        list->size--;
    }
}

void list_free(list_t* list) {
    free(list->array);
    list->array = NULL;
    list->size = 0;
    list->capacity = 0;
}
