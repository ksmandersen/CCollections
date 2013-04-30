/*
 * CC_ENUMERATOR.H
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

#ifndef CC_ENUMERATOR_H
#define CC_ENUMERATOR_H

struct cc_enumerator_struct;
typedef struct cc_enumerator_struct cc_enumerator;

#include "cc_private.h"
#include "cc_object.h"
#include "../cc_linked_list/cc_linked_list.h"

typedef bool (*cc_enumerator_filter_func)(cc_object *obj);
typedef cc_object *(*cc_enumerator_map_func)(cc_object *obj);

cc_object *cc_enumerator_current(cc_enumerator *e);
bool cc_enumerator_move_next(cc_enumerator *e);

cc_enumerator *cc_enumerator_filter(cc_enumerator *e, cc_enumerator_filter_func filter);
cc_enumerator *cc_enumerator_map(cc_enumerator *e, cc_enumerator_map_func map);
cc_enumerator *cc_enumerator_order(cc_enumerator *e);

cc_linked_list *cc_enumerator_to_list(cc_enumerator *e);

#endif
