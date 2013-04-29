#include "../../lib/unity/src/unity.h"
#include <stdio.h>
#include <setjmp.h>

extern void setUp(void);
extern void tearDown(void);

extern void test_can_create_stack(void);
extern void test_can_add_objects_to_stack(void);
extern void test_can_peek_at_objects_on_stack(void);
extern void test_can_pop_objects_from_stack(void);
extern void test_can_clear_stack(void);
extern void test_can_enumerate_stack(void);
extern void test_can_push_and_pop_many_objects(void);
extern void test_peek_on_empty_stack_returns_null(void);
extern void test_pop_on_empty_stack_returns_null(void);
extern void test_move_next_on_empty_stack_returns_null(void);
extern void test_size_on_empty_stack_is_zero(void);
extern void test_can_create_cc_object_from_stack(void);
extern void test_can_create_stack_from_cc_object(void);
extern void test_can_determine_if_stacks_are_equal(void);
extern void test_can_determine_if_stacks_are_unequal(void);
extern void test_can_determine_if_empty_stacks_are_equal(void);
extern void test_can_determine_stack_contains_object(void);
extern void test_can_determine_stack_does_not_contain_object(void);
extern void test_can_determine_empty_stack_does_not_contain_object(void);


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
  Unity.TestFile = "test_stack.c";
  UnityBegin();

  RUN_TEST(test_can_create_stack, 1);
  RUN_TEST(test_can_add_objects_to_stack, 1);
  RUN_TEST(test_can_peek_at_objects_on_stack, 1);
  RUN_TEST(test_can_pop_objects_from_stack, 1);
  RUN_TEST(test_can_clear_stack, 1);
  RUN_TEST(test_can_enumerate_stack, 1);
  RUN_TEST(test_can_push_and_pop_many_objects, 1);
  RUN_TEST(test_peek_on_empty_stack_returns_null, 1);
  RUN_TEST(test_pop_on_empty_stack_returns_null, 1);
  RUN_TEST(test_move_next_on_empty_stack_returns_null, 1);
  RUN_TEST(test_size_on_empty_stack_is_zero, 1);
  RUN_TEST(test_can_create_cc_object_from_stack, 1);
  RUN_TEST(test_can_create_stack_from_cc_object, 1);
  RUN_TEST(test_can_determine_if_stacks_are_equal, 1);
  RUN_TEST(test_can_determine_if_stacks_are_unequal, 1);
  RUN_TEST(test_can_determine_if_empty_stacks_are_equal, 1);
  RUN_TEST(test_can_determine_stack_contains_object, 1);
  RUN_TEST(test_can_determine_stack_does_not_contain_object, 1);
  RUN_TEST(test_can_determine_empty_stack_does_not_contain_object, 1);

  UnityEnd();
  return 0;
}