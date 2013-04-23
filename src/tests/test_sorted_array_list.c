#include "../ccollections/shared/cc.h"
#include "../ccollections/cc_sorted_array_list/cc_sorted_array_list.h"
#include "../lib/unity/src/unity.h"

#define GC_DEBUG
#include "gc/gc.h"

void setUp(void)
{
  GC_INIT();
  cc_init();
}

void tearDown(void) {}

void populateList(cc_sorted_array_list *l)
{
  int i;
  for(i = 1; i < 120; i++) {
    cc_object *v = cc_object_with_int(i * 100);
    cc_sorted_array_list_add(l, v);
  }
}

void test_can_create_array_list(void)
{
  cc_sorted_array_list *list = cc_sorted_array_list_new();

  TEST_ASSERT_NOT_EQUAL(NULL, list);
}

void test_can_add_objects_to_list(void)
{
  cc_sorted_array_list *list = cc_sorted_array_list_new();

  cc_object *i1 = cc_object_with_int(100);
  cc_object *i2 = cc_object_with_int(200);
  cc_object *i3 = cc_object_with_int(300);
  cc_object *i4 = cc_object_with_int(400);
  cc_object *i5 = cc_object_with_int(500);
  cc_object *i6 = cc_object_with_int(600);

  cc_sorted_array_list_add(list, i2);
  cc_sorted_array_list_add(list, i1);
  cc_sorted_array_list_add(list, i5);
  cc_sorted_array_list_add(list, i4);
  cc_sorted_array_list_add(list, i6);
  cc_sorted_array_list_add(list, i3);

  cc_object *o1 = cc_sorted_array_list_get(list, 0);
  cc_object *o2 = cc_sorted_array_list_get(list, 1);
  cc_object *o3 = cc_sorted_array_list_get(list, 2);
  cc_object *o4 = cc_sorted_array_list_get(list, 3);
  cc_object *o5 = cc_sorted_array_list_get(list, 4);
  cc_object *o6 = cc_sorted_array_list_get(list, 5);

  TEST_ASSERT_EQUAL(true, cc_object_is_equal(i1, o1));
  TEST_ASSERT_EQUAL(true, cc_object_is_equal(i2, o2));
  TEST_ASSERT_EQUAL(true, cc_object_is_equal(i3, o3));
  TEST_ASSERT_EQUAL(true, cc_object_is_equal(i4, o4));
  TEST_ASSERT_EQUAL(true, cc_object_is_equal(i5, o5));
  TEST_ASSERT_EQUAL(true, cc_object_is_equal(i6, o6));

}
