#include "cc_queue.h"
#include "../shared/cc_private.h"
#include "../cc_linked_list/cc_linked_list.h"

const char * const cc_queue_type = "cc_queue_type";

static int cc_queue_compare(cc_object *obj1, cc_object *obj2);
static void cc_queue_register_comparator();

struct cc_queue_struct {
	cc_collection c;
	
	cc_linked_list *linked_list;
};

cc_queue *cc_queue_new() {
	cc_queue_register_comparator();
	
	cc_queue *queue = GC_MALLOC(sizeof(cc_queue));
	
	queue->linked_list = cc_linked_list_new();
	
	return queue;
}

void cc_queue_enqueue(cc_queue *queue, cc_object *obj) {
	cc_linked_list_add_last(queue->linked_list, obj);
}

cc_object *cc_queue_dequeue(cc_queue *queue) {
	cc_object *obj = cc_linked_list_get_first(queue->linked_list);
	cc_linked_list_remove_first(queue->linked_list);
	return obj;
}

cc_object *cc_queue_peek(cc_queue *queue) {
	return cc_linked_list_get_first(queue->linked_list);
}

int cc_queue_count(cc_queue *queue) {
	return cc_linked_list_length(queue->linked_list);
}

void cc_queue_clear(cc_queue *queue) {
	cc_linked_list_clear(queue->linked_list);
}

bool cc_queue_contains(cc_queue *queue, cc_object *obj) {
	return cc_linked_list_contains(queue->linked_list, obj);
}

cc_enumerator *cc_queue_get_enumerator(cc_queue *queue) {
	return cc_linked_list_get_enumerator(queue->linked_list);
}

cc_object *cc_queue_to_object(cc_queue *queue) {
	return cc_object_with_pointer(queue, cc_queue_type);
}

cc_queue *cc_queue_from_object(cc_object *object) {
	return cc_object_pointer_value(object);
}

int cc_queue_compare(cc_object *obj1, cc_object *obj2) {
	cc_queue *queue1 = cc_queue_from_object(obj1);
	cc_queue *queue2 = cc_queue_from_object(obj2);
	
	int len1 = cc_queue_count(queue1);
	int len2 = cc_queue_count(queue2);
	
	if (len1 > len2) {
		return 1;
	} else if (len1 < len2) {
		return -1;
	}
	
	cc_enumerator *e1 = cc_queue_get_enumerator(queue1);
	cc_enumerator *e2 = cc_queue_get_enumerator(queue2);
	
	while (cc_enumerator_move_next(e1), cc_enumerator_move_next(e2)) {
		int diff = cc_object_compare(cc_enumerator_current(e1), cc_enumerator_current(e2));
		
		if (diff != 0) {
			return diff;
		}
	}
	
	return 0;
}

void cc_queue_register_comparator() {
	static bool first = true;
	
	if (first) {
		first = false;
		cc_object_register_comparator_for_type(cc_queue_type, cc_queue_compare);
	}
}
