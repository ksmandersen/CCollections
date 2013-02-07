#include "linked_list.h"
#include "gc/gc.h"

linked_node_t *create_linked_node(any_t item)
{
  linked_node_t *node = GC_MALLOC(sizeof(linked_node_t));
  if (node == NULL)
    return NULL;

  node->next = NULL;
  node->item = item;

  return node;
}


linked_list_t *create_linked_list()
{
  linked_list_t *list;

  GC_INIT();

  if ((list = GC_MALLOC(sizeof(linked_list_t))) == NULL)
  {
    return NULL;
  }

  list->head = NULL;
  list->length = 0;

  return list;
}

void empty_linked_list(linked_list_t *list)
{
  if (list == NULL || list->head == NULL)
    return;

  list->head = NULL;
  list->length = 0;
}

void destroy_linked_list(linked_list_t *list)
{
  // if (list == NULL)
  //   return;

  // empty_linked_list(list);
  // GC_FREE(list);
}

any_t get_first(linked_list_t *list)
{
  if (list == NULL || list->head == NULL)
  {
    return;
  }

  return list->head->item;
}

any_t get_last(linked_list_t *list)
{
  if (list == NULL || list->head == NULL)
  {
    return;
  }

  if (list->length == 1)
  {
    return get_first(list);
  } else {
    linked_node_t *curr = list->head;
    while(curr->next != NULL)
    {
      curr = curr->next;
    }

    return curr->next->item;
  }
}

any_t get(linked_list_t *list, int index)
{
  if (list == NULL || list->head == NULL)
  {
    return;
  }

  linked_node_t *curr = list->head;
  int i;
  for (i = 1; i < index; i++)
  {
    curr = curr->next;
  }

  if (curr == NULL)
  {
    return NULL;
  }

  return curr->item;
}

void insert_first(linked_list_t *list, any_t item)
{
  linked_node_t *temp = create_linked_node(item);
  if (temp == NULL)
    return;

  temp->item = item;

  if (list->head == NULL)
  {
    list->head = temp;
    list->head->next = NULL;
    list->length = 1;
  } else {
    temp->next = list->head;
    list->head = temp;
    list->length++;
  }
}

void insert_last(linked_list_t *list, any_t item)
{
  linked_node_t *temp = create_linked_node(item);
  if (temp == NULL)
  {
    return;
  }

  temp->item = item;

  if (list->head == NULL)
  {
    list->head = temp;
    list->head->next = NULL;
    list->length = 1;
  } else {
    struct node_struct *tail = list->head;

    while (tail->next != NULL)
    {
      tail = tail->next;
    }

    temp->next = NULL;
    tail->next = temp;
    list->length++;
  }
}

void insert_at(linked_list_t *list, int index, any_t *item)
{
  linked_node_t *temp, *prev, *next, *curr;

  curr = list->head;
  if (index > list->length + 1 || index <= 0)
  {
    // Exception?
    return;
  } else {
    if (index == 1)
    {
      insert_first(list, item);
    } else {
      int i;
      for (i = 1; i < index; i++)
      {
        prev = curr;
        curr = curr->next;
      }

      if (curr != NULL)
      {
        if ((temp = create_linked_node(item)) == NULL)
        {
          return;
        }
        temp->item = item;

        list->length++;

        prev->next = temp;
        temp->next = curr;
      }
    }
  }
}

void reverse_linked_list(linked_list_t *list)
{
  linked_node_t *reversed;
  linked_node_t *current = list->head;
  linked_node_t *temp = NULL;

  while (current != NULL)
  {
    temp = current;
    current = current->next;
    temp->next = reversed;
    reversed = temp;
  }

  list->head = reversed;
}

void display_list(linked_list_t *list)
{
  linked_node_t *current = list->head;
  if (list->head == NULL)
  {
    return;
  } else {
    while (current != NULL)
    {
      object *o = (object *)current->item;
      printf(": %d\n", o->val);
      current = current->next;
    }

  }
}