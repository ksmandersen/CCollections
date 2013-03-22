#include "../ccollections/shared/cc.h"
#include "../ccollections/cc_dictionary/cc_dictionary.h"
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

void cc_dictionary_populate(cc_dictionary *dict)
{
  int i;
  for(i = 1; i <= POPULATE_COUNT; i++) {
    cc_object *v = cc_object_with_int(i * 100);
    const char *key = "key_" + i;
    cc_dictionary_add(dict, key, v);
  }
}

void test_can_create_dictionary(void)
{
  cc_dictionary *a_dict = cc_dictionary_new();
  
  TEST_ASSERT_NOT_EQUAL(NULL, a_dict);
}

void test_can_add_object_to_dictionary(void)
{
  // cc_dictionary *a_dict = cc_dictionary_new();
  // cc_dictionary_populate(a_dict);
  // TEST_ASSERT_EQUAL(POPULATE_COUNT, cc_dictionary_count(a_dict));
}