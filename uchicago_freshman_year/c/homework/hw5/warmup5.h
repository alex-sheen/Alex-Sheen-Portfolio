#ifndef HW5_H
#define HW5_H
#include "warmup5_provided.h"

typedef unsigned int uint;

typedef struct {
    unsigned int allocated_size;
    int *array;
} int_vector;

/* *safe_str_concat
 * allocates new string to hold str2 concated behind str1
 * inputs:
 *   char* str1 : first string
 *   char* str2 : second string
 * output:
 *   returns pointer to new string
 */
char *safe_str_concat(char *str1, char *str2);

/* make_init_array
 * allocates the int_vector and initializes the values for an array with 
 * 0 items
 * outputs:
 *   returns pointer to new int array of size 0
 */
int_vector* make_init_array();

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
void write_value(int_vector *vector, unsigned int index, int value);

/* read_value
 * attempts to read value in the array. if the index is out of bounds,
 * return 0
 * inputs:
 *   int_vector *vector : int vector
 *   uint index : index of value
 * output:
 *   value at index or 0 if index is out of bounds
 */
int read_value(int_vector *vector, uint index);

/* make_and_init_image
 * initializes a 2D array of pixels all set to a color
 * inputs:
 *   int height : height of image
 *   int width : width of image
 *   pixel color : color of each pixel
 */
pixel** make_and_init_image(int height, int width, pixel color);

#endif






