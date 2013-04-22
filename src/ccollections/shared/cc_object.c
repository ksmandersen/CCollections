#include "cc_private.h"
#include "cc_object.h"

const char * const cc_object_type_int = "cc_object_type_int";
const char * const cc_object_type_float = "cc_object_type_float";
const char * const cc_object_type_string = "cc_object_type_string";

int cc_object_int_compare(cc_object *obj1, cc_object *obj2);
int cc_object_float_compare(cc_object *obj1, cc_object *obj2);
int cc_object_string_compare(cc_object *obj1, cc_object *obj2);

bool cc_object_int_equals(cc_object *obj1, cc_object *obj2);
bool cc_object_float_equals(cc_object *obj1, cc_object *obj2);
bool cc_object_string_equals(cc_object *obj1, cc_object *obj2);

cc_hash cc_object_int_hash_func(cc_object *obj);
cc_hash cc_object_float_hash_func(cc_object *obj);
cc_hash cc_object_string_hash_func(cc_object *obj);

typedef struct {
	const char *type;
	cc_object_comparator comparator;
} cc_object_registered_comparator;

typedef struct {
	const char *type;
	cc_object_hash_func hash_func;
} cc_object_registered_hash_func;

static unsigned int registered_comparators_count = 0;
static cc_object_registered_comparator registered_comparators[256];

static unsigned int registered_hash_funcs_count = 0;
static cc_object_registered_hash_func registered_hash_funcs[256];

struct cc_object_struct {
	const char *type;
	cc_object_hash_func hash_func;
	
	union {
		int i;
		float f;
		char *str;
		void *data;
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
	
	size_t str_size = strlen(str) + 1;
	obj->value.str = GC_MALLOC(str_size);
	memcpy(obj->value.str, str, str_size);
	obj->type = cc_object_type_string;
	return obj;
}

cc_object *cc_object_with_data(const void *data, size_t len, const char *typeid) {
	cc_object *obj = GC_MALLOC(sizeof(cc_object));
	obj->value.data = GC_MALLOC(len);
	memcpy(obj->value.data, data, len);
	obj->type = typeid;
	return obj;
}


const char *cc_object_get_type(cc_object *obj) {
	return obj->type;
}

bool cc_object_is_equal(cc_object *obj1, cc_object *obj2) {
	if ((obj1 == NULL && obj2 != NULL) | (obj1 != NULL && obj2 == NULL)) return false;
	if (obj1 == NULL && obj2 == NULL) return true;
    
	
	if (strcmp(obj1->type, obj2->type) != 0) return false;
	
	const char *type = obj1->type;
	
	int i;
	for (i = 0; i < registered_comparators_count; i++) {
		cc_object_registered_comparator reg = registered_comparators[i];
		
		if (strcmp(reg.type, type) == 0) {
			return reg.comparator(obj1, obj2) == 0;
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

void cc_object_register_hash_func_for_type(const char *type, cc_object_hash_func hash_func) {
	if (registered_hash_funcs_count >= sizeof(registered_hash_funcs) / sizeof(registered_hash_funcs[0])) {
		printf("registered hash funcs overflow\n");
	}
	
	registered_hash_funcs[registered_hash_funcs_count++] = (cc_object_registered_hash_func) {
		.type = type,
		.hash_func = hash_func,
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

void *cc_object_data_value(cc_object *obj) {
	return obj->value.data;
}


cc_hash cc_object_hash(cc_object *obj) {
	const char *type = obj->type;
	
	int i;
	for (i = 0; i < registered_hash_funcs_count; i++) {
		cc_object_registered_hash_func reg = registered_hash_funcs[i];
    
		if (strcmp(reg.type, type) == 0) {
			return reg.hash_func(obj);
		}
	}
	
	printf("Unregistered type '%s'\n", type);
	return false;
}

void cc_object_register_default_comparators() {
	cc_object_register_comparator_for_type(cc_object_type_int, cc_object_int_compare);
	cc_object_register_comparator_for_type(cc_object_type_float, cc_object_float_compare);
	cc_object_register_comparator_for_type(cc_object_type_string, cc_object_string_compare);
	
	cc_object_register_hash_func_for_type(cc_object_type_int, cc_object_int_hash_func);
}

// Compare methods
// -1 for a smaller than b
// 0 for identical
// 1 for a larger than b

int cc_object_int_compare(cc_object *obj1, cc_object *obj2) {
    int obj1_val = cc_object_int_value(obj1);
    int obj2_val = cc_object_int_value(obj2);
    
    if (obj1_val > obj2_val) return -1;
    if (obj1_val < obj2_val) return 1;
    
    return 0;
}

int cc_object_float_compare(cc_object *obj1, cc_object *obj2) {
	float obj1_val = cc_object_float_value(obj1);
    float obj2_val = cc_object_float_value(obj2);
    
    if (obj1_val > obj2_val) return -1;
    if (obj1_val < obj2_val) return 1;
    
    return 0;
}

int cc_object_string_compare(cc_object *obj1, cc_object *obj2) {
	return strcmp(cc_object_string_value(obj1), cc_object_string_value(obj2));
}

// Equals methods

bool cc_object_int_equals(cc_object *obj1, cc_object *obj2) {
    return (cc_object_int_compare(obj1, obj2) == 0);
}

bool cc_object_float_equals(cc_object *obj1, cc_object *obj2) {
    return (cc_object_float_compare(obj1, obj2) == 0);
}

bool cc_object_string_equals(cc_object *obj1, cc_object *obj2) {
	return cc_object_string_compare(obj1, obj2) == 0;
}

// Hash methods

cc_hash cc_object_int_hash_func(cc_object *obj) {
	int i = cc_object_int_value(obj);
	return cc_hash_from_data(&i, sizeof(int));
}

cc_hash cc_object_float_hash_func(cc_object *obj) {
	float f = cc_object_float_value(obj);
	return cc_hash_from_data(&f, sizeof(float));
}

cc_hash cc_object_string_hash_func(cc_object *obj) {
	return cc_hash_from_string(cc_object_string_value(obj));
}
