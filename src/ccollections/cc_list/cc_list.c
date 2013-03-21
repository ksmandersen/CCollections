#include "../shared/cc_private.h"
#include "cc_list.private.h"
#include "../shared/cc_enumerator_private.h"

const char * const cc_list_type = "cc_list_type";

#define HEAP_IMPLEMENTATION 1
#define LINKED_LIST_IMPLEMENTATION 2

#define CURRENT_IMPLEMENTATION HEAP_IMPLEMENTATION

#if CURRENT_IMPLEMENTATION == LINKED_LIST_IMPLEMENTATION

static bool cc_list_enumerator_move_next(cc_collection *c, cc_enumerator *e);
static bool cc_list_compare(cc_object *obj1, cc_object *obj2);
static void cc_list_register_comparator();

struct cc_list_struct
{
  cc_collection c;

  struct cc_list_node_struct *head;
  struct cc_list_node_struct *tail;

  int length;
};


/*! \brief Create a linked list object
 * \return A new linked list object */
cc_list *cc_list_new()
{
  cc_list_register_comparator();

  cc_list *list;
  if ((list = GC_MALLOC(sizeof(cc_list))) == NULL)
    return NULL;

  list->c.enumerator_move_next = cc_list_enumerator_move_next;

  list->head = NULL;
  list->tail = NULL;
  list->length = 0;

  return list;
}

/*! \brief Get the length of the list
 * \return The length of the list */
int cc_list_length(cc_list *list)
{
  if (list == NULL)
    return 0;

  return list->length;
}


/*! \brief Get a node in a linked list
 * \param list the linked list
 * \param index the index of the node to get */
cc_object *cc_list_get(cc_list *list, int index)
{
  if (list == NULL || list->head == NULL || index >= list->length)
    return NULL;

  cc_list_node *curr = list->head;
  int i;
  for (i = 1; i < index; i++)
  {
    curr = curr->next;
  }

  if (curr == NULL)
    return NULL;

  return curr->object;
}

/*! \brief Get the first node in a linked list
 * \param list the linked list */
cc_object * cc_list_get_first(cc_list *list)
{
  if (list == NULL || list->head == NULL)
    return NULL;

  return list->head->object;
}

/*! \brief Get the last node in a linked list
 * \param list the linked list */
cc_object * cc_list_get_last(cc_list *list)
{
  if (list == NULL || list->tail == NULL)
    return NULL;

  return list->tail->object; 
}

/*! \brief Insert a value at a position in the linked list
 * \param list the linked list
 * \param index the index at which to insert the object
 * \param object the object to insert */
