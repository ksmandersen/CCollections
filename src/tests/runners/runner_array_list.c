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

  UnityEnd();
  return 0;
}