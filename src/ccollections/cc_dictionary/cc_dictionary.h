#ifndef CC_DICTIONARY_H
#define CC_DICTIONARY_H

#include "../shared/cc_private.h"
#include "../shared/cc_object.h"
#include "../shared/cc_enumerator.h"

extern const char * const cc_dictionary_type;

struct cc_dictionary_struct;
typedef struct cc_dictionary_struct cc_dictionary;

/*! \brief Create a new dictionary data structure
 * \return a new empty dictionary */
cc_dictionary *cc_dictionary_new();

/*! \brief Set an object for a key
 * \param dictionary the dictionary
 * \param key the key
 * \param obj the object to set */
void cc_dictionary_add(cc_dictionary *dictionary, const char *key, cc_object *obj);

/*! \brief Get the object for a key
 * \param dictionary the dictionary
 * \param key the key
 * \return the object associated with the key */
cc_object *cc_dictionary_get(cc_dictionary *dictionary, const char *key);

/*! \brief Removes all objects and keys
 * \param dictionary the dictionary */
void cc_dictionary_clear(cc_dictionary *dictionary);

/*! \brief Returns wether or not a key exists in the dictionary
 * \param dictionary the dictionary
 * \param key the key
 * \return true if the dictionary has an object associated with that key, false otherwise */
bool cc_dictionary_contains_key(cc_dictionary *dictionary, const char *key);

/*! \brief Returns wether or not a value exists in the dictionary
 * \param dictionary the dictionary
 * \param obj the object to look for
 * \return true if the object exists for a key in the dictionary */
bool cc_dictionary_contains_value(cc_dictionary *dictionary, cc_object *obj);

/*! \brief Gets an enumerator for the keys in a dictionary
 * \param dictionary the dictionary
 * \return an enumerator for all keys in the dictionary */
cc_enumerator *cc_dictionary_get_enumerator(cc_dictionary *dictionary);

/*! \brief Removes a key and associated object from a dictionary
 * \param dictionary the dictionary
 * \param key the key */
void cc_dictionary_remove(cc_dictionary *dictionary, const char *key);

/*! \brief Counts the number of keys in the dictionary
 * \param dictionary the dictionary
 * \return the number of keys in the dictionary */
int cc_dictionary_count(cc_dictionary *dictionary);

/*! \brief Gets the dictionary wrapped in a cc_object
 * \param dictionary the dictionary 
 * \return a cc_object */
cc_object *cc_dictionary_to_object(cc_dictionary *dictionary);

/*! \brief Gets the dictionary from a cc_object
 * \param obj the object
 * \return the dictionary */
cc_dictionary *cc_dictionary_from_object(cc_object *obj);

#endif
