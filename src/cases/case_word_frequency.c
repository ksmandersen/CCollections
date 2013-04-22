#include "../ccollections/shared/cc.h"
#include "../ccollections/cc_dictionary/cc_dictionary.h"

// #define GC_DEBUG
#include "gc/gc.h"
#include <stdio.h>   /* required for file operations */
#include <string.h>

void string_to_lower(char *str) {
    int i;
    for (i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void choppy( char *s )
{
    s[strcspn ( s, "\n" )] = '\0';
    s[strcspn ( s, "\r" )] = '\0';
}

int main(void)
{
  GC_INIT();
  cc_init();

  // key: String (the word)
  // value: int (the frequency)
  cc_dictionary *dict = cc_dictionary_new();


  static const char filename[] = "/Users/ksma/Projects/CCollections/src/cases/words.txt";
    FILE *file = fopen ( filename, "r" );
    if ( file != NULL ) {
        char line [ 1024 ]; /* or other suitable maximum line size */
        while ( fgets ( line, sizeof line, file ) != NULL ) {
            // fputs ( line, stdout ); /* write the line */
            string_to_lower(line);
            choppy(line);
            
            // split the line by whitespace
            char tokens[] = " .,:;!?";
            char *pch = strtok(line, tokens);

            
            while (pch != NULL) {
                if (!cc_dictionary_contains_key(dict, pch)) {
                    cc_dictionary_add(dict, pch, cc_object_with_int(1));
                } else {
                    cc_object *val = cc_dictionary_get(dict, pch);
                    int f = cc_object_int_value(val);
                    f = f + 1;
                    cc_object *ins = cc_object_with_int(f);
                    if (ins != NULL) {
                        cc_dictionary_add(dict, pch, ins);
                    }
                }
                pch = strtok(NULL, tokens);
                
            }
            
            // take each word and remove all ,.!?
        }
        
        cc_enumerator *e = cc_dictionary_get_enumerator(dict);
        while (cc_enumerator_move_next(e)) {
            const char *key = cc_object_string_value(cc_enumerator_current(e));
            printf("%s,%i\n", key, cc_object_int_value(cc_dictionary_get(dict, key)));
        }
        
        fclose ( file );
    } else {
        perror ( filename ); /* why didn't the file open? */
    }

    return 0;
}