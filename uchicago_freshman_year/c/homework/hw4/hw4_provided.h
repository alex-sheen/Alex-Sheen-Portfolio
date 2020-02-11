#ifndef HW4_PROVIDED_H
#define HW4_PROVIDED_H

#define ROWS 50
#define COLS 50

#define QUALITY 100

/* provided_read_png
 * Reads in a png from filename and populates the rgb arrays as well
 * as the image width and length. All out parameter space must have been
 * allocated prior to the function call. This function does not allocate
 * memory for use outside of it.
 *
 * in parameters:
 *   char *filename - the filename to read from
 * out parameters:
 *   red[ROWS][COLS] - 2D array to which red pixel values will be placed.
 *   green[ROWS][COLS] - 2D array to which green pixel values will be placed.
 *   blue[ROWS][COLS] - 2D array to which blue pixel values will be placed.
 *   uint *image_width - the width of the read-in image
 *   uint *image_length - the length of the read-in image
 */
int provided_read_png(char *filename, 
    unsigned int red[ROWS][COLS], 
    unsigned int green[ROWS][COLS], 
    unsigned int blue[ROWS][COLS], 
    unsigned int *image_width, 
    unsigned int *image_length);

/* provided_write_png
 * Writes to a png named filename, writing data in the rgb arrays.
 * It will use image_width and image_length to determine how much data to write.
 *
 * in parameters:
 *   char *filename - the filename to read from
 *   red[ROWS][COLS] - 2D array from which red pixel values will be read.
 *   green[ROWS][COLS] - 2D array from which green pixel values will be read.
 *   blue[ROWS][COLS] - 2D array from which blue pixel values will be read.
 *   uint image_width - the width to write out the image
 *   uint image_length - the length to write out the image
 */
int provided_write_png(char *filename, 
    unsigned int red[ROWS][COLS], 
    unsigned int green[ROWS][COLS], 
    unsigned int blue[ROWS][COLS], 
    unsigned int image_width, 
    unsigned int image_length);

/* provided_print_image_to_html
 * Writes a file named filename, writing data in the rgb arrays to html format, 
 * which looks very pixelated but sort of works..
 * It will use image_width and image_length to determine how much data to write.
 *
 * in parameters:
 *   char *filename - the filename to read from
 *   red[ROWS][COLS] - 2D array from which red pixel values will be read.
 *   green[ROWS][COLS] - 2D array from which green pixel values will be read.
 *   blue[ROWS][COLS] - 2D array from which blue pixel values will be read.
 *   uint image_width - the width to write out the image
 *   uint image_length - the length to write out the image
 */
int provided_print_image_to_html(char *filename, unsigned int red[ROWS][COLS],
    unsigned int green[ROWS][COLS],
    unsigned int blue[ROWS][COLS],
    unsigned int image_width,
    unsigned int image_height);

#endif /* HW4_PROVIDED_H */
