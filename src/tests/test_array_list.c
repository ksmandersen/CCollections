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

void populateList(cc_array_list *l)
{
  int i;
  for(i = 1; i < 120; i++) {
    cc_object *v = cc_object_with_int(i * 100);
    cc_array_list_add_last(l, v);
  }
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

void test_can_merge_empty_list_with_non_empty_list(void)
{
  cc_array_list *a_list = cc_array_list_new();
  cc_array_list *b_list = cc_array_list_new();

  populateList(b_list);
  cc_array_list_merge(a_list, b_list);

  cc_object *a_obj = cc_array_list_to_object(a_list);
  cc_object *b_obj = cc_array_list_to_object(b_list);

  bool lists_equals = cc_object_is_equal(a_obj, b_obj);
  TEST_ASSERT_EQUAL(true, lists_equals);
}

void test_merge_non_empty_list_with_empty_list(void)
{
  cc_array_list *a_list = cc_array_list_new();
  cc_array_list *b_list = cc_array_list_new();
  cc_array_list *c_list = cc_array_list_new();

  populateList(a_list);
  populateList(c_list);
  cc_array_list_merge(a_list, b_list);

  TEST_ASSERT_EQUAL(0, cc_array_list_compare(cc_array_list_to_object(a_list), cc_array_list_to_object(c_list)));
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

void test_can_list_compare_equal(void)
{
  cc_array_list *a_list = cc_array_list_new();
  cc_array_list *b_list = cc_array_list_new();
  populateList(a_list);
  populateList(b_list);

  int compare = cc_array_list_compare(cc_array_list_to_object(a_list), cc_array_list_to_object(b_list));

  TEST_ASSERT_EQUAL(0, compare);
}

void test_can_list_compare_non_equal(void)
{
  cc_array_list *a_list = cc_array_list_new();
  cc_array_list *b_list = cc_array_list_new();
  populateList(a_list);
  populateList(b_list);

  cc_object *obj = cc_object_with_int(5000);
  cc_array_list_add_last(a_list, obj);

  int compare = cc_array_list_compare(cc_array_list_to_object(a_list), cc_array_list_to_object(b_list));

  TEST_ASSERT_NOT_EQUAL(0, compare);
}

void test_can_enumerate_list(void)
{
  cc_array_list *a_list = cc_array_list_new();
  populateList(a_list);

  int i = 1;
  cc_enumerator *e = cc_array_list_get_enumerator(a_list);
  while (cc_enumerator_move_next(e)) {
    TEST_ASSERT_EQUAL(true, cc_object_is_equal(cc_enumerator_current(e), cc_object_with_int(i * 100)));
    i++;
  }
}

void test_can_add_and_get_identical_objects(void)
{
  cc_array_list *a_list = cc_array_list_new();
  populateList(a_list);

  cc_object *obj = cc_object_with_int(100);
  cc_array_list_add_last(list, obj);

  TEST_ASSERT_EQUAL(true, cc_object_is_equal(obj, cc_array_list_get_last(list)));
  TEST_ASSERT_EQUAL(true, cc_object_is_equal(obj, cc_array_list_get_first(list)));
}

void test_can_find_contained_objects_in_list(void)
{
  cc_array_list *a_list = cc_array_list_new();
  populateList(a_list);  

  cc_object *obj = cc_object_with_int(100);

  TEST_ASSERT_EQUAL(true, cc_array_list_contains(a_list, obj));
}

void test_cannot_find_object_in_list_without_object(void)
{
  cc_array_list *a_list = cc_array_list_new();

  cc_object *obj = cc_object_with_int(100);

  TEST_ASSERT_EQUAL(false, cc_array_list_contains(a_list, obj));
}