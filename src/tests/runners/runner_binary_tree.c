#include "../../lib/unity/src/unity.h"
#include <stdio.h>
#include <setjmp.h>

extern void setUp(void);
extern void tearDown(void);

extern void test_can_create_binary_tree(void);
extern void test_can_create_binary_tree_with_object(void);
extern void test_can_add_branches(void);
extern void test_can_remove_branch(void);
extern void test_can_enumerate_depth_first(void);
extern void test_can_enumerate_breadth_first(void);

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

  RUN_TEST(test_can_create_binary_tree, 1);
  RUN_TEST(test_can_create_binary_tree_with_object, 2);
  RUN_TEST(test_can_add_branches, 3);
  RUN_TEST(test_can_remove_branch, 4);
  RUN_TEST(test_can_enumerate_depth_first, 5);
  RUN_TEST(test_can_enumerate_breadth_first, 6);

  UnityEnd();
  return 0;
}