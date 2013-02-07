#include "cc.h"
#include <stdio.h>

int main(void) {
	GC_INIT();
	cc_init();
	
	cc_set *set = cc_set_new();
	cc_set_add(set, cc_object_with_string("object 1"));
	cc_set_add(set, cc_object_with_string("object 2"));
	cc_set_add(set, cc_object_with_string("object 3"));
	
	cc_set *set2 = cc_set_new();
	cc_set_add(set2, cc_object_with_string("object 1"));
	cc_set_add(set2, cc_object_with_string("object 2"));
	cc_set_add(set2, cc_object_with_string("object 4"));
	
	if (cc_object_is_equal(cc_set_to_object(set), cc_set_to_object(set2))) {
		printf("Equal :D\n");
	} else {
		printf("Not equal :(\n");
	}
	
	return 0;
}
