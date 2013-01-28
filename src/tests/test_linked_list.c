#include "../ccollections/linked_list/linked_list.h"
#include "../lib/unity/src/unity.h"

// extern linked_list_t *list;

void setUp(void)
{
  // list = create_linked_list();
}

void tearDown(void)
{
  // free(list);
}

void test_can_create_linked_list(void)
{
  linked_list_t *list = create_linked_list();
  TEST_ASSERT_NOT_EQUAL(NULL, list);
  free(list);
}