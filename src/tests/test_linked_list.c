#include "../ccollections/shared/cc.h"
#include "../lib/unity/src/unity.h"

#define GC_DEBUG
#include "gc/gc.h"

cc_linked_list *list;

void setUp(void)
{
  GC_INIT();
  cc_init();
  list = cc_linked_list_new();
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
  cc_object *val1 = cc_object_with_int(100);

  cc_linked_list_add_first(list, val1);

  cc_object *val2 = cc_object_with_int(200);

  cc_linked_list_add_first(list, val2);

  TEST_ASSERT_EQUAL(cc_linked_list_length(list), 2);
  TEST_ASSERT_EQUAL(cc_object_is_equal(cc_linked_list_get_first(list), val2), true);
  TEST_ASSERT_EQUAL(cc_object_is_equal(cc_linked_list_get_last(list), val1), true);
}

void test_can_add_object_to_last(void)
{
  cc_object *val1 = cc_object_with_int(100);

  cc_linked_list_add_last(list, val1);

  cc_object *val2 = cc_object_with_int(200);

  cc_linked_list_add_last(list, val2);

  TEST_ASSERT_EQUAL(cc_linked_list_length(list), 2);
  TEST_ASSERT_EQUAL(cc_object_is_equal(cc_linked_list_get_last(list), val2), true);
  TEST_ASSERT_EQUAL(cc_object_is_equal(cc_linked_list_get_first(list), val1), true);
}

void test_can_clear_list(void)
{
  cc_object *val1 = cc_object_with_int(100);

  cc_linked_list_add_first(list, val1);
  cc_linked_list_clear(list);

  TEST_ASSERT_EQUAL(cc_linked_list_length(list), 0);
  TEST_ASSERT_EQUAL(cc_linked_list_get_first(list), NULL);
}

void test_can_merge_lists(void)
{
  cc_object *val1 = cc_object_with_int(100);
  cc_object *val2 = cc_object_with_int(200);
  cc_object *val3 = cc_object_with_int(300);

  cc_linked_list_add_last(list, val1);
  cc_linked_list_add_last(list, val2);
  cc_linked_list_add_last(list, val3);

  cc_linked_list *list2 = cc_linked_list_new();

  cc_object *val4 = cc_object_with_int(400);
  cc_object *val5 = cc_object_with_int(500);
  cc_object *val6 = cc_object_with_int(600);

  cc_linked_list_add_last(list2, val4);
  cc_linked_list_add_last(list2, val5);
  cc_linked_list_add_last(list2, val6);

  cc_linked_list_merge(list, list2);

  TEST_ASSERT_EQUAL(cc_linked_list_length(list), 6);
  TEST_ASSERT_EQUAL(cc_object_is_equal(cc_linked_list_get_first(list), val1), true);
  TEST_ASSERT_EQUAL(cc_object_is_equal(cc_linked_list_get_last(list2), val6), true);
}