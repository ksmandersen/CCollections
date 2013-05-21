/*
 * CC_LINKED_LIST.PRIVATE.H
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

#ifndef CC_LINKED_LIST_PRIVATE_H
#define CC_LINKED_LIST_PRIVATE_H

#include "cc_linked_list.h"

/*
 *  This data structure represents each node
 *  in a linked list. Nodes are only exposed in the
 *  internal interface to ease the enumeration pattern
 *  of CCollections.
 */
struct cc_linked_list_node_struct {
  cc_object *object;
  struct cc_linked_list_node_struct *next;
  struct cc_linked_list_node_struct *prev;
};
typedef struct cc_linked_list_node_struct cc_linked_list_node;

// Create a new linked list node from a cc_object.
cc_linked_list_node *cc_linked_list_node_new(cc_object *object);

// Compare two lists agains each other.
// This function doesn't make a lot of sense since it's not
// good design to say that a list is smaller or bigger than
// another list apart from size.
// The function is used for determining whether two lists are
// equal (i.e. contains all ofthe same elements).
extern int cc_linked_list_compare(cc_object *obj1, cc_object *obj2);

// Enumerator & comperator
extern bool cc_linked_list_enumerator_move_next(cc_enumerable *c, cc_enumerator *e);
extern void cc_linked_list_register_comparator();

#endif
