#include <stdio.h>
#include <stdlib.h>
#include "warmup5_provided.h"
#include "warmup5.h"
/* Alex Sheen, alexsheen */
/* CS152, Winter 2019 */
/* warmup 5 */

/* *safe_str_concat
 * allocates new string to hold str2 concated behind str1
 * inputs:
 *   char* str1 : first string
 *   char* str2 : second string
 * output:
 *   returns pointer to new string
 */
char *safe_str_concat(char *str1, char *str2)
{
    int len1;
    int len2;
    //finds length of str1
    for(len1 = 0; str1[len1] != '\0'; len1++)
    {
        ;
    }
    //finds length of str2
    for(len2 = 0; str2[len2] != '\0'; len2++)
    {
        ;
    }
    //creates new array
    char *newstr;
    newstr = (char*)malloc((len1+len2+1)*sizeof(char));
    int i;
    //fills in array with str1
    for(i = 0; i<len1; i++)
    {
        newstr[i] = str1[i];
    }
    //fills in rest of array with str2
    for(i = 0; i<len2; i++)
    {
        newstr[i+len1] = str2[i];
    }
    newstr[len1+len2+1] = '\0';
    return newstr;
}

/* make_init_array
 * allocates the int_vector and initializes the values for an array with
 * 0 items
 * outputs:i
 *   returns pointer to new int_vector of array size 0
 */
int_vector *make_init_array()
{
    int_vector *vec = (int_vector*)malloc(sizeof(int_vector));
    vec->allocated_size = 0;
    vec->array = NULL;
    return vec;
}

/* write_value
 * attempts to write a value in the array. if the array is not large enough,
 * array is reallocated to double the current size of the array (minimum 16)
 * inputs:
 *   int_vector *vector : initial int vector
 *   uint index : index of value
 *   int value : value
 * output:
 *   modifies int_vector or reallocates memory
 */
void write_value(int_vector *vector, unsigned int index, int value)
{
    int *p;
    //if array is NULL
    if(vector->array == NULL)
    {
        p = (int*)malloc(16*sizeof(int));
        vector->allocated_size = 16;
    }
    //if memory needs to be reallocated
    if(index >= vector->allocated_size)
    {
        //double array size until index is within bounds
        while(vector->allocated_size<=index)
        {
             vector->allocated_size *= 2;
        }
        p = (int*)malloc(vector->allocated_size*sizeof(int));
    }
    vector->array = p;
    vector->array[index] = value;
    }
    /* read_value
     * attempts to read value in the array. if the index is out of bounds,
     * return 0
     * inputs:
     *   int_vector *vector : int vector
     *   uint index : index of value
     * output:
     *   value at index or 0 if index is out of bounds
     */
    int read_value(int_vector *vector, uint index)
    {
    //checks if index is within array
    if(index < vector->allocated_size)
    {
        return vector->array[index];
    }
    //else, return 0
    else
    {
        return 0;
    }
}

/* make_and_init_image
 * initializes a 2D array of pixels all set to a color
 * inputs:
 *   int height : height of image
 *   int width : width of image
 *   pixel color : color of each pixel
 */
pixel** make_and_init_image(int height, int width, pixel color)
{
    pixel** TwoDArray;
    TwoDArray = (pixel**)malloc(height*sizeof(pixel*));
    int i;
    for(i = 0; i<height; i++)
    {
        TwoDArray[i] = (pixel*)malloc(width*sizeof(pixel));
        int j;
        for(j = 0; j<width; j++)
        {
            TwoDArray[i][j].red = color.red;
            TwoDArray[i][j].green = color.green;
            TwoDArray[i][j].blue = color.blue;
        }
    }
    return TwoDArray;
}
