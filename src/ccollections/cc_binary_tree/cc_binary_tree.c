/*
 * CC_BINARY_TREE.C
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


#include "cc_binary_tree.h"
#include "../shared/cc_private.h"

const char * const cc_binary_tree_type = "cc_binary_tree_type";

static bool cc_binary_tree_enumerator_move_next(cc_enumerable *c, cc_enumerator *e);
static int cc_binary_tree_compare(cc_object *obj1, cc_object *obj2);
static void cc_binary_tree_register_comparator();

static bool cc_binary_tree_depth_first_enumerator_move_next(cc_enumerable *c, cc_enumerator *e);
static bool cc_binary_tree_breadth_first_enumerator_move_next(cc_enumerable *c, cc_enumerator *e);

struct cc_binary_tree_struct {
	cc_collection c;
	
	cc_object *obj;
	cc_binary_tree *parent;
	cc_binary_tree *left_branch;
	cc_binary_tree *right_branch;
};

typedef struct {
	enum { depth_first, breadth_first } type;
	cc_array_list *bfs_marked_trees;
} cc_binary_tree_enumerator_data;

cc_binary_tree *cc_binary_tree_new(cc_object *obj) {
	// cc_binary_tree_register_comparator();
	
	cc_binary_tree *tree;
	if ((tree = GC_MALLOC(sizeof(cc_binary_tree))) == NULL) {
		return NULL;
	}
	
	tree->c.enumerable.move_next = cc_binary_tree_enumerator_move_next;
	
	tree->parent = NULL;
	tree->obj = obj;
	tree->left_branch = NULL;
	tree->right_branch = NULL;
	
	return tree;
}

cc_object *cc_binary_tree_get_object(cc_binary_tree *tree) {
	return tree->obj;
}

void cc_binary_tree_set_object(cc_binary_tree *tree, cc_object *obj) {
	tree->obj = obj;
}

cc_binary_tree *cc_binary_tree_get_parent(cc_binary_tree *tree) {
	return tree->parent;
}

cc_binary_tree *cc_binary_tree_get_left_branch(cc_binary_tree *tree) {
	return tree->left_branch;
}

void cc_binary_tree_set_left_branch(cc_binary_tree *tree, cc_binary_tree *branch) {
	tree->left_branch = branch;
	if (branch) branch->parent = tree;
}

cc_binary_tree *cc_binary_tree_get_right_branch(cc_binary_tree *tree) {
	return tree->right_branch;
}

void cc_binary_tree_set_right_branch(cc_binary_tree *tree, cc_binary_tree *branch) {
	tree->right_branch = branch;
	branch->parent = tree;
}

cc_object *cc_binary_tree_to_object(cc_binary_tree *tree) {
	return cc_object_with_pointer(tree, cc_binary_tree_type);
}

cc_binary_tree *cc_binary_tree_from_object(cc_object *object) {
	return cc_object_pointer_value(object);
}

cc_enumerator *cc_binary_tree_get_depth_first_enumerator(cc_binary_tree *tree) {
	cc_enumerator *e = cc_enumerator_new(&tree->c.enumerable);
	e->data = GC_MALLOC(sizeof(cc_binary_tree_enumerator_data));
	cc_binary_tree_enumerator_data *edata = (cc_binary_tree_enumerator_data *)e->data;
	edata->type = depth_first;
	return e;
}

cc_enumerator *cc_binary_tree_get_breadth_first_enumerator(cc_binary_tree *tree) {
	cc_enumerator *e = cc_enumerator_new(&tree->c.enumerable);
	e->data = GC_MALLOC(sizeof(cc_binary_tree_enumerator_data));
	cc_binary_tree_enumerator_data *edata = (cc_binary_tree_enumerator_data *)e->data;
	edata->type = breadth_first;
	edata->bfs_marked_trees = cc_array_list_new();
	return e;
}

static bool cc_binary_tree_enumerator_move_next(cc_enumerable *c, cc_enumerator *e) {
	cc_binary_tree_enumerator_data *edata = (cc_binary_tree_enumerator_data *)e->data;
	if (edata->type == depth_first) {
		return cc_binary_tree_depth_first_enumerator_move_next(c, e);
	} else if (edata->type == breadth_first) {
		return cc_binary_tree_breadth_first_enumerator_move_next(c, e);
	}
	
	return false;
}

bool cc_binary_tree_depth_first_enumerator_move_next(cc_enumerable *c, cc_enumerator *e) {
	cc_binary_tree *selected_tree = NULL;
	cc_binary_tree *tree = e->current? cc_binary_tree_from_object(e->current): NULL;
	
	// first call, choose root tree
	if (tree == NULL) {
		selected_tree = (cc_binary_tree *)c;
		goto choose_tree;
	}
	
	// if there's a left branch, choose that
	cc_binary_tree *left_branch = cc_binary_tree_get_left_branch(tree);
	if (left_branch) {
		selected_tree = left_branch;
		goto choose_tree;
	}
	
	// if there's a right branch, choose that
	cc_binary_tree *right_branch = cc_binary_tree_get_right_branch(tree);
	if (right_branch) {
		selected_tree = right_branch;
		goto choose_tree;
	}
	
	// search up through parent nodes to find a right branch
	cc_binary_tree *parent = tree;
	cc_binary_tree *prev = tree;
	while ((parent = cc_binary_tree_get_parent(parent)) != NULL) {
		cc_binary_tree *right_branch = cc_binary_tree_get_right_branch(parent);
		
		if (right_branch && right_branch != prev) {
			selected_tree = right_branch;
			goto choose_tree;
		}
		
		prev = parent;
	}
	
	// we're at the end of the tree
	return false;
	
	// choose the selected tree
	choose_tree: {
		e->current = cc_binary_tree_to_object(selected_tree);
		return true;
	}
}

bool cc_binary_tree_breadth_first_enumerator_move_next(cc_enumerable *c, cc_enumerator *e) {
	cc_binary_tree_enumerator_data *edata = (cc_binary_tree_enumerator_data *)e->data;
	cc_binary_tree *selected_tree = NULL;
	cc_array_list *marked = edata->bfs_marked_trees;
	
	// first call, choose root tree
	if (e->current == NULL) {
		selected_tree = (cc_binary_tree *)c;
		goto choose_tree;
	}
	
	// choose next marked tree
	if (cc_array_list_length(marked) > 0) {
		cc_binary_tree *tree = cc_binary_tree_from_object(cc_array_list_get_first(marked));
		cc_array_list_remove_first(marked);
		selected_tree = tree;
		goto choose_tree;
	}
	
	// we're at the end of the tree
	return false;
	
	// choose the selected tree and mark all branches
	choose_tree: {
		e->current = cc_binary_tree_to_object(selected_tree);
		
		cc_binary_tree *left_branch = cc_binary_tree_get_left_branch(selected_tree);
		cc_binary_tree *right_branch = cc_binary_tree_get_right_branch(selected_tree);
		
		if (left_branch) cc_array_list_add_last(marked, cc_binary_tree_to_object(left_branch));
		if (right_branch) cc_array_list_add_last(marked, cc_binary_tree_to_object(right_branch));
		
		return true;
	}
}

int cc_binary_tree_compare(cc_object *obj1, cc_object *obj2) {
	cc_binary_tree *tree1 = cc_binary_tree_from_object(obj1);
	cc_binary_tree *tree2 = cc_binary_tree_from_object(obj2);
	
	cc_enumerator *e1 = cc_binary_tree_get_depth_first_enumerator(tree1);
	cc_enumerator *e2 = cc_binary_tree_get_depth_first_enumerator(tree2);
	
	while (true) {
		bool e1_has_next = cc_enumerator_move_next(e1);
		bool e2_has_next = cc_enumerator_move_next(e2);
		
		if (e1_has_next && !e2_has_next) {
			return -1;
		} else if (!e1_has_next && e2_has_next) {
			return 1;
		}
		
		int diff = cc_object_compare(cc_enumerator_current(e1), cc_enumerator_current(e2));
		if (diff != 0) {
			return diff;
		}
	}
	
	return 0;
}

void cc_binary_tree_register_comparator() {
	static bool first = true;
	
	if (first) {
		first = false;
		cc_object_register_comparator_for_type(cc_binary_tree_type, cc_binary_tree_compare);
	}
}
