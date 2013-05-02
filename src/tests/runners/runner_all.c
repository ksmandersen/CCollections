#include "../../lib/unity/src/unity.h"
#include <stdio.h>
#include <setjmp.h>

// #ifndef CG_DEBUG
#define GC_DEBUG

#import <gc/gc.h>
#import "../../ccollections/shared/cc.h"

// ============== ARRAY LIST ============== //

extern void test_can_create_array_list(void);

extern void test_can_add_objects_to_end_of_array_list(void);
extern void test_can_add_objects_to_array_list_with_index(void);
extern void test_can_add_objects_to_front_of_array_list(void);
extern void test_can_add_and_get_identical_objects_from_array_list(void);
extern void test_can_add_and_get_many_objects_from_array_list(void);

extern void test_can_get_objects_from_array_list_with_index(void);
extern void test_can_get_elements_from_start_of_array_list(void);
extern void test_can_get_elements_from_end_of_array_list(void);
extern void test_getting_object_from_array_list_empty_array_list_returns_null(void);

extern void test_can_remove_object_from_array_list_with_index(void);
extern void test_can_remove_object_from_front_of_array_list(void);
extern void test_can_remove_object_from_end_of_array_list(void);
extern void test_removing_non_existing_index_from_array_list_does_nothing(void);

extern void test_can_merge_array_lists_together(void);
extern void test_can_merge_empty_array_list_with_non_empty_array_list(void);
extern void test_can_merge_empty_array_lists(void);

extern void test_can_clear_array_list(void);

extern void test_can_array_list_compare_equal(void);
extern void test_can_array_list_compare_non_equal(void);
extern void test_can_empty_array_list_compare_equal(void);

extern void test_can_enumerate_array_list(void);

extern void test_can_find_contained_objects_in_array_list(void);
extern void test_cannot_find_object_in_array_list_without_object(void);
extern void test_cannot_find_object_in_empty_array_list(void);

extern void test_can_shuffle_array_with_objects(void);
extern void test_can_sort_array_with_objects(void);

extern void test_can_create_cc_object_from_array_list(void);
extern void test_can_create_array_list_from_cc_object(void);

void test_array_list() {
  printf("-----------------------\nARRAY LIST TEST\n-----------------------\n");

  RUN_TEST(test_can_create_array_list, 1);

  RUN_TEST(test_can_add_objects_to_end_of_array_list, 1);
  RUN_TEST(test_can_add_objects_to_array_list_with_index, 1);
  RUN_TEST(test_can_add_objects_to_front_of_array_list, 1);
  RUN_TEST(test_can_add_and_get_identical_objects_from_array_list, 1);
  RUN_TEST(test_can_add_and_get_many_objects_from_array_list, 1);

  RUN_TEST(test_can_get_objects_from_array_list_with_index, 1);
  RUN_TEST(test_can_get_elements_from_start_of_array_list, 1);
  RUN_TEST(test_can_get_elements_from_end_of_array_list, 1);
  RUN_TEST(test_getting_object_from_array_list_empty_array_list_returns_null, 1);

  RUN_TEST(test_can_remove_object_from_array_list_with_index, 1);
  RUN_TEST(test_can_remove_object_from_front_of_array_list, 1);
  RUN_TEST(test_can_remove_object_from_end_of_array_list, 1);
  RUN_TEST(test_removing_non_existing_index_from_array_list_does_nothing, 1);

  RUN_TEST(test_can_merge_array_lists_together, 1);
  RUN_TEST(test_can_merge_empty_array_list_with_non_empty_array_list, 1);
  RUN_TEST(test_can_merge_empty_array_lists, 1);

  RUN_TEST(test_can_clear_array_list, 1);

  RUN_TEST(test_can_array_list_compare_equal, 1);
  RUN_TEST(test_can_array_list_compare_non_equal, 1);
  RUN_TEST(test_can_empty_array_list_compare_equal, 1);
  
  RUN_TEST(test_can_enumerate_array_list, 1);

  RUN_TEST(test_can_find_contained_objects_in_array_list, 1);
  RUN_TEST(test_cannot_find_object_in_array_list_without_object, 1);
  RUN_TEST(test_cannot_find_object_in_empty_array_list, 1);

  RUN_TEST(test_can_shuffle_array_with_objects, 1);
  RUN_TEST(test_can_sort_array_with_objects, 1);

  RUN_TEST(test_can_create_cc_object_from_array_list, 1);
  RUN_TEST(test_can_create_array_list_from_cc_object, 1);
}

