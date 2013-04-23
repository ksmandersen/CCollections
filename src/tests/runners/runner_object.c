#include "../../lib/unity/src/unity.h"
#include <stdio.h>
#include <setjmp.h>

extern void setUp(void);
extern void tearDown(void);

extern void test_can_create_string_object(void);
extern void test_can_create_float_object(void);
extern void test_can_create_int_object(void);
extern void test_can_create_data_object(void);
extern void test_can_create_string_object_from_stack(void);
extern void test_can_create_data_object_from_stack(void);
extern void test_string_object_has_string_type(void);
extern void test_int_object_has_int_type(void);
extern void test_float_object_has_float_type(void);
extern void test_data_object_has_custom_type(void);
extern void test_different_object_types_does_not_equal(void);
extern void test_same_string_objects_equals(void);
extern void test_different_string_objects_does_not_equal(void);
extern void test_same_int_objects_equals(void);
extern void test_different_int_objects_does_not_equal(void);
extern void test_same_float_objects_equals(void);
extern void test_different_float_objects_does_not_equal(void);
extern void test_same_custom_data_equals(void);
extern void test_different_custom_data_does_not_equal(void);
extern void test_can_get_string_hash(void);
extern void test_can_get_custom_hash(void);

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
  
  RUN_TEST(test_can_create_string_object, 1);
  RUN_TEST(test_can_create_float_object, 2);
  RUN_TEST(test_can_create_int_object, 3);
  RUN_TEST(test_can_create_data_object, 4);
  RUN_TEST(test_can_create_string_object_from_stack, 5);
  RUN_TEST(test_can_create_data_object_from_stack, 6);
  RUN_TEST(test_string_object_has_string_type, 7);
  RUN_TEST(test_int_object_has_int_type, 8);
  RUN_TEST(test_float_object_has_float_type, 9);
  RUN_TEST(test_data_object_has_custom_type, 10);
  RUN_TEST(test_different_object_types_does_not_equal, 11);
  RUN_TEST(test_same_string_objects_equals, 12);
  RUN_TEST(test_different_string_objects_does_not_equal, 13);
  RUN_TEST(test_same_int_objects_equals, 14);
  RUN_TEST(test_different_int_objects_does_not_equal, 15);
  RUN_TEST(test_same_float_objects_equals, 16);
  RUN_TEST(test_different_float_objects_does_not_equal, 17);
  RUN_TEST(test_same_custom_data_equals, 18);
  RUN_TEST(test_different_custom_data_does_not_equal, 19);
  RUN_TEST(test_can_get_string_hash, 20);
  RUN_TEST(test_can_get_custom_hash, 21);
  RUN_TEST(test_can_create_string_object, 22);

  UnityEnd();
  return 0;
}
