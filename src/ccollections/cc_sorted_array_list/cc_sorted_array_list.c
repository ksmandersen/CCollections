#include "cc_sorted_array_list.h"
#include "../cc_array_list/cc_array_list.private.h"
#include "../shared/cc_enumerator_private.h"
#include <stdlib.h>

const char * const cc_sorted_array_list_type = "cc_sorted_array_list_type";

static bool cc_sorted_array_list_enumerator_move_next(cc_collection *c, cc_enumerator *e);
static int cc_sorted_array_list_compare(cc_object *obj1, cc_object *obj2);
static void cc_sorted_array_list_register_comparator();

struct cc_sorted_array_list_struct {
  cc_collection c;
  
  cc_array_list *heap;
};

cc_sorted_array_list *cc_sorted_array_list_new() {
  cc_sorted_array_list_register_comparator();
  
  cc_sorted_array_list *list;
  if ((list = GC_MALLOC(sizeof(cc_sorted_array_list))) == NULL) {
    return NULL;
  }
  
  list->c.enumerator_move_next = cc_sorted_array_list_enumerator_move_next;
  list->heap = cc_array_list_new();
    
  return list;
}

void cc_sorted_array_list_add(cc_sorted_array_list *list, cc_object *obj) {
  if (list == NULL || obj == NULL) return;

  cc_array_list_add_last(list->heap, obj);
  
  if (list->heap->count > 1)
    cc_array_list_sort(list->heap);
}

/*! \brief Get the length of the list
 * \return The length of the list */
int cc_sorted_array_list_length(cc_sorted_array_list *list) {
  return list->heap->count;
}

/*! \brief Get a node in a linked list
 * \param list the linked list
 * \param index the index of the node to get */
cc_object *cc_sorted_array_list_get(cc_sorted_array_list *list, int index) {
  return cc_array_list_get(list->heap, index);
}

/*! \brief Get the first node in a linked list
 * \param list the linked list */
cc_object *cc_sorted_array_list_get_first(cc_sorted_array_list *list) {
  return cc_array_list_get_first(list->heap);
}

/*! \brief Get the last node in a linked list
 * \param list the linked list */
cc_object *cc_sorted_array_list_get_last(cc_sorted_array_list *list) {
  return cc_array_list_get_last(list->heap);
}


cc_enumerator *cc_sorted_array_list_get_enumerator(cc_sorted_array_list *list) {
  return cc_array_list_get_enumerator(list->heap);
}

bool cc_sorted_array_list_enumerator_move_next(cc_collection *c, cc_enumerator *e) {
  return cc_array_list_enumerator_move_next(c, e);
}

static int cc_sorted_array_list_compare(cc_object *obj1, cc_object *obj2) {
  cc_sorted_array_list *a_list = (cc_sorted_array_list *)obj1;
  cc_sorted_array_list *b_list = (cc_sorted_array_list *)obj2;

  return cc_array_list_compare((cc_object *)a_list->heap, (cc_object *)b_list->heap);
}

void cc_sorted_array_list_register_comparator() {
  static bool first = true;
  
  if (first) {
    first = false;
    cc_object_register_comparator_for_type(cc_sorted_array_list_type, cc_sorted_array_list_compare);
  }
}