#include "../../lib/unity/src/unity.h"
#include <stdio.h>
#include <setjmp.h>

extern void setUp(void);
extern void tearDown(void);

extern void test_can_create_enumerator(void);
extern void test_enumerator_can_enumerate(void);
extern void test_enumerator_can_filter(void);
extern void test_enumerator_can_sort(void);
extern void test_enumerator_can_enumerate(void);
extern void test_enumerator_can_map(void);
extern void test_enumerator_can_stack_enumerators(void);
extern void test_can_convert_enumerator_to_list(void);

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
  Unity.TestFile = "test_object.c";
  UnityBegin();
  
  RUN_TEST(test_can_create_enumerator, 1);
  RUN_TEST(test_enumerator_can_enumerate, 2);
  RUN_TEST(test_enumerator_can_filter, 3);
  RUN_TEST(test_enumerator_can_sort, 4);
  RUN_TEST(test_enumerator_can_enumerate, 5);
  RUN_TEST(test_enumerator_can_map, 6);
  RUN_TEST(test_enumerator_can_stack_enumerators, 7);
  RUN_TEST(test_can_convert_enumerator_to_list, 8);

  UnityEnd();
  return 0;
}
