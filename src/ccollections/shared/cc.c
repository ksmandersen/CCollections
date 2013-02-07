#include "cc_private.h"
#include "cc_object_private.h"

void cc_init() {
	cc_object_register_default_comparators();
}
