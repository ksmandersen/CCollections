#include "../../lib/unity/src/unity.h"
#include <stdio.h>
#include <setjmp.h>

extern void setUp(void);
extern void tearDown(void);

extern void test_can_create_queue(void);
extern void test_can_add_objects_to_queue(void);
extern void test_can_dequeue_objects_from_queue(void);
extern void test_can_peek_at_queue(void);
extern void test_can_clear_queue(void);
extern void test_queue_contains_object(void);

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

  RUN_TEST(test_can_create_queue, 1);
  RUN_TEST(test_can_add_objects_to_queue, 1);
  RUN_TEST(test_can_dequeue_objects_from_queue, 1);
  RUN_TEST(test_can_peek_at_queue, 1);
  RUN_TEST(test_can_clear_queue, 1);
  RUN_TEST(test_queue_contains_object, 1);

  UnityEnd();
  return 0;
}