// ========================================= //

// ============== LINKED LIST ============== //

extern void test_can_create_linked_list(void);

extern void test_can_add_objects_to_end_of_linked_list(void);
extern void test_can_add_objects_to_linked_list_with_index(void);
extern void test_can_add_objects_to_front_of_linked_list(void);
extern void test_can_add_and_get_identical_objects_from_linked_list(void);
extern void test_can_add_and_get_many_objects_from_linked_list(void);
extern void test_can_create_linked_linked_list_from_array_list(void);

extern void test_can_get_objects_from_linked_list_with_index(void);
extern void test_can_get_elements_from_start_of_linked_list(void);
extern void test_can_get_elements_from_end_of_linked_list(void);
extern void test_getting_object_from_linked_list_empty_linked_list_returns_null(void);

extern void test_can_remove_object_from_linked_list_with_index(void);
extern void test_can_remove_object_from_front_of_linked_list(void);
extern void test_can_remove_object_from_end_of_linked_list(void);
extern void test_removing_non_existing_index_from_linked_list_does_nothing(void);

extern void test_can_merge_linked_lists_together(void);
extern void test_can_merge_empty_linked_list_with_non_empty_linked_list(void);
extern void test_can_merge_empty_linked_lists(void);

extern void test_can_clear_linked_list(void);

extern void test_can_linked_list_compare_equal(void);
extern void test_can_linked_list_compare_non_equal(void);
extern void test_can_empty_linked_list_compare_equal(void);

extern void test_can_enumerate_linked_list(void);

extern void test_can_find_contained_objects_in_linked_list(void);
extern void test_cannot_find_object_in_linked_list_without_object(void);
extern void test_cannot_find_object_in_empty_linked_list(void);

extern void test_can_create_cc_object_from_linked_list(void);
extern void test_can_create_linked_list_from_cc_object(void);

extern void test_can_create_linked_list_with_ints_from_args(void);
extern void test_can_create_linked_list_with_floats_from_args(void);
extern void test_can_create_linked_list_with_strings_from_args(void);

void test_linked_list() {
  printf("-----------------------\nLINKED LIST TEST\n-----------------------\n");

  RUN_TEST(test_can_create_linked_list, 1);

  RUN_TEST(test_can_add_objects_to_end_of_linked_list, 1);
  RUN_TEST(test_can_add_objects_to_linked_list_with_index, 1);
  RUN_TEST(test_can_add_objects_to_front_of_linked_list, 1);
  RUN_TEST(test_can_add_and_get_identical_objects_from_linked_list, 1);
  RUN_TEST(test_can_add_and_get_many_objects_from_linked_list, 1);
  RUN_TEST(test_can_create_linked_linked_list_from_array_list, 1);

  RUN_TEST(test_can_get_objects_from_linked_list_with_index, 1);
  RUN_TEST(test_can_get_elements_from_start_of_linked_list, 1);
  RUN_TEST(test_can_get_elements_from_end_of_linked_list, 1);
  RUN_TEST(test_getting_object_from_linked_list_empty_linked_list_returns_null, 1);

  RUN_TEST(test_can_remove_object_from_linked_list_with_index, 1);
  RUN_TEST(test_can_remove_object_from_front_of_linked_list, 1);
  RUN_TEST(test_can_remove_object_from_end_of_linked_list, 1);
  RUN_TEST(test_removing_non_existing_index_from_linked_list_does_nothing, 1);

  RUN_TEST(test_can_merge_linked_lists_together, 1);
  RUN_TEST(test_can_merge_empty_linked_list_with_non_empty_linked_list, 1);
  RUN_TEST(test_can_merge_empty_linked_lists, 1);

  RUN_TEST(test_can_clear_linked_list, 1);

  RUN_TEST(test_can_linked_list_compare_equal, 1);
  RUN_TEST(test_can_linked_list_compare_non_equal, 1);
  RUN_TEST(test_can_empty_linked_list_compare_equal, 1);
  
  RUN_TEST(test_can_enumerate_linked_list, 1);

  RUN_TEST(test_can_find_contained_objects_in_linked_list, 1);
  RUN_TEST(test_cannot_find_object_in_linked_list_without_object, 1);
  RUN_TEST(test_cannot_find_object_in_empty_linked_list, 1);

  RUN_TEST(test_can_create_cc_object_from_linked_list, 1);
  RUN_TEST(test_can_create_linked_list_from_cc_object, 1);
  
  RUN_TEST(test_can_create_linked_list_with_ints_from_args, 1);
  RUN_TEST(test_can_create_linked_list_with_floats_from_args, 1);
  RUN_TEST(test_can_create_linked_list_with_strings_from_args, 1);
}

