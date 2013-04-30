#include "../ccollections/shared/cc.h"
#include "../lib/unity/src/unity.h"

#define GC_DEBUG
#include "gc/gc.h"

void setUp(void)
{
  GC_INIT();
  cc_init();
}

void tearDown(void) {}

void populate_list(cc_linked_list *l, int count)
{
  int i;
  for(i = 1; i <= count; i++) {
    cc_object *v = cc_object_with_int(i);
    cc_linked_list_add_last(l, v);
  }
}

void print_list(cc_linked_list *list) {
  cc_enumerator *e = cc_linked_list_get_enumerator(list);
  while(cc_enumerator_move_next(e)) {
    cc_object *obj = cc_enumerator_current(e);
    printf("%i, ", cc_object_int_value(obj));
  }

  printf("\n");
}

void test_can_create_linked_list(void) {
  cc_linked_list *a_list = cc_linked_list_new();

  TEST_ASSERT_NOT_EQUAL(NULL, a_list);
  TEST_ASSERT_EQUAL(0, cc_linked_list_length(a_list));
}

void test_elements_in_list(cc_linked_list *list) {
  int i = 1;
  cc_enumerator *e = cc_linked_list_get_enumerator(list);
  while(cc_enumerator_move_next(e)) {
    cc_object *obj = cc_enumerator_current(e);
    TEST_ASSERT_EQUAL(true, cc_object_is_equal(obj, cc_object_with_int(i)));
    i++;
  }
}

// Adding

void test_can_add_objects_to_end_of_list(void) {
  cc_linked_list *a_list = cc_linked_list_new();

  cc_object *ins1 = cc_object_with_int(1);
  cc_object *ins2 = cc_object_with_int(2);
  cc_object *ins3 = cc_object_with_int(3);

  cc_linked_list_add_last(a_list, ins1);
  TEST_ASSERT_EQUAL(1, cc_object_int_value(cc_linked_list_get_last(a_list)));

  cc_linked_list_add_last(a_list, ins2);
  TEST_ASSERT_EQUAL(2, cc_object_int_value(cc_linked_list_get_last(a_list)));

  cc_linked_list_add_last(a_list, ins3);
  TEST_ASSERT_EQUAL(3, cc_object_int_value(cc_linked_list_get_last(a_list)));

  TEST_ASSERT_EQUAL(1, cc_object_int_value(cc_linked_list_get(a_list, 0)));
  TEST_ASSERT_EQUAL(2, cc_object_int_value(cc_linked_list_get(a_list, 1)));
  TEST_ASSERT_EQUAL(3, cc_object_int_value(cc_linked_list_get(a_list, 2)));
  TEST_ASSERT_EQUAL(3, cc_linked_list_length(a_list));
}

void test_can_add_objects_to_list_with_index(void) {
  cc_linked_list *a_list = cc_linked_list_new();

  populate_list(a_list, 128);

  cc_object *ins = cc_object_with_int(7283);
  cc_linked_list_add(a_list, 49, ins);

  TEST_ASSERT_EQUAL(7283, cc_object_int_value(cc_linked_list_get(a_list, 49)));
  TEST_ASSERT_EQUAL(49, cc_object_int_value(cc_linked_list_get(a_list, 48)));
  TEST_ASSERT_EQUAL(50, cc_object_int_value(cc_linked_list_get(a_list, 50)));
  TEST_ASSERT_EQUAL(129, cc_linked_list_length(a_list));
}

void test_can_add_objects_to_front_of_list(void) {
  cc_linked_list *a_list = cc_linked_list_new();

  cc_object *ins1 = cc_object_with_int(1);
  cc_object *ins2 = cc_object_with_int(2);
  cc_object *ins3 = cc_object_with_int(3);

  cc_linked_list_add_first(a_list, ins1);
  TEST_ASSERT_EQUAL(1, cc_object_int_value(cc_linked_list_get_first(a_list)));

  cc_linked_list_add_first(a_list, ins2);
  TEST_ASSERT_EQUAL(2, cc_object_int_value(cc_linked_list_get_first(a_list)));

  cc_linked_list_add_first(a_list, ins3);
  TEST_ASSERT_EQUAL(3, cc_object_int_value(cc_linked_list_get_first(a_list)));

  TEST_ASSERT_EQUAL(3, cc_object_int_value(cc_linked_list_get(a_list, 0)));
  TEST_ASSERT_EQUAL(2, cc_object_int_value(cc_linked_list_get(a_list, 1)));
  TEST_ASSERT_EQUAL(1, cc_object_int_value(cc_linked_list_get(a_list, 2)));
  TEST_ASSERT_EQUAL(3, cc_linked_list_length(a_list));
}

