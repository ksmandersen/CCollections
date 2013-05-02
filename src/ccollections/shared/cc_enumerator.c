/*
 * CC_ENUMERATOR.C
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

#include "cc_private.h"
#include "cc_enumerator_private.h"
#include "../cc_sorted_list/cc_sorted_list.h"

typedef struct {
	cc_enumerator *parent;
	cc_enumerator_filter_func filter;
} filter_enumerator_data;

typedef struct {
	cc_enumerator *parent;
	cc_sorted_list *elements;
	cc_enumerator *elements_enumerator;
} order_enumerator_data;

typedef struct {
	cc_enumerator *parent;
	cc_enumerator_map_func map;
} map_enumerator_data;

static bool cc_enumerator_filter_move_next(cc_enumerable *c, cc_enumerator *e);
static bool cc_enumerator_order_move_next(cc_enumerable *c, cc_enumerator *e);
static bool cc_enumerator_map_move_next(cc_enumerable *c, cc_enumerator *e);

cc_enumerator *cc_enumerator_new(cc_enumerable *e) {
	cc_enumerator *en = GC_MALLOC(sizeof(cc_enumerator));
	en->enumerable = e;
	en->current = NULL;
	return en;
}

cc_object *cc_enumerator_current(cc_enumerator *e) {
	return e->current;
}

bool cc_enumerator_move_next(cc_enumerator *e) {
	return e->enumerable->move_next(e->enumerable, e);
}

cc_enumerator *cc_enumerator_filter(cc_enumerator *e, cc_enumerator_filter_func filter) {
	cc_enumerator *en = cc_enumerator_new(cc_enumerable_new(cc_enumerator_filter_move_next));
	filter_enumerator_data *data = GC_malloc(sizeof(filter_enumerator_data));
	data->parent = e;
	data->filter = filter;
	en->data = data;
	return en;
}

cc_enumerator *cc_enumerator_order(cc_enumerator *e) {
	cc_enumerator *en = cc_enumerator_new(cc_enumerable_new(cc_enumerator_order_move_next));
	order_enumerator_data *data = GC_malloc(sizeof(order_enumerator_data));
	data->parent = e;
	data->elements = NULL;
	en->data = data;
	return en;
}

cc_enumerator *cc_enumerator_map(cc_enumerator *e, cc_enumerator_map_func map) {
	cc_enumerator *en = cc_enumerator_new(cc_enumerable_new(cc_enumerator_map_move_next));
	map_enumerator_data *data = GC_malloc(sizeof(map_enumerator_data));
	data->parent = e;
	data->map = map;
	en->data = data;
	return en;
}

cc_object *cc_enumerator_fold(cc_enumerator *e, cc_object *seed, cc_enumerator_fold_func fold) {
	while (cc_enumerator_move_next(e)) {
		seed = fold(seed, cc_enumerator_current(e));
	}
	
	return seed;
}

cc_linked_list *cc_enumerator_to_list(cc_enumerator *e) {
	cc_linked_list *list = cc_linked_list_new();
	
	while (cc_enumerator_move_next(e)) {
		cc_linked_list_add_last(list, cc_enumerator_current(e));
	}
	
	return list;
}

cc_enumerable *cc_enumerable_new(cc_enumerator_move_next_func move_next) {
	cc_enumerable *e = GC_malloc(sizeof(cc_enumerator));
	e->move_next = move_next;
	return e;
}

bool cc_enumerator_filter_move_next(cc_enumerable *c, cc_enumerator *e) {
	filter_enumerator_data *data = e->data;
	cc_enumerator *parent_e = data->parent;
	
	while (cc_enumerator_move_next(parent_e)) {
		cc_object *obj = cc_enumerator_current(parent_e);
		
		if (data->filter(obj)) {
			e->current = obj;
			return true;
		}
	}
	
	return false;
}

static bool cc_enumerator_order_move_next(cc_enumerable *c, cc_enumerator *e) {
	order_enumerator_data *data = e->data;
	cc_enumerator *parent_e = data->parent;
	
	if (data->elements == NULL) {
		data->elements = cc_sorted_list_new();
		while (cc_enumerator_move_next(parent_e)) {
			cc_sorted_list_add(data->elements, cc_enumerator_current(parent_e));
		}
		data->elements_enumerator = cc_sorted_list_get_enumerator(data->elements);
	}
	
	bool status = cc_enumerator_move_next(data->elements_enumerator);
	e->current = cc_enumerator_current(data->elements_enumerator);
	return status;
}

static bool cc_enumerator_map_move_next(cc_enumerable *c, cc_enumerator *e) {
	map_enumerator_data *data = e->data;
	cc_enumerator *parent_e = data->parent;
	
	while (cc_enumerator_move_next(parent_e)) {
		e->current = data->map(cc_enumerator_current(parent_e));
		return true;
	}
	
	return false;
}
