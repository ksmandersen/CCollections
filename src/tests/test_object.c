#include "../ccollections/shared/cc.h"
#include "../lib/unity/src/unity.h"

#include <string.h>
#include <stdlib.h>

const char * const custom_data_type = "custom_data_type";

typedef struct {
	int i;
	float flt;
} custom_data;

cc_object *cc_object_with_custom_data(custom_data *dat) {
	return cc_object_with_data(dat, sizeof(custom_data), custom_data_type);
}

int custom_data_compare(cc_object *obj1, cc_object *obj2) {
	custom_data *dat1 = cc_object_data_value(obj1);
	custom_data *dat2 = cc_object_data_value(obj2);
	
	return (dat1->i == dat2->i && dat1->flt == dat2->flt? 0: -1);
}

cc_hash custom_data_get_hash(cc_object *obj) {
	custom_data *dat = cc_object_data_value(obj);
	char buffer[512] = {};
	sprintf(buffer, "%i%f", dat->i, dat->flt);
	return cc_object_hash(cc_object_with_string(buffer));
}

void test_can_create_string_object(void) {
	cc_object *str = cc_object_with_string("test string");
	const char *str_val = cc_object_string_value(str);
	TEST_ASSERT_EQUAL(strcmp(str_val, "test string"), 0);
}

void test_can_create_float_object(void) {
	cc_object *flt = cc_object_with_float(3.141592654);
	float flt_val = cc_object_float_value(flt);
	TEST_ASSERT_EQUAL(flt_val, 3.141592654);
}

void test_can_create_int_object(void) {
	cc_object *in = cc_object_with_int(42);
	int in_val = cc_object_int_value(in);
	TEST_ASSERT_EQUAL(in_val, 42);
}

void test_can_create_data_object(void) {
	size_t data_len = sizeof(int) * 10;
	int *data = GC_MALLOC(data_len);
	int i;
	for (i = 0; i < 10; i++) {
		data[i] = i * 100;
	}
	
	cc_object *dat = cc_object_with_data(data, data_len, "custom_data_id");
	int *dat_val = cc_object_data_value(dat);
	
	for (i = 0; i < 10; i++) {
		TEST_ASSERT_EQUAL(dat_val[i], data[i]);
	}
}

void test_can_create_string_object_from_stack(void) {
	const char *static_str = "test string";
	int len = strlen(static_str);
	
	char stack_str[len + 1];
	memcpy(stack_str, static_str, len + 1);
	
	cc_object *str = cc_object_with_string(stack_str);
	memset(stack_str, 0, len + 1);
	const char *str_val = cc_object_string_value(str);
	
	TEST_ASSERT_EQUAL(strcmp(str_val, static_str), 0);
}

void test_can_create_data_object_from_stack(void) {
	int data[10];
	int i;
	for (i = 0; i < 10; i++) {
		data[i] = i * 100;
	}
	
	cc_object *dat = cc_object_with_data(data, sizeof(data), "custom_data_id");
	memset(data, 0, sizeof(data));
	int *dat_val = cc_object_data_value(dat);
	
	for (i = 0; i < 10; i++) {
		TEST_ASSERT_EQUAL(dat_val[i], i * 100);
	}
}

void test_string_object_has_string_type(void) {
	cc_object *str = cc_object_with_string("test string");
	TEST_ASSERT_EQUAL(strcmp(cc_object_get_type(str), cc_object_type_string), 0);
}

void test_int_object_has_int_type(void) {
	cc_object *in = cc_object_with_int(42);
	TEST_ASSERT_EQUAL(strcmp(cc_object_get_type(in), cc_object_type_int), 0);
}

void test_float_object_has_float_type(void) {
	cc_object *flt = cc_object_with_float(3.141592654);
	TEST_ASSERT_EQUAL(strcmp(cc_object_get_type(flt), cc_object_type_float), 0);
}

