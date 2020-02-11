#ifndef WARMUP5_PROVIDED_H
#define WARMUP5_PROVIDED_H


typedef struct {
    unsigned int red;
    unsigned int green;
    unsigned int blue;
} pixel;

/* provided_read_png_struct
 *
 * This function reads in a png file (filename) into a 2-d array of pixels. 
 * inputs:
 *   char *filename - the name of the png image file
 * outputs:
 *   int *image_width - the width of the image (in pixels)
 *   int *image_height - the height of the image (in pixels)
 *   pixel **image - a 2-d array of pixels - this function allocates the array
 *     and fills it in with the contents of the image.
 */
pixel ** provided_read_png_struct(char *filename, int *image_width, int *image_height);

/* provided_write_png_struct
 *
 * This function writes to a png file (filename) from a 2-d array of pixels. 
 * inputs:
 *   char *filename - the name of the png image file
 *   pixel **image - a 2-d array of pixels
 *   int image_width - the width of the image (in pixels)
 *   int image_height - the height of the image (in pixels)
 */
int provided_write_png_struct(char *filename, pixel **image, int image_width, int image_height);


void read_png_file(char* file_name);

void write_png_file(char* file_name);

void abort_(const char * s, ...);

#endif /* PNG_FUNCTIONS_H */
