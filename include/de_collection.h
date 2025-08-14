/**
* @file collection.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "pch.h"

typedef struct {
    void* array;
    size_t size;
    size_t capacity;
    size_t type_size;
} list_t;

// List functions
void list_init(list_t* list, size_t type_size);
void list_init_size(list_t* list, size_t type_size, size_t reserve);
void list_add(list_t* list, void* value);
void* list_get(list_t* list, size_t index);
size_t list_size(list_t* list);
size_t list_capacity(list_t* list);
bool list_is_empty(list_t* list);
void list_clear(list_t* list);
void list_remove(list_t* list, size_t index);
void list_resize(list_t* list, size_t new_capacity);
void list_free(list_t* list);
