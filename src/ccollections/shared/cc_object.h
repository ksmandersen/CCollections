/*
 * CC_OBJECT.H
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

#ifndef CC_OBJECT_H
#define CC_OBJECT_H

#include "cc_private.h"
#include "cc_hash.h"

extern const char * const cc_object_type_int;
extern const char * const cc_object_type_float;
extern const char * const cc_object_type_string;

struct cc_object_struct;
typedef struct cc_object_struct cc_object;

typedef int (*cc_object_comparator)(cc_object *obj1, cc_object *obj2);
typedef cc_hash (*cc_object_hash_func)(cc_object *obj);

cc_object *cc_object_with_int(int i);
cc_object *cc_object_with_float(float f);
cc_object *cc_object_with_string(const char *str);
cc_object *cc_object_with_pointer(void *ptr, const char *typeid);
cc_object *cc_object_with_data(const void *data, size_t len, const char *typeid);

const char *cc_object_get_type(cc_object *obj);
int cc_object_compare(cc_object *obj1, cc_object *obj2);
bool cc_object_is_equal(cc_object *obj1, cc_object *obj2);

void cc_object_register_comparator_for_type(const char *type, cc_object_comparator comparator); // <- not thread safe; only run on main thread
void cc_object_register_hash_func_for_type(const char *type, cc_object_hash_func hash_func);
cc_object_comparator cc_get_comperator_for_object(cc_object *obj);

const char *cc_object_string_value(cc_object *obj);
int cc_object_int_value(cc_object *obj);
float cc_object_float_value(cc_object *obj);
void *cc_object_pointer_value(cc_object *obj);
void *cc_object_data_value(cc_object *obj);

cc_hash cc_object_hash(cc_object *obj);

#endif