void test_can_add_and_get_identical_objects(void)
{
  cc_linked_list *a_list = cc_linked_list_new();
  populate_list(a_list, 30);

  cc_object *obj = cc_object_with_int(1);
  cc_linked_list_add_last(a_list, obj);

  TEST_ASSERT_EQUAL(true, cc_object_is_equal(obj, cc_linked_list_get_last(a_list)));
  TEST_ASSERT_EQUAL(true, cc_object_is_equal(obj, cc_linked_list_get_first(a_list)));
}

void test_can_add_and_get_many_objects(void) {
  cc_linked_list *a_list = cc_linked_list_new();
  populate_list(a_list, 10000);

  for (int i = 0; i < 2500; ++i) {
    cc_linked_list_remove_last(a_list);
  }

  populate_list(a_list, 2500);

  TEST_ASSERT_EQUAL(10000, cc_linked_list_length(a_list));

  cc_enumerator *e = cc_linked_list_get_enumerator(a_list);
  while(cc_enumerator_move_next(e)) {
    TEST_ASSERT_NOT_EQUAL(NULL, cc_enumerator_current(e));
  }
}

void test_can_create_linked_list_from_array_list(void) {
  cc_array_list *a_list = cc_array_list_new();
  int i;
  for (i = 1; i < 512; i++) {
    cc_array_list_add_last(a_list, cc_object_with_int(i));
  }

  cc_enumerator *e = cc_array_list_get_enumerator(a_list);
  cc_linked_list *b_list = cc_linked_list_new_with_enumerator(e);

  TEST_ASSERT_EQUAL(cc_array_list_length(a_list), cc_linked_list_length(b_list));
  e = cc_array_list_get_enumerator(a_list);
  while (cc_enumerator_move_next(e)) {
    cc_object *obj = cc_enumerator_current(e);
    TEST_ASSERT_EQUAL(true, cc_linked_list_contains(b_list, obj));
  }
}

// Getting

void test_can_get_objects_from_list_with_index(void) {
  cc_linked_list *a_list = cc_linked_list_new();

  populate_list(a_list, 3);

  TEST_ASSERT_EQUAL(1, cc_object_int_value(cc_linked_list_get(a_list, 0)));
  TEST_ASSERT_EQUAL(2, cc_object_int_value(cc_linked_list_get(a_list, 1)));
  TEST_ASSERT_EQUAL(3, cc_object_int_value(cc_linked_list_get(a_list, 2)));
}

void test_can_get_elements_from_start_of_list(void) {
  cc_linked_list *a_list = cc_linked_list_new();

  populate_list(a_list, 3);

  TEST_ASSERT_EQUAL(1, cc_object_int_value(cc_linked_list_get_first(a_list)));
}

void test_can_get_elements_from_end_of_list(void) {
  cc_linked_list *a_list = cc_linked_list_new();

  populate_list(a_list, 3);

  TEST_ASSERT_EQUAL(3, cc_object_int_value(cc_linked_list_get_last(a_list)));
}

void test_getting_object_from_list_empty_list_returns_null(void) {
  cc_linked_list *a_list = cc_linked_list_new();

  TEST_ASSERT_EQUAL(NULL, cc_linked_list_get(a_list, 12));
  TEST_ASSERT_EQUAL(NULL, cc_linked_list_get_first(a_list));
  TEST_ASSERT_EQUAL(NULL, cc_linked_list_get_last(a_list));
}

// Removing

void test_can_remove_object_from_list_with_index(void) {
  cc_linked_list *a_list = cc_linked_list_new();

  populate_list(a_list, 100);

  cc_linked_list_remove(a_list, 67);

  TEST_ASSERT_EQUAL(67, cc_object_int_value(cc_linked_list_get(a_list, 66)));
  TEST_ASSERT_EQUAL(69, cc_object_int_value(cc_linked_list_get(a_list, 67)));
  TEST_ASSERT_EQUAL(99, cc_linked_list_length(a_list));
}

void test_can_remove_object_from_front_of_list(void) {
  cc_linked_list *a_list = cc_linked_list_new();

  populate_list(a_list, 100);

  cc_linked_list_remove_first(a_list);

  TEST_ASSERT_EQUAL(2, cc_object_int_value(cc_linked_list_get_first(a_list)));
  TEST_ASSERT_EQUAL(99, cc_linked_list_length(a_list));
}

void test_can_remove_object_from_end_of_list(void) {
  cc_linked_list *a_list = cc_linked_list_new();

  populate_list(a_list, 100);

  cc_linked_list_remove_last(a_list);

  TEST_ASSERT_EQUAL(99, cc_object_int_value(cc_linked_list_get_last(a_list)));
  TEST_ASSERT_EQUAL(99, cc_linked_list_length(a_list));
}

