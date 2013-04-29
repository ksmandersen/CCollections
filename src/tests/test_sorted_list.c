#include "../ccollections/shared/cc.h"
#include "../lib/unity/src/unity.h"

#define GC_DEBUG
#include "gc/gc.h"

void setUp(void)
{
  GC_INIT();
  cc_init();
}

void tearDown(void)
{
}

void test_can_create_linked_list(void)
{
  cc_sorted_list *list = cc_sorted_list_new();
  TEST_ASSERT_NOT_EQUAL(NULL, list);
}

void test_can_add_objects(void)
{
  cc_sorted_list *list = cc_sorted_list_new();

  cc_object *val1 = cc_object_with_int(100);
  cc_object *val2 = cc_object_with_int(200);

  cc_sorted_list_add(list, val1);
  cc_sorted_list_add(list, val2);

  TEST_ASSERT_EQUAL(2, cc_sorted_list_length(list));

  TEST_ASSERT_EQUAL(cc_object_is_equal(cc_sorted_list_get_first(list), val1), true);
  TEST_ASSERT_EQUAL(cc_object_is_equal(cc_sorted_list_get_last(list), val2), true);
}

void test_will_sort_inserted_objects(void)
{
  cc_sorted_list *list = cc_sorted_list_new();
  
  cc_object *val1 = cc_object_with_int(100);
  cc_object *val2 = cc_object_with_int(200);

  cc_sorted_list_add(list, val2);
  cc_sorted_list_add(list, val1);

  TEST_ASSERT_EQUAL(2, cc_sorted_list_length(list));

  TEST_ASSERT_EQUAL(cc_object_is_equal(cc_sorted_list_get_first(list), val1), true);
  TEST_ASSERT_EQUAL(cc_object_is_equal(cc_sorted_list_get_last(list), val2), true);
}

void test_contains_will_return_true_for_contained_objects(void) {
  cc_sorted_list *list = cc_sorted_list_new();
  
  cc_object *val1 = cc_object_with_int(100);
  cc_object *val2 = cc_object_with_int(200);

  cc_sorted_list_add(list, val2);
  cc_sorted_list_add(list, val1);

  TEST_ASSERT_EQUAL(true, cc_sorted_list_contains(list, val2));
}

void test_contains_will_return_false_for_non_contained_objects(void) {
  cc_sorted_list *list = cc_sorted_list_new();
  
  cc_object *val1 = cc_object_with_int(100);
  cc_object *val2 = cc_object_with_int(200);

  // cc_sorted_list_add(list, val2);
  cc_sorted_list_add(list, val1);

  TEST_ASSERT_EQUAL(false, cc_sorted_list_contains(list, val2));
}

void test_can_clear_list(void)
{
  cc_sorted_list *list = cc_sorted_list_new();
  cc_object *val1 = cc_object_with_int(100);

  cc_sorted_list_add(list, val1);
  cc_sorted_list_clear(list);

  TEST_ASSERT_EQUAL(cc_sorted_list_length(list), 0);
  TEST_ASSERT_EQUAL(cc_sorted_list_get_first(list), NULL);
}

void test_can_merge_lists(void)
{
  cc_sorted_list *list = cc_sorted_list_new();
  
  cc_object *val1 = cc_object_with_int(100);
  cc_object *val2 = cc_object_with_int(200);
  cc_object *val3 = cc_object_with_int(300);

  cc_sorted_list_add(list, val1);
  cc_sorted_list_add(list, val2);
  cc_sorted_list_add(list, val3);

  cc_sorted_list *list2 = cc_sorted_list_new();

  cc_object *val4 = cc_object_with_int(400);
  cc_object *val5 = cc_object_with_int(500);
  cc_object *val6 = cc_object_with_int(600);

  cc_sorted_list_add(list2, val4);
  cc_sorted_list_add(list2, val5);
  cc_sorted_list_add(list2, val6);

  cc_sorted_list_merge(list, list2);

  TEST_ASSERT_EQUAL(cc_sorted_list_length(list), 6);
  TEST_ASSERT_EQUAL(cc_object_is_equal(cc_sorted_list_get_first(list), val1), true);
  TEST_ASSERT_EQUAL(cc_object_is_equal(cc_sorted_list_get_last(list2), val6), true);
}