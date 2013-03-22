#include "cc_dictionary.h"
#include "../cc_linked_list/cc_linked_list.h"
#include "../cc_array_list/cc_array_list.h"
#include "../shared/cc_hash.h"
#include "../shared/cc_enumerator_private.h"
#include <stdlib.h>

#define DICT_HEAP_SIZE 100

const char * const cc_dictionary_type = "cc_dictionary_type";

static bool cc_dictionary_enumerator_move_next(cc_collection *c, cc_enumerator *e);
static bool cc_dictionary_compare(cc_object *obj1, cc_object *obj2);
static void cc_dictionary_register_comparator();
static void cc_dictionary_expand_heap(cc_dictionary *list);

struct cc_dictionary_struct {
	cc_collection c;
	
	cc_linked_list **heap;
	cc_array_list *keys;
	int count;
};

cc_dictionary *cc_dictionary_new() {
	cc_dictionary_register_comparator();
	
	cc_dictionary *dictionary;
	if ((dictionary = GC_MALLOC(sizeof(cc_dictionary))) == NULL) {
		return NULL;
	}
	
	dictionary->c.enumerator_move_next = cc_dictionary_enumerator_move_next;
	size_t size = sizeof(cc_linked_list *) * DICT_HEAP_SIZE;
	dictionary->heap = GC_MALLOC(size);
	memset(dictionary->heap, 0, size);
	
	dictionary->keys = cc_array_list_new();
	dictionary->count = 0;
		
	return dictionary;
}

int cc_dictionary_count(cc_dictionary *dictionary)
{
	return dictionary->count;
}

void cc_dictionary_add(cc_dictionary *dictionary, const char *key, cc_object *obj) {
	int index = cc_hash_from_string(key) % DICT_HEAP_SIZE;
	
	cc_linked_list *linked_list = dictionary->heap[index];
	if (linked_list == NULL) {
		linked_list = cc_linked_list_new();
		cc_array_list_add_last(dictionary->keys, cc_object_with_string(key));
		dictionary->heap[index] = linked_list;
	}
	
	cc_linked_list_add_last(linked_list, obj);
	dictionary->count++;
}

void cc_dictionary_clear(cc_dictionary *dictionary) {
	memset(dictionary->heap, 0, sizeof(cc_linked_list *) * DICT_HEAP_SIZE);
	dictionary->count = 0;
}

bool cc_dictionary_contains_key(cc_dictionary *dictionary, const char *key) {
	return (dictionary->heap[cc_hash_from_string(key) % DICT_HEAP_SIZE] != NULL);
}

bool cc_dictionary_contains_value(cc_dictionary *dictionary, cc_object *obj) {
	cc_enumerator *e = cc_dictionary_get_enumerator(dictionary);
	while (cc_enumerator_move_next(e)) {
		const char *key = cc_object_string_value(e->current);
		cc_linked_list *list = dictionary->heap[cc_hash_from_string(key) % DICT_HEAP_SIZE];
		
		cc_enumerator *e2 = cc_linked_list_get_enumerator(list);
		while (cc_enumerator_move_next(e2)) {
			cc_object *obj2 = e2->current;
			
			if (cc_object_is_equal(obj, obj2)) {
				return true;
			}
		}
	}
	
	return false;
}

cc_enumerator *cc_dictionary_get_enumerator(cc_dictionary *dictionary) {
	cc_enumerator *e = GC_MALLOC(sizeof(cc_enumerator));
	e->collection = (cc_collection *)dictionary;
	*((int *)e->data) = -1;
	return e;
}

bool cc_dictionary_enumerator_move_next(cc_collection *c, cc_enumerator *e) {
	int *index = (int *)e->data;
	*index = *index + 1;
	
	cc_dictionary *dictionary = (cc_dictionary *)c;
	
	if (*index >= cc_array_list_length(dictionary->keys)) {
		return false;
	}
	
	e->current = cc_array_list_get(dictionary->keys, *index);
	return true;
}

void cc_dictionary_remove(cc_dictionary *dictionary, const char *key) {
	int index = cc_hash_from_string(key) % DICT_HEAP_SIZE;
	if (dictionary->heap[index] != NULL) {
		cc_linked_list_clear(dictionary->heap[index]);
		dictionary->count--;
	}
}

cc_object *cc_dictionary_to_object(cc_set *set) {
	return NULL;
}

cc_dictionary *cc_dictionary_from_object(cc_object *obj) {
	return NULL;
}

bool cc_dictionary_compare(cc_object *obj1, cc_object *obj2) {
	return false;
}

void cc_dictionary_register_comparator() {
	static bool first = true;
	
	if (first) {
		first = false;
		cc_object_register_comparator_for_type(cc_dictionary_type, cc_dictionary_compare);
	}
}