void test_removing_non_existing_index_from_list_does_nothing(void) {
  cc_linked_list *a_list = cc_linked_list_new();

  populate_list(a_list, 100);

  cc_linked_list_remove(a_list, 131);

  TEST_ASSERT_EQUAL(100, cc_linked_list_length(a_list));
  test_elements_in_list(a_list);
}

// Merging

void test_can_merge_lists_together(void)
{
  cc_linked_list *list1 = cc_linked_list_new();

  cc_object *val1 = cc_object_with_int(100);
  cc_object *val2 = cc_object_with_int(200);
  cc_object *val3 = cc_object_with_int(300);
  
  cc_linked_list_add_last(list1, val1);
  cc_linked_list_add_last(list1, val2);
  cc_linked_list_add_last(list1, val3);

  cc_linked_list *list2 = cc_linked_list_new();

  cc_object *val4 = cc_object_with_int(400);
  cc_object *val5 = cc_object_with_int(500);
  cc_object *val6 = cc_object_with_int(600);
  
  cc_linked_list_add_last(list2, val4);
  cc_linked_list_add_last(list2, val5);
  cc_linked_list_add_last(list2, val6);

  cc_linked_list_merge(list1, list2);

  TEST_ASSERT_EQUAL(6, cc_linked_list_length(list1));

  cc_object *ret1 = cc_linked_list_get(list1, 0);
  cc_object *ret2 = cc_linked_list_get(list1, 1);
  cc_object *ret3 = cc_linked_list_get(list1, 2);
  cc_object *ret4 = cc_linked_list_get(list1, 3);
  cc_object *ret5 = cc_linked_list_get(list1, 4);
  cc_object *ret6 = cc_linked_list_get(list1, 5);

  TEST_ASSERT_EQUAL(true, cc_object_is_equal(ret1, val1));
  TEST_ASSERT_EQUAL(true, cc_object_is_equal(ret2, val2));
  TEST_ASSERT_EQUAL(true, cc_object_is_equal(ret3, val3));
  TEST_ASSERT_EQUAL(true, cc_object_is_equal(ret4, val4));
  TEST_ASSERT_EQUAL(true, cc_object_is_equal(ret5, val5));
  TEST_ASSERT_EQUAL(true, cc_object_is_equal(ret6, val6));
}

void test_can_merge_empty_list_with_non_empty_list(void)
{
  cc_linked_list *a_list = cc_linked_list_new();
  cc_linked_list *b_list = cc_linked_list_new();

  populate_list(b_list, 10);
  cc_linked_list_merge(a_list, b_list);

  cc_object *a_obj = cc_linked_list_to_object(a_list);
  cc_object *b_obj = cc_linked_list_to_object(b_list);

  bool lists_equals = cc_object_is_equal(a_obj, b_obj);
  TEST_ASSERT_EQUAL(true, lists_equals);

  test_elements_in_list(a_list);
  TEST_ASSERT_EQUAL(10, cc_linked_list_length(a_list));
}

void test_can_merge_empty_lists(void) {
  cc_linked_list *a_list = cc_linked_list_new();
  cc_linked_list *b_list = cc_linked_list_new();

  cc_linked_list_merge(a_list, b_list);

  cc_object *a_obj = cc_linked_list_to_object(a_list);
  cc_object *b_obj = cc_linked_list_to_object(b_list);

  bool lists_equals = cc_object_is_equal(a_obj, b_obj);
  TEST_ASSERT_EQUAL(true, lists_equals);

  TEST_ASSERT_EQUAL(cc_linked_list_length(a_list), cc_linked_list_length(b_list));
  TEST_ASSERT_EQUAL(0, cc_linked_list_length(a_list));
}

// Clearing

void test_can_clear_list(void)
{
  cc_linked_list *a_list = cc_linked_list_new();

  populate_list(a_list, 5);
  cc_linked_list_clear(a_list);

  TEST_ASSERT_EQUAL(0, cc_linked_list_length(a_list));
  TEST_ASSERT_EQUAL(NULL, cc_linked_list_get_first(a_list));
}

// Equality

void test_can_list_compare_equal(void)
{
  cc_linked_list *a_list = cc_linked_list_new();
  cc_linked_list *b_list = cc_linked_list_new();
  populate_list(a_list, 45);
  populate_list(b_list, 45);

  bool equal = cc_object_is_equal(cc_linked_list_to_object(a_list), cc_linked_list_to_object(b_list));

  TEST_ASSERT_EQUAL(true, equal);
}

