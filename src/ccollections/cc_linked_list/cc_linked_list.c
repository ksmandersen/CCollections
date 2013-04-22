#include "../shared/cc_private.h"
#include "cc_linked_list.private.h"
#include "../shared/cc_enumerator_private.h"

const char * const cc_linked_list_type = "cc_linked_list_type";

struct cc_linked_list_struct {
  cc_collection c;

  struct cc_linked_list_node_struct *head;
  struct cc_linked_list_node_struct *tail;

  int length;
};


/*! \brief Create a linked list object
 * \return A new linked list object */
cc_linked_list *cc_linked_list_new() {
  cc_linked_list_register_comparator();

  cc_linked_list *list;
  if ((list = GC_MALLOC(sizeof(cc_linked_list))) == NULL)
    return NULL;

  list->c.enumerator_move_next = cc_linked_list_enumerator_move_next;

  list->head = NULL;
  list->tail = NULL;
  list->length = 0;

  return list;
}

/*! \brief Get the length of the list
 * \return The length of the list */
int cc_linked_list_length(cc_linked_list *list) {
  if (list == NULL)
    return 0;

  return list->length;
}


/*! \brief Get a node in a linked list
 * \param list the linked list
 * \param index the index of the node to get */
cc_object *cc_linked_list_get(cc_linked_list *list, int index) {
  if (list == NULL || list->head == NULL || index >= list->length)
    return NULL;

  cc_linked_list_node *curr = list->head;
  int i;
  for (i = 1; i < index; i++) {
    curr = curr->next;
  }

  if (curr == NULL)
    return NULL;

  return curr->object;
}

/*! \brief Get the first node in a linked list
 * \param list the linked list */
cc_object * cc_linked_list_get_first(cc_linked_list *list) {
  if (list == NULL || list->head == NULL)
    return NULL;

  return list->head->object;
}

/*! \brief Get the last node in a linked list
 * \param list the linked list */
cc_object * cc_linked_list_get_last(cc_linked_list *list)
{
  if (list == NULL || list->tail == NULL)
    return NULL;

  return list->tail->object; 
}

/*! \brief Insert a value at a position in the linked list
 * \param list the linked list
 * \param index the index at which to insert the object
 * \param object the object to insert */
void cc_linked_list_add(cc_linked_list *list, int index, cc_object *object)
{
  cc_linked_list_node *temp, *prev, *next, *curr;

  curr = list->head;
  if (index > list->length + 1 || index < 0) {
    // Exception?
    return;
  } else {
    if (index == 0) {
      cc_linked_list_add_first(list, object);
    } else if (index == list->length - 1) {
      cc_linked_list_add_last(list, object);
    } else {
      int i;
      for (i = 1; i < index; i++) {
        prev = curr;
        curr = curr->next;
      }

      if (curr != NULL) {
        if ((temp = cc_linked_list_node_new(object)) == NULL)
        {
          return;
        }
        temp->object = object;

        list->length++;

        prev->next = temp;
        temp->next = curr;
        curr->prev = temp;
      }
    }
  }
}

/*! \brief Insert a value as the first node in a linked list
 * \param list the linked list
 * \param object the value to insert */
void cc_linked_list_add_first(cc_linked_list *list, cc_object *object) {
  cc_linked_list_node *temp = cc_linked_list_node_new(object);
  if (list == NULL || temp == NULL)
    return;

  temp->object = object;

  if (list->head == NULL) {
    list->head = temp;
    list->tail = temp;
    list->length = 1;
  } else {
    temp->next = list->head;
    list->head = temp;
    list->length++;
  }
}

/*! \brief Insert a value as the last node in a linked list
 * \param list the linked list
 * \param object the value to insert */
void cc_linked_list_add_last(cc_linked_list *list, cc_object *object) {
  cc_linked_list_node *temp = cc_linked_list_node_new(object);
  if (list == NULL || temp == NULL)
    return;

  temp->object = object;
  temp->prev = list->tail;

  if (list->tail != NULL)
    list->tail->next = temp;

  list->tail = temp;

  if(list->head == NULL)
    list->head = temp;

  list->length++;
}

/*! \brief Remove a value at a position in the linked list
 * \param list the linked list
 * \param index the index at which to remove the object */
