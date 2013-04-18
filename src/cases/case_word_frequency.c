#include "../ccollections/shared/cc.h"
#include "../ccollections/cc_dictionary/cc_dictionary.h"

// #define GC_DEBUG
#include "gc/gc.h"
#include <stdio.h>   /* required for file operations */
#include <string.h>


int main(void)
{
  GC_INIT();
  cc_init();

  // key: String (the word)
  // value: int (the frequency)
  cc_dictionary *dict = cc_dictionary_new();


  static const char filename[] = "words.txt";
  FILE *file = fopen ( filename, "r" );
  if ( file != NULL ) {
    char line [ 128 ]; /* or other suitable maximum line size */
    while ( fgets ( line, sizeof line, file ) != NULL ) {
        // fputs ( line, stdout ); /* write the line */
        
        // split the line by whitespace
        char tokens[] = " .,!?";
        char *pch = strtok(line, tokens);
        while (pch != NULL) {
            if (!cc_dictionary_contains_key(dict, pch)) {
                cc_dictionary_add(dict, pch, cc_object_with_int(1));
            } else {
                cc_object *val = cc_dictionary_get(dict, pch);
                int f = cc_object_int_value(val);
                f = f + 1;
                cc_dictionary_add(dict, pch, cc_object_with_int(f));
            }
            pch = strtok(NULL, tokens);
            
        }
        
        // take each word and remove all ,.!?
    }

    cc_enumerator *e = cc_dictionary_get_enumerator(dict);
    while (cc_enumerator_move_next(e)) {
       

    fclose ( file );
  } else {
    perror ( filename ); /* why didn't the file open? */
  }

    return 0;
}