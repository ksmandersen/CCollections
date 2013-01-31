#include <stdlib.h>
#include <stdio.h>

/*! \brief A value container
 * Used when inserting objects into the linked list */
struct object_struct {
  int val;
};

typedef struct object_struct object;

/*! \brief A value pointer */
typedef void * any_t;

/*! \brief A node in the linked list */
struct node_struct
{
  any_t *item;
  struct node_struct *next;
};

typedef struct node_struct linked_node_t;

/*! \brief A linked list data structure */
struct linked_list_struct
{
  struct node_struct *head;

  int length;
};

typedef struct linked_list_struct linked_list_t;

/*! \brief Create a linked list node object
 * \param item the value of the node
 * \return A new linked list node object */
linked_node_t *create_linked_node(any_t item);

/*! \brief Create a linked list object
 * \return A new linked list object */
linked_list_t *create_linked_list();

/*! \brief Removes all items from a linked list
 * \param list the linked list to be emptied */
void empty_linked_list(linked_list_t *list);
 
/*! \brief Destroys a linked list
 * Call this when the list is no longer used to free up memory
 * \param list the linked list to be destroyed */
void destroy_linked_list(linked_list_t *list);

/*! \brief Get the first node in a linked list
 * \param list the linked list */
any_t get_first(linked_list_t *list);

/*! \brief Get the last node in a linked list
 * \param list the linked list */
any_t get_last(linked_list_t *list);

/*! \brief Get a node in a linked list
 * \param list the linked list
 * \param index the index of the node to get */
any_t get(linked_list_t *list, int index);

/*! \brief Insert a value as the first node in a linked list
 * \param list the linked list
 * \param item the value to insert */
void insert_first(linked_list_t *list, any_t item);

/*! \brief Insert a value as the last node in a linked list
 * \param list the linked list
 * \param item the value to insert */
void insert_last(linked_list_t *list, any_t item);

/*! \brief Insert a value at a position in the linked list
 * \param list the linked list
 * \param index the index at which to insert the object
 * \param item the item to insert */
void insert_at(linked_list_t *list, int index, any_t *item);

/*! \brief Reverses the nodes in a linked list
 * \param list the linked list */
void reverse_linked_list(linked_list_t *list);

/*! \brief Prints the nodes in a linked list to stdout
 * \param list the linked list */
void display_list(linked_list_t *list);
