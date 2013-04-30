#include "../../lib/unity/src/unity.h"
#include <stdio.h>
#include <setjmp.h>

extern void setUp(void);
extern void tearDown(void);

extern void test_can_create_linked_list(void);

extern void test_can_add_objects_to_end_of_list(void);
extern void test_can_add_objects_to_list_with_index(void);
extern void test_can_add_objects_to_front_of_list(void);
extern void test_can_add_and_get_identical_objects(void);
extern void test_can_add_and_get_many_objects(void);
extern void test_can_create_linked_list_from_array_list(void);

extern void test_can_get_objects_from_list_with_index(void);
extern void test_can_get_elements_from_start_of_list(void);
extern void test_can_get_elements_from_end_of_list(void);
extern void test_getting_object_from_list_empty_list_returns_null(void);

extern void test_can_remove_object_from_list_with_index(void);
extern void test_can_remove_object_from_front_of_list(void);
extern void test_can_remove_object_from_end_of_list(void);
extern void test_removing_non_existing_index_from_list_does_nothing(void);

extern void test_can_merge_lists_together(void);
extern void test_can_merge_empty_list_with_non_empty_list(void);
extern void test_can_merge_empty_lists(void);

extern void test_can_clear_list(void);

extern void test_can_list_compare_equal(void);
extern void test_can_list_compare_non_equal(void);
extern void test_can_empty_list_compare_equal(void);

extern void test_can_enumerate_list(void);

extern void test_can_find_contained_objects_in_list(void);
extern void test_cannot_find_object_in_list_without_object(void);
extern void test_cannot_find_object_in_empty_list(void);

// extern void test_can_shuffle_array_with_objects(void);
// extern void test_can_sort_array_with_objects(void);

extern void test_can_create_cc_object_from_list(void);
extern void test_can_create_list_from_cc_object(void);

extern void test_can_create_list_with_ints_from_args(void);
extern void test_can_create_list_with_floats_from_args(void);
extern void test_can_create_list_with_strings_from_args(void);


static void runTest(UnityTestFunction test)
{
  if (TEST_PROTECT())
  {
    setUp();
    test();
  }

  if (TEST_PROTECT() && !TEST_IS_IGNORED)
  {
    tearDown();
  }
}

void resetTest()
{
  tearDown();
  setUp();
}

int main(void)
{
  Unity.TestFile = "test_linked_list.c";
  UnityBegin();

  RUN_TEST(test_can_create_linked_list, 1);

  RUN_TEST(test_can_add_objects_to_end_of_list, 1);
  RUN_TEST(test_can_add_objects_to_list_with_index, 1);
  RUN_TEST(test_can_add_objects_to_front_of_list, 1);
  RUN_TEST(test_can_add_and_get_identical_objects, 1);
  RUN_TEST(test_can_add_and_get_many_objects, 1);
  RUN_TEST(test_can_create_linked_list_from_array_list, 1);

  RUN_TEST(test_can_get_objects_from_list_with_index, 1);
  RUN_TEST(test_can_get_elements_from_start_of_list, 1);
  RUN_TEST(test_can_get_elements_from_end_of_list, 1);
  RUN_TEST(test_getting_object_from_list_empty_list_returns_null, 1);

  RUN_TEST(test_can_remove_object_from_list_with_index, 1);
  RUN_TEST(test_can_remove_object_from_front_of_list, 1);
  RUN_TEST(test_can_remove_object_from_end_of_list, 1);
  RUN_TEST(test_removing_non_existing_index_from_list_does_nothing, 1);

  RUN_TEST(test_can_merge_lists_together, 1);
  RUN_TEST(test_can_merge_empty_list_with_non_empty_list, 1);
  RUN_TEST(test_can_merge_empty_lists, 1);

  RUN_TEST(test_can_clear_list, 1);

  RUN_TEST(test_can_list_compare_equal, 1);
  RUN_TEST(test_can_list_compare_non_equal, 1);
  RUN_TEST(test_can_empty_list_compare_equal, 1);
  
  RUN_TEST(test_can_enumerate_list, 1);

  RUN_TEST(test_can_find_contained_objects_in_list, 1);
  RUN_TEST(test_cannot_find_object_in_list_without_object, 1);
  RUN_TEST(test_cannot_find_object_in_empty_list, 1);

  // RUN_TEST(test_can_shuffle_array_with_objects, 1);
  // RUN_TEST(test_can_sort_array_with_objects, 1);

  RUN_TEST(test_can_create_cc_object_from_list, 1);
  RUN_TEST(test_can_create_list_from_cc_object, 1);
  
  RUN_TEST(test_can_create_list_with_ints_from_args, 1);
  RUN_TEST(test_can_create_list_with_floats_from_args, 1);
  RUN_TEST(test_can_create_list_with_strings_from_args, 1);

  UnityEnd();
  return 0;
}
