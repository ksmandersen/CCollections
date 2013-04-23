#ifndef CC_SORTED_ARRAY_LIST_H
#define CC_SORTED_ARRAY_LIST_H

#include "../shared/cc_private.h"
#include "../shared/cc_object.h"
#include "../shared/cc_enumerator.h"

extern const char * const cc_sorted_array_list_type;

struct cc_sorted_array_list_struct;
typedef struct cc_sorted_array_list_struct cc_sorted_array_list;

cc_sorted_array_list *cc_sorted_array_list_new();
void cc_sorted_array_list_add(cc_sorted_array_list *list, cc_object *obj);

/*! \brief Get the length of the list
 * \return The length of the list */
int cc_sorted_array_list_length(cc_sorted_array_list *list);

/*! \brief Get a node in a linked list
 * \param list the linked list
 * \param index the index of the node to get */
cc_object *cc_sorted_array_list_get(cc_sorted_array_list *list, int index);

/*! \brief Get the first node in a linked list
 * \param list the linked list */
cc_object *cc_sorted_array_list_get_first(cc_sorted_array_list *list);

/*! \brief Get the last node in a linked list
 * \param list the linked list */
cc_object *cc_sorted_array_list_get_last(cc_sorted_array_list *list);

cc_enumerator *cc_sorted_array_list_get_enumerator(cc_sorted_array_list *list);

// cc_object *cc_sorted_array_list_to_object(cc_set *set);
// cc_sorted_array_list *cc_sorted_array_list_from_object(cc_object *obj);

#endif
