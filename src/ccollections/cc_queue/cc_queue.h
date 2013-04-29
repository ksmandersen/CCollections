#ifndef CC_QUEUE_H
#define CC_QUEUE_H

#include "../shared/cc.h"

struct cc_queue_struct;
typedef struct cc_queue_struct cc_queue;

cc_queue *cc_queue_new();

void cc_queue_enqueue(cc_queue *queue, cc_object *obj);
cc_object *cc_queue_dequeue(cc_queue *queue);
cc_object *cc_queue_peek(cc_queue *queue);

int cc_queue_count(cc_queue *queue);
void cc_queue_clear(cc_queue *queue);

bool cc_queue_contains(cc_queue *queue, cc_object *obj);

cc_enumerator *cc_queue_get_enumerator(cc_queue *queue);

cc_object *cc_queue_to_object(cc_queue *queue);
cc_queue *cc_queue_from_object(cc_object *object);

#endif