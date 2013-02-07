#include "../ccollections/linked_list/linked_list.h"
#include "../lib/unity/src/unity.h"

#define GC_DEBUG
#include "gc/gc.h"

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
  // free(list);
}

void test_can_add_objects_to_linked_list(void)
{
  linked_list_t *list = create_linked_list();

  int i;
  for(i = 0; i < 1000000000; i++)
  {
    int *val = GC_MALLOC(sizeof(int));
    val = i * 10;
    insert_last(list, val);

    if (i % 100 == 0)
    {
      empty_linked_list(list);
    }
  }

  destroy_linked_list(list);
}