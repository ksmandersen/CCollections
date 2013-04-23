#ifndef CC_ARRAY_LIST_PRIVATE_H
  #define CC_ARRAY_LIST_PRIVATE_H

#include "cc_array_list.h"

void cc_array_list_quicksort(cc_array_list *list, int left, int right);
int cc_array_list_partition(cc_array_list *list, int left, int right);
void cc_array_list_swap(cc_array_list *list, int i, int j);

#endif
