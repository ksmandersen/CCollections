/*
 * CC_LINKED_LIST.H
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

#ifndef CC_LINKED_LIST_H
  #define CC_LINKED_LIST_H

#include "../shared/cc_private.h"
#include "../shared/cc_object.h"
#include "../shared/cc_enumerator.h"

extern const char *const cc_linked_list_type;

/*! \brief A linked list data structure */
struct cc_linked_list_struct;
typedef struct cc_linked_list_struct cc_linked_list;

/*! \brief Create a linked list object
 * \return A new linked list object */
cc_linked_list *cc_linked_list_new();

/*! \brief Get the length of the list
 * \return The length of the list */
int cc_linked_list_length(cc_linked_list *list);

/*! \brief Get a node in a linked list
 * \param list the linked list
 * \param index the index of the node to get */
cc_object *cc_linked_list_get(cc_linked_list *list, int index);

/*! \brief Get the first node in a linked list
 * \param list the linked list */
cc_object *cc_linked_list_get_first(cc_linked_list *list);

/*! \brief Get the last node in a linked list
 * \param list the linked list */
cc_object *cc_linked_list_get_last(cc_linked_list *list);

/*! \brief Insert a value at a position in the linked list
 * \param list the linked list
 * \param index the index at which to insert the object
 * \param object the object to insert */
void cc_linked_list_add(cc_linked_list *list, int index, cc_object *object);

/*! \brief Insert a value as the first node in a linked list
 * \param list the linked list
 * \param object the value to insert */
void cc_linked_list_add_first(cc_linked_list *list, cc_object *object);

/*! \brief Insert a value as the last node in a linked list
 * \param list the linked list
 * \param object the value to insert */
void cc_linked_list_add_last(cc_linked_list *list, cc_object *object);

/*! \brief Remove a value at a position in the linked list
 * \param list the linked list
 * \param index the index at which to remove the object */
void cc_linked_list_remove(cc_linked_list *list, int index);

/*! \brief Remove the value from the front node in a linked list
 * \param list the linked list */
void cc_linked_list_remove_first(cc_linked_list *list);

/*! \brief Remove the value from the end node in a linked list
 * \param list the linked list */
void cc_linked_list_remove_last(cc_linked_list *list);

/*! \brief Removes all objects from a linked list
 * \param list the linked list to be emptied */
void cc_linked_list_clear(cc_linked_list *list);

/*! \brief Merges two lists together by adding all objects
 * from the first list to the second list.
 * \param a_list the first list
 * \param b_list the second list
 * \returns The lists merged together */
cc_linked_list *cc_linked_list_merge(cc_linked_list *a_list, cc_linked_list *b_list);

bool cc_linked_list_contains(cc_linked_list *list, cc_object *object);
cc_enumerator *cc_linked_list_get_enumerator(cc_linked_list *list);

cc_object *cc_linked_list_to_object(cc_linked_list *list);
cc_linked_list *cc_linked_list_from_object(cc_object *object);

#endif
