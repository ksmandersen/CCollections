// /*
//  * CC_SET.C
//  * 
//  * This file is part of the CCollections library.
//  *
//  * CCollections is licensed under the BSD-2-Clause License (FreeBSD).
//  * Copyright (c) 2012, Ulrik Damm and Kristian Andersen.
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without 
//  * modification, are permitted provided that the following conditions 
//  * are met:
//  *
//  * Redistributions of source code must retain the above copyright notice, 
//  * this list of conditions and the following disclaimer. Redistributions 
//  * in binary form must reproduce the above copyright notice, this list 
//  * of conditions and the following disclaimer in the documentation and/or 
//  * other materials provided with the distribution. THIS SOFTWARE IS 
//  * PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
//  * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
//  * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
//  * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
//  * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
//  * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
//  * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
//  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
//  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
//  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  */

// #include "../shared/cc_private.h"
// #include "cc_set.h"
// #include "../shared/cc_enumerator_private.h"

// const char * const cc_set_type = "cc_set_type";

// #define HEAP_IMPLEMENTATION 1
// #define LIST_IMPLEMENTATION 2

// #define CURRENT_IMPLEMENTATION HEAP_IMPLEMENTATION

// #if CURRENT_IMPLEMENTATION == HEAP_IMPLEMENTATION

// static bool cc_set_enumerator_move_next(cc_enumerable *c, cc_enumerator *e);
// static int cc_set_compare(cc_object *obj1, cc_object *obj2);
// static void cc_set_register_comparator();
// static void cc_set_expand_heap(cc_set *set);

// struct cc_set_struct {
//   cc_collection c;
//   cc_object **heap;
//   int heap_size;
//   int count;
// };

// cc_set *cc_set_new() {
//   cc_set_register_comparator();
  
//   cc_set *set;
//   if ((set = GC_MALLOC(sizeof(cc_set))) == NULL) {
//     return NULL;
//   }
  
//   set->c.enumerable.move_next = cc_set_enumerator_move_next;
//   set->heap_size = 128;
//   set->count = 0;
//   set->heap = GC_MALLOC(sizeof(cc_object *) * set->heap_size);
//   return set;
// }

// cc_enumerator *cc_set_get_enumerator(cc_set *set) {
//   cc_enumerator *e = cc_enumerator_new(&set->c.enumerable);
//   e->data = GC_MALLOC(sizeof(int));
//   *((int *)e->data) = -1;
//   return e;
// }

// int cc_set_count(cc_set *set)
// {
//   return set->count;
// }

// bool cc_set_enumerator_move_next(cc_enumerable *c, cc_enumerator *e) {
//   int *counter = (int *)e->data;
//   *counter = *counter + 1;
//   cc_set *set = (cc_set *)c;
  
//   if (*counter >= set->count) {
//     return false;
//   }
  
//   e->current = set->heap[*counter];
//   return true;
// }

// void cc_set_add(cc_set *set, cc_object *obj) {
//   if (!cc_set_contains(set, obj)) {
//     int i;
//     for (i = 0; i <= set->heap_size; i++) {
//       if (i == set->heap_size) {
//         cc_set_expand_heap(set);
//       }
//       if (set->heap[i] == NULL) {
//         set->heap[i] = obj;
//         set->count++;
//         break;
//       }
//     }
//   }
// }

// void cc_set_merge(cc_set *a_set, cc_set *b_set) {
//   cc_enumerator *e = cc_set_get_enumerator(b_set);
//   while (cc_enumerator_move_next(e)) {
//     cc_set_add(a_set, cc_enumerator_current(e));
//   }
// }

// void cc_set_expand_heap(cc_set *set) {    
//     set->heap_size = 2 * set->heap_size;
//     set->heap = GC_REALLOC(set->heap, sizeof(cc_object *) * set->heap_size);
// }

// void cc_set_clear(cc_set *set) {
//   int i;
//   for (i = 0; i < set->count; i++) {
//     set->heap[i] = NULL;
//   }
  
//   set->count = 0;
// }

// bool cc_set_contains(cc_set *set, cc_object *obj) {
//   cc_enumerator *e = cc_set_get_enumerator(set);
//   while (cc_enumerator_move_next(e)) {
//     cc_object *obj2 = cc_enumerator_current(e);
    
