#include "../ccollections/linked_list/linked_list.h"
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

void test_can_add_object_to_front(void)
{
  int *val1 = GC_MALLOC(sizeof(int));
  val1 = (int *)500;

  cc_list_add_front(list, val1);

  int *val2 = GC_MALLOC(sizeof(int));
  val2 = (int *)200;

  cc_list_add_front(list, val2);

  TEST_ASSERT_EQUAL(cc_list_length(list), 2);
  TEST_ASSERT_EQUAL(cc_list_get_front(list), val2);
  TEST_ASSERT_EQUAL(cc_list_get_end(list), val1);
}

void test_can_add_object_to_end(void)
{
  int *val1 = GC_MALLOC(sizeof(int));
  val1 = (int *)500;

  cc_list_add_end(list, val1);

  int *val2 = GC_MALLOC(sizeof(int));
  val2 = (int *)200;

  cc_list_add_end(list, val2);

  TEST_ASSERT_EQUAL(cc_list_length(list), 2);
  TEST_ASSERT_EQUAL(cc_list_get_end(list), val2);
  TEST_ASSERT_EQUAL(cc_list_get_front(list), val1);
}

void test_can_clear_list(void)
{
  int *val1 = GC_MALLOC(sizeof(int));
  val1 = (int *)500;

  cc_list_add_front(list, val1);
  cc_list_clear(list);

  TEST_ASSERT_EQUAL(cc_list_length(list), 0);
  TEST_ASSERT_EQUAL(cc_list_get_front(list), NULL);
}