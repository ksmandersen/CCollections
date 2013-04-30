/*
 * CC.H
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

#ifndef CC_H
#define CC_H

#include <stdbool.h>
#include <gc/gc.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "cc_error.h"
#include "cc_object.h"

#include "../cc_array_list/cc_array_list.h"
#include "../cc_set/cc_set.h"
#include "../cc_linked_list/cc_linked_list.h"
#include "../cc_dictionary/cc_dictionary.h"
#include "../cc_binary_tree/cc_binary_tree.h"
#include "../cc_sorted_list/cc_sorted_list.h"
#include "../cc_stack/cc_stack.private.h"
#include "../cc_queue/cc_queue.h"

void cc_init();

#endif
