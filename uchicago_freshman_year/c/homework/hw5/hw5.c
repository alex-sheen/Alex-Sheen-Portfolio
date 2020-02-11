#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "warmup5_provided.h"
#include "hw5.h"
/* Alex Sheen, alexsheen */
/* CS152, Winter 2019 */
/* hw5 5 */

/* make_empty_string
 * creates an empty string
 * inputs:
 *   none
 * output:
 *   empty safe string
 */
safe_string* make_empty_string()
{
    safe_string *str = (safe_string*)malloc(sizeof(safe_string));
    str->str = "";
    str->allocated_length = 0;
    return str;
}
/* make_string
 * converts a char * to safe string
 * inputs:
 *   char *str : char *
 * output:
 *   safe string with char* inside of it
 *   note: if str is NULL, it makes an empty string
 */
safe_string* make_string(char *str)
{
    //if str is NULL
    if(str[0] == '\0')
    {
        return make_empty_string();
    }

    safe_string *newstr = (safe_string*)malloc(sizeof(safe_string));
    newstr->str = str;
    newstr->allocated_length = strlen(str);
    return newstr;
}

/* safe version of string copy
 * inputs:
 *   safe_string *dest : destination string
 *   safe_string *src : source string
 * output:
 *   none, reallocates memory if dest string isn't big enough
 */
void safe_str_cpy(safe_string *dest, safe_string *src)
{
    //if destination memory is too small, reallocate
    if(dest->allocated_length < strlen(src->str) + 1)
    {
        char *olddest = dest->str;
        char *newstr = (char*)malloc((strlen(src->str)+1)*sizeof(char));
        dest->allocated_length = strlen(src->str) + 1;
        strcpy(newstr,src->str);
        dest->str = newstr;
        free(olddest);
    }
    //else do not need to reallocate
    else
    {
        strcpy(dest->str,src->str);
    }
}

/* safe version of string concat
 * inputs:
 *   safe_string *dest : destination string
 *   safe_string *src : source string
 * output:
 *   none, reallocates memory if dest memory isn't big enough
 */
void safe_str_cat(safe_string *dest, safe_string *src)
{
    char *tempstr = dest->str;
    //if destination memory is too small, reallocate
    if(dest->allocated_length < strlen(dest->str) + strlen(src->str) + 1)
    {
        char *olddest = dest->str;
        tempstr = (char*)malloc
                    ((strlen(dest->str) + strlen(src->str) + 1)*sizeof(char));
        dest->allocated_length = strlen(dest->str) + strlen(src->str) + 1;
        strcpy(tempstr,dest->str);
        strcat(tempstr,src->str);
        dest->str = tempstr;
        free(olddest);
    }
    //else do not need to reallocate
    else
    {
        strcat(dest->str,src->str);
    }
}

/* safe_strchr
 * returns pointer to first occurence of char within string
 * inputs:
 *   safe_string *s : safe string
 *   char c : character
 * output:
 *   char * to character in safe string, NULL if character not found
 */
char *safe_strchr(safe_string *s, char c)
{
    char *pnt;
    int i = 0;
    int char_not_found = 1;
    //if safe_string is empty
    if(s->str == NULL || s->allocated_length == 0)
    {
        pnt = NULL;
    }
    //loops through string
    while(i < s->allocated_length && s->str[i] != '\0')
    {
        pnt = &s->str[i];
        //checks if character matches
        if(*pnt == c)
        {
            i = s->allocated_length;
            char_not_found = 0;
        }
        i++;
    }
    //if char wasn't reached
    if(char_not_found)
    {
        pnt = NULL;
    }
    return pnt;
}

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
int safe_strcmp(safe_string *s1, safe_string *s2)
{
    //error check if s1 and s2 are NULL
    if(s1->str == NULL && s2->str == NULL)
    {
        fprintf(stderr, "ERROR: safe_strcmp, both strings are NULL");
    }
    //error check if s1 is NULL
    else if(s1->str == NULL)
    {
        return 1;
    }
    //error check if s1 is NULL
    else if(s2->str == NULL)
    {
        return -1;
    }

    //if both strings are identical
    if(strcmp(s1->str,s2->str) == 0)
    {
        return 0;
    }
    char c1 = s1->str[0];
    char c2 = s2->str[0];
    //makes all uppercase letters lowercase
    if(c1 > 90)
    {
        c1 = c1 - 32;
    }
    //makes all uppercase letters lowercase
    if(c2 > 90)
    {
        c2 = c2 - 32;
    }
    //if s1 < s2 alphabetically
    if(c1 < c2)
    {
        return -1;
    }
    //else s2 < s1 alphabetically
    else if(c1 > c2)
    {
        return 1;
    }
    //else, if first characters match
    else
    {
        //if s1 is shorter than s2
        if(strlen(s1->str) < strlen(s2->str))
        {
            return -1;
        }
        //else if s2 is shorter than s1
        else if(strlen(s2->str) < strlen(s1->str))
        {
            return 1;
        }
        //else, they are the same size, there is no information on Piazza
        //      for this situation
        else
        {
            fprintf(stderr, "ERROR, safe_strcmp : cannot determine which string is\
  alphabetically first");
        }
    }
}
