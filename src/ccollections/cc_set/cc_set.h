#ifndef CC_SET_H
#define CC_SET_H

#include "cc_private.h"
#include "cc_object.h"
#include "cc_enumerator.h"

extern const char * const cc_set_type;

struct cc_set_struct;
typedef struct cc_set_struct cc_set;

cc_set *cc_set_new();
void cc_set_add(cc_set *set, cc_object *obj);
void cc_set_clear(cc_set *set);
bool cc_set_contains(cc_set *set, cc_object *obj);
cc_enumerator *cc_set_get_enumerator(cc_set *set);
void cc_set_remove(cc_set *set, cc_object *obj);

cc_object *cc_set_to_object(cc_set *set);
cc_set *cc_set_from_object(cc_object *obj);

#endif
