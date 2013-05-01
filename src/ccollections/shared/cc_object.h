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

/*! \file cc_object.h

    This file contains the interface of the CCollection cc_objects.

    This object is used as the basis for all data
    inserted and passed around the collection library.

    Each cc_object has value and an associated type.
    The type is used for several things, most importantly
    to choose the comperator for which to compare objects
    in collections.

    It is possible to extends CCollections with custom
    cc_object types with custom comparators.

    Default cc_object types are included for integers, floats,
    strings, pointers and arbitrary data.
*/

#ifndef CC_OBJECT_H
#define CC_OBJECT_H

#include "cc_private.h"
#include "cc_hash.h"

extern const char * const cc_object_type_int;
extern const char * const cc_object_type_float;
extern const char * const cc_object_type_string;

struct cc_object_struct;
/*! \brief cc_object type */
typedef struct cc_object_struct cc_object;

/*! \brief cc_object comparator function pointer type */
typedef int (*cc_object_comparator)(cc_object *obj1, cc_object *obj2);

/*! \brief cc_object hash function pointer type */
typedef cc_hash (*cc_object_hash_func)(cc_object *obj);

/*! \brief Creates an object with an integer
 * \param i the integer
 * \return A new integer object */
cc_object *cc_object_with_int(int i);

/*! \brief Creates an object with a float value
 * \param f the float
 * \return A new floating point object */
cc_object *cc_object_with_float(float f);

/*! \brief Creates an object with a string value
 * \param str the string
 * \return A new string object */
cc_object *cc_object_with_string(const char *str);

/*! \brief Creates an object with a function
 * \param ptr the pointer
 * \param typeid the type of the object being pointed to
 * \return A new pointer object */
cc_object *cc_object_with_pointer(void *ptr, const char *typeid);

/*! \brief Creates an object with an integer
 * \param data the data
 * \param len the bytesize of the data
 * \param typeid the type of the data
 * \return A new data object */
cc_object *cc_object_with_data(const void *data, size_t len, const char *typeid);

/*! \brief Gets the type identifier from an object
 * \param obj the object
 * \return The type identifier for the object */
const char *cc_object_get_type(cc_object *obj);

/*! \brief Compares two objects using their mutual comparator
 * \param obj1 the first object
 * \param obj2 the second object
 * \return An integer representing the equality of the two objects being compared */
int cc_object_compare(cc_object *obj1, cc_object *obj2);

/*! \brief Determines whether two objects are equal to eachother. Equality includes identity
 * \param obj1 the first object
 * \param obj2 the second object
 * \return true if objects are equal; false, otherwise */
bool cc_object_is_equal(cc_object *obj1, cc_object *obj2);

/*! \brief Registers a comparator for a object type.
 * \param type the identifier for the object type
 * \param comparator a function pointer to the comparator for the type */
void cc_object_register_comparator_for_type(const char *type, cc_object_comparator comparator); // <- not thread safe; only run on main thread

/*! \brief Registers a hash function for a object type.
 * \param type the identifier for the object type
 * \param hash_func a function pointer to the hash function for the type */
void cc_object_register_hash_func_for_type(const char *type, cc_object_hash_func hash_func);

/*! \brief Gets the comparator for an object. The comparator is inferred from the object type.
 * \param obj the object
 * \return the comparator registered for the object type; NULL if no comparator is associated */
cc_object_comparator cc_get_comperator_for_object(cc_object *obj);

/*! \brief Gets the string value from an object
 * \param obj the object
 * \return The string from the object */
const char *cc_object_string_value(cc_object *obj);

/*! \brief Gets the integer value from an object
 * \param obj the object
 * \return The integer from the object */
int cc_object_int_value(cc_object *obj);

/*! \brief Gets the floating point value from an object
 * \param obj the object
 * \return The floating point from the object */
float cc_object_float_value(cc_object *obj);

/*! \brief Gets the pointer value from an object
 * \param obj the object
 * \return The pointer from the object */
void *cc_object_pointer_value(cc_object *obj);

/*! \brief Gets the data value from an object
 * \param obj the object
 * \return The data from the object */
void *cc_object_data_value(cc_object *obj);

/*! \brief Gets the hashed data value from an object
 * \param obj the object
 * \return The hashed data from the object */
cc_hash cc_object_hash(cc_object *obj);

#endif
