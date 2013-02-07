#ifndef CC_LINKED_LIST_H
  #define CC_LINKED_LIST_H

/*! \brief A value pointer */
typedef void * any_t;

/*! \brief A node in the linked list */
struct cc_list_node_struct
{
  any_t *object;
  struct cc_list_node_struct *next;
  struct cc_list_node_struct *prev;
};

typedef struct cc_list_node_struct cc_list_node;

/*! \brief A linked list data structure */
struct cc_list_struct
{
  struct cc_list_node_struct *head;
  struct cc_list_node_struct *tail;

  int length;
};

typedef struct cc_list_struct cc_list;

/*! \brief Create a linked list object
 * \return A new linked list object */
cc_list *cc_list_new();

/*! \brief Get the length of the list
 * \return The length of the list */
int cc_list_length(cc_list *list);

/*! \brief Get a node in a linked list
 * \param list the linked list
 * \param index the index of the node to get */
any_t cc_list_get(cc_list *list, int index);

/*! \brief Get the first node in a linked list
 * \param list the linked list */
any_t cc_list_get_first(cc_list *list);

/*! \brief Get the last node in a linked list
 * \param list the linked list */
any_t cc_list_get_last(cc_list *list);

/*! \brief Insert a value at a position in the linked list
 * \param list the linked list
 * \param index the index at which to insert the object
 * \param object the object to insert */
void cc_list_add(cc_list *list, int index, any_t *object);

/*! \brief Insert a value as the first node in a linked list
 * \param list the linked list
 * \param object the value to insert */
void cc_list_add_first(cc_list *list, any_t object);

/*! \brief Insert a value as the last node in a linked list
 * \param list the linked list
 * \param object the value to insert */
void cc_list_add_last(cc_list *list, any_t object);

/*! \brief Remove a value at a position in the linked list
 * \param list the linked list
 * \param index the index at which to remove the object */
void cc_list_remove(cc_list *list, int index);

/*! \brief Remove the value from the front node in a linked list
 * \param list the linked list */
void cc_list_remove_first(cc_list *list);

/*! \brief Remove the value from the end node in a linked list
 * \param list the linked list */
void cc_list_remove_last(cc_list *list);

/*! \brief Removes all objects from a linked list
 * \param list the linked list to be emptied */
void cc_list_clear(cc_list *list);

#endif
