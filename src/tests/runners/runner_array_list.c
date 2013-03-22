#include "../../lib/unity/src/unity.h"
#include <stdio.h>
#include <setjmp.h>

extern void setUp(void);
extern void tearDown(void);

extern void test_can_create_array_list(void);
extern void test_can_add_objects_to_list(void);
extern void test_can_remove_objects_from_list(void);
extern void test_can_merge_lists_together(void);
extern void test_can_clear_list(void);
extern void test_can_list_compare_equal(void);
extern void test_can_list_compare_non_equal(void);
extern void test_can_enumerate_list(void);
extern void test_can_add_and_get_identical_objects(void);
extern void test_can_find_contained_objects_in_list(void);
extern void test_can_merge_empty_list_with_non_empty_list(void);
extern void test_merge_non_empty_list_with_empty_list(void);
extern void test_cannot_find_object_in_list_without_object(void);


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
  Unity.TestFile = "test_array_list.c";
  UnityBegin();

  RUN_TEST(test_can_create_array_list, 1);
  RUN_TEST(test_can_add_objects_to_list, 2);
  RUN_TEST(test_can_remove_objects_from_list, 3);
  RUN_TEST(test_can_merge_lists_together, 4);
  RUN_TEST(test_can_clear_list, 5);
  RUN_TEST(test_can_list_compare_equal, 6);
  RUN_TEST(test_can_list_compare_non_equal, 7);
  RUN_TEST(test_can_enumerate_list, 8);
  RUN_TEST(test_can_add_and_get_identical_objects, 9);
  RUN_TEST(test_can_find_contained_objects_in_list, 10);
  RUN_TEST(test_can_merge_empty_list_with_non_empty_list, 11);
  RUN_TEST(test_merge_non_empty_list_with_empty_list, 12);
  RUN_TEST(test_cannot_find_object_in_list_without_object, 13);

  UnityEnd();
  return 0;
}