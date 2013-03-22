#include "../ccollections/shared/cc.h"
#include "../ccollections/cc_array_list/cc_array_list.h"
#include "../lib/unity/src/unity.h"

#define GC_DEBUG
#include "gc/gc.h"

cc_array_list *list;

void setUp(void)
{
  GC_INIT();
  cc_init();
  list = cc_array_list_new();
}

void tearDown(void)
{
  list = NULL;
}

void test_can_create_array_list(void)
{
  TEST_ASSERT_NOT_EQUAL(NULL, list);
}

void test_can_add_objects_to_list(void)
{
  cc_object *val1 = cc_object_with_int(100);

  cc_array_list_add(list, 0, val1);

  cc_object *val2 = cc_object_with_int(200);

  cc_array_list_add_first(list, val2);

  cc_object *val3 = cc_object_with_int(300);

  cc_array_list_add_last(list, val3);

  TEST_ASSERT_EQUAL(cc_array_list_length(list), 3);

  cc_object *ret1 = cc_array_list_get_first(list);
  cc_object *ret2 = cc_array_list_get(list, 1);
  cc_object *ret3 = cc_array_list_get_last(list);

  TEST_ASSERT_EQUAL(cc_object_is_equal(ret1, val2), true);
  TEST_ASSERT_EQUAL(cc_object_is_equal(ret2, val1), true);
  TEST_ASSERT_EQUAL(cc_object_is_equal(ret3, val3), true);
}

void test_can_remove_objects_from_list(void)
{
  cc_object *val1 = cc_object_with_int(100);
  cc_object *val2 = cc_object_with_int(200);
  cc_object *val3 = cc_object_with_int(300);
  
  cc_array_list_add_last(list, val1);
  cc_array_list_add_last(list, val2);
  cc_array_list_add_last(list, val3);

  cc_array_list_remove_first(list);

  TEST_ASSERT_EQUAL(2, cc_array_list_length(list));

  cc_object *ret1 = cc_array_list_get_first(list);
  cc_object *ret2 = cc_array_list_get_last(list);

  TEST_ASSERT_EQUAL(true, cc_object_is_equal(ret1, val2));
  TEST_ASSERT_EQUAL(true, cc_object_is_equal(ret2, val3));

  cc_array_list_remove_last(list);

  TEST_ASSERT_EQUAL(1, cc_array_list_length(list));

  cc_object *ret3 = cc_array_list_get_first(list);

  TEST_ASSERT_EQUAL(true, cc_object_is_equal(ret1, val2));
}

void test_can_merge_lists_together(void)
{
  cc_object *val1 = cc_object_with_int(100);
  cc_object *val2 = cc_object_with_int(200);
  cc_object *val3 = cc_object_with_int(300);
  
  cc_array_list_add_last(list, val1);
  cc_array_list_add_last(list, val2);
  cc_array_list_add_last(list, val3);

  cc_array_list *list2 = cc_array_list_new();

  cc_object *val4 = cc_object_with_int(400);
  cc_object *val5 = cc_object_with_int(500);
  cc_object *val6 = cc_object_with_int(600);
  
  cc_array_list_add_last(list2, val4);
  cc_array_list_add_last(list2, val5);
  cc_array_list_add_last(list2, val6);

  cc_array_list *list3 = cc_array_list_merge(list, list2);

  TEST_ASSERT_EQUAL(6, cc_array_list_length(list3));

  cc_object *ret1 = cc_array_list_get(list3, 0);
  cc_object *ret2 = cc_array_list_get(list3, 1);
  cc_object *ret3 = cc_array_list_get(list3, 2);
  cc_object *ret4 = cc_array_list_get(list3, 3);
  cc_object *ret5 = cc_array_list_get(list3, 4);
  cc_object *ret6 = cc_array_list_get(list3, 5);

  TEST_ASSERT_EQUAL(true, cc_object_is_equal(ret1, val1));
  TEST_ASSERT_EQUAL(true, cc_object_is_equal(ret2, val2));
  TEST_ASSERT_EQUAL(true, cc_object_is_equal(ret3, val3));
  TEST_ASSERT_EQUAL(true, cc_object_is_equal(ret4, val4));
  TEST_ASSERT_EQUAL(true, cc_object_is_equal(ret5, val5));
  TEST_ASSERT_EQUAL(true, cc_object_is_equal(ret6, val6));
}

void test_can_clear_list(void)
{
  cc_object *val1 = cc_object_with_int(100);
  cc_object *val2 = cc_object_with_int(200);
  cc_object *val3 = cc_object_with_int(300);
  
  cc_array_list_add_last(list, val1);
  cc_array_list_add_last(list, val2);
  cc_array_list_add_last(list, val3);

  cc_array_list_clear(list);

  TEST_ASSERT_EQUAL(0, cc_array_list_length(list));
}
