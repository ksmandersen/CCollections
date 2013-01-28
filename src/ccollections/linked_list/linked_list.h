#include <stdlib.h>
#include <stdio.h>

struct object_struct {
  int val;
};

typedef struct object_struct object;

typedef void * any_t;

struct node_struct
{
  any_t *item;
  struct node_struct *next;
};

typedef struct node_struct linked_node_t;

struct linked_list_struct
{
  struct node_struct *head;

  int length;
};

typedef struct linked_list_struct linked_list_t;

typedef int comperator_t(any_t, any_t);

linked_node_t *create_linked_node(any_t item);
linked_list_t *create_linked_list();

void empty_linked_list(linked_list_t *list);
void destroy_linked_list(linked_list_t *list);

any_t get_first(linked_list_t *list);
any_t get_last(linked_list_t *list);
any_t get(linked_list_t *list, int index);

void insert_first(linked_list_t *list, any_t item);
void insert_last(linked_list_t *list, any_t item);
void insert_at(linked_list_t *list, int index, any_t *item);

void reverse_linked_list(linked_list_t *list);

void display_list(linked_list_t *list);