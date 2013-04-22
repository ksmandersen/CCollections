#include "../../lib/unity/src/unity.h"
#include <stdio.h>
#include <setjmp.h>

extern void setUp(void);
extern void tearDown(void);

extern void test_can_create_set(void);
extern void test_can_add_object_to_set(void);
extern void test_can_enumerate_objects_in_set(void);
extern void test_can_find_contained_objects_in_set(void);
extern void test_cannot_find_uncontained_objects_in_set(void);
extern void test_can_remove_objects_from_set(void);
extern void test_set_only_contains_unique_objects(void);
extern void test_can_insert_many_objects(void);

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

  RUN_TEST(test_can_create_set, 1);
  RUN_TEST(test_can_add_object_to_set, 1);
  RUN_TEST(test_can_enumerate_objects_in_set, 1);
  RUN_TEST(test_can_find_contained_objects_in_set, 1);
  RUN_TEST(test_cannot_find_uncontained_objects_in_set, 1);
  RUN_TEST(test_can_remove_objects_from_set, 1);
  RUN_TEST(test_set_only_contains_unique_objects, 1);
  RUN_TEST(test_can_insert_many_objects, 1);

  UnityEnd();
  return 0;
}