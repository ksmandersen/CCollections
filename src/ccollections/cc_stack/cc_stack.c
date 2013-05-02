/*
 * CC_STACK.C
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

#include "cc_stack.private.h"
#include "../cc_linked_list/cc_linked_list.private.h"
#include "../cc_array_list/cc_array_list.h"
#include "../shared/cc_hash.h"
#include "../shared/cc_enumerator_private.h"
#include <stdlib.h>

const char * const cc_stack_type = "cc_stack_type";

struct cc_stack_struct {
  cc_collection c;

  cc_linked_list *items;
};

cc_stack *cc_stack_new() {
  // cc_stack_register_comparator();

  cc_stack *stack;
  if ((stack = GC_MALLOC(sizeof(cc_stack))) == NULL) {
    return NULL;
  }

  stack->c.enumerable.move_next = cc_stack_enumerator_move_next;
  stack->items = cc_linked_list_new();

  return stack;
}

void cc_stack_push(cc_stack *stack, cc_object *obj) {
  cc_linked_list_add_last(stack->items, obj);
}

cc_object *cc_stack_pop(cc_stack *stack) {
  cc_object *obj = cc_stack_peek(stack);
  cc_linked_list_remove_last(stack->items);
  return obj;
}

cc_object *cc_stack_peek(cc_stack *stack) {
  return cc_linked_list_get_last(stack->items);;
}

int cc_stack_size(cc_stack *stack) {
  return cc_linked_list_length(stack->items);
}

void cc_stack_clear(cc_stack *stack) {
  cc_linked_list_clear(stack->items);
}

bool cc_stack_contains(cc_stack *stack, cc_object *obj) {
  return cc_linked_list_contains(stack->items, obj);
}

cc_enumerator *cc_stack_get_enumerator(cc_stack *stack) {
  return cc_linked_list_get_enumerator(stack->items);
}

bool cc_stack_equals(cc_stack *a_stack, cc_stack *b_stack) {
  return cc_linked_list_equals(a_stack->items, b_stack->items);
}

bool cc_stack_enumerator_move_next(cc_enumerable *c, cc_enumerator *e) {
  return cc_linked_list_enumerator_move_next(c, e);
}

int cc_stack_compare(cc_object *obj1, cc_object *obj2) {
  cc_stack *a_stack = (cc_stack *)obj1;
  cc_stack *b_stack = (cc_stack *)obj2;

  return cc_linked_list_compare((cc_object *)a_stack->items, (cc_object *)b_stack->items);
}

void cc_stack_register_comparator() {
  static bool first = true;
  
  if (first) {
    first = false;
    cc_object_register_comparator_for_type(cc_stack_type, cc_stack_compare);
  }
}

cc_object *cc_stack_to_object(cc_stack *stack) {
  return cc_object_with_pointer(stack, cc_stack_type);
}

cc_stack *cc_stack_from_object(cc_object *obj) {
  cc_stack *stack = cc_object_pointer_value(obj);
  return stack;
}
