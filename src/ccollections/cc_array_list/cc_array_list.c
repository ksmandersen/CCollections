#include "../shared/cc_private.h"
#include "cc_array_list.private.h"
#include "../shared/cc_enumerator_private.h"

#define ARRAY_LIST_DEFAULT_SIZE 256

extern const char *const cc_array_list_type = "cc_array_list_type";

struct cc_linked_list_struct
{
  cc_collection c;
  cc_object **elements;

  
  int count;
  int size;
};

bool cc_array_list_enumerator_move_next(cc_collection *c, cc_enumerator *e);
bool cc_array_list_compare(cc_object *obj1, cc_object *obj2);
void cc_array_list_register_comparator();

/*! \brief Create a linked list object
 * \return A new linked list object */
cc_array_list *cc_array_list_new()
{
  cc_array_list_register_comparator()
;
  cc_array_list *list;
  if ((list = GC_MALLOC(sizeof(cc_array_list))) == NULL)
    return NULL;

  list->c.cc_array_list_enumerator_move_next = cc_array_list_enumerator_move_next;
  list->size = ARRAY_LIST_DEFAULT_SIZE;
  list->count = 0;

  if (!(list->elements = GC_MALLOC(sizeof(cc_object), list->size))) {
    GC_FREE(list);
    return NULL;
  }

  return list;
}

/*! \brief Get the length of the list
 * \return The length of the list */
int cc_array_list_count(cc_array_list *list)
{
  if (list == NULL)
    return 0;

  return list->count;
}

void cc_array_list_add(cc_array_list *list, int index, cc_object *obj)
{
  if (index > list->size - 1)
    return;

  if (list->count > list->size - 1) {
    list->elements = GC_REALLOC(list->elements, list->size * 2);
  }

  list->elements[index] = obj;
}