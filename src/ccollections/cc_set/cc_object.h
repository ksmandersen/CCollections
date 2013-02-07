#ifndef CC_OBJECT_H
#define CC_OBJECT_H

#include "cc_private.h"

extern const char * const cc_object_type_int;
extern const char * const cc_object_type_float;
extern const char * const cc_object_type_string;

struct cc_object_struct;
typedef struct cc_object_struct cc_object;

typedef bool (*cc_object_comparator)(cc_object *obj1, cc_object *obj2);

cc_object *cc_object_with_int(int i);
cc_object *cc_object_with_float(float f);
cc_object *cc_object_with_string(const char *str);
cc_object *cc_object_with_data(const void *data, size_t len, const char *typeid);


const char *cc_object_get_type(cc_object *obj);
bool cc_object_is_equal(cc_object *obj1, cc_object *obj2);
void cc_object_register_comparator_for_type(const char *type, cc_object_comparator comparator); // <- not thread safe; only run on main thread

const char *cc_object_string_value(cc_object *obj);
int cc_object_int_value(cc_object *obj);
float cc_object_float_value(cc_object *obj);
size_t cc_object_data_value(cc_object *obj, void **data, size_t max);

const char *cc_object_hash(cc_object *obj);

#endif
