/*
 * CC_QUEUE.H
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

#ifndef CC_QUEUE_H
#define CC_QUEUE_H

#include "../shared/cc.h"

struct cc_queue_struct;
typedef struct cc_queue_struct cc_queue;

/*! \brief Create a queue data structure
 * \return A new empty queue */
cc_queue *cc_queue_new();

/*! \brief Add an object to the queue
 * \param queue the queue
 * \param obj the object to add */
void cc_queue_enqueue(cc_queue *queue, cc_object *obj);

/*! \brief Remove the first object of the queue
 * \param queue the queue
 * \return the removed object */
cc_object *cc_queue_dequeue(cc_queue *queue);

/*! \brief Get the first item in the queue
 * \param queue the queue
 * \return the first object in the queue */
cc_object *cc_queue_peek(cc_queue *queue);

/*! \brief Count the number of objects in the queue
 * \param queue the queue
 * \return the number of objects in the queue */
int cc_queue_count(cc_queue *queue);

/*! \brief Remove all objects from the queue
 * \param queue the queue */
void cc_queue_clear(cc_queue *queue);

/*! \brief Returns wether or not an object is in the queue
 * \param queue the queue
 * \param obj the object to search for
 * \return true if the object exists in the queue, false otherwise */
bool cc_queue_contains(cc_queue *queue, cc_object *obj);

/*! \brief Gets an enumerator for the elements in the queue
 * \param queue the queue
 * \return an enumerator, going from the beginning to the end */
cc_enumerator *cc_queue_get_enumerator(cc_queue *queue);

/*! \brief Get the queue wrapped in a cc_object
 * \param queue the queue
 * \return the cc_object */
cc_object *cc_queue_to_object(cc_queue *queue);

/*! \brief Get the queue from a cc_object
 * \param object the object
 * \return the queue */
cc_queue *cc_queue_from_object(cc_object *object);

static void cc_queue_register_comparator();

#endif