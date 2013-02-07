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