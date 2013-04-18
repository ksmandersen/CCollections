#ifndef CC_STACK_H
#define CC_STACK_H

#include "../shared/cc_private.h"
#include "../shared/cc_object.h"
#include "../shared/cc_enumerator.h"

extern const char * const cc_stack_type;

struct cc_stack_struct;
typedef struct cc_stack_struct cc_stack;

cc_stack *cc_stack_new();
void cc_stack_push(cc_stack *stack, cc_object *obj);
cc_object *cc_stack_pop(cc_stack *stack);
cc_object *cc_stack_peek(cc_stack *stack);
void cc_stack_clear(cc_stack *stack);

cc_object *cc_stack_to_object(cc_set *set);
cc_stack *cc_stack_from_object(cc_object *obj);

cc_enumerator *cc_stack_get_enumerator(cc_stack *stack);

#endif
