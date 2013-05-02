#include "../ccollections/shared/cc.h"
#include "../lib/unity/src/unity.h"

// void setUp(void)
// {
//   GC_INIT();
//   cc_init();
// }

// void tearDown(void)
// {
	
// }

void test_can_create_queue(void)
{
	cc_queue *q = cc_queue_new();
	TEST_ASSERT_NOT_EQUAL(q, NULL);
}

void test_can_add_objects_to_queue(void)
{
	cc_queue *q = cc_queue_new();
	cc_queue_enqueue(q, cc_object_with_int(1));
	cc_queue_enqueue(q, cc_object_with_int(2));
	cc_queue_enqueue(q, cc_object_with_int(3));
	
	TEST_ASSERT_EQUAL(cc_queue_count(q), 3);
	
	cc_enumerator *e = cc_queue_get_enumerator(q);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(e), true);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_enumerator_current(e)), 1);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(e), true);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_enumerator_current(e)), 2);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(e), true);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_enumerator_current(e)), 3);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(e), false);
}

void test_can_dequeue_objects_from_queue(void)
{
	cc_queue *q = cc_queue_new();
	cc_queue_enqueue(q, cc_object_with_int(1));
	cc_queue_enqueue(q, cc_object_with_int(2));
	cc_queue_enqueue(q, cc_object_with_int(3));
	
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_queue_dequeue(q)), 1);
	TEST_ASSERT_EQUAL(cc_queue_count(q), 2);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_queue_dequeue(q)), 2);
	TEST_ASSERT_EQUAL(cc_queue_count(q), 1);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_queue_dequeue(q)), 3);
	TEST_ASSERT_EQUAL(cc_queue_count(q), 0);
}

void test_can_peek_at_queue(void)
{
	cc_queue *q = cc_queue_new();
	cc_queue_enqueue(q, cc_object_with_int(1));
	cc_queue_enqueue(q, cc_object_with_int(2));
	cc_queue_enqueue(q, cc_object_with_int(3));
	
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_queue_peek(q)), 1);
	TEST_ASSERT_EQUAL(cc_object_int_value(cc_queue_peek(q)), 1);
}

void test_can_clear_queue(void)
{
	cc_queue *q = cc_queue_new();
	cc_queue_enqueue(q, cc_object_with_int(1));
	cc_queue_enqueue(q, cc_object_with_int(2));
	cc_queue_enqueue(q, cc_object_with_int(3));
	
	cc_queue_clear(q);
	TEST_ASSERT_EQUAL(cc_queue_count(q), 0);
}

void test_queue_contains_object(void)
{
	cc_queue *q = cc_queue_new();
	cc_queue_enqueue(q, cc_object_with_int(1));
	cc_queue_enqueue(q, cc_object_with_int(2));
	cc_queue_enqueue(q, cc_object_with_int(3));
	
	TEST_ASSERT_EQUAL(cc_queue_contains(q, cc_object_with_int(2)), true);
	TEST_ASSERT_EQUAL(cc_queue_contains(q, cc_object_with_int(4)), false);
}
