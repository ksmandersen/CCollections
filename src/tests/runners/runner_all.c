#include "../../lib/unity/src/unity.h"
#include <stdio.h>
#include <setjmp.h>

extern void setUp(void);
extern void tearDown(void);

extern void test_can_create_linked_list(void);
extern void test_can_add_objects_to_linked_list(void);

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
  RUN_TEST(test_can_add_objects_to_linked_list, 2);

  UnityEnd();
  return 0;
}