#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "warmup5.h"

/* test_safe_str_concat
 * tests safe_str_concat
 * inputs:
 *   char *str1 : first string
 *   char *str2 : second strig
 * output:
 *   prints results of testing
 */
void test_safe_str_concat(char *str1, char *str2)
{
    char *result = safe_str_concat(str1,str2);
    printf("safe_str_concat(%s,%s) -> %s\n",str1,str2,result);
}

/* test_write_value
 * tests write_value
 * inputs:
 *   int_vector *v : initialized int vector
 *   uint index : index
 *   int value : value
 * outputs:
 *  prints results of testing
 */
void test_write_value(int_vector *v, uint index, int value)
{
    write_value(v,index,value);
    printf("write_value(int_vector,%u,%d) -> %d at index %u\n"
    ,index,value,v->array[index],index);
}

/* test_read_value
 * tests read_value
 * inputs:
 *   int_vector *v : int vector
 *   uint index : index
 *   int expected : expected value
 * outputs:
 *  prints results of testing
 */
void test_read_value(int_vector *v, uint index, int expected)
{
//if v is empty
if(v == NULL)
{
    fprintf(stderr, "ERROR: test_read_value given NULL int_vector\n");
}
else
{
    int res = read_value(v,index);
    //if test worked
    if(res == expected)
    {
        printf("read_value(int_vector,%u) == %d, SUCCESS\n",index,res);
    }
    //else it didn't
    else
    {
        printf("read_value(int_vector,%u) = %d, expected : %d, FAILURE\n"
                ,index,res,expected);
    }
}
}

/* test_make_and_init_image
 * tests make_and_init_image
 * inputs:
 *   int height : image height
 *   int width : image width
 *   int r : red value
 *   int g : green value
 *   int b : blue value
 *   char *name : file name
 * outputs:
 *  prints results of testing
 */
void test_make_and_init_image(int height, int width, int r, int g, int b,
char *name)
{
    pixel pix;
    pix.red = r;
    pix.green = g;
    pix.blue = b;
    pixel** img = make_and_init_image(height,width,pix);
    provided_write_png_struct(name,img,width,height);
    printf("test_make_and_init_image for %s\n", name);
}
// -------------------- end of testing -------------------------

int main(int argc, char *argv[])
{
    //if 0 -> safe_str_concat
    if(strcmp(argv[1],"0") == 0)
    {
        test_safe_str_concat(argv[2],argv[3]);
    }
    //else if 1 -> write_value
    else if(strcmp(argv[1],"1") == 0)
    {
        //fprintf(stderr,"test_write_value not yet implented\n");
        int_vector *v = make_init_array();
        //first write_value test
        if(strcmp(argv[2],"1") == 0)
        {
            test_write_value(v,3,5);
        }
        //second write_value test
        else if(strcmp(argv[2],"2") == 0)
        {
            test_write_value(v,17,-1);
        }
        //third write_value test
        else if(strcmp(argv[2],"3") == 0)
        {
            v->allocated_size = 16;
            v->array = (int*)malloc(16*sizeof(int));
            test_write_value(v,34,100);
        }
        //else error
        else
        {
            fprintf(stderr, "ERROR main : test_write_value given invalid input\
    to choose test\n");
        }
        free(v);
    }
    //else if 2 -> read_value
    else if(strcmp(argv[1],"2") == 0)
    {
        int_vector *v = (int_vector*)malloc(sizeof(int_vector));
        //first read_value test
        if(strcmp(argv[2],"1") == 0)
        {
            v->allocated_size = 16;
            v->array = (int*)malloc(16*sizeof(int));
            v->array[5] = 3;
            test_read_value(v,5,3);
        }
        //second read_value test
        else if(strcmp(argv[2],"2") == 0)
        {
          v->allocated_size = 16;
          v->array = (int*)malloc(16*sizeof(int));
          v->array[15] = 3;
          test_read_value(v,15,3);
        }
        //third read_value test
        else if(strcmp(argv[2],"3") == 0)
        {
            v->allocated_size = 16;
            v->array = (int*)malloc(16*sizeof(int));
            v->array[16] = 3;
            test_read_value(v,16,0);
        }
    }
    //else if 3 -> make_and_init_image
    else if(strcmp(argv[1],"3") == 0)
    {
        test_make_and_init_image(atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),
                                 atoi(argv[5]),atoi(argv[6]),argv[7]);
    }
    //else if 4 -> print beginning of warmup5 testing
    else if(strcmp(argv[1],"start") == 0)
    {
        printf("\n----- Beginning of warmup5 Testing -----\n\n");
    }
    //else if 5 -> print end of warmup5 testing
    else if(strcmp(argv[1],"end") == 0)
    {
        printf("\n\n----- End of warmup5 Testing ----- \n\n");
    }
    //else -> error
    else
    {
        fprintf(stderr, "ERROR main : first argument invalid, %s\n",argv[1]);
    }
    return 1;
}