//     if (cc_object_is_equal(obj, obj2)) {
//       return true;
//     }
//   }
  
//   return false;
// }

// void cc_set_remove(cc_set *set, cc_object *obj) {
//   int i;
//   for (i = 0; i < set->count; i++) {
//     if (cc_object_is_equal(obj, set->heap[i])) {
//       set->heap[i] = NULL;
//       set->count--;
//     }
//   }
// }

// cc_object *cc_set_to_object(cc_set *set) {
//   return cc_object_with_pointer(set, cc_set_type);
// }

// cc_set *cc_set_from_object(cc_object *obj) {
//   cc_set *set = cc_object_pointer_value(obj);
//   return set;
// }

// int cc_set_compare(cc_object *obj1, cc_object *obj2) {
//   cc_set *set1 = cc_set_from_object(obj1);
//   cc_set *set2 = cc_set_from_object(obj2);
  
//   cc_enumerator *e1 = cc_set_get_enumerator(set1);
//   cc_enumerator *e2 = cc_set_get_enumerator(set2);
//   while (cc_enumerator_move_next(e1)) {
//     if (!cc_enumerator_move_next(e2)) return -1;
//     if (!cc_object_is_equal(cc_enumerator_current(e1), cc_enumerator_current(e2))) return -1;
//   }
  
//   if (cc_enumerator_move_next(e2)) return 1;
//   return 0;
// }

// void cc_set_register_comparator() {
//   static bool first = true;
  
//   if (first) {
//     first = false;
//     cc_object_register_comparator_for_type(cc_set_type, cc_set_compare);
//   }
// }

// #elif CURRENT_IMPLEMENTATION == LIST_IMPLEMENTATION

// #include "../cc_list/cc_list.h"

// static bool cc_set_enumerator_move_next(cc_collection *c, cc_enumerator *e);
// static bool cc_set_compare(cc_object *obj1, cc_object *obj2);
// static void cc_set_register_comparator();

// struct cc_set_struct {
//   cc_collection c;
//   cc_list *list;
// };

// cc_set *cc_set_new() {
//   cc_set_register_comparator();
//   cc_set *set = GC_MALLOC(sizeof(cc_set));
//   set->c.enumerator_move_next = cc_set_enumerator_move_next;
//   set->list = cc_list_new();
//   return set;
// }

// cc_enumerator *cc_set_get_enumerator(cc_set *set) {
//   return cc_list_get_enumerator(set->list);
// }

// bool cc_set_enumerator_move_next(cc_collection *c, cc_enumerator *e) {
//   return cc_list_enumerator_move_next(c, e);
// }

// void cc_set_add(cc_set *set, cc_object *obj) {
//   if (!cc_set_contains(set, obj)) {
//     cc_list_add(set->list, obj);
//   }
// }

// void cc_set_clear(cc_set *set) {
//   cc_list_clear(set->list);
// }

// bool cc_set_contains(cc_set *set, cc_object *obj) {
//   return cc_list_contains(set->list, obj);
// }

// void cc_set_remove(cc_set *set, cc_object *obj) {
//   cc_list_remove(set->list, obj);
// }

// cc_object *cc_set_to_object(cc_set *set) {
//   return cc_object_with_data(set, sizeof(cc_set), cc_set_type);
// }

// cc_set *cc_set_from_object(cc_object *obj) {
//   cc_set *set = cc_set_new();
//   cc_object_data_value(obj, (void **)&set, sizeof(cc_set));
//   return set;
// }

// bool cc_set_compare(cc_object *obj1, cc_object *obj2) {
//   return cc_list_compare(obj1->list, obj2->list);
// }

// void cc_set_register_comparator() {
//   static bool first = true;
  
//   if (first) {
//     first = false;
//     cc_object_register_comparator_for_type(cc_set_type, cc_set_compare);
//   }
// }

// void cc_set_merge(cc_set *a_set, cc_set *b_set) {
//   cc_enumerator *e = cc_set_get_enumerator(b_set);
//   while (cc_enumerator_move_next(e)) {
//     cc_set_add(a_set, cc_enumerator_current(e));
//   }
// }

// #endif