// ========================================= //

// ============== DICTIONARY =============== //

extern void test_can_create_dictionary(void);
extern void test_can_add_object_to_dictionary(void);
extern void test_can_set_value_for_key_in_dictionary(void);
extern void test_can_change_value_for_key(void);
extern void test_can_find_key_in_dictionary(void);
extern void test_can_enumerate_keys_in_dictionary(void);
extern void test_can_insert_and_enumerate_many_objects(void);
extern void test_can_create_dictionary_from_key_and_value_enumerators(void);

void test_dictionary() {
  printf("-----------------------\nDICTIONARY TEST\n-----------------------\n");

  RUN_TEST(test_can_create_dictionary, 1);
  RUN_TEST(test_can_add_object_to_dictionary, 1);
  RUN_TEST(test_can_set_value_for_key_in_dictionary, 1);
  RUN_TEST(test_can_change_value_for_key, 1);
  RUN_TEST(test_can_find_key_in_dictionary, 1);
  RUN_TEST(test_can_enumerate_keys_in_dictionary, 1);
  RUN_TEST(test_can_insert_and_enumerate_many_objects, 1);
  RUN_TEST(test_can_create_dictionary_from_key_and_value_enumerators, 1);
}

// ========================================= //

// ============== BINARY TREE ============== //

extern void test_can_create_binary_tree(void);
extern void test_can_create_binary_tree_with_object(void);
extern void test_can_add_branches(void);
extern void test_can_remove_branch(void);
extern void test_can_enumerate_depth_first(void);
extern void test_can_enumerate_breadth_first(void);

void test_binary_tree() {
  printf("-----------------------\nBINARY TREE TEST\n-----------------------\n");

  RUN_TEST(test_can_create_binary_tree, 1);
  RUN_TEST(test_can_create_binary_tree_with_object, 2);
  RUN_TEST(test_can_add_branches, 3);
  RUN_TEST(test_can_remove_branch, 4);
  RUN_TEST(test_can_enumerate_depth_first, 5);
  RUN_TEST(test_can_enumerate_breadth_first, 6);
}

// ========================================= //

// ================= QUEUE ================= //

extern void test_can_create_queue(void);
extern void test_can_add_objects_to_queue(void);
extern void test_can_dequeue_objects_from_queue(void);
extern void test_can_peek_at_queue(void);
extern void test_can_clear_queue(void);
extern void test_queue_contains_object(void);

void test_queue() {
  printf("-----------------------\nQUEUE TEST\n-----------------------\n");

  RUN_TEST(test_can_create_queue, 1);
  RUN_TEST(test_can_add_objects_to_queue, 1);
  RUN_TEST(test_can_dequeue_objects_from_queue, 1);
  RUN_TEST(test_can_peek_at_queue, 1);
  RUN_TEST(test_can_clear_queue, 1);
  RUN_TEST(test_queue_contains_object, 1);
}


