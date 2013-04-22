#include "../ccollections/shared/cc.h"
#include "../lib/unity/src/unity.h"

#define GC_DEBUG
#include "gc/gc.h"

#define POPULATE_COUNT 120


void setUp(void)
{
  GC_INIT();
  cc_init();
}

void tearDown(void)
{

}

void cc_set_populate(cc_set *set)
{
  int i;
  for(i = 1; i <= POPULATE_COUNT; i++) {
    cc_object *v = cc_object_with_int(i * 100);
    cc_set_add(set, v);
  }
}

void test_can_create_set(void)
{
  cc_set *a_set = cc_set_new();
  
  TEST_ASSERT_NOT_EQUAL(NULL, a_set);
}

void test_can_add_object_to_set(void)
{
  cc_set *a_set = cc_set_new();
  cc_set_populate(a_set);
  TEST_ASSERT_EQUAL(POPULATE_COUNT, cc_set_count(a_set));
}

void test_can_enumerate_objects_in_set(void)
{
  cc_set *a_set = cc_set_new();
  cc_set_populate(a_set);

  int i = 1;
  cc_enumerator *e = cc_set_get_enumerator(a_set);
  while (cc_enumerator_move_next(e)) {
    cc_object *value = cc_object_with_int(i * 100);
    cc_object *current = cc_enumerator_current(e);

    TEST_ASSERT_EQUAL(true, cc_object_is_equal(value, current));
    i++;
  }
}

void test_can_find_contained_objects_in_set(void)
{
  cc_set *a_set = cc_set_new();
  cc_set_populate(a_set);

  cc_object *val = cc_object_with_int(800);
  bool contained = cc_set_contains(a_set, val);

  TEST_ASSERT_EQUAL(true, contained);
}

void test_cannot_find_uncontained_objects_in_set(void)
{
  cc_set *a_set = cc_set_new();
  cc_set_populate(a_set);

  cc_object *val = cc_object_with_int(-200);
  bool contained = cc_set_contains(a_set, val);

  TEST_ASSERT_EQUAL(false, contained); 
}

void test_can_remove_objects_from_set(void)
{
  cc_set *a_set = cc_set_new();
  cc_set_populate(a_set);

  cc_object *val = cc_object_with_int(800);
  bool contained = cc_set_contains(a_set, val);

  TEST_ASSERT_EQUAL(true, contained);

  cc_set_remove(a_set, val);
  contained = cc_set_contains(a_set, val);

  TEST_ASSERT_EQUAL(false, contained);
}

void test_set_only_contains_unique_objects(void)
{
  cc_set *a_set = cc_set_new();
  cc_set_populate(a_set);

  cc_object *val = cc_object_with_int(100);
  cc_set_add(a_set, val);

  int foundCount = 0;
  cc_enumerator *e = cc_set_get_enumerator(a_set);
  while (cc_enumerator_move_next(e)) {
    cc_object *current = cc_enumerator_current(e);
    int intValue = cc_object_int_value(current);
    if (intValue == 100) foundCount++;
  }

  TEST_ASSERT_EQUAL(1, foundCount);
}

void test_can_insert_many_objects(void)
{
  cc_set *a_set = cc_set_new();

  int i;
  for(i = 1; i <= 1000; i++) {
    cc_object *v = cc_object_with_int(i * 100);
    cc_set_add(a_set, v);
  }

}