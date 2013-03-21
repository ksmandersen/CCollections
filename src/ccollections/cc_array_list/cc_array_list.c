#include "../shared/cc_private.h"
#include "cc_array_list.private.h"
#include "../shared/cc_enumerator_private.h"

const char *const cc_array_list_type = "cc_array_list_type";

static bool cc_array_list_enumerator_move_next(cc_collection *c, cc_enumerator *e);
static bool cc_array_list_compare(cc_object *obj1, cc_object *obj2);
static void cc_array_list_register_comparator();
static void cc_array_list_expand_heap(cc_array_list *list);

struct cc_array_list_struct {
  cc_collection c;
  
  cc_object **heap;
  int count;
  int heap_size;
};


/*! \brief Create a linked list object
 * \return A new linked list object */
cc_array_list *cc_array_list_new() {
  cc_array_list_register_comparator();
  
  cc_array_list *list;
  if ((list = GC_MALLOC(sizeof(cc_array_list))) == NULL) {
    return NULL;
  }
  
  list->c.enumerator_move_next = cc_array_list_enumerator_move_next;
  
  list->count = 0;
  list->heap_size = 128;
  list->heap = GC_MALLOC(sizeof(cc_object *) * list->heap_size);
  
  return list;
}

void cc_array_list_expand_heap(cc_array_list *list) {
  list->heap_size *= 2;
  list->heap = GC_REALLOC(list->heap, list->heap_size);
}

/*! \brief Get the length of the list
 * \return The length of the list */
int cc_array_list_length(cc_array_list *list) {
  if (list == NULL) {
    return 0;
  }

  return list->count;
}

/*! \brief Get a node in a linked list
 * \param list the linked list
 * \param index the index of the node to get */
cc_object *cc_array_list_get(cc_array_list *list, int index) {
  if (list == NULL || index >= list->count) return NULL;
  
  return list->heap[index];
}

/*! \brief Get the first node in a linked list
 * \param list the linked list */
cc_object * cc_array_list_get_first(cc_array_list *list) {
  if (list == NULL || list->count == 0) return NULL;

  return list->heap[0];
}

/*! \brief Get the last node in a linked list
 * \param list the linked list */
cc_object * cc_array_list_get_last(cc_array_list *list) {
  if (list == NULL || list->count == 0) return NULL;

  return list->heap[list->count - 1];
}

/*! \brief Insert a value at a position in the linked list
 * \param list the linked list
 * \param index the index at which to insert the object
 * \param object the object to insert */
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

/*! \brief Insert a value as the first node in a linked list
 * \param list the linked list
 * \param object the value to insert */
void cc_array_list_add_first(cc_array_list *list, cc_object *object) {
  cc_array_list_add(list, 0, object);
}

/*! \brief Insert a value as the last node in a linked list
 * \param list the linked list
 * \param object the value to insert */
void cc_array_list_add_last(cc_array_list *list, cc_object *object) {
  cc_array_list_add(list, list->count, object);
}

/*! \brief Remove a value at a position in the linked list
 * \param list the linked list
 * \param index the index at which to remove the object */
void cc_array_list_remove(cc_array_list *list, int index) {
  if (list == NULL || index >= list->count) return;
  
  int i;
  for (i = index; i < list->count; i++) {
    list->heap[i] = list->heap[i + 1];
  }

  list->count--;
}

/*! \brief Remove the value from the front node in a linked list
 * \param list the linked list */
void cc_array_list_remove_first(cc_array_list *list) {
  cc_array_list_remove(list, 0);
}

/*! \brief Remove the value from the end node in a linked list
 * \param list the linked list */
void cc_array_list_remove_last(cc_array_list *list) {
  cc_array_list_remove(list, list->count - 1);
}

/*! \brief Removes all objects from a linked list
 * \param list the linked list to be emptied */
void cc_array_list_clear(cc_array_list *list) {
  memset(list->heap, 0, list->heap_size * sizeof(cc_object *));
  list->count = 0;
}

/*! \brief Merges two lists together by adding all objects
 * from the first list to the second list.
 * \param a_list the first list
 * \param b_list the second list
 * \returns The lists merged together */
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
  cc_enumerator *e = GC_MALLOC(sizeof(cc_enumerator));
  e->collection = (cc_collection *)list;
  e->data = GC_MALLOC(sizeof(int));
  *((int *)e->data) = -1;

  return e;
}

bool cc_array_list_enumerator_move_next(cc_collection *collection, cc_enumerator *e) {
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
  return cc_object_with_data(list, sizeof(cc_array_list), cc_array_list_type);
}

cc_array_list *cc_array_list_from_object(cc_object *object) {
  cc_array_list *list = cc_array_list_new();
  cc_object_data_value(object, (void **)&list, sizeof(cc_array_list_type));
  return list;
}

bool cc_array_list_compare(cc_object *obj1, cc_object *obj2) {
  cc_array_list *list1 = cc_array_list_from_object(obj1);
  cc_array_list *list2 = cc_array_list_from_object(obj2);

  cc_enumerator *e1 = cc_array_list_get_enumerator(list1);
  cc_enumerator *e2 = cc_array_list_get_enumerator(list2);
  while (cc_enumerator_move_next(e1)) {
    if (!cc_enumerator_move_next(e2)) return false;
    if (!cc_object_is_equal(cc_enumerator_current(e1), cc_enumerator_current(e2))) return false;
  }

  if (cc_enumerator_move_next(e2)) return false;

  return true;
}

void cc_array_list_register_comparator() {
  static bool first = true;

  if (first) {
    first = false;
    cc_object_register_comparator_for_type(cc_array_list_type, cc_array_list_compare);
  }
}