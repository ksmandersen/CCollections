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
	char key[128];
	sprintf(key, "key_%i", i);
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
	cc_dictionary *a_dict = cc_dictionary_new();
	cc_dictionary_populate(a_dict);
	TEST_ASSERT_EQUAL(POPULATE_COUNT, cc_dictionary_count(a_dict));
}

void test_can_set_value_for_key_in_dictionary(void)
{
	cc_dictionary *a_dict = cc_dictionary_new();
	cc_object *value = cc_object_with_string("test_value");
	cc_dictionary_add(a_dict, "test_key", value);
	cc_object *out_value = cc_dictionary_get(a_dict, "test_key");
	TEST_ASSERT_NOT_EQUAL(NULL, out_value);
	TEST_ASSERT_EQUAL(0, strcmp(cc_object_string_value(value), cc_object_string_value(out_value)));
}

void test_can_change_value_for_key(void)
{
	cc_dictionary *a_dict = cc_dictionary_new();
	cc_object *value1 = cc_object_with_string("test_value_1");
	cc_object *value2 = cc_object_with_string("test_value_2");
	cc_dictionary_add(a_dict, "test_key", value1);
	cc_dictionary_add(a_dict, "test_key", value2);
	cc_object *out_value = cc_dictionary_get(a_dict, "test_key");
	TEST_ASSERT_NOT_EQUAL(NULL, out_value);
	TEST_ASSERT_EQUAL(0, strcmp(cc_object_string_value(value2), cc_object_string_value(out_value)));
}


