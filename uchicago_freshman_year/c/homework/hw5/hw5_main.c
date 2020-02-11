#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw5.h"

/* test_make_empty_string
 * tests make_empty_string
 * inputs:
 *   none
 * output:
 *   prints results of test
 */
void test_make_empty_string()
{
    //if test correct
    if(strcmp(make_empty_string()->str, "") == 0)
    {
        printf("test_make_empty_string -> an empty string SUCCESS\n");
    }
    else
    {
        printf("test_make_empty_string -> %s, FAILURE\n",
                make_empty_string()->str);
    }

}

/* test_make_string
 * tests make_string
 * inputs:
 *   char *str : string
 * output:
 *   prints results of test
 */
void test_make_string(char *str)
{
    safe_string *s = make_string(str);
    //if initial and final string match
    if(strcmp(str,s->str) == 0)
    {
       printf("test_make_string(\"%s\") -> \"%s\", SUCCESS\n",str,s->str);
    }
    else
    {
        printf("test_make_string -> \"%s\" -> \"%s\", FAILURE\n",str,s->str);
    }
}

/* test_safe_str_cpy
 * tests safe_str_cpy
 * inputs:
 *   safe_string *dest : destination safe string
 *   safe_string *src : source safe string
 *   safe_string *expected : expected safe string
 * output:
 *   results of testing
 */
void test_safe_str_cpy(safe_string *dest, safe_string *src,
                        safe_string *expected)
{
    char *oldstr = dest->str;
    uint oldlen = dest->allocated_length;
    safe_str_cpy(dest,src);
    //if test is SUCCESS
    if(strcmp(dest->str,expected->str) == 0 &&
        dest->allocated_length == expected->allocated_length)
    {
        printf("safe_str_cpy test SUCCESS\n");
        printf("    dest | \"%s\", len: %u\n",oldstr,oldlen);
        printf("    src | \"%s\", len: %u\n",src->str,src->allocated_length);
        printf("    result | \"%s\", len: %u\n",
                            dest->str,dest->allocated_length);
    }
    else
    {
        printf("safe_str_cpy test FAILURE\n");
        printf("    dest | \"%s\", len: %u\n",oldstr,oldlen);
        printf("    src | \"%s\", len: %u\n",src->str,src->allocated_length);
        printf("    result | \"%s\", len: %u\n",
                            dest->str,dest->allocated_length);
        printf("    expected | \"%s\", len: %u\n",
                            expected->str,expected->allocated_length);
    }

}

/* test_safe_str_cat
 * tests safe_str_cat
 * inputs:
 *   safe_string *dest : destination safe string
 *   safe_string *src : source safe string
 *   safe_string *expected : expected safe string
 * output:
 *   results of testing
 */
void test_safe_str_cat(safe_string *dest, safe_string *src,
                        safe_string *expected)
{
    char *oldstr = dest->str;
    uint oldlen = dest->allocated_length;
    safe_str_cat(dest,src);
    //if test is SUCCESS
    if(strcmp(dest->str,expected->str) == 0 &&
        dest->allocated_length == expected->allocated_length)
    {
        printf("safe_str_cat test SUCCESS\n");
        printf("    dest | \"%s\", len: %u\n",oldstr,oldlen);
        printf("    src | \"%s\", len: %u\n",src->str,src->allocated_length);
        printf("    result | \"%s\", len: %u\n",
                            dest->str,dest->allocated_length);
    }
    //else test was a FAILURE
    else
    {
        printf("safe_str_cat test FAILURE\n");
        printf("    dest | \"%s\", len: %u\n",oldstr,oldlen);
        printf("    src | \"%s\", len: %u\n",src->str,src->allocated_length);
        printf("    result | \"%s\", len: %u\n",
                            dest->str,dest->allocated_length);
        printf("    expected | \"%s\", len: %u\n",
                            expected->str,expected->allocated_length);
    }
}

/* test safe_strchr
 * tests safe_strchr
 * inputs:
 *   safe_string *s : safe_string
 *   char c : character
 *   char *expected : expected string after pointer
 * output:
 *   prints results of test
 */
void test_safe_strchr(safe_string *s, char c, char *expected)
{
    char *pnt = safe_strchr(s,c);
    //if both are NULL -> SUCCESS
    if(pnt == NULL && expected == NULL)
    {
        printf("safe_strchr(%s,%c) -> NULL, SUCCESS\n",s->str,c);
    }
    //else if test was SUCCESS generally
    else if(pnt[0] == c && strcmp(pnt,expected) == 0)
    {
        printf("safe_strchr(%s,%c) SUCCESS\n",s->str,c);
    }
    //else test was a FAILURE
    else
    {
        printf("safe_strchr(%s,%c) FAILURE\n",s->str,c);
        printf("    resulting char : %c\n",c);
        printf("    expected char : %c\n",expected[0]);
        printf("    resulting string after pointer : %s\n",pnt);
        printf("    expected string after pointer : %s\n",expected);
    }
}
/* test_safe_strcmp
 * tests safe_strcmp
 * inputs:
 *   safe_string *s1 : first string
 *   safe_string *s2 : second string
 *   int exp : expected result
 * output:
 *   prints results of testing
 */
void test_safe_strcmp(safe_string *s1, safe_string *s2, int exp)
{
    int res = safe_strcmp(s1,s2);
    //if results correct
    if(res == exp)
    {
        printf("safe_strcmp(%s,%s) == %d, SUCCESS\n",
        s1->str,s2->str,exp);
    }
    //else failed
    else
    {
        printf("safe_strcmp(%s,%s) = %d, expected : %d, FAILURE\n",
        s1->str,s2->str,res,exp);
    }
}

