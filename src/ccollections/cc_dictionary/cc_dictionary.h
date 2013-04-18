#ifndef CC_DICTIONARY_H
#define CC_DICTIONARY_H

#include "../shared/cc_private.h"
#include "../shared/cc_object.h"
#include "../shared/cc_enumerator.h"

extern const char * const cc_dictionary_type;

struct cc_dictionary_struct;
typedef struct cc_dictionary_struct cc_dictionary;

cc_dictionary *cc_dictionary_new();
void cc_dictionary_add(cc_dictionary *dictionary, const char *key, cc_object *obj);
cc_object *cc_dictionary_get(cc_dictionary *dictionary, const char *key);
void cc_dictionary_clear(cc_dictionary *dictionary);
bool cc_dictionary_contains_key(cc_dictionary *dictionary, const char *key);
bool cc_dictionary_contains_value(cc_dictionary *dictionary, cc_object *obj);
cc_enumerator *cc_dictionary_get_enumerator(cc_dictionary *dictionary);
void cc_dictionary_remove(cc_dictionary *dictionary, const char *key);
int cc_dictionary_count(cc_dictionary *dictionary);

cc_object *cc_dictionary_to_object(cc_set *set);
cc_dictionary *cc_dictionary_from_object(cc_object *obj);

#endif