// ========================================= //

// ================== SET ================== //

extern void test_can_create_set(void);
extern void test_can_add_object_to_set(void);
extern void test_can_enumerate_objects_in_set(void);
extern void test_can_find_contained_objects_in_set(void);
extern void test_cannot_find_uncontained_objects_in_set(void);
extern void test_can_remove_objects_from_set(void);
extern void test_set_only_contains_unique_objects(void);
extern void test_can_insert_many_objects(void);

void test_set() {
  printf("-----------------------\nSET TEST\n-----------------------\n");

  RUN_TEST(test_can_create_set, 1);
  RUN_TEST(test_can_add_object_to_set, 1);
  RUN_TEST(test_can_enumerate_objects_in_set, 1);
  RUN_TEST(test_can_find_contained_objects_in_set, 1);
  RUN_TEST(test_cannot_find_uncontained_objects_in_set, 1);
  RUN_TEST(test_can_remove_objects_from_set, 1);
  RUN_TEST(test_set_only_contains_unique_objects, 1);
  RUN_TEST(test_can_insert_many_objects, 1);
}

// ========================================= //

// ================= STACK ================= //

extern void test_can_create_stack(void);
extern void test_can_add_objects_to_stack(void);
extern void test_can_peek_at_objects_on_stack(void);
extern void test_can_pop_objects_from_stack(void);
extern void test_can_clear_stack(void);
extern void test_can_enumerate_stack(void);
extern void test_can_push_and_pop_many_objects(void);
extern void test_peek_on_empty_stack_returns_null(void);
extern void test_pop_on_empty_stack_returns_null(void);
extern void test_move_next_on_empty_stack_returns_null(void);
extern void test_size_on_empty_stack_is_zero(void);
extern void test_can_create_cc_object_from_stack(void);
extern void test_can_create_stack_from_cc_object(void);
extern void test_can_determine_if_stacks_are_equal(void);
extern void test_can_determine_if_stacks_are_unequal(void);
extern void test_can_determine_if_empty_stacks_are_equal(void);
extern void test_can_determine_stack_contains_object(void);
extern void test_can_determine_stack_does_not_contain_object(void);
extern void test_can_determine_empty_stack_does_not_contain_object(void);

void test_stack() {
  printf("-----------------------\nSTACK TEST\n-----------------------\n");

  RUN_TEST(test_can_create_stack, 1);
  RUN_TEST(test_can_add_objects_to_stack, 1);
  RUN_TEST(test_can_peek_at_objects_on_stack, 1);
  RUN_TEST(test_can_pop_objects_from_stack, 1);
  RUN_TEST(test_can_clear_stack, 1);
  RUN_TEST(test_can_enumerate_stack, 1);
  RUN_TEST(test_can_push_and_pop_many_objects, 1);
  RUN_TEST(test_peek_on_empty_stack_returns_null, 1);
  RUN_TEST(test_pop_on_empty_stack_returns_null, 1);
  RUN_TEST(test_move_next_on_empty_stack_returns_null, 1);
  RUN_TEST(test_size_on_empty_stack_is_zero, 1);
  RUN_TEST(test_can_create_cc_object_from_stack, 1);
  RUN_TEST(test_can_create_stack_from_cc_object, 1);
  RUN_TEST(test_can_determine_if_stacks_are_equal, 1);
  RUN_TEST(test_can_determine_if_stacks_are_unequal, 1);
  RUN_TEST(test_can_determine_if_empty_stacks_are_equal, 1);
  RUN_TEST(test_can_determine_stack_contains_object, 1);
  RUN_TEST(test_can_determine_stack_does_not_contain_object, 1);
  RUN_TEST(test_can_determine_empty_stack_does_not_contain_object, 1);
}

// ========================================= //

// =============== ENUMERATOR ============== //

extern void test_can_create_enumerator(void);
extern void test_enumerator_can_enumerate(void);
extern void test_enumerator_can_filter(void);
extern void test_enumerator_can_sort(void);
extern void test_enumerator_can_enumerate(void);
extern void test_enumerator_can_map(void);
extern void test_enumerator_can_stack_enumerators(void);
extern void test_can_convert_enumerator_to_list(void);

