/*
 * CC_ARRAY_LIST.PRIVATE.H
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

#ifndef CC_ARRAY_LIST_PRIVATE_H
#define CC_ARRAY_LIST_PRIVATE_H

#include "cc_array_list.h"

// Enumerator & comperator
extern void cc_array_list_register_comparator();
extern bool cc_array_list_enumerator_move_next(cc_enumerable *c, cc_enumerator *e);

// Compare two lists agains each other.
// This function doesn't make a lot of sense since it's not
// good design to say that a list is smaller or bigger than
// another list apart from size.
// The function is used for determining whether two lists are
// equal (i.e. contains all ofthe same elements).
int cc_array_list_compare(cc_object *obj1, cc_object *obj2);

// This internal function is called whenever the list reaches the
// limit of its allocated number of objects. When function reallocates
// the space and doubles the allocated space.
extern void cc_array_list_expand_heap(cc_array_list *list);

// the array list data structure. (Internal use only)
struct cc_array_list_struct {
	cc_collection c;
	
	cc_object **heap;
	int count;
	int heap_size;
};

// Sorting

// Sorting of an array list uses quicksort. A call to
// cc_array_list_sort will invoke quicksort.
void cc_array_list_quicksort(cc_array_list *list, int left, int right);
int cc_array_list_partition(cc_array_list *list, int left, int right);
void cc_array_list_swap(cc_array_list *list, int i, int j);

#endif