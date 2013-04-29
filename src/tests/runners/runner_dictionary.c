#include "../../lib/unity/src/unity.h"
#include <stdio.h>
#include <setjmp.h>

extern void setUp(void);
extern void tearDown(void);

extern void test_can_create_dictionary(void);
extern void test_can_add_object_to_dictionary(void);
extern void test_can_set_value_for_key_in_dictionary(void);
extern void test_can_change_value_for_key(void);
extern void test_can_find_key_in_dictionary(void);
extern void test_can_enumerate_keys_in_dictionary(void);
extern void test_can_insert_and_enumerate_many_objects(void);

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

  RUN_TEST(test_can_create_dictionary, 1);
  RUN_TEST(test_can_add_object_to_dictionary, 1);
  RUN_TEST(test_can_set_value_for_key_in_dictionary, 1);
  RUN_TEST(test_can_change_value_for_key, 1);
  RUN_TEST(test_can_find_key_in_dictionary, 1);
  RUN_TEST(test_can_enumerate_keys_in_dictionary, 1);
  RUN_TEST(test_can_insert_and_enumerate_many_objects, 1);

  UnityEnd();
  return 0;
}