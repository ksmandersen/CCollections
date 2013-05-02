#include "../ccollections/shared/cc.h"
#include "../lib/unity/src/unity.h"

#include <string.h>
#include <stdlib.h>

// void setUp(void)
// {
//   GC_INIT();
//   cc_init();
// }

// void tearDown(void)
// {
  
// }

void test_comparing_different_object_types_gives_error(void) {
  cc_object *int_object = cc_object_with_int(100);
  cc_object *string_object = cc_object_with_string("test");

  cc_object_is_equal(int_object, string_object);

}