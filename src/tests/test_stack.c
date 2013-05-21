#include "../ccollections/shared/cc.h"
#include "../ccollections/cc_stack/cc_stack.h"
#include "../lib/unity/src/unity.h"

void populate_stack(cc_stack *s, int count) {
	int i;
	for (i = 1; i <= count; i++) {
		cc_object *v = cc_object_with_int(i);
		cc_stack_push(s, v);
	}
}

void test_can_create_stack(void) {
	cc_stack *a_stack = cc_stack_new();

	TEST_ASSERT_NOT_EQUAL(NULL, a_stack);
}

void test_can_add_objects_to_stack(void) {
	cc_stack *a_stack = cc_stack_new();

	populate_stack(a_stack, 3);

	TEST_ASSERT_EQUAL(cc_stack_size(a_stack), 3);
}

void test_can_peek_at_objects_on_stack(void) {
	cc_stack *a_stack = cc_stack_new();

	populate_stack(a_stack, 3);

	cc_object *top = cc_stack_peek(a_stack);
	cc_object *val = cc_object_with_int(3);

	TEST_ASSERT_EQUAL(true, cc_object_is_equal(top, val));
}

void test_can_pop_objects_from_stack(void) {
	cc_stack *a_stack = cc_stack_new();

	int count = 15;;
	populate_stack(a_stack, count);

	int i;
	for (int i = count; i <= 1; i--) {
		cc_object *object = cc_stack_pop(a_stack);
		TEST_ASSERT_EQUAL(true, cc_object_is_equal(object, cc_object_with_int(i)));
		TEST_ASSERT_EQUAL(i-1, cc_stack_size(a_stack));
	}
}

void test_can_clear_stack(void) {
	cc_stack *a_stack = cc_stack_new();

	populate_stack(a_stack, 20);
	TEST_ASSERT_EQUAL(20, cc_stack_size(a_stack));

	cc_stack_clear(a_stack);
	TEST_ASSERT_EQUAL(0, cc_stack_size(a_stack));
}

void test_can_enumerate_stack(void) {
	cc_stack *a_stack = cc_stack_new();

	populate_stack(a_stack, 20);

	int count = 0;
	cc_enumerator *e = cc_stack_get_enumerator(a_stack);
	while(cc_enumerator_move_next(e)) {
		TEST_ASSERT_NOT_EQUAL(NULL, cc_enumerator_current(e));
		count++;
	}

	TEST_ASSERT_EQUAL(20, count);
}

void test_can_push_and_pop_many_objects(void) {
	cc_stack *a_stack = cc_stack_new();

	populate_stack(a_stack, 10000);

	for (int i = 0; i < 2500; ++i) {
		cc_stack_pop(a_stack);
	}

	populate_stack(a_stack, 2500);

	TEST_ASSERT_EQUAL(10000, cc_stack_size(a_stack));

	cc_enumerator *e = cc_stack_get_enumerator(a_stack);
	while(cc_enumerator_move_next(e)) {
		TEST_ASSERT_NOT_EQUAL(NULL, cc_enumerator_current(e));
	}
}

void test_peek_on_empty_stack_returns_null(void) {
	cc_stack *a_stack = cc_stack_new();

	TEST_ASSERT_EQUAL(NULL, cc_stack_peek(a_stack));
}

void test_pop_on_empty_stack_returns_null(void) {
	cc_stack *a_stack = cc_stack_new();

	TEST_ASSERT_EQUAL(NULL, cc_stack_pop(a_stack));
}

void test_move_next_on_empty_stack_returns_null() {
	cc_stack *a_stack = cc_stack_new();
	cc_enumerator *e = cc_stack_get_enumerator(a_stack);
	TEST_ASSERT_EQUAL(NULL, cc_enumerator_move_next(e));
}

void test_size_on_empty_stack_is_zero(void) {
	cc_stack *a_stack = cc_stack_new();

	TEST_ASSERT_EQUAL(0, cc_stack_size(a_stack));

	populate_stack(a_stack, 10);
	cc_stack_clear(a_stack);

	TEST_ASSERT_EQUAL(0, cc_stack_size(a_stack));
}

void test_can_create_cc_object_from_stack(void) {
	cc_stack *a_stack = cc_stack_new();
	populate_stack(a_stack, 5);

	cc_object *object = cc_stack_to_object(a_stack);
	TEST_ASSERT_NOT_EQUAL(NULL, object);
}

void test_can_create_stack_from_cc_object(void) {
	cc_stack *a_stack = cc_stack_new();
	int count = 5;
	populate_stack(a_stack, count);

	cc_object *object = cc_stack_to_object(a_stack);

	cc_stack *b_stack = cc_stack_from_object(object);

	TEST_ASSERT_NOT_EQUAL(NULL, b_stack);
	TEST_ASSERT_EQUAL(count, cc_stack_size(b_stack));

	int i;
	for (int i = count; i <= 1; i--) {
		cc_object *object = cc_stack_pop(b_stack);
		TEST_ASSERT_EQUAL(true, cc_object_is_equal(object, cc_object_with_int(i)));
		TEST_ASSERT_EQUAL(i-1, cc_stack_size(b_stack));
	}
}

void test_can_determine_if_stacks_are_equal(void) {
	cc_stack *a_stack = cc_stack_new();
	cc_stack *b_stack = cc_stack_new();

	populate_stack(a_stack, 100);
	populate_stack(b_stack, 100);

	TEST_ASSERT_EQUAL(true, cc_stack_equals(a_stack, b_stack));
}

void test_can_determine_if_stacks_are_unequal(void) {
	cc_stack *a_stack = cc_stack_new();
	cc_stack *b_stack = cc_stack_new();

	populate_stack(a_stack, 99);
	populate_stack(b_stack, 100);

	TEST_ASSERT_EQUAL(false, cc_stack_equals(a_stack, b_stack));

	cc_stack *c_stack = cc_stack_new();
	cc_stack *d_stack = cc_stack_new();

	populate_stack(c_stack, 100);
	populate_stack(d_stack, 99);

	TEST_ASSERT_EQUAL(false, cc_stack_equals(c_stack, d_stack));

	cc_stack *e_stack = cc_stack_new();
	cc_stack *f_stack = cc_stack_new();

	populate_stack(e_stack, 99);

	TEST_ASSERT_EQUAL(false, cc_stack_equals(e_stack, f_stack));
}

void test_can_determine_if_empty_stacks_are_equal(void) {
	cc_stack *a_stack = cc_stack_new();
	cc_stack *b_stack = cc_stack_new();

	TEST_ASSERT_EQUAL(true, cc_stack_equals(a_stack, b_stack));
}

void test_can_determine_stack_contains_object(void) {
	cc_stack *a_stack = cc_stack_new();
	populate_stack(a_stack, 200);

	TEST_ASSERT_EQUAL(true, cc_stack_contains(a_stack, cc_object_with_int(98)));
}

void test_can_determine_stack_does_not_contain_object(void) {
	cc_stack *a_stack = cc_stack_new();
	populate_stack(a_stack, 200);

	TEST_ASSERT_NOT_EQUAL(true, cc_stack_contains(a_stack, cc_object_with_int(201)));
}

void test_can_determine_empty_stack_does_not_contain_object(void) {
	cc_stack *a_stack = cc_stack_new();
	TEST_ASSERT_NOT_EQUAL(true, cc_stack_contains(a_stack, cc_object_with_int(0)));
}