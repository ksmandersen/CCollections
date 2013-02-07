#include "linked_list.private.h"

#include "gc/gc.h"

/*! \brief Create a linked list object
 * \return A new linked list object */
cc_list *cc_list_new()
{
  // TODO: Only do this, if it hasn't been done yet!
  GC_INIT();\

  cc_list *list;
  if ((list = GC_MALLOC(sizeof(cc_list))) == NULL)
    return NULL;

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
any_t cc_list_get(cc_list *list, int index)
{
  if (list == NULL || list->head == NULL || index > list->length)
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
any_t cc_list_get_front(cc_list *list)
{
  if (list == NULL || list->head == NULL)
    return NULL;

  return list->head->object;
}

/*! \brief Get the last node in a linked list
 * \param list the linked list */
any_t cc_list_get_end(cc_list *list)
{
  if (list == NULL || list->tail == NULL)
    return NULL;

  return list->tail->object; 
}

/*! \brief Insert a value at a position in the linked list
 * \param list the linked list
 * \param index the index at which to insert the object
 * \param object the object to insert */
void cc_list_add(cc_list *list, int index, any_t *object)
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
      cc_list_add_front(list, object);
    } else if (index == list->length - 1) {
      cc_list_add_end(list, object);
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
void cc_list_add_front(cc_list *list, any_t object)
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
void cc_list_add_end(cc_list *list, any_t object)
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
    cc_list_remove_front(list);
  } else if (index == list->length - 1) {
    cc_list_remove_end(list);
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
void cc_list_remove_front(cc_list *list)
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
void cc_list_remove_end(cc_list *list)
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


// Internal functions

cc_list_node *cc_list_node_new(any_t object)
{
  cc_list_node *node = GC_MALLOC(sizeof(cc_list_node));
  if (node == NULL)
      return NULL;

  node->next = NULL;
  node->prev = NULL;
  node->object = object;

  return node;
}