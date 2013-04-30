/*
 * CC_DICTIONARY.H
 * 
 * This file is part of the CCollections library.
 *
 * CCollections is licensed under the BSD-2-Clause License (FreeBSD).
 * Copyright (c) 2012, Ulrik Damm and Kristian Andersen.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met:
 *
 * Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer. Redistributions 
 * in binary form must reproduce the above copyright notice, this list 
 * of conditions and the following disclaimer in the documentation and/or 
 * other materials provided with the distribution. THIS SOFTWARE IS 
 * PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


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

/*! \brief Creates a new dictionary with all objects from the enumerator
 * \param key_enumerator the enumerator of a collection of keys for the dictionary
 * \param object_enumerator the enumerator of a collection of objects for the dictionary
 * \return A new dictionary object */
cc_dictionary *cc_dictionary_new_with_enumerators(cc_enumerator *key_enumerator, cc_enumerator *object_enumerator);

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
