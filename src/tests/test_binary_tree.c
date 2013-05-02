#include "../ccollections/shared/cc.h"
#include "../lib/unity/src/unity.h"

// void setUp(void)
// {
//   GC_INIT();
//   cc_init();
// }

// void tearDown(void)
// {
	
// }

cc_binary_tree *generate_complicated_binary_tree()
{
	//	        0
	//	       / \
	//	      1   2
	//	     / \ / \
	//	    3  X X  4
	//	   / \     / \
	//	  X   X   5   X
	//	         / \
	//	        X   X
	
	cc_binary_tree *tree0 = cc_binary_tree_new(cc_object_with_int(0));
	cc_binary_tree *tree1 = cc_binary_tree_new(cc_object_with_int(1));
	cc_binary_tree *tree2 = cc_binary_tree_new(cc_object_with_int(2));
	cc_binary_tree *tree3 = cc_binary_tree_new(cc_object_with_int(3));
	cc_binary_tree *tree4 = cc_binary_tree_new(cc_object_with_int(4));
	cc_binary_tree *tree5 = cc_binary_tree_new(cc_object_with_int(5));
	
	cc_binary_tree_set_left_branch(tree0, tree1);
	cc_binary_tree_set_right_branch(tree0, tree2);
	cc_binary_tree_set_left_branch(tree1, tree3);
	cc_binary_tree_set_right_branch(tree2, tree4);
	cc_binary_tree_set_left_branch(tree4, tree5);
	
	return tree0;
}

void test_can_create_binary_tree(void)
{
	cc_binary_tree *tree = cc_binary_tree_new(NULL);
	TEST_ASSERT_NOT_EQUAL(NULL, tree);
}

void test_can_create_binary_tree_with_object(void)
{
	cc_binary_tree *tree = cc_binary_tree_new(cc_object_with_int(123));
	TEST_ASSERT_EQUAL(123, cc_object_int_value(cc_binary_tree_get_object(tree)));
}

void test_can_add_branches(void)
{
	cc_binary_tree *tree = cc_binary_tree_new(cc_object_with_int(0));
	
	cc_binary_tree_set_left_branch(tree, cc_binary_tree_new(cc_object_with_int(1)));
	cc_binary_tree_set_right_branch(tree, cc_binary_tree_new(cc_object_with_int(2)));
	
	TEST_ASSERT_EQUAL(1, cc_object_int_value(cc_binary_tree_get_object(cc_binary_tree_get_left_branch(tree))));
	TEST_ASSERT_EQUAL(2, cc_object_int_value(cc_binary_tree_get_object(cc_binary_tree_get_right_branch(tree))));
}

void test_can_remove_branch(void)
{
	cc_binary_tree *tree = cc_binary_tree_new(cc_object_with_int(0));
	
	cc_binary_tree_set_left_branch(tree, cc_binary_tree_new(cc_object_with_int(1)));
	TEST_ASSERT_EQUAL(1, cc_object_int_value(cc_binary_tree_get_object(cc_binary_tree_get_left_branch(tree))));
	
	cc_binary_tree_set_left_branch(tree, NULL);
	TEST_ASSERT_EQUAL(NULL, cc_binary_tree_get_left_branch(tree));
}

void test_can_enumerate_depth_first(void)
{
	// expected order: 0, 1, 3, 2, 4, 5
	
	cc_binary_tree *tree = generate_complicated_binary_tree();
	
	cc_enumerator *e = cc_binary_tree_get_depth_first_enumerator(tree);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(e), true);
	cc_binary_tree *tree0 = cc_binary_tree_from_object(cc_enumerator_current(e));
	
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(e), true);
	cc_binary_tree *tree1 = cc_binary_tree_from_object(cc_enumerator_current(e));
	
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(e), true);
	cc_binary_tree *tree3 = cc_binary_tree_from_object(cc_enumerator_current(e));
	
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(e), true);
	cc_binary_tree *tree2 = cc_binary_tree_from_object(cc_enumerator_current(e));
	
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(e), true);
	cc_binary_tree *tree4 = cc_binary_tree_from_object(cc_enumerator_current(e));
	
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(e), true);
	cc_binary_tree *tree5 = cc_binary_tree_from_object(cc_enumerator_current(e));
	
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(e), false);
	
	TEST_ASSERT_EQUAL(0, cc_object_int_value(cc_binary_tree_get_object(tree0)));
	TEST_ASSERT_EQUAL(1, cc_object_int_value(cc_binary_tree_get_object(tree1)));
	TEST_ASSERT_EQUAL(2, cc_object_int_value(cc_binary_tree_get_object(tree2)));
	TEST_ASSERT_EQUAL(3, cc_object_int_value(cc_binary_tree_get_object(tree3)));
	TEST_ASSERT_EQUAL(4, cc_object_int_value(cc_binary_tree_get_object(tree4)));
	TEST_ASSERT_EQUAL(5, cc_object_int_value(cc_binary_tree_get_object(tree5)));
}

void test_can_enumerate_breadth_first(void)
{
	// expected order: 0, 1, 2, 3, 4, 5
	
	cc_binary_tree *tree = generate_complicated_binary_tree();
	
	cc_enumerator *e = cc_binary_tree_get_breadth_first_enumerator(tree);
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(e), true);
	cc_binary_tree *tree0 = cc_binary_tree_from_object(cc_enumerator_current(e));
	
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(e), true);
	cc_binary_tree *tree1 = cc_binary_tree_from_object(cc_enumerator_current(e));
	
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(e), true);
	cc_binary_tree *tree2 = cc_binary_tree_from_object(cc_enumerator_current(e));
	
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(e), true);
	cc_binary_tree *tree3 = cc_binary_tree_from_object(cc_enumerator_current(e));
	
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(e), true);
	cc_binary_tree *tree4 = cc_binary_tree_from_object(cc_enumerator_current(e));
	
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(e), true);
	cc_binary_tree *tree5 = cc_binary_tree_from_object(cc_enumerator_current(e));
	
	TEST_ASSERT_EQUAL(cc_enumerator_move_next(e), false);
	
	TEST_ASSERT_EQUAL(0, cc_object_int_value(cc_binary_tree_get_object(tree0)));
	TEST_ASSERT_EQUAL(1, cc_object_int_value(cc_binary_tree_get_object(tree1)));
	TEST_ASSERT_EQUAL(2, cc_object_int_value(cc_binary_tree_get_object(tree2)));
	TEST_ASSERT_EQUAL(3, cc_object_int_value(cc_binary_tree_get_object(tree3)));
	TEST_ASSERT_EQUAL(4, cc_object_int_value(cc_binary_tree_get_object(tree4)));
	TEST_ASSERT_EQUAL(5, cc_object_int_value(cc_binary_tree_get_object(tree5)));
}
