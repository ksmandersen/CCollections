/*
 * CC_STACK.H
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

#ifndef CC_STACK_H
#define CC_STACK_H

#include "../shared/cc_private.h"
#include "../shared/cc_object.h"
#include "../shared/cc_enumerator.h"

extern const char * const cc_stack_type;

struct cc_stack_struct;
typedef struct cc_stack_struct cc_stack;

/*! \brief Creates a new empty stack
 * \return A new empty stack */
cc_stack *cc_stack_new();

/*! \brief Pushes a given object to on to the top of a given stack
 * \param stack the stack
 * \param obj the object */
void cc_stack_push(cc_stack *stack, cc_object *obj);

/*! \brief Pops the top-most object from the given stack
 * \return the top-most object that has been popped from the stack */
cc_object *cc_stack_pop(cc_stack *stack);

/*! \brief Peeks at the top-most object on a given stack
 * \return the top-most object on the stack */
cc_object *cc_stack_peek(cc_stack *stack);

/*! \brief Get the size of a given stack
 * \return The size of the stack */
int cc_stack_size(cc_stack *stack);

/*! \brief Removes all the objects from a given stack */
void cc_stack_clear(cc_stack *stack);

/*! \brief Get an enumerator for an instance of a stack
 * \param stack the stack
 * \returns an enumerator for the stack */
cc_enumerator *cc_stack_get_enumerator(cc_stack *stack);

/*! \brief Determines whether two stacks are equal
 * \param a_stack the first stack
 * \param b_stack the second stack
 * \returns true if the two stacks are equal to eachother; otherwise, false */
bool cc_stack_equals(cc_stack *a_stack, cc_stack *b_stack);

/*! \brief Determines whether an object is on the stack
 * \param stack the stack to search
 * \param object the object to search the stack for
 * \returns true if the object is found on the stack; otherwise, false */
bool cc_stack_contains(cc_stack *stack, cc_object *obj);

/*! \brief Make a cc_object from a given stack
 * \param stack the stack */
cc_object *cc_stack_to_object(cc_stack *stack);

/*! \brief Make a stack from a cc_object
 * \param object the object */
cc_stack *cc_stack_from_object(cc_object *obj);

#endif
