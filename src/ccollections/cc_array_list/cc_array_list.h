#ifndef CC_ARRAY_LIST_H
  #define CC_ARRAY_LIST_H

#include "../shared/cc_private.h"
#include "../shared/cc_object.h"
#include "../shared/cc_enumerator.h"

extern const char *const cc_array_list_type;

/*! \brief A linked list data structure */
struct cc_array_list_struct;
typedef struct cc_array_list_struct cc_array_list;

/*! \brief Create a linked list object
 * \return A new linked list object */
cc_array_list *cc_array_list_new();

/*! \brief Get the length of the list
 * \return The length of the list */
int cc_array_list_length(cc_array_list *list);

/*! \brief Get a node in a linked list
 * \param list the linked list
 * \param index the index of the node to get */
cc_object *cc_array_list_get(cc_array_list *list, int index);

/*! \brief Get the first node in a linked list
 * \param list the linked list */
cc_object *cc_array_list_get_first(cc_array_list *list);

/*! \brief Get the last node in a linked list
 * \param list the linked list */
cc_object *cc_array_list_get_last(cc_array_list *list);

/*! \brief Insert a value at a position in the linked list
 * \param list the linked list
 * \param index the index at which to insert the object
 * \param object the object to insert */
void cc_array_list_add(cc_array_list *list, int index, cc_object *object);

/*! \brief Insert a value as the first node in a linked list
 * \param list the linked list
 * \param object the value to insert */
void cc_array_list_add_first(cc_array_list *list, cc_object *object);

/*! \brief Insert a value as the last node in a linked list
 * \param list the linked list
 * \param object the value to insert */
void cc_array_list_add_last(cc_array_list *list, cc_object *object);

/*! \brief Remove a value at a position in the linked list
 * \param list the linked list
 * \param index the index at which to remove the object */
void cc_array_list_remove(cc_array_list *list, int index);

/*! \brief Remove the value from the front node in a linked list
 * \param list the linked list */
void cc_array_list_remove_first(cc_array_list *list);

/*! \brief Remove the value from the end node in a linked list
 * \param list the linked list */
void cc_array_list_remove_last(cc_array_list *list);

/*! \brief Removes all objects from a linked list
 * \param list the linked list to be emptied */
void cc_array_list_clear(cc_array_list *list);

/*! \brief Merges two lists together by adding all objects
 * from the first list to the second list.
 * \param a_list the first list
 * \param b_list the second list
 * \returns The lists merged together */
cc_array_list *cc_array_list_merge(cc_array_list *a_list, cc_array_list *b_list);

bool cc_array_list_contains(cc_array_list *list, cc_object *object);
cc_enumerator *cc_array_list_get_enumerator(cc_array_list *list);

cc_object *cc_array_list_to_object(cc_array_list *list);
cc_array_list *cc_array_list_from_object(cc_object *object);

#endif
