/*
 * CC_ARRAY_LIST.H
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

/*! \file cc_array_List.h

    This file contains the interface of the CCollection array list.
    The array list data structure is a dynamically expanding list implemented
    with standard C arrays.
*/

#ifndef CC_ARRAY_LIST_H
#define CC_ARRAY_LIST_H

#include "../shared/cc_private.h"
#include "../shared/cc_object.h"
#include "../shared/cc_enumerator.h"

extern const char * const cc_array_list_type;

struct cc_array_list_struct;
typedef struct cc_array_list_struct cc_array_list;

/*! \brief Creates a new empty array list.
 * \return A new array list object */
cc_array_list *cc_array_list_new();

/*! \brief Creates a new array list with all objects from the enumerator
 * \param e the enumerator of a collection
 * \return A new array list object */
cc_array_list *cc_array_list_new_with_enumerator(cc_enumerator *e);

/*! \brief Get the length of the list
 * \return The length of the list */
int cc_array_list_length(cc_array_list *list);

/*! \brief Get an object from a given index in an array list
 * \param list the array list
 * \param index the index of the object to get */
cc_object *cc_array_list_get(cc_array_list *list, int index);

/*! \brief Get the first object in an array list
 * \param list the array list */
cc_object *cc_array_list_get_first(cc_array_list *list);

/*! \brief Get the last node in an array list
 * \param list the linked list */
cc_object *cc_array_list_get_last(cc_array_list *list);

/*! \brief Adds an object to a given index in an array list
 * \param list the array list
 * \param index the index at wich to add the object in the list
 * \param object the object to add */
void cc_array_list_add(cc_array_list *list, int index, cc_object *object);

/*! \brief Adds an object to the beginning of an array list
 * \param list the array list
 * \param object the value to add */
void cc_array_list_add_first(cc_array_list *list, cc_object *object);

/*! \brief Adds an object to the end of an array list
 * \param list the array list
 * \param object the value to add */
void cc_array_list_add_last(cc_array_list *list, cc_object *object);

/*! \brief Removes an object at a given index from an array list
 * \param list the linked list
 * \param index the index at which to remove the object */
void cc_array_list_remove(cc_array_list *list, int index);

/*! \brief Removes the first object from an array list
 * \param list the array list */
void cc_array_list_remove_first(cc_array_list *list);

/*! \brief Removes the last object from an array list
 * \param list the array list */
void cc_array_list_remove_last(cc_array_list *list);

/*! \brief Removes all objects from a array list
 * \param list the array list to be emptied */
void cc_array_list_clear(cc_array_list *list);

/*! \brief Merges two lists together by adding all objects
 * from the b_list to the a_list
 * \param a_list the first list
 * \param b_list the second list
 * \return The lists merged together */
cc_array_list *cc_array_list_merge(cc_array_list *a_list, cc_array_list *b_list);

/*! \brief Determines whether an object is in the array list
 * \param list the array list to search
 * \param object the object to search the list for
 * \returns true if the object is found in the array list; otherwise, false */
bool cc_array_list_contains(cc_array_list *list, cc_object *object);

/*! \brief Sorts the objects in an array list using the registered comperators
 * for the objects type
 * \param list the array list */
void cc_array_list_sort(cc_array_list *list);

/*! \brief Shuffles all the objects in an array list by random
 * \param list the array list */
void cc_array_list_shuffle(cc_array_list *list);

/*! \brief Get an enumerator for an instance of an array list
 * \param list the array list
 * \returns an enumerator for the list */
cc_enumerator *cc_array_list_get_enumerator(cc_array_list *list);

/*! \brief Make a cc_object from an array list
 * \param list the array list */
cc_object *cc_array_list_to_object(cc_array_list *list);

/*! \brief Make an array list from a cc_object
 * \param object the object */
cc_array_list *cc_array_list_from_object(cc_object *object);

#endif
