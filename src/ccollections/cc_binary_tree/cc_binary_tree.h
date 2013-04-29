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