void test_can_list_compare_non_equal(void)
{
  cc_linked_list *a_list = cc_linked_list_new();
  cc_linked_list *b_list = cc_linked_list_new();
  populate_list(a_list, 45);
  populate_list(b_list, 45);

  cc_object *obj = cc_object_with_int(5000);
  cc_linked_list_add_last(a_list, obj);

  bool equal = cc_object_is_equal(cc_linked_list_to_object(a_list), cc_linked_list_to_object(b_list));

  TEST_ASSERT_NOT_EQUAL(true, equal);
}

void test_can_empty_list_compare_equal(void) {
  cc_linked_list *a_list = cc_linked_list_new();
  cc_linked_list *b_list = cc_linked_list_new();

  bool equal = cc_object_is_equal(cc_linked_list_to_object(a_list), cc_linked_list_to_object(b_list));

  TEST_ASSERT_EQUAL(true, equal);
}

// Enumerating

void test_can_enumerate_list(void)
{
  cc_linked_list *a_list = cc_linked_list_new();
  populate_list(a_list, 100);

  int i = 1;
  cc_enumerator *e = cc_linked_list_get_enumerator(a_list);
  while (cc_enumerator_move_next(e)) {
    TEST_ASSERT_EQUAL(true, cc_object_is_equal(cc_enumerator_current(e), cc_object_with_int(i)));
    i++;
  }
}

// Containment

void test_can_find_contained_objects_in_list(void)
{
  cc_linked_list *a_list = cc_linked_list_new();
  populate_list(a_list, 120);  

  cc_object *obj = cc_object_with_int(100);

  TEST_ASSERT_EQUAL(true, cc_linked_list_contains(a_list, obj));
}

void test_cannot_find_object_in_list_without_object(void)
{
  cc_linked_list *a_list = cc_linked_list_new();
  populate_list(a_list, 99);

  cc_object *obj = cc_object_with_int(100);

  TEST_ASSERT_EQUAL(false, cc_linked_list_contains(a_list, obj));
}

void test_cannot_find_object_in_empty_list(void) {
  cc_linked_list *a_list = cc_linked_list_new();

  cc_object *obj = cc_object_with_int(100);

  TEST_ASSERT_EQUAL(false, cc_linked_list_contains(a_list, obj));
}

// Sorting

// void test_can_shuffle_array_with_objects(void) {
//   cc_linked_list *a_list = cc_linked_list_new();
//   populate_list(a_list, 400);

//   cc_linked_list_shuffle(a_list);
//   cc_linked_list_sort(a_list);

//   cc_enumerator *e = cc_linked_list_get_enumerator(a_list);
//   while (cc_enumerator_move_next(e)) {
//     cc_object *obj = cc_enumerator_current(e);
//     int i = cc_object_int_value(obj);
//   }
// }

// void test_can_sort_array_with_objects(void) {
//   cc_linked_list *a_list = cc_linked_list_new();
//   cc_linked_list_add_last(a_list, cc_object_with_string("q"));
//   cc_linked_list_add_last(a_list, cc_object_with_string("w"));
//   cc_linked_list_add_last(a_list, cc_object_with_string("e"));
//   cc_linked_list_add_last(a_list, cc_object_with_string("r"));
//   cc_linked_list_add_last(a_list, cc_object_with_string("t"));
//   cc_linked_list_add_last(a_list, cc_object_with_string("y"));
//   cc_linked_list_add_last(a_list, cc_object_with_string("u"));
//   cc_linked_list_add_last(a_list, cc_object_with_string("i"));
//   cc_linked_list_add_last(a_list, cc_object_with_string("o"));
//   cc_linked_list_add_last(a_list, cc_object_with_string("p"));

//   cc_linked_list_sort(a_list);

//   cc_enumerator *e = cc_linked_list_get_enumerator(a_list);
//   while (cc_enumerator_move_next(e)) {
//     cc_object *obj = cc_enumerator_current(e);
//     const char *s = cc_object_string_value(obj);
//   }
// }

// Convertion

void test_can_create_cc_object_from_list(void) {
  cc_linked_list *a_list = cc_linked_list_new();
  populate_list(a_list, 400);

  cc_object *object = cc_linked_list_to_object(a_list);
  TEST_ASSERT_NOT_EQUAL(NULL, object);
}

void test_can_create_list_from_cc_object(void) {
  cc_linked_list *a_list = cc_linked_list_new();
  int count = 5;
  populate_list(a_list, count);

  cc_object *object = cc_linked_list_to_object(a_list);

  cc_linked_list *b_list = cc_linked_list_from_object(object);

  TEST_ASSERT_NOT_EQUAL(NULL, b_list);
  TEST_ASSERT_EQUAL(count, cc_linked_list_length(b_list));

  test_elements_in_list(b_list);
}
