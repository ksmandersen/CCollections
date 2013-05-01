#include "../ccollections/shared/cc.h"
#include "../ccollections/shared/cc_enumerator_private.h"
#include "../lib/unity/src/unity.h"

#define GC_DEBUG
#include "gc/gc.h"

bool one_to_three(cc_enumerable *c, cc_enumerator *e) {
	int *data = (int *)e->data;
	if (*data == 3) return false;
	*data = *data + 1;
	e->current = cc_object_with_int(*data);
	return true;
}

bool one_to_ten(cc_enumerable *c, cc_enumerator *e) {
	int *data = (int *)e->data;
	if (*data == 10) return false;
	*data = *data + 1;
	e->current = cc_object_with_int(*data);
	return true;
}

bool odd_filter(cc_object *obj) {
	return (cc_object_int_value(obj) % 2 == 1);
}

cc_object *int_to_string_map(cc_object *obj) {
	char buffer[20];
	snprintf(buffer, sizeof(buffer), "%i", cc_object_int_value(obj));
	return cc_object_with_string(buffer);
}

cc_object *string_concat(cc_object *agg, cc_object *obj) {
	const char *str1 = cc_object_string_value(agg);
	const char *str2 = cc_object_string_value(obj);
	
	size_t size = strlen(str1) + strlen(str2) + 2;
	char buffer[size];
	snprintf(buffer, size, "%s %s", str1, str2);
	
	return cc_object_with_string(buffer);
}

void setUp(void)
{
  GC_INIT();
  cc_init();
}

void tearDown(void)
{
	
}

void test_can_create_enumerator(void)
{
	cc_enumerator *e = cc_enumerator_new(cc_enumerable_new(one_to_three));
	e->data = GC_MALLOC(sizeof(int));
	*((int *)e->data) = 0;
	
	TEST_ASSERT_NOT_EQUAL(e, NULL);
}

void test_enumerator_can_enumerate(void)
{
	cc_enumerator *e = cc_enumerator_new(cc_enumerable_new(one_to_three));
	e->data = GC_MALLOC(sizeof(int));
	*((int *)e->data) = 0;
	
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(e), true);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_enumerator_current(e)), 1);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(e), true);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_enumerator_current(e)), 2);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(e), true);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_enumerator_current(e)), 3);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(e), false);
}

void test_enumerator_can_filter(void)
{
	cc_enumerator *e = cc_enumerator_new(cc_enumerable_new(one_to_ten));
	e->data = GC_MALLOC(sizeof(int));
	*((int *)e->data) = 0;
	
	cc_enumerator *odd_numbers = cc_enumerator_filter(e, odd_filter);
	
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(odd_numbers), true);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_enumerator_current(odd_numbers)), 1);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(odd_numbers), true);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_enumerator_current(odd_numbers)), 3);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(odd_numbers), true);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_enumerator_current(odd_numbers)), 5);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(odd_numbers), true);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_enumerator_current(odd_numbers)), 7);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(odd_numbers), true);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_enumerator_current(odd_numbers)), 9);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(odd_numbers), false);
}

void test_enumerator_can_sort(void)
{
	cc_linked_list *list = cc_linked_list_new();
	cc_linked_list_add_last(list, cc_object_with_int(4));
	cc_linked_list_add_last(list, cc_object_with_int(2));
	cc_linked_list_add_last(list, cc_object_with_int(7));
	cc_linked_list_add_last(list, cc_object_with_int(9));
	cc_linked_list_add_last(list, cc_object_with_int(1));
	cc_linked_list_add_last(list, cc_object_with_int(3));
	cc_linked_list_add_last(list, cc_object_with_int(6));
	cc_linked_list_add_last(list, cc_object_with_int(5));
	cc_linked_list_add_last(list, cc_object_with_int(8));
	
	cc_enumerator *e = cc_linked_list_get_enumerator(list);
	cc_enumerator *sorted = cc_enumerator_order(e);
	
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(sorted), true);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_enumerator_current(sorted)), 1);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(sorted), true);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_enumerator_current(sorted)), 2);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(sorted), true);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_enumerator_current(sorted)), 3);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(sorted), true);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_enumerator_current(sorted)), 4);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(sorted), true);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_enumerator_current(sorted)), 5);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(sorted), true);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_enumerator_current(sorted)), 6);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(sorted), true);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_enumerator_current(sorted)), 7);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(sorted), true);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_enumerator_current(sorted)), 8);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(sorted), true);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_enumerator_current(sorted)), 9);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(sorted), false);
}

void test_enumerator_can_map(void)
{
	cc_enumerator *e = cc_enumerator_new(cc_enumerable_new(one_to_three));
	e->data = GC_MALLOC(sizeof(int));
	*((int *)e->data) = 0;
	
	cc_enumerator *strings = cc_enumerator_map(e, int_to_string_map);
	
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(strings), true);
	TEST_ASSERT_EQUAL(strcmp(cc_object_string_value(cc_enumerator_current(strings)), "1"), 0);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(strings), true);
	TEST_ASSERT_EQUAL(strcmp(cc_object_string_value(cc_enumerator_current(strings)), "2"), 0);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(strings), true);
	TEST_ASSERT_EQUAL(strcmp(cc_object_string_value(cc_enumerator_current(strings)), "3"), 0);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(strings), false);
}

void test_can_convert_enumerator_to_list(void)
{
	cc_enumerator *e = cc_enumerator_new(cc_enumerable_new(one_to_three));
	e->data = GC_MALLOC(sizeof(int));
	*((int *)e->data) = 0;
	
	cc_linked_list *expected = cc_linked_list_new();
	cc_linked_list_add_last(expected, cc_object_with_int(1));
	cc_linked_list_add_last(expected, cc_object_with_int(2));
	cc_linked_list_add_last(expected, cc_object_with_int(3));
	
	cc_linked_list *list = cc_enumerator_to_list(e);
	TEST_ASSERT_EQUAL(cc_linked_list_equals(list, expected), true);
}

void test_enumerator_can_stack_enumerators(void)
{
	cc_linked_list *list = cc_linked_list_new_with_values(cc_object_type_int, 4, 2, 7, 9, 1, 3, 6, 5, 8, CC_END);
	
	cc_enumerator *e = cc_linked_list_get_enumerator(list);
	cc_enumerator *odd_numbers = cc_enumerator_filter(e, odd_filter);
	cc_enumerator *ordered = cc_enumerator_order(odd_numbers);
	cc_enumerator *strings = cc_enumerator_map(ordered, int_to_string_map);
	cc_linked_list *result = cc_enumerator_to_list(strings);
	
	cc_linked_list *expected = cc_linked_list_new_with_values(cc_object_type_string, "1", "3", "5", "7", "9", CC_END);
	TEST_ASSERT_EQUAL(cc_linked_list_equals(expected, result), true);
}

void test_enumerator_can_fold(void)
{
	cc_linked_list *list = cc_linked_list_new_with_values(cc_object_type_string, "good", "artists", "copy,", "great", "artists", "steal");
	cc_object *result = cc_enumerator_fold(cc_linked_list_get_enumerator(list), cc_object_with_string(""), string_concat);
	TEST_ASSERT_EQUAL(strcmp("good artists copy, great artists steal", cc_object_string_value(result)), 0);
}
