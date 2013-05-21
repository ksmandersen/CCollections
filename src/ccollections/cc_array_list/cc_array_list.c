/*
 * CC_ARRAY_LIST.C
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

#include "../shared/cc_private.h"
#include "cc_array_list.private.h"
#include "../shared/cc_enumerator_private.h"

const char * const cc_array_list_type = "cc_array_list_type";

cc_array_list *cc_array_list_new() {
	cc_array_list *list;
	if ((list = GC_MALLOC(sizeof(cc_array_list))) == NULL) {
		return NULL;
	}
	
	list->c.enumerable.move_next = cc_array_list_enumerator_move_next;
	
	list->count = 0;
	list->heap_size = 128;
	list->heap = GC_MALLOC(sizeof(cc_object *) * list->heap_size);
	
	return list;
}

cc_array_list *cc_array_list_new_with_enumerator(cc_enumerator *e) {
	cc_array_list *list = cc_array_list_new();
	while (cc_enumerator_move_next(e)) {
		cc_array_list_add_last(list, cc_enumerator_current(e));
	}

	return list;
}

void cc_array_list_expand_heap(cc_array_list *list) {
	list->heap_size *= 2;
	list->heap = GC_REALLOC(list->heap, sizeof(cc_object *) * list->heap_size);
}

int cc_array_list_length(cc_array_list *list) {
	if (list == NULL) {
		return 0;
	}

	return list->count;
}

cc_object *cc_array_list_get(cc_array_list *list, int index) {
	if (list == NULL || index >= list->count) return NULL;
	
	return list->heap[index];
}

cc_object * cc_array_list_get_first(cc_array_list *list) {
	if (list == NULL || list->count == 0) return NULL;

	return list->heap[0];
}

cc_object * cc_array_list_get_last(cc_array_list *list) {
	if (list == NULL || list->count == 0) return NULL;

	return list->heap[list->count - 1];
}

void cc_array_list_add(cc_array_list *list, int index, cc_object *object) {
	if (list == NULL || object == NULL || index > list->count) return;
	if (list->heap_size == list->count) cc_array_list_expand_heap(list);
	
	int i;
	for (i = list->count; i > index; i--) {
		list->heap[i] = list->heap[i - 1];
	}

	list->heap[i] = object;
	list->count++;
}

void cc_array_list_add_first(cc_array_list *list, cc_object *object) {
	cc_array_list_add(list, 0, object);
}

void cc_array_list_add_last(cc_array_list *list, cc_object *object) {
	cc_array_list_add(list, list->count, object);
}

void cc_array_list_remove(cc_array_list *list, int index) {
	if (list == NULL || index >= list->count) return;
	
	int i;
	for (i = index; i < list->count; i++) {
		list->heap[i] = list->heap[i + 1];
	}

	list->count--;
}

void cc_array_list_remove_first(cc_array_list *list) {
	cc_array_list_remove(list, 0);
}

void cc_array_list_remove_last(cc_array_list *list) {
	cc_array_list_remove(list, list->count - 1);
}

void cc_array_list_clear(cc_array_list *list) {
	memset(list->heap, 0, list->heap_size * sizeof(cc_object *));
	list->count = 0;
}

cc_array_list *cc_array_list_merge(cc_array_list *a_list, cc_array_list *b_list) {
	cc_enumerator *e = cc_array_list_get_enumerator(b_list);
	while (cc_enumerator_move_next(e)) {
		cc_array_list_add_last(a_list, cc_enumerator_current(e));
	}

	return a_list;
}

bool cc_array_list_contains(cc_array_list *list, cc_object *obj) {
	int i;
	for (i = 0; i < list->count; i++) {
		if (cc_object_is_equal(list->heap[i], obj)) {
			return true;
		}
	}
	
	return false;
}

cc_enumerator *cc_array_list_get_enumerator(cc_array_list *list) {
	cc_enumerator *e = cc_enumerator_new(&list->c.enumerable);
	e->data = GC_MALLOC(sizeof(int));
	*((int *)e->data) = -1;

	return e;
}

bool cc_array_list_enumerator_move_next(cc_enumerable *collection, cc_enumerator *e) {
	int *counter = (int *)e->data;
	*counter = *counter + 1;
	cc_array_list *list = (cc_array_list *)collection;
	
	if (*counter >= list->count) {
		return false;
	}
	
	e->current = list->heap[*counter];
	return true;
}

cc_object *cc_array_list_to_object(cc_array_list *list) {
	return cc_object_with_pointer(list, cc_array_list_type);
}

cc_array_list *cc_array_list_from_object(cc_object *object) {
	return cc_object_pointer_value(object);
}

int cc_array_list_compare(cc_object *obj1, cc_object *obj2) {
	cc_array_list *list1 = cc_array_list_from_object(obj1);
	cc_array_list *list2 = cc_array_list_from_object(obj2);
		
	if (list1->count < list2->count) return -1;
	if (list1->count > list2->count) return 1;

	cc_enumerator *e1 = cc_array_list_get_enumerator(list1);
	cc_enumerator *e2 = cc_array_list_get_enumerator(list2);
	while (cc_enumerator_move_next(e1)) {
		if (!cc_enumerator_move_next(e2)) return -1;
		if (!cc_object_is_equal(cc_enumerator_current(e1), cc_enumerator_current(e2))) return -1;
	}

	if (cc_enumerator_move_next(e2)) return 1;

	return 0;
}

void cc_array_list_register_comparator() {
	static bool first = true;

	if (first) {
		first = false;
		cc_object_register_comparator_for_type(cc_array_list_type, cc_array_list_compare);
	}
}

// Sorting

void cc_array_list_sort(cc_array_list *list) {
	cc_array_list_quicksort(list, 0, list->count - 1);
}

void cc_array_list_quicksort(cc_array_list *list, int left, int right) {
	if (list == NULL || list->count <= 1) {
		return;
	}

	if (right <= left) return;
	int i = cc_array_list_partition(list, left, right);
	cc_array_list_quicksort(list, left, i - 1);
	cc_array_list_quicksort(list, i + 1, right);
}

int cc_array_list_partition(cc_array_list *list, int left, int right) {
	int i = left - 1;
	int j = right;

	while (true) {
		cc_object *first = cc_array_list_get_first(list);
		cc_object_comparator comp = cc_get_comperator_for_object(first);
		while (comp(list->heap[++i], list->heap[right]) > 0)
			;
		while (comp(list->heap[right], list->heap[--j]) > 0)
			if (j == left) break;

		if (i >= j) break;
		cc_array_list_swap(list, i, j);
	}
	
	cc_array_list_swap(list, i, right);
	return i;
}

void cc_array_list_swap(cc_array_list *list, int i, int j) {
	cc_object *swap = list->heap[i];
	list->heap[i] = list->heap[j];
	list->heap[j] = swap;
}

void cc_array_list_shuffle(cc_array_list *list) {
	int N = list->count;
	int i;
	for (i = 0; i < N; i++) {
		int r = rand() % N;
		cc_array_list_swap(list, i, r);
	}
}
