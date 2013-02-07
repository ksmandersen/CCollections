#ifndef CC_LINKED_LIST_PRIVATE_H
#define CC_LINKED_LIST_PRIVATE_H

#include "cc_list.h"

/*! \brief A node in the linked list */
struct cc_list_node_struct
{
  cc_object *object;
  struct cc_list_node_struct *next;
  struct cc_list_node_struct *prev;
};
typedef struct cc_list_node_struct cc_list_node;

cc_list_node *cc_list_node_new(cc_object *object);

#endif
