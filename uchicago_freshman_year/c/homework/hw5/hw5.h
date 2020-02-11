#ifndef HW5_H
#define HW5_H
#include "warmup5_provided.h"

typedef unsigned int uint;

typedef struct {
	char *str;
	uint allocated_length;
} safe_string;

/* make_empty_string
 * creates an empty string
 * inputs:
 *   none
 * output:
 *   empty safe string
 */
safe_string* make_empty_string();
/* make_string
 * converts a char * to safe string
 * inputs:
 *   char *str : char *
 * output:
 *   safe string with char* inside of it
 *   note: if str is NULL, it makes an empty string
 */
safe_string* make_string(char *str);

/* safe version of string copy
 * inputs:
 *   safe_string *dest : destination string
 *   safe_string *src : source string
 * output:
 *   none, reallocates memory if dest memory isn't big enough
 */
void safe_str_cpy(safe_string *dest, safe_string *src);

/* safe version of string concat
 * inputs:
 *   safe_string *dest : destination string
 *   safe_string *src : source string
 * output:
 *   none, reallocates memory if dest memory isn't big enough
 */
void safe_str_cat(safe_string *dest, safe_string *src);

/* safe_strchr
 * returns pointer to first occurence of char within string
 * inputs:
 *   safe_string *s : safe string
 *   char c : character
 * output:
 *   char * to character in safe string, NULL if character not found
 */
char *safe_strchr(safe_string *s, char c);

/* safe_strcmp
 * returns 0 if strings identical, -1 if s1 is earlier alphabetically,
 * 1 if s2 is earlier alphabetically
 * This version considers 'A' < 'a' but 'A' and 'a' < 'B' and 'b'
 * inputs:
 *   safe_string *s1 : string 1
 *   safe_string *s2 : string 2
 * output:
 *   0, -1, 1
 */
int safe_strcmp(safe_string *s1, safe_string *s2);


#endif
