#ifndef CC_ENUMERATOR_H
#define CC_ENUMERATOR_H

#include "cc_private.h"
#include "cc_object.h"

struct cc_enumerator_struct;
typedef struct cc_enumerator_struct cc_enumerator;

cc_object *cc_enumerator_current(cc_enumerator *e);
bool cc_enumerator_move_next(cc_enumerator *e);

#endif