int main(int argc, char *argv[])
{
    //if start -> print beginning of hw5 testing
    if(strcmp(argv[1],"start") == 0)
    {
        printf("----- Beginning of hw5 Testing -----\n\n");
    }

    //else if end -> print end of hw5 testing
    else if(strcmp(argv[1],"end") == 0)
    {
        printf("\n----- End of hw5 Testing -----\n\n");
    }
    //else if 0-> test_make_empty_string
    else if(strcmp(argv[1],"0") == 0)
    {
        test_make_empty_string();
    }
    //else if 1 -> test_make_string
    else if(strcmp(argv[1],"1") == 0)
    {
        test_make_string(argv[2]);
    }
    //else if 2 -> test_safe_str_cpy
    else if(strcmp(argv[1],"2") == 0)
    {
        safe_string *dest = (safe_string*)malloc(sizeof(safe_string));
        safe_string *src = (safe_string*)malloc(sizeof(safe_string));
        safe_string *expected = (safe_string*)malloc(sizeof(safe_string));
        //first safe_str_cpy test
        if(strcmp(argv[2],"1") == 0)
        {

            dest->str = (char*)malloc(9*sizeof(char));
            strcpy(dest->str,"adsfasdf");
            dest->allocated_length = 9;
            src->str = "asdf";
            src->allocated_length = 5;
            expected->str = "asdf";
            expected->allocated_length = 9;
            test_safe_str_cpy(dest,src,expected);
        }
        //second safe_str_cpy test
        else if(strcmp(argv[2],"2") == 0)
        {
            dest->str = (char*)malloc(5*sizeof(char));
            strcpy(dest->str,"asdf");
            src->str = "asdfasdf";
            src->allocated_length = 9;
            expected->str = "asdfasdf";
            expected->allocated_length = 9;
            test_safe_str_cpy(dest,src,expected);
        }
    }
    //else if 3 -> test_safe_str_cat
    else if(strcmp(argv[1],"3") == 0)
    {
        safe_string *dest = (safe_string*)malloc(sizeof(safe_string));
        safe_string *src = (safe_string*)malloc(sizeof(safe_string));
        safe_string *expected = (safe_string*)malloc(sizeof(safe_string));
        //first safe_str_cat test
        if(strcmp(argv[2],"1") == 0)
        {
            dest->str = (char*)malloc(9*sizeof(char));
            strcpy(dest->str,"adsfasdf");
            dest->allocated_length = 9;
            src->str = "aaaa";
            src->allocated_length = 5;
            expected->str = "adsfasdfaaaa";
            expected->allocated_length = 13;
            test_safe_str_cat(dest,src,expected);
        }
        //second safe_str_cat test
        else if(strcmp(argv[2],"2") == 0)
        {
            dest->str = (char*)malloc(17*sizeof(char));
            strcpy(dest->str,"adsfasdf");
            dest->allocated_length = 17;
            src->str = "aaaa";
            src->allocated_length = 5;
            expected->str = "adsfasdfaaaa";
            expected->allocated_length = 17;
            test_safe_str_cat(dest,src,expected);
        }
    }
    //else if 4 -> safe_strchr
    else if(strcmp(argv[1],"4") == 0)
    {
        safe_string *strtest = (safe_string*)malloc(sizeof(strtest));
        //first safe_str_cat test
        if(strcmp(argv[2],"1") == 0)
        {
            strtest->str = "abcde";
            strtest->allocated_length = 6;
            test_safe_strchr(strtest,'b',"bcde");
        }
        //second safe_str_cat test
        else if(strcmp(argv[2],"2") == 0)
        {
            strtest->str = "TestABC";
            strtest->allocated_length = 8;
            test_safe_strchr(strtest,'t',"tABC");
        }
        //third safe_str_cat test
        else if(strcmp(argv[2],"3") == 0)
        {
            strtest->str = "TesTABCt";
            strtest->allocated_length = 8;
            test_safe_strchr(strtest,'t',"t");
        }
        //fourth safe_str_cat test
        else if(strcmp(argv[2],"4") == 0)
        {
            strtest->str = "TesTABCt";
            strtest->allocated_length = 8;
            test_safe_strchr(strtest,'x',NULL);
        }
    }
    //else if 5 -> safe_strcmp
    else if(strcmp(argv[1],"5") == 0)
    {
        safe_string *s1 = (safe_string*)malloc(sizeof(safe_string));
        safe_string *s2 = (safe_string*)malloc(sizeof(safe_string));
        //first safe_str_cat test
        if(strcmp(argv[2],"1") == 0)
        {
            s1->str = "asdfASDF";
            s2->str = "asdfASDF";
            test_safe_strcmp(s1,s2,0);
        }
        //second safe_str_cat test
        else if(strcmp(argv[2],"2") == 0)
        {
            s1->str = "asdfASDSF";
            s2->str = "basdfASDF";
            test_safe_strcmp(s1,s2,-1);
        }
        //third safe_str_cat test
        else if(strcmp(argv[2],"3") == 0)
        {
            s1->str = "zsdfASDSF";
            s2->str = "JsdfASDF";
            test_safe_strcmp(s1,s2,1);
        }
        //fourth safe_str_cat test
        else if(strcmp(argv[2],"4") == 0)
        {
            s1->str = "FsdfASDSF";
            s2->str = "zsdfASDF";
            test_safe_strcmp(s1,s2,-1);
        }
        //fifth safe_str_cat test
        else if(strcmp(argv[2],"4") == 0)
        {
            s1->str = NULL;
            s2->str = "zsdfASDF";
            test_safe_strcmp(s1,s2,1);
        }
    }
    //else -> print error
    else
    {
        printf("ERROR : main given invalid first arg\n");
    }
}
