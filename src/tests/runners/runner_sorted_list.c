#include "../../lib/unity/src/unity.h"
#include <stdio.h>
#include <setjmp.h>

extern void setUp(void);
extern void tearDown(void);

extern void test_can_create_linked_list(void);
extern void test_can_add_objects(void);
extern void test_will_sort_inserted_objects(void);
extern void test_can_clear_list(void);
extern void test_can_merge_lists(void);
extern void test_contains_will_return_true_for_contained_objects(void);
extern void test_contains_will_return_false_for_non_contained_objects(void);

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
  Unity.TestFile = "test_sorted_list.c";
  UnityBegin();

  RUN_TEST(test_can_create_linked_list, 1);
  RUN_TEST(test_can_add_objects, 2);
  RUN_TEST(test_will_sort_inserted_objects, 3);
  RUN_TEST(test_can_clear_list, 4);
  RUN_TEST(test_can_merge_lists, 5);
  RUN_TEST(test_contains_will_return_true_for_contained_objects, 5);
  RUN_TEST(test_contains_will_return_false_for_non_contained_objects, 5);

  UnityEnd();
  return 0;
}