void cc_linked_list_remove(cc_linked_list *list, int index) {
  if (list == NULL || index > list->length - 1 || index < 0)
    return;

  if (list->length == 1) {
    cc_linked_list_clear(list);
  } else if (index == 0) {
    cc_linked_list_remove_first(list);
  } else if (index == list->length - 1) {
    cc_linked_list_remove_last(list);
  } else {

    cc_linked_list_node *curr = list->head;
    cc_linked_list_node *prev = NULL;
    int i;
    for (i = 1; i < index; i++) {
      prev = curr;
      curr = curr->next;
    }

    prev->next = curr->next;
    curr->next->prev = prev;
    curr = NULL;

    list->length--;
  }
}

/*! \brief Remove the value from the front node in a linked list
 * \param list the linked list */
void cc_linked_list_remove_first(cc_linked_list *list) {
  if (list == NULL || list->head == NULL)
    return;

  if (list->length == 1)
  {
    cc_linked_list_clear(list);
  } else {
    list->head = list->head->next;
    list->head->prev = NULL;  
    list->length--;
  }
}

/*! \brief Remove the value from the end node in a linked list
 * \param list the linked list */
void cc_linked_list_remove_last(cc_linked_list *list) {
  if (list == NULL || list->tail == NULL)
    return;

  if (list->length == 1) {
    cc_linked_list_clear(list);
  } else {
    list->tail = list->tail->prev;
    list->tail->next = NULL;  
    list->length--;
  }
}

/*! \brief Removes all objects from a linked list
 * \param list the linked list to be emptied */
void cc_linked_list_clear(cc_linked_list *list) {
  if (list == NULL)
    return;

  list->head = NULL;
  list->tail = NULL;
  list->length = 0;
}

/*! \brief Merges two lists together by adding all objects
 * from the first list to the second list.
 * \param a_list the first list
 * \param b_list the second list
 * \returns The lists merged together */
cc_linked_list *cc_linked_list_merge(cc_linked_list *a_list, cc_linked_list *b_list) {
  cc_linked_list_node *curr = b_list->head;
  while (curr != NULL) {
    cc_linked_list_add_last(a_list, curr->object);

    curr = curr->next;
  }

  b_list = NULL;

  return a_list;
}

bool cc_linked_list_contains(cc_linked_list *list, cc_object *obj) {
  // TODO
  return false;
}

cc_enumerator *cc_linked_list_get_enumerator(cc_linked_list *list) {
  cc_enumerator *e = GC_MALLOC(sizeof(cc_enumerator));
  e->collection = (cc_collection *)list;
  e->data = NULL;

  return e;
}

bool cc_linked_list_enumerator_move_next(cc_collection *collection, cc_enumerator *e)
{
  cc_linked_list *list = (cc_linked_list *)collection;
  cc_linked_list_node *prev_node = (cc_linked_list_node *)e->data;
  
  if (!prev_node) {
	  e->data = list->head;
  } else if (prev_node->next) {
	  e->data = prev_node->next;
  } else {
	  e->data = NULL;
  }
  
  if (!e->data) return false;
  
  cc_linked_list_node *current_node = (cc_linked_list_node *)e->data;
  e->current = current_node->object;
  
  return true;
}

cc_object *cc_linked_list_to_object(cc_linked_list *list) {
  return cc_object_with_data(list, sizeof(cc_linked_list), cc_linked_list_type);
}

cc_linked_list *cc_linked_list_from_object(cc_object *object)
{
  cc_linked_list *list = cc_object_data_value(object);
  return list;
}

int cc_linked_list_compare(cc_object *obj1, cc_object *obj2) {
  cc_linked_list *list1 = cc_linked_list_from_object(obj1);
  cc_linked_list *list2 = cc_linked_list_from_object(obj2);

  cc_enumerator *e1 = cc_linked_list_get_enumerator(list1);
  cc_enumerator *e2 = cc_linked_list_get_enumerator(list2);
  while (cc_enumerator_move_next(e1))
  {
    if (!cc_enumerator_move_next(e2)) return -1;
    if (!cc_object_is_equal(cc_enumerator_current(e1), cc_enumerator_current(e2))) return -1;
  }

  if (cc_enumerator_move_next(e2)) return 0;

  return true;
}

void cc_linked_list_register_comparator() {
  static bool first = true;

  if (first)
  {
    first = false;
    cc_object_register_comparator_for_type(cc_linked_list_type, cc_linked_list_compare);
  }
}

// Internal functions

cc_linked_list_node *cc_linked_list_node_new(cc_object *object) {
  cc_linked_list_node *node = GC_MALLOC(sizeof(cc_linked_list_node));
  if (node == NULL)
      return NULL;

  node->next = NULL;
  node->prev = NULL;
  node->object = object;

  return node;
}
