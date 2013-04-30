/*
 * CC_SORTED_LIST.H
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

#ifndef CC_SORTED_LIST_H
  #define CC_SORTED_LIST_H

#include "../shared/cc_private.h"
#include "../shared/cc_object.h"
#include "../shared/cc_enumerator.h"

extern const char *const cc_sorted_list_type;

/*! \brief A sorted list data structure that stays sorted with insertions. 
 * Sorting is performed using inserted objects comperator. It is therefore
 * important that all inserted objects have the same type. */
struct cc_sorted_list_struct;
typedef struct cc_sorted_list_struct cc_sorted_list;

/*! \brief Create a sorted list object
 * \return A new sorted list object */
cc_sorted_list *cc_sorted_list_new();

/*! \brief Get the length of the list
 * \return The length of the list */
int cc_sorted_list_length(cc_sorted_list *list);

/*! \brief Get a node in a sorted list
 * \param list the sorted list
 * \param index the index of the node to get */
cc_object *cc_sorted_list_get(cc_sorted_list *list, int index);

/*! \brief Get the first node in a sorted list
 * \param list the sorted list */
cc_object *cc_sorted_list_get_first(cc_sorted_list *list);

/*! \brief Get the last node in a sorted list
 * \param list the sorted list */
cc_object *cc_sorted_list_get_last(cc_sorted_list *list);

/*! \brief Insert a value at a position in the sorted list
 * \param list the sorted list
 * \param index the index at which to insert the object
 * \param object the object to insert */
void cc_sorted_list_add(cc_sorted_list *list, cc_object *object);

/*! \brief Remove a value at a position in the sorted list
 * \param list the sorted list
 * \param index the index at which to remove the object */
void cc_sorted_list_remove(cc_sorted_list *list, int index);

/*! \brief Remove the value from the front node in a sorted list
 * \param list the sorted list */
void cc_sorted_list_remove_first(cc_sorted_list *list);

/*! \brief Remove the value from the end node in a sorted list
 * \param list the sorted list */
void cc_sorted_list_remove_last(cc_sorted_list *list);

/*! \brief Removes all objects from a sorted list
 * \param list the sorted list to be emptied */
void cc_sorted_list_clear(cc_sorted_list *list);

/*! \brief Merges two lists together by adding all objects
 * from the first list to the second list.
 * \param a_list the first list
 * \param b_list the second list
 * \returns The lists merged together */
cc_sorted_list *cc_sorted_list_merge(cc_sorted_list *a_list, cc_sorted_list *b_list);

bool cc_sorted_list_contains(cc_sorted_list *list, cc_object *object);
cc_enumerator *cc_sorted_list_get_enumerator(cc_sorted_list *list);

cc_object *cc_sorted_list_to_object(cc_sorted_list *list);
cc_sorted_list *cc_sorted_list_from_object(cc_object *object);

#endif
