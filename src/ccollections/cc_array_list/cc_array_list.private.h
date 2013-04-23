#ifndef CC_ARRAY_LIST_PRIVATE_H
  #define CC_ARRAY_LIST_PRIVATE_H

#include "cc_array_list.h"

extern bool cc_array_list_enumerator_move_next(cc_collection *c, cc_enumerator *e);
extern void cc_array_list_register_comparator();
extern void cc_array_list_expand_heap(cc_array_list *list);

struct cc_array_list_struct {
  cc_collection c;
  
  cc_object **heap;
  int count;
  int heap_size;
};

void cc_array_list_quicksort(cc_array_list *list, int left, int right);
int cc_array_list_partition(cc_array_list *list, int left, int right);
void cc_array_list_swap(cc_array_list *list, int i, int j);

#endif
