/*
 * CC_QUEUE.C
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

#include "cc_queue.h"
#include "../shared/cc_private.h"
#include "../cc_linked_list/cc_linked_list.h"

const char * const cc_queue_type = "cc_queue_type";

static int cc_queue_compare(cc_object *obj1, cc_object *obj2);
static void cc_queue_register_comparator();

struct cc_queue_struct {
	cc_collection c;
	
	cc_linked_list *linked_list;
};

cc_queue *cc_queue_new() {
	// cc_queue_register_comparator();
	
	cc_queue *queue = GC_MALLOC(sizeof(cc_queue));
	
	queue->linked_list = cc_linked_list_new();
	
	return queue;
}

void cc_queue_enqueue(cc_queue *queue, cc_object *obj) {
	cc_linked_list_add_last(queue->linked_list, obj);
}

cc_object *cc_queue_dequeue(cc_queue *queue) {
	cc_object *obj = cc_linked_list_get_first(queue->linked_list);
	cc_linked_list_remove_first(queue->linked_list);
	return obj;
}

cc_object *cc_queue_peek(cc_queue *queue) {
	return cc_linked_list_get_first(queue->linked_list);
}

int cc_queue_count(cc_queue *queue) {
	return cc_linked_list_length(queue->linked_list);
}

void cc_queue_clear(cc_queue *queue) {
	cc_linked_list_clear(queue->linked_list);
}

bool cc_queue_contains(cc_queue *queue, cc_object *obj) {
	return cc_linked_list_contains(queue->linked_list, obj);
}

cc_enumerator *cc_queue_get_enumerator(cc_queue *queue) {
	return cc_linked_list_get_enumerator(queue->linked_list);
}

cc_object *cc_queue_to_object(cc_queue *queue) {
	return cc_object_with_pointer(queue, cc_queue_type);
}

cc_queue *cc_queue_from_object(cc_object *object) {
	return cc_object_pointer_value(object);
}

int cc_queue_compare(cc_object *obj1, cc_object *obj2) {
	cc_queue *queue1 = cc_queue_from_object(obj1);
	cc_queue *queue2 = cc_queue_from_object(obj2);
	
	int len1 = cc_queue_count(queue1);
	int len2 = cc_queue_count(queue2);
	
	if (len1 > len2) {
		return 1;
	} else if (len1 < len2) {
		return -1;
	}
	
	cc_enumerator *e1 = cc_queue_get_enumerator(queue1);
	cc_enumerator *e2 = cc_queue_get_enumerator(queue2);
	
	while (cc_enumerator_move_next(e1), cc_enumerator_move_next(e2)) {
		int diff = cc_object_compare(cc_enumerator_current(e1), cc_enumerator_current(e2));
		
		if (diff != 0) {
			return diff;
		}
	}
	
	return 0;
}

void cc_queue_register_comparator() {
	static bool first = true;
	
	if (first) {
		first = false;
		cc_object_register_comparator_for_type(cc_queue_type, cc_queue_compare);
	}
}
