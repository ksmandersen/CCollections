#include "cc_stack.h"
#include "../cc_linked_list/cc_linked_list.private.h"
#include "../cc_array_list/cc_array_list.h"
#include "../shared/cc_hash.h"
#include "../shared/cc_enumerator_private.h"
#include <stdlib.h>

const char * const cc_stack_type = "cc_stack_type";

static bool cc_stack_enumerator_move_next(cc_collection *c, cc_enumerator *e);
static bool cc_stack_compare(cc_object *obj1, cc_object *obj2);
static void cc_stack_register_comparator();

struct cc_stack_struct {
  cc_collection c;

  cc_linked_list *items;
};

cc_stack *cc_stack_new() {
  cc_stack_register_comparator();

  cc_stack *stack;
  if ((stack = GC_MALLOC(sizeof(cc_stack))) == NULL) {
    return NULL;
  }

  stack->c.enumerator_move_next = cc_stack_enumerator_move_next;
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

bool cc_stack_enumerator_move_next(cc_collection *c, cc_enumerator *e) {
  return cc_linked_list_enumerator_move_next(c, e);
}

bool cc_stack_compare(cc_object *obj1, cc_object *obj2) {
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

cc_object *cc_stack_to_object(cc_set *set) {
  return cc_object_with_data(set, sizeof(cc_stack), cc_stack_type);
}

cc_stack *cc_stack_from_object(cc_object *obj) {
  cc_stack *stack = cc_stack_new();
  cc_object_data_value(obj, (void **)&stack, sizeof(cc_stack_type));
  return stack;
}