void test_enumerator() {
  printf("-----------------------\nENUMERATOR TEST\n-----------------------\n");

  RUN_TEST(test_can_create_enumerator, 1);
  RUN_TEST(test_enumerator_can_enumerate, 2);
  RUN_TEST(test_enumerator_can_filter, 3);
  RUN_TEST(test_enumerator_can_sort, 4);
  RUN_TEST(test_enumerator_can_enumerate, 5);
  RUN_TEST(test_enumerator_can_map, 6);
  RUN_TEST(test_enumerator_can_stack_enumerators, 7);
  RUN_TEST(test_can_convert_enumerator_to_list, 8);
}

// ========================================= //

// =============== OBJECT ============== //

extern void test_can_create_string_object(void);
extern void test_can_create_float_object(void);
extern void test_can_create_int_object(void);
extern void test_can_create_data_object(void);
extern void test_can_create_string_object_from_stack(void);
extern void test_can_create_data_object_from_stack(void);
extern void test_string_object_has_string_type(void);
extern void test_int_object_has_int_type(void);
extern void test_float_object_has_float_type(void);
extern void test_data_object_has_custom_type(void);
extern void test_different_object_types_does_not_equal(void);
extern void test_same_string_objects_equals(void);
extern void test_different_string_objects_does_not_equal(void);
extern void test_same_int_objects_equals(void);
extern void test_different_int_objects_does_not_equal(void);
extern void test_same_float_objects_equals(void);
extern void test_different_float_objects_does_not_equal(void);
extern void test_same_custom_data_equals(void);
extern void test_different_custom_data_does_not_equal(void);
extern void test_can_get_string_hash(void);
extern void test_can_get_custom_hash(void);

void test_object() {
  printf("-----------------------\nOBJECT TEST\n-----------------------\n");

  RUN_TEST(test_can_create_string_object, 1);
  RUN_TEST(test_can_create_float_object, 2);
  RUN_TEST(test_can_create_int_object, 3);
  RUN_TEST(test_can_create_data_object, 4);
  RUN_TEST(test_can_create_string_object_from_stack, 5);
  RUN_TEST(test_can_create_data_object_from_stack, 6);
  RUN_TEST(test_string_object_has_string_type, 7);
  RUN_TEST(test_int_object_has_int_type, 8);
  RUN_TEST(test_float_object_has_float_type, 9);
  RUN_TEST(test_data_object_has_custom_type, 10);
  RUN_TEST(test_different_object_types_does_not_equal, 11);
  RUN_TEST(test_same_string_objects_equals, 12);
  RUN_TEST(test_different_string_objects_does_not_equal, 13);
  RUN_TEST(test_same_int_objects_equals, 14);
  RUN_TEST(test_different_int_objects_does_not_equal, 15);
  RUN_TEST(test_same_float_objects_equals, 16);
  RUN_TEST(test_different_float_objects_does_not_equal, 17);
  RUN_TEST(test_same_custom_data_equals, 18);
  RUN_TEST(test_different_custom_data_does_not_equal, 19);
  RUN_TEST(test_can_get_string_hash, 20);
  RUN_TEST(test_can_get_custom_hash, 21);
  RUN_TEST(test_can_create_string_object, 22);
}


void setUp(void) {}
void tearDown(void) {}

static void runTest(UnityTestFunction test)
{
  if (TEST_PROTECT())
  {
    // setUp();
    test();
  }

  if (TEST_PROTECT() && !TEST_IS_IGNORED)
  {
    // tearDown();
  }
}

void resetTest()
{
  tearDown();
  setUp();
}

int main(void)
{
  cc_init();

  UnityBegin();

  setUp();
  
  test_array_list();
  test_linked_list();
  test_dictionary();
  test_binary_tree();
  test_queue();
  test_set();
  test_stack();
  test_enumerator();
  test_object();

  tearDown();

  UnityEnd();

  return 0;
}