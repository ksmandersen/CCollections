/*
 * CC_SET.H
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

#ifndef CC_SET_H
#define CC_SET_H

#include "../shared/cc_private.h"
#include "../shared/cc_object.h"
#include "../shared/cc_enumerator.h"

extern const char * const cc_set_type;

struct cc_set_struct;
typedef struct cc_set_struct cc_set;

/*! \brief Creates a new empty set
 * \return A new empty set */
cc_set *cc_set_new();

/*! \brief Adds an object to the set
 * \param set the set
 * \param obj the object to add */
void cc_set_add(cc_set *set, cc_object *obj);

/*! \brief Gets an object from a set
 * \param set the set
 * \param index the index of the object in the set */
cc_object *cc_set_get(cc_set *set, int index);

/*! \brief Removes an object from the set
 * \param set the set
 * \param obj the object to remove */
void cc_set_remove(cc_set *set, cc_object *obj);

/*! \brief Removes all objects from the set
 * \param set the set */
void cc_set_clear(cc_set *set);

/*! \brief Get the number of objects in the set
 * \param set the set */
int cc_set_count(cc_set *set);

/*! \brief Determines whether an object is in the set
 * \param set the set to search
 * \param object the object to search the set for
 * \returns true if the object is found on the stack; otherwise, false */
bool cc_set_contains(cc_set *set, cc_object *obj);

/*! \brief Merges two sets together by adding all objects
 * from the b_set to the a_set
 * \param a_list the first set
 * \param b_list the second set */
void cc_set_merge(cc_set *a_set, cc_set *b_set);

/*! \brief Get an enumerator for the set
 * \param set the set
 * \returns an enumerator for the set */
cc_enumerator *cc_set_get_enumerator(cc_set *set);

/*! \brief Make a cc_object from the set
 * \param set the set */
cc_object *cc_set_to_object(cc_set *set);

/*! \brief Make a set from the cc_object
 * \param obj the object */
cc_set *cc_set_from_object(cc_object *obj);

#endif
