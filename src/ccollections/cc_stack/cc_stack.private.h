/*
 * CC_ARRAY_LIST.PRIVATE.H
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

#ifndef CC_STACK_PRIVATE_H
#define CC_STACK_PRIVATE_H

#include "cc_stack.h"
#include "../shared/cc_enumerator_private.h"

// Enumerator & comperator
extern void cc_stack_register_comparator();
extern bool cc_stack_enumerator_move_next(cc_enumerable *c, cc_enumerator *e);

// Compare two stacks agains each other.
// This function doesn't make a lot of sense since it's not
// good design to say that a stack is smaller or bigger than
// another list apart from size.
// The function is used for determining whether two stacks are
// equal (i.e. contains all ofthe same elements).
int cc_stack_compare(cc_object *obj1, cc_object *obj2);

#endif


