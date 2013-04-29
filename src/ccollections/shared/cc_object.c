/*
 * CC_OBJECT.C
 * 
 * This file is part of the CCollections library.
 *
 * CCollections is licensed under the BSD-2-Clause License (FreeBSD).
 * Copyright (c) 2012, Ulrik Damm and Kristian Andersen.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met:
 *
 * Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer. Redistributions 
 * in binary form must reproduce the above copyright notice, this list 
 * of conditions and the following disclaimer in the documentation and/or 
 * other materials provided with the distribution. THIS SOFTWARE IS 
 * PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
		void *ptr;
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

cc_object *cc_object_with_pointer(void *ptr, const char *typeid) {
	cc_object *obj = GC_MALLOC(sizeof(cc_object));
	obj->value.ptr = ptr;
	obj->type = typeid;
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

int cc_object_compare(cc_object *obj1, cc_object *obj2) {
	if (obj1 == obj2) {
		return 0;
	}
	
	if (obj1 == NULL && obj2 != NULL) {
		return -1;
	}
	
	if (obj1 != NULL && obj2 == NULL) {
		return 1;
	}
	
	int type_diff = strcmp(obj1->type, obj2->type);
	if (type_diff != 0) return type_diff;
	
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

bool cc_object_is_equal(cc_object *obj1, cc_object *obj2) {
	return (cc_object_compare(obj1, obj2) == 0);
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

cc_object_comparator cc_get_comperator_for_object(cc_object *obj) {
	if (obj == NULL || obj->type == NULL) return NULL;

	const char *type = obj->type;

  int i;
	for (i = 0; i < registered_comparators_count; i++) {
		cc_object_registered_comparator reg = registered_comparators[i];
		
		if (strcmp(reg.type, type) == 0) {
			return reg.comparator;
		}
	}
  
  return NULL;
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

void *cc_object_pointer_value(cc_object *obj) {
	return obj->value.ptr;
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
	cc_object_register_hash_func_for_type(cc_object_type_float, cc_object_float_hash_func);
	cc_object_register_hash_func_for_type(cc_object_type_string, cc_object_string_hash_func);
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
	int compare = strcmp(cc_object_string_value(obj1), cc_object_string_value(obj2));
	if (compare > 0) return -1;
	if (compare < 0) return 1;
	return 0;
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
