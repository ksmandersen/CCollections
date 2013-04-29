#include "../shared/cc_private.h"
#include "../cc_linked_list/cc_linked_list.private.h"
#include "../shared/cc_enumerator_private.h"

/*! \brief A linked list data structure that stays sorted with insertions. 
 * Sorting is performed using inserted objects comperator. It is therefore
 * important that all inserted objects have the same type. */
const char *const cc_sorted_list_type = "cc_sorted_list_type";

struct cc_sorted_list_struct
{
  cc_collection c;
  cc_linked_list *data;
};

/*! \brief Create a linked list object
 * \return A new linked list object */
cc_sorted_list *cc_sorted_list_new() {
  cc_sorted_list *list;
  if ((list = GC_MALLOC(sizeof(cc_sorted_list))) == NULL)
    return NULL;

  list->c.enumerator_move_next = cc_linked_list_enumerator_move_next;

  if ((list->data = cc_linked_list_new()) == NULL)
    return NULL;

  return list;
}

/*! \brief Get the length of the list
 * \return The length of the list */
int cc_sorted_list_length(cc_sorted_list *list) {
  return cc_linked_list_length(list->data);
}

/*! \brief Get a node in a linked list
 * \param list the linked list
 * \param index the index of the node to get */
cc_object *cc_sorted_list_get(cc_sorted_list *list, int index) {
  return cc_linked_list_get(list->data, index);
}

/*! \brief Get the first node in a linked list
 * \param list the linked list */
cc_object *cc_sorted_list_get_first(cc_sorted_list *list) {
  return cc_linked_list_get_first(list->data);
}

/*! \brief Get the last node in a linked list
 * \param list the linked list */
cc_object *cc_sorted_list_get_last(cc_sorted_list *list) {
  return cc_linked_list_get_last(list->data);
}

/*! \brief Insert a value at a position in the linked list
 * \param list the linked list
 * \param index the index at which to insert the object
 * \param object the object to insert */
void cc_sorted_list_add(cc_sorted_list *list, cc_object *object) {
  if (cc_sorted_list_length(list) == 0)
    return cc_linked_list_add_first(list->data, object);

  int index = 0;
  cc_enumerator *e = cc_linked_list_get_enumerator(list->data);
  cc_object_comparator comp = cc_get_comperator_for_object(object);
  while (cc_enumerator_move_next(e)) {
    if (comp(object, cc_enumerator_current(e)) == 1) {
      break;
    }
    index++;
  }

  cc_linked_list_add(list->data, index, object);
}


/*! \brief Remove a value at a position in the linked list
 * \param list the linked list
 * \param index the index at which to remove the object */
void cc_sorted_list_remove(cc_sorted_list *list, int index) {
  cc_linked_list_remove(list->data, index);
}

/*! \brief Remove the value from the front node in a linked list
 * \param list the linked list */
void cc_sorted_list_remove_first(cc_sorted_list *list) {
  cc_linked_list_remove_first(list->data);
}

/*! \brief Remove the value from the end node in a linked list
 * \param list the linked list */
void cc_sorted_list_remove_last(cc_sorted_list *list) {
  cc_linked_list_remove_last(list->data);
}

/*! \brief Removes all objects from a linked list
 * \param list the linked list to be emptied */
void cc_sorted_list_clear(cc_sorted_list *list) {
  cc_linked_list_clear(list->data);
}

/*! \brief Merges two lists together by adding all objects
 * from the first list to the second list.
 * \param a_list the first list
 * \param b_list the second list
 * \returns The lists merged together */
cc_sorted_list *cc_sorted_list_merge(cc_sorted_list *a_list, cc_sorted_list *b_list) {
  cc_enumerator *e = cc_sorted_list_get_enumerator(b_list);
  while (cc_enumerator_move_next(e)) {
    cc_sorted_list_add(a_list, cc_enumerator_current(e));
  }

  return a_list;
}

bool cc_sorted_list_contains(cc_sorted_list *list, cc_object *object) {
  return cc_linked_list_contains(list->data, object);
}

cc_enumerator *cc_sorted_list_get_enumerator(cc_sorted_list *list) {
  return cc_linked_list_get_enumerator(list->data);
}

cc_object *cc_sorted_list_to_object(cc_sorted_list *list) {
  return cc_object_with_data(list, sizeof(cc_sorted_list), cc_sorted_list_type);
}

cc_sorted_list *cc_sorted_list_from_object(cc_object *object) {
  cc_sorted_list *list = cc_object_data_value(object);
  return list;
}