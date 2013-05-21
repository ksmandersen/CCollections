/*
 * CC_DICTIONARY.C
 * 
 * This file is part of the CCollections library.
 *
 * CCollections is licensed under the BSD-2-Clause License (FreeBSD).
 * Copyright (c) 2012, Ulrik Damm and Kristian Andersen.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met:
 *
 * Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer. Redistributions 
 * in binary form must reproduce the above copyright notice, this list 
 * of conditions and the following disclaimer in the documentation and/or 
 * other materials provided with the distribution. THIS SOFTWARE IS 
 * PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "cc_dictionary.h"
#include "../cc_linked_list/cc_linked_list.h"
#include "../cc_array_list/cc_array_list.h"
#include "../shared/cc_hash.h"
#include "../shared/cc_enumerator_private.h"
#include <stdlib.h>

#define DICT_HEAP_SIZE 100

const char * const cc_dictionary_type = "cc_dictionary_type";

//static bool cc_dictionary_enumerator_move_next(cc_collection *c, cc_enumerator *e);
static int cc_dictionary_compare(cc_object *obj1, cc_object *obj2);
static void cc_dictionary_register_comparator();
static void cc_dictionary_expand_heap(cc_dictionary *list);

typedef struct {
	const char *key;
	cc_object *value;
} cc_key_value_pair;

struct cc_dictionary_struct {
	cc_collection c;
	
	cc_linked_list **heap;
	cc_set *keys;
	int count;
};

cc_dictionary *cc_dictionary_new() {
	// cc_dictionary_register_comparator();
	
	cc_dictionary *dictionary;
	if ((dictionary = GC_MALLOC(sizeof(cc_dictionary))) == NULL) {
		return NULL;
	}
	
//	dictionary->c.enumerator_move_next = cc_dictionary_enumerator_move_next;
	size_t size = sizeof(cc_linked_list *) * DICT_HEAP_SIZE;
	dictionary->heap = GC_MALLOC(size);
	memset(dictionary->heap, 0, size);
	
	dictionary->keys = cc_set_new();
	dictionary->count = 0;
		
	return dictionary;
}

cc_dictionary *cc_dictionary_new_with_enumerators(cc_enumerator *key_enumerator, cc_enumerator *object_enumerator) {
	cc_dictionary *dictionary = cc_dictionary_new();

	while(cc_enumerator_move_next(key_enumerator) && cc_enumerator_move_next(object_enumerator)) {
		cc_dictionary_add(dictionary, cc_object_string_value(cc_enumerator_current(key_enumerator)), cc_enumerator_current(object_enumerator));
	}

	return dictionary;
}

int cc_dictionary_count(cc_dictionary *dictionary) {
	return dictionary->count;
}

void cc_dictionary_add(cc_dictionary *dictionary, const char *key, cc_object *obj) {
	int index = cc_hash_from_string(key) % DICT_HEAP_SIZE;
	
	cc_linked_list *linked_list = dictionary->heap[index];
	if (linked_list == NULL) {
		linked_list = cc_linked_list_new();
		dictionary->heap[index] = linked_list;
	}
	
	size_t key_len = strlen(key) + 1;
	char *key_copy = GC_MALLOC(key_len);
	memcpy(key_copy, key, key_len);
		
		cc_set_add(dictionary->keys, cc_object_with_string(key));
	
	cc_enumerator *e = cc_linked_list_get_enumerator(linked_list);
	while (cc_enumerator_move_next(e)) {
		cc_key_value_pair *key_value_pair = (cc_key_value_pair *)cc_object_data_value(e->current);
		if (strcmp(key, key_value_pair->key) == 0) {
			key_value_pair->value = obj;
			goto found;
		}
	}
	
	cc_key_value_pair pair = (cc_key_value_pair) { .key = key_copy, .value = obj };
	cc_object *key_value_pair = cc_object_with_data(&pair, sizeof(cc_key_value_pair), "cc_key_value_pair");
	cc_linked_list_add_last(linked_list, key_value_pair);
	dictionary->count++;
	
	found: return;
}

cc_object *cc_dictionary_get(cc_dictionary *dictionary, const char *key) {
	int index = cc_hash_from_string(key) % DICT_HEAP_SIZE;
	cc_linked_list *linked_list = dictionary->heap[index];
	
	if (!linked_list) return NULL;
	cc_enumerator *e = cc_linked_list_get_enumerator(linked_list);
	while (cc_enumerator_move_next(e)) {
		cc_key_value_pair *key_value_pair = (cc_key_value_pair *)cc_object_data_value(e->current);
		if (strcmp(key, key_value_pair->key) == 0) {
			return key_value_pair->value;
		}
	}
	
	return NULL;
}

void cc_dictionary_clear(cc_dictionary *dictionary) {
	memset(dictionary->heap, 0, sizeof(cc_linked_list *) * DICT_HEAP_SIZE);
	dictionary->count = 0;
}

bool cc_dictionary_contains_key(cc_dictionary *dictionary, const char *key) {
//	return cc_array_list_contains(dictionary->keys, cc_object_with_string(key));
		return cc_set_contains(dictionary->keys, cc_object_with_string(key));
}

bool cc_dictionary_contains_value(cc_dictionary *dictionary, cc_object *obj) {
	cc_enumerator *e = cc_dictionary_get_enumerator(dictionary);
	while (cc_enumerator_move_next(e)) {
		const char *key = cc_object_string_value(e->current);
		cc_linked_list *list = dictionary->heap[cc_hash_from_string(key) % DICT_HEAP_SIZE];
		
		cc_enumerator *e2 = cc_linked_list_get_enumerator(list);
		while (cc_enumerator_move_next(e2)) {
			cc_key_value_pair *key_value_pair = cc_object_data_value(e2->current);
			
			if (cc_object_is_equal(obj, key_value_pair->value)) {
				return true;
			}
		}
	}
	
	return false;
}

cc_enumerator *cc_dictionary_get_enumerator(cc_dictionary *dictionary) {
		return cc_set_get_enumerator(dictionary->keys);
}

void cc_dictionary_remove(cc_dictionary *dictionary, const char *key) {
	int index = cc_hash_from_string(key) % DICT_HEAP_SIZE;
	if (dictionary->heap[index] != NULL) {
		cc_linked_list_clear(dictionary->heap[index]);
		dictionary->count--;
	}
}

cc_object *cc_dictionary_to_object(cc_dictionary *dictionary) {
	return cc_object_with_pointer(dictionary, cc_dictionary_type);
}

cc_dictionary *cc_dictionary_from_object(cc_object *obj) {
	return cc_object_pointer_value(obj);
}

int cc_dictionary_compare(cc_object *obj1, cc_object *obj2) {
	return -1;
}

void cc_dictionary_register_comparator() {
	static bool first = true;
	
	if (first) {
		first = false;
		cc_object_register_comparator_for_type(cc_dictionary_type, cc_dictionary_compare);
	}
}
