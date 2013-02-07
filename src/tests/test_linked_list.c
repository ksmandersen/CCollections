#include "../ccollections/cc_list/cc_list.h"
#include "../lib/unity/src/unity.h"

#define GC_DEBUG
#include "gc/gc.h"

cc_list *list;

void setUp(void)
{
  list = cc_list_new();
}

void tearDown(void)
{
  list = NULL;
}

void test_can_create_linked_list(void)
{
  TEST_ASSERT_NOT_EQUAL(NULL, list);
}

void test_can_add_object_to_first(void)
{
  int *val1 = GC_MALLOC(sizeof(int));
  val1 = (int *)500;

  cc_list_add_first(list, val1);

  int *val2 = GC_MALLOC(sizeof(int));
  val2 = (int *)200;

  cc_list_add_first(list, val2);

  TEST_ASSERT_EQUAL(cc_list_length(list), 2);
  TEST_ASSERT_EQUAL(cc_list_get_first(list), val2);
  TEST_ASSERT_EQUAL(cc_list_get_last(list), val1);
}

void test_can_add_object_to_last(void)
{
  int *val1 = GC_MALLOC(sizeof(int));
  val1 = (int *)500;

  cc_list_add_last(list, val1);

  int *val2 = GC_MALLOC(sizeof(int));
  val2 = (int *)200;

  cc_list_add_last(list, val2);

  TEST_ASSERT_EQUAL(cc_list_length(list), 2);
  TEST_ASSERT_EQUAL(cc_list_get_last(list), val2);
  TEST_ASSERT_EQUAL(cc_list_get_first(list), val1);
}

void test_can_clear_list(void)
{
  int *val1 = GC_MALLOC(sizeof(int));
  val1 = (int *)500;

  cc_list_add_first(list, val1);
  cc_list_clear(list);

  TEST_ASSERT_EQUAL(cc_list_length(list), 0);
  TEST_ASSERT_EQUAL(cc_list_get_first(list), NULL);
}

void test_can_merge_lists(void)
{
  int *val1 = GC_MALLOC(sizeof(int));
  int *val2 = GC_MALLOC(sizeof(int));
  int *val3 = GC_MALLOC(sizeof(int));
  val1 = (int *)100;
  val2 = (int *)200;
  val3 = (int *)300;

  cc_list_add_last(list, val1);
  cc_list_add_last(list, val2);
  cc_list_add_last(list, val3);

  cc_list *list2 = cc_list_new();

  int *val4 = GC_MALLOC(sizeof(int));
  int *val5 = GC_MALLOC(sizeof(int));
  int *val6 = GC_MALLOC(sizeof(int));
  val4 = (int *)400;
  val5 = (int *)500;
  val6 = (int *)600;

  cc_list_add_last(list2, val4);
  cc_list_add_last(list2, val5);
  cc_list_add_last(list2, val6);

  cc_list_merge(list, list2);

  TEST_ASSERT_EQUAL(cc_list_length(list), 6);
  TEST_ASSERT_EQUAL(cc_list_get_first(list), val1);
  TEST_ASSERT_EQUAL(cc_list_get_last(list), val6);
}