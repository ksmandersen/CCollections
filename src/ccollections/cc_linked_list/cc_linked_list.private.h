#ifndef CC_LINKED_LIST_PRIVATE_H
#define CC_LINKED_LIST_PRIVATE_H

#include "cc_linked_list.h"

/*! \brief A node in the linked list */
struct cc_linked_list_node_struct
{
  cc_object *object;
  struct cc_linked_list_node_struct *next;
  struct cc_linked_list_node_struct *prev;
};
typedef struct cc_linked_list_node_struct cc_linked_list_node;

cc_linked_list_node *cc_linked_list_node_new(cc_object *object);

extern bool cc_linked_list_enumerator_move_next(cc_collection *c, cc_enumerator *e);
extern bool cc_linked_list_compare(cc_object *obj1, cc_object *obj2);
extern void cc_linked_list_register_comparator();

#endif
