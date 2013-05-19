/*
 * CC_SET.C
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
#include "cc_set.private.h"
#include "../cc_linked_list/cc_linked_list.private.h"
#include "../shared/cc_enumerator_private.h"

const char * const cc_set_type = "cc_set_type";

struct cc_set_struct {
	cc_collection c;
	
	cc_linked_list *list;
};

cc_set *cc_set_new() {
	// cc_set_register_comparator();

	cc_set *set;
	if ((set = GC_MALLOC(sizeof(cc_set))) == NULL) {
		return NULL;
	}

	set->c.enumerable.move_next = cc_set_enumerator_move_next;
	set->list = cc_linked_list_new();

	return set;
}

void cc_set_add(cc_set *set, cc_object *obj) {
	if (set == NULL || obj == NULL)
		return;

	if (!cc_set_contains(set, obj)) {
		cc_linked_list_add_last(set->list, obj);
	}
}

cc_object *cc_set_get(cc_set *set, int index) {
	if (set == NULL)
		return NULL;

	return cc_linked_list_get(set->list, index);
}

void cc_set_remove(cc_set *set, cc_object *obj) {
	int index = cc_set_find(set, obj);

	if (index != -1) {
		cc_linked_list_remove(set->list, index);
	}
}

int cc_set_find(cc_set *set, cc_object *obj) {
	cc_enumerator *e = cc_set_get_enumerator(set);
	int i = 0;
	while(cc_enumerator_move_next(e)) {
		if (cc_object_is_equal(obj, cc_enumerator_current(e))) {
			return i;
		}

		i++;
	}

	return -1;
}

void cc_set_clear(cc_set *set) {
	cc_linked_list_clear(set->list);
}

int cc_set_count(cc_set *set) {
	return cc_linked_list_length(set->list);
}

bool cc_set_contains(cc_set *set, cc_object *obj) {
	return cc_linked_list_contains(set->list, obj);
}

void cc_set_merge(cc_set *a_set, cc_set *b_set) {
	cc_enumerator *e = cc_set_get_enumerator(b_set);
	while(cc_enumerator_move_next(e)) {
		cc_set_add(a_set, cc_enumerator_current(e));
	}
}

cc_enumerator *cc_set_get_enumerator(cc_set *set) {
	return cc_linked_list_get_enumerator(set->list);
}

bool cc_set_enumerator_move_next(cc_enumerable *c, cc_enumerator *e) {
	return cc_linked_list_enumerator_move_next(c, e);
}

int cc_set_compare(cc_object *obj1, cc_object *obj2) {
	cc_set *a_set = (cc_set *)obj1;
	cc_set *b_set = (cc_set *)obj2;

	return cc_linked_list_compare((cc_object *)a_set->list, (cc_object *)b_set->list);
}

void cc_set_register_comparator() {
  static bool first = true;
  
  if (first) {
    first = false;
    cc_object_register_comparator_for_type(cc_set_type, cc_set_compare);
  }
}

cc_object *cc_set_to_object(cc_set *set) {
  return cc_object_with_pointer(set, cc_set_type);
}

cc_set *cc_set_from_object(cc_object *obj) {
  cc_set *set = cc_object_pointer_value(obj);
  return set;
}
