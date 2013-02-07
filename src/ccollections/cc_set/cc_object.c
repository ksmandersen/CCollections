#include "cc_private.h"
#include "cc_object.h"

const char * const cc_object_type_int = "cc_object_type_int";
const char * const cc_object_type_float = "cc_object_type_float";
const char * const cc_object_type_string = "cc_object_type_string";

bool cc_object_int_comparator(cc_object *obj1, cc_object *obj2);
bool cc_object_float_comparator(cc_object *obj1, cc_object *obj2);
bool cc_object_string_comparator(cc_object *obj1, cc_object *obj2);

typedef struct {
	const char *type;
	cc_object_comparator comparator;
} cc_object_registered_comparator;

static unsigned int registered_comparators_count = 0;
static cc_object_registered_comparator registered_comparators[256];

struct cc_object_struct {
	const char *type;
	
	union {
		int i;
		float f;
		const char *str;
		struct { const void *data; size_t len; } data;
	} value;
};

cc_object *cc_object_with_int(int i) {
	cc_object *obj = GC_MALLOC(sizeof(cc_object));
	obj->value.i = i;
	obj->type = cc_object_type_int;
	return obj;
}

cc_object *cc_object_with_float(float f) {
	cc_object *obj = GC_MALLOC(sizeof(cc_object));
	obj->value.f = f;
	obj->type = cc_object_type_float;
	return obj;
}

cc_object *cc_object_with_string(const char *str) {
	cc_object *obj = GC_MALLOC(sizeof(cc_object));
	obj->value.str = str;
	obj->type = cc_object_type_string;
	return obj;
}

cc_object *cc_object_with_data(const void *data, size_t len, const char *typeid) {
	cc_object *obj = GC_MALLOC(sizeof(cc_object));
	obj->value.data.data = data;
	obj->value.data.len = len;
	obj->type = typeid;
	return obj;
}


const char *cc_object_get_type(cc_object *obj) {
	return obj->type;
}

bool cc_object_is_equal(cc_object *obj1, cc_object *obj2) {
	if (strcmp(obj1->type, obj2->type) != 0) return false;
	
	const char *type = obj1->type;
	
	int i;
	for (i = 0; i < registered_comparators_count; i++) {
		cc_object_registered_comparator reg = registered_comparators[i];
		
		if (strcmp(reg.type, type) == 0) {
			return reg.comparator(obj1, obj2);
		}
	}
	
	printf("Unregistered type '%s'\n", type);
	return false;
}

void cc_object_register_comparator_for_type(const char *type, cc_object_comparator comparator) {
	if (registered_comparators_count >= sizeof(registered_comparators) / sizeof(registered_comparators[0])) {
		printf("registered comparators overflow\n");
	}
	
	registered_comparators[registered_comparators_count++] = (cc_object_registered_comparator) {
		.type = type,
		.comparator = comparator,
	};
}


const char *cc_object_string_value(cc_object *obj) {
	return obj->value.str;
}

int cc_object_int_value(cc_object *obj) {
	return obj->value.i;
}

float cc_object_float_value(cc_object *obj) {
	return obj->value.f;
}

size_t cc_object_data_value(cc_object *obj, void **data, size_t max) {
	const void *d = obj->value.data.data;
	size_t len = obj->value.data.len;
	len = (max > len? max: len);
	memcpy(*data, d, len);
	return len;
}


const char *cc_object_hash(cc_object *obj) {
	return "some hash 123";
}

void cc_object_register_default_comparators() {
	cc_object_register_comparator_for_type(cc_object_type_int, cc_object_int_comparator);
	cc_object_register_comparator_for_type(cc_object_type_float, cc_object_float_comparator);
	cc_object_register_comparator_for_type(cc_object_type_string, cc_object_string_comparator);
}

bool cc_object_int_comparator(cc_object *obj1, cc_object *obj2) {
	return (cc_object_int_value(obj1) == cc_object_int_value(obj2));
}

bool cc_object_float_comparator(cc_object *obj1, cc_object *obj2) {
	return (cc_object_float_value(obj1) == cc_object_float_value(obj2));
}

bool cc_object_string_comparator(cc_object *obj1, cc_object *obj2) {
	return (strcmp(cc_object_string_value(obj1), cc_object_string_value(obj2)) == 0);
}