void test_data_object_has_custom_type(void) {
	const char *str_data = "test_string";
	cc_object *dat = cc_object_with_data(str_data, strlen(str_data) + 1, "custom_type");
	TEST_ASSERT_EQUAL(strcmp(cc_object_get_type(dat), "custom_type"), 0);
}

void test_different_object_types_does_not_equal(void) {
	const char *static_str = "test string";
	cc_object *str = cc_object_with_string(static_str);
	cc_object *dat = cc_object_with_data(static_str, strlen(static_str) + 1, "custom_type");
	TEST_ASSERT_EQUAL(cc_object_is_equal(str, dat), false);
}

void test_same_string_objects_equals(void) {
	cc_object *str1 = cc_object_with_string("test string");
	cc_object *str2 = cc_object_with_string("test string");
	TEST_ASSERT_EQUAL(cc_object_is_equal(str1, str2), true);
}

void test_different_string_objects_does_not_equal(void) {
	cc_object *str1 = cc_object_with_string("test string 1");
	cc_object *str2 = cc_object_with_string("test string 2");
	TEST_ASSERT_EQUAL(cc_object_is_equal(str1, str2), false);
}

void test_same_int_objects_equals(void) {
	cc_object *in1 = cc_object_with_int(42);
	cc_object *in2 = cc_object_with_int(42);
	TEST_ASSERT_EQUAL(cc_object_is_equal(in1, in2), true);
}

void test_different_int_objects_does_not_equal(void) {
	cc_object *in1 = cc_object_with_int(42);
	cc_object *in2 = cc_object_with_int(1337);
	TEST_ASSERT_EQUAL(cc_object_is_equal(in1, in2), false);
}

void test_same_float_objects_equals(void) {
	cc_object *flt1 = cc_object_with_float(3.141592654);
	cc_object *flt2 = cc_object_with_float(3.141592654);
	TEST_ASSERT_EQUAL(cc_object_is_equal(flt1, flt2), true);
}

void test_different_float_objects_does_not_equal(void) {
	cc_object *flt1 = cc_object_with_float(3.141592654);
	cc_object *flt2 = cc_object_with_float(2.718281828);
	TEST_ASSERT_EQUAL(cc_object_is_equal(flt1, flt2), false);
}

void test_same_custom_data_equals(void) {
	cc_object_register_comparator_for_type(custom_data_type, custom_data_compare);
	
	custom_data prim_obj = (custom_data) { .i = 42, .flt = 3.141592654 };
	cc_object *obj1 = cc_object_with_custom_data(&prim_obj);
	cc_object *obj2 = cc_object_with_custom_data(&prim_obj);
	TEST_ASSERT_EQUAL(cc_object_is_equal(obj1, obj2), true);
}

void test_different_custom_data_does_not_equal(void) {
	cc_object_register_comparator_for_type(custom_data_type, custom_data_compare);
	
	custom_data prim_obj1 = (custom_data) { .i = 42, .flt = 3.141592654 };
	cc_object *obj1 = cc_object_with_custom_data(&prim_obj1);
	
	custom_data prim_obj2 = (custom_data) { .i = 1337, .flt = 2.718281828 };
	cc_object *obj2 = cc_object_with_custom_data(&prim_obj2);
	
	TEST_ASSERT_EQUAL(cc_object_is_equal(obj1, obj2), false);
}

void test_can_get_string_hash(void) {
	cc_hash hash = cc_object_hash(cc_object_with_string("test string"));
	TEST_ASSERT_NOT_EQUAL(hash, 0);
}

void test_can_get_custom_hash(void) {
	cc_object_register_hash_func_for_type(custom_data_type, custom_data_get_hash);
	
	custom_data prim_obj = (custom_data) { .i = 42, .flt = 3.141592654 };
	cc_object *obj = cc_object_with_custom_data(&prim_obj);
	cc_hash hash = cc_object_hash(obj);
	TEST_ASSERT_NOT_EQUAL(hash, 0);
}