void cc_list_add(cc_list *list, int index, cc_object *object)
{
  cc_list_node *temp, *prev, *next, *curr;

  curr = list->head;
  if (index > list->length + 1 || index < 0)
  {
    // Exception?
    return;
  } else {
    if (index == 0)
    {
      cc_list_add_first(list, object);
    } else if (index == list->length - 1) {
      cc_list_add_last(list, object);
    } else {
      int i;
      for (i = 1; i < index; i++)
      {
        prev = curr;
        curr = curr->next;
      }

      if (curr != NULL)
      {
        if ((temp = cc_list_node_new(object)) == NULL)
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
void cc_list_add_first(cc_list *list, cc_object *object)
{
  cc_list_node *temp = cc_list_node_new(object);
  if (list == NULL || temp == NULL)
    return;

  temp->object = object;

  if (list->head == NULL)
  {
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
void cc_list_add_last(cc_list *list, cc_object *object)
{
  cc_list_node *temp = cc_list_node_new(object);
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
void cc_list_remove(cc_list *list, int index)
{
  if (list == NULL || index > list->length - 1 || index < 0)
    return;

  if (list->length == 1) {
    cc_list_clear(list);
  } else if (index == 0) {
    cc_list_remove_first(list);
  } else if (index == list->length - 1) {
    cc_list_remove_last(list);
  } else {

    cc_list_node *curr = list->head;
    cc_list_node *prev = NULL;
    int i;
    for (i = 1; i < index; i++)
    {
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
void cc_list_remove_first(cc_list *list)
{
  if (list == NULL || list->head == NULL)
    return;

  if (list->length == 1)
  {
    cc_list_clear(list);
  } else {
    list->head = list->head->next;
    list->head->prev = NULL;  
    list->length--;
  }
}

/*! \brief Remove the value from the end node in a linked list
 * \param list the linked list */
void cc_list_remove_last(cc_list *list)
{
  if (list == NULL || list->tail == NULL)
    return;

  if (list->length == 1)
  {
    cc_list_clear(list);
  } else {
    list->tail = list->tail->prev;
    list->tail->next = NULL;  
    list->length--;
  }
}

/*! \brief Removes all objects from a linked list
 * \param list the linked list to be emptied */
void cc_list_clear(cc_list *list)
{
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
cc_list *cc_list_merge(cc_list *a_list, cc_list *b_list)
{
  cc_list_node *curr = b_list->head;
  while (curr != NULL)
  {
    cc_list_add_last(a_list, curr->object);

    curr = curr->next;
  }

  b_list = NULL;

  return a_list;
}

bool cc_list_contains(cc_list *list, cc_object *obj)
{
  return false;
}

cc_enumerator *cc_list_get_enumerator(cc_list *list)
{
  cc_enumerator *e = GC_MALLOC(sizeof(cc_enumerator));
  e->collection = (cc_collection *)list;
  e->data = GC_MALLOC(sizeof(cc_list_node));
  // *((cc_list_node *)e->data) = NULL;

  return e;
}

bool cc_list_enumerator_move_next(cc_collection *collection, cc_enumerator *e)
{
  cc_list_node *marker = (cc_list_node *)e->data;
  *marker = *marker->next;
  cc_list *list = (cc_list *)collection;

  // FIXME: This condition is met both at the beginning and
  // end of the list. Make a struct with a bool and a pointer
  // instead. The boolean indicating wether the enumeration has
  // yet begun.
  if (marker == NULL)
    return false;

  e->current = marker->object;

  return true;
}

cc_object *cc_list_to_object(cc_list *list)
{
  return cc_object_with_data(list, sizeof(cc_list), cc_list_type);
}

cc_list *cc_list_from_object(cc_object *object)
{
  cc_list *list = cc_list_new();
  cc_object_data_value(object, (void **)&list, sizeof(cc_list_type));
  return list;
}

bool cc_list_compare(cc_object *obj1, cc_object *obj2)
{
  cc_list *list1 = cc_list_from_object(obj1);
  cc_list *list2 = cc_list_from_object(obj2);

  cc_enumerator *e1 = cc_list_get_enumerator(list1);
  cc_enumerator *e2 = cc_list_get_enumerator(list2);
  while (cc_enumerator_move_next(e1))
  {
    if (!cc_enumerator_move_next(e2)) return false;
    if (!cc_object_is_equal(cc_enumerator_current(e1), cc_enumerator_current(e2))) return false;
  }

  if (cc_enumerator_move_next(e2)) return false;

  return true;
}

void cc_list_register_comparator()
{
  static bool first = true;

  if (first)
  {
    first = false;
    cc_object_register_comparator_for_type(cc_list_type, cc_list_compare);
  }
}

// Internal functions

cc_list_node *cc_list_node_new(cc_object *object)
{
  cc_list_node *node = GC_MALLOC(sizeof(cc_list_node));
  if (node == NULL)
      return NULL;

  node->next = NULL;
  node->prev = NULL;
  node->object = object;

  return node;
}

#elif CURRENT_IMPLEMENTATION == HEAP_IMPLEMENTATION

static bool cc_list_enumerator_move_next(cc_collection *c, cc_enumerator *e);
static bool cc_list_compare(cc_object *obj1, cc_object *obj2);
static void cc_list_register_comparator();
static void cc_list_expand_heap(cc_list *list);

struct cc_list_struct {
	cc_collection c;
	
	cc_object **heap;
	int count;
	int heap_size;
};


/*! \brief Create a linked list object
 * \return A new linked list object */
cc_list *cc_list_new() {
	cc_list_register_comparator();
	
	cc_list *list;
	if ((list = GC_MALLOC(sizeof(cc_list))) == NULL) {
		return NULL;
	}
	
	list->c.enumerator_move_next = cc_list_enumerator_move_next;
	
	list->count = 0;
	list->heap_space = 128;
	list->heap = CG_MALLOC(sizeof(cc_object *) * list->heap_size);
	
	return list;
}

/*! \brief Get the length of the list
 * \return The length of the list */
int cc_list_length(cc_list *list) {
	if (list == NULL) {
	 	return 0;
	}

	return list->count;
}

/*! \brief Get a node in a linked list
 * \param list the linked list
 * \param index the index of the node to get */
cc_object *cc_list_get(cc_list *list, int index) {
	if (list == NULL || index >= list->count) return NULL;
	
	return list->heap[index];
}

/*! \brief Get the first node in a linked list
 * \param list the linked list */
cc_object * cc_list_get_first(cc_list *list) {
	if (list == NULL || list->count == 0) return NULL;

	return list->heap[0];
}

/*! \brief Get the last node in a linked list
 * \param list the linked list */
cc_object * cc_list_get_last(cc_list *list) {
	if (list == NULL || list->count == 0) return NULL;

	return list->heap[list->count - 1];
}

/*! \brief Insert a value at a position in the linked list
 * \param list the linked list
 * \param index the index at which to insert the object
 * \param object the object to insert */
void cc_list_add(cc_list *list, int index, cc_object *object) {
	if (list == NULL || object == NULL || index > list->count) return NULL;
	
	if (list->heap_space == list->count) cc_list_expand_heap(list);
	
	int i;
	for (i = list->count; i >= index; i--) {
		list->heap[i + 1] = list->heap[i]; 
	}
	
	list->heap[i] = object;
}

/*! \brief Insert a value as the first node in a linked list
 * \param list the linked list
 * \param object the value to insert */
void cc_list_add_first(cc_list *list, cc_object *object) {
	cc_list_add(list, 0, object);
}

/*! \brief Insert a value as the last node in a linked list
 * \param list the linked list
 * \param object the value to insert */
void cc_list_add_last(cc_list *list, cc_object *object) {
	cc_list_add(list, list->count, object);
}

/*! \brief Remove a value at a position in the linked list
 * \param list the linked list
 * \param index the index at which to remove the object */
void cc_list_remove(cc_list *list, int index) {
	if (list == NULL || index >= list->count) return;
	
	int i;
	for (i = index; i < count; i++) {
		list->heap[i] = list->heap[i + 1];
	}
}

/*! \brief Remove the value from the front node in a linked list
 * \param list the linked list */
void cc_list_remove_first(cc_list *list) {
	cc_list_remove(list, 0);
}

/*! \brief Remove the value from the end node in a linked list
 * \param list the linked list */
void cc_list_remove_last(cc_list *list) {
	cc_list_remove(list, list->count - 1);
}

/*! \brief Removes all objects from a linked list
 * \param list the linked list to be emptied */
void cc_list_clear(cc_list *list) {
	memset(list->heap, 0, list->heap_size * sizeof(object *));
	list->count = 0;
}

/*! \brief Merges two lists together by adding all objects
 * from the first list to the second list.
 * \param a_list the first list
 * \param b_list the second list
 * \returns The lists merged together */
cc_list *cc_list_merge(cc_list *a_list, cc_list *b_list) {
	cc_enumerator *e = cc_list_get_enumerator(a_list);
	while (cc_enumerator_move_next(e)) {
		cc_list_add(b_list, cc_enumerator_current(e));
	}
}

bool cc_list_contains(cc_list *list, cc_object *obj) {
	int i;
	for (i = 0; i < list->count; i++) {
		if (cc_object_is_equal(list->heap[i], obj)) {
			return true;
		}
	}
	
	return false;
}

cc_enumerator *cc_list_get_enumerator(cc_list *list) {
	cc_enumerator *e = GC_MALLOC(sizeof(cc_enumerator));
	e->collection = (cc_collection *)list;
	e->data = GC_MALLOC(sizeof(int));
	*((int *)e->data) = -1;

	return e;
}

bool cc_list_enumerator_move_next(cc_collection *collection, cc_enumerator *e) {
	int *counter = (int *)e->data;
	*counter = *counter + 1;
	cc_list *list = (cc_list *)collection;
	
	if (*counter >= list->count) {
		return false;
	}
	
	e->current = list->heap[*counter];
	return true;
}

cc_object *cc_list_to_object(cc_list *list) {
	return cc_object_with_data(list, sizeof(cc_list), cc_list_type);
}

cc_list *cc_list_from_object(cc_object *object) {
	cc_list *list = cc_list_new();
	cc_object_data_value(object, (void **)&list, sizeof(cc_list_type));
	return list;
}

bool cc_list_compare(cc_object *obj1, cc_object *obj2) {
	cc_list *list1 = cc_list_from_object(obj1);
	cc_list *list2 = cc_list_from_object(obj2);

	cc_enumerator *e1 = cc_list_get_enumerator(list1);
	cc_enumerator *e2 = cc_list_get_enumerator(list2);
	while (cc_enumerator_move_next(e1)) {
		if (!cc_enumerator_move_next(e2)) return false;
		if (!cc_object_is_equal(cc_enumerator_current(e1), cc_enumerator_current(e2))) return false;
	}

	if (cc_enumerator_move_next(e2)) return false;

	return true;
}

void cc_list_register_comparator() {
	static bool first = true;

	if (first) {
		first = false;
		cc_object_register_comparator_for_type(cc_list_type, cc_list_compare);
	}
}

#endif