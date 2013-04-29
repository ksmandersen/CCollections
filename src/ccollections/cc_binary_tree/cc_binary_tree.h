/*
 * CC_BINARY_TREE.H
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


#ifndef CC_BINARY_TREE_H
#define CC_BINARY_TREE_H

#include "../shared/cc.h"

extern const char * const cc_binary_tree_type;

struct cc_binary_tree_struct;
typedef struct cc_binary_tree_struct cc_binary_tree;

/*! \brief Create a binary tree object
 * \return A new binary tree object */
cc_binary_tree *cc_binary_tree_new(cc_object *obj);

/*! \brief Get the parent tree of a binary tree
 * \param tree the binary tree
 * \return the tree's parent tree */
cc_binary_tree *cc_binary_tree_get_parent(cc_binary_tree *tree);

/*! \brief Get the object associated with the tree
 * \param tree the tree
 * \return the object associated with the tree */
cc_object *cc_binary_tree_get_object(cc_binary_tree *tree);

/*! \brief Associate an object with the tree
 * \param tree the tree
 * \param obj the object to assocate */
void cc_binary_tree_set_object(cc_binary_tree *tree, cc_object *obj);

/*! \brief Gets the left branch of the tree
 * \param tree the tree
 * \return the left branch of the tree */
cc_binary_tree *cc_binary_tree_get_left_branch(cc_binary_tree *tree);

/*! \brief Sets the left branch of the tree
 * \param tree the tree
 * \param branch the branch tree to set as the left branch */
void cc_binary_tree_set_left_branch(cc_binary_tree *tree, cc_binary_tree *branch);

/*! \brief Gets the right branch of the tree
 * \param tree the tree
 * \return the right branch of the tree */
cc_binary_tree *cc_binary_tree_get_right_branch(cc_binary_tree *tree);

/*! \brief Sets the right branch of the tree
 * \param tree the tree
 * \param branch the branch tree to set as the right branch */
void cc_binary_tree_set_right_branch(cc_binary_tree *tree, cc_binary_tree *branch);

/*! \brief Get an enumerator that loops through all the subtrees depth-first
 * \param tree the tree
 * \return the enumerator */
cc_enumerator *cc_binary_tree_get_depth_first_enumerator(cc_binary_tree *tree);

/*! \brief Get an enumerator that loops through all the subtrees breadth-first
 * \param tree the tree
 * \return the enumerator */
cc_enumerator *cc_binary_tree_get_breadth_first_enumerator(cc_binary_tree *tree);

/*! \brief Get the tree wrapped in a cc_object
 * \param tree the tree
 * \return the cc_object */
cc_object *cc_binary_tree_to_object(cc_binary_tree *tree);

/*! \brief Get the tree from a cc_object
 * \param object the cc_object
 * \return the tree */
cc_binary_tree *cc_binary_tree_from_object(cc_object *object);

#endif