#ifndef CC_BINARY_TREE_H
#define CC_BINARY_TREE_H

#include "../shared/cc.h"

struct cc_binary_tree_struct;
typedef struct cc_binary_tree_struct cc_binary_tree;

cc_binary_tree *cc_binary_tree_new(cc_object *obj);

cc_binary_tree *cc_binary_tree_get_parent(cc_binary_tree *tree);

cc_object *cc_binary_tree_get_object(cc_binary_tree *tree);
void cc_binary_tree_set_object(cc_binary_tree *tree, cc_object *obj);

cc_binary_tree *cc_binary_tree_get_left_branch(cc_binary_tree *tree);
void cc_binary_tree_set_left_branch(cc_binary_tree *tree, cc_binary_tree *branch);

cc_binary_tree *cc_binary_tree_get_right_branch(cc_binary_tree *tree);
void cc_binary_tree_set_right_branch(cc_binary_tree *tree, cc_binary_tree *branch);

cc_enumerator *cc_binary_tree_get_depth_first_enumerator(cc_binary_tree *tree);
cc_enumerator *cc_binary_tree_get_breadth_first_enumerator(cc_binary_tree *tree);

cc_object *cc_binary_tree_to_object(cc_binary_tree *tree);
cc_binary_tree *cc_binary_tree_from_object(cc_object *object);

#endif