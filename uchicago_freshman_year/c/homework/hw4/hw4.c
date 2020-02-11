#include <stdio.h>
#include <stdlib.h>
#include "hw4.h"
#include "hw4_provided.h"
/* Alex Sheen, alexsheen */
/* CS152, Winter 2019 */
/* hw 4 */

/* hide_pixel
 * modifies result pixel based on reference and hidden image pixel
 * hidden image values of at least 128 result in odd values in the result(+1)
 * hidden image values less than 128 result in even values in the result(-1)
 * inputs:
 *   uint ref : reference pixel value
 *   uint hid : hidden pixel value
 *   *uint res : pointer to result pixel value
 * output:
 *   *uint res : output paramter
 */
void hide_pixel(uint ref, uint hid, uint *res)
{
//if hidden value is at least 128, result should be odd
if(hid >= 128)
{
    //checks if reference value is already odd
    if(ref % 2 == 1)
    {
        *res = ref;
    }
    //else reference value is even
    else
    {
        *res = ref + 1;
    }
}
//else hidden value is less than 128, result should be even
else
{
    //checks if reference value is already even
    if(ref % 2 == 0)
    {
        *res = ref;
    }
    //else reference value is odd
    else
    {
        *res = ref - 1;
    }
}
}

/* hide_image
 * combines a reference image and a hidden data image into a third image output
 * hidden image values of at least 128 result in odd values in the result(+1)
 * hidden image values less than 128 result in even values in the result(-1)
 * inputs:
 *   uint ref_r[][]: red 2D array for reference image
 *   uint ref_g[][]: green 2D array for reference image
 *   uint ref_b[][]: blue 2D array for reference image
 *   uint hid_r[][]: red 2D array for hidden image
 *   uint hid_g[][]: green 2D array for hidden image
 *   uint hid_b[][]: blue 2D array for hidden image
 *   uint res_r[][]: red 2D array for result image
 *   uint res_g[][]: green 2D array for result image
 *   uint res_b[][]: blue 2D array for result image
 *   uint height: image height
 *   uint width: image width
 * output:
 *   modifies rgb values for result image
 *   res_r, res_g, res_b are out parameters
 */
void hide_image(
	unsigned int ref_r[ROWS][COLS], 
	unsigned int ref_g[ROWS][COLS], 
	unsigned int ref_b[ROWS][COLS], 
	unsigned int hid_r[ROWS][COLS], 
	unsigned int hid_g[ROWS][COLS], 
	unsigned int hid_b[ROWS][COLS], 
	unsigned int res_r[ROWS][COLS], 
	unsigned int res_g[ROWS][COLS], 
	unsigned int res_b[ROWS][COLS], 
	unsigned int height, unsigned int width)
{
//checks image dimensions
if(height > ROWS || width > COLS)
{
    fprintf(stderr, "ERROR hide_image: image dimensions greater \
than 2D array dimensions\n");
}
//else image has correct dimensions
else
{
    int i, j;
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            hide_pixel(ref_r[i][j],hid_r[i][j],&res_r[i][j]);
            hide_pixel(ref_g[i][j],hid_g[i][j],&res_g[i][j]);
            hide_pixel(ref_b[i][j],hid_b[i][j],&res_b[i][j]);
            
        }
    }
}
}

/* unhide_pixel
 * modifies result pixel based on encoded image pixel
 * encoded image values that are odd result in 255 in the result pixel
 * encoded image values that are even result in 0 in the result pixel
 * inputs:
 *   uint enc : encoded image value
 *   *uint res : result image value
 * output:
 *   *uint res : output paramter
 */
void unhide_pixel(uint enc, uint *res)
{
//if encoded image value is odd
if(enc % 2 == 1)
{
   *res = 255; 
}
//else encoded image value is even
else
{
    *res = 0;
}
}
/* extract_image
 * extracts a hidden image from an encoded image
 * odd rgb values result in 255 rgb values in the hidden image
 * even rgb values result in 0 rgb values in the hidden image
 * inputs:
 *   uint res_r[][]: red 2D array for encoded image
 *   uint res_g[][]: green 2D array for encoded image
 *   uint res_b[][]: blue 2D array for encoded iamge
 *   uint hid_r[][]: red 2D array for hidden image
 *   uint hid_g[][]: green 2D array for hidden image
 *   uint hid_b[][]: blue 2D array for hidden image
 *   uint height : image height
 *   uint width: image width
 * output:
 *   modifies rgb values for hidden image
 *   hid_r, hid_g, hid_b are out parameters 
 */
void extract_image(
	unsigned int res_r[ROWS][COLS], 
	unsigned int res_g[ROWS][COLS],
 	unsigned int res_b[ROWS][COLS], 
	unsigned int hid_r[ROWS][COLS], 
	unsigned int hid_g[ROWS][COLS], 
	unsigned int hid_b[ROWS][COLS], 
	unsigned int height, unsigned int width)
{
//checks if image dimensions are greater than 2D dimensions
if(height > ROWS || width > COLS)
{
    fprintf(stderr, "ERROR, extract_image: image dimensions greater than \
2D array dimensions");
}
//else dimensions are within bounds
else
{
    int i, j;
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            unhide_pixel(res_r[i][j],&hid_r[i][j]);
            unhide_pixel(res_g[i][j],&hid_g[i][j]);
            unhide_pixel(res_b[i][j],&hid_b[i][j]);
        }
    }
}
}
/* encode
 * encodes an image into a reference image, producing a third encoded image
 * inputs:
 *   char *ref_filename : name of reference file
 *   char *hid_filename : name of hidden image file
 *   char *enc_filename : name of encoded image file
 * output:
 *   writes encoded image to encoded image file (enc_filename) 
 */
void encode(char *ref_filename, char *hid_filename, char *enc_filename)
{ 
unsigned int ref_r[ROWS][COLS]; 
unsigned int ref_g[ROWS][COLS]; 
unsigned int ref_b[ROWS][COLS]; 
unsigned int hid_r[ROWS][COLS]; 
unsigned int hid_g[ROWS][COLS]; 
unsigned int hid_b[ROWS][COLS]; 
unsigned int res_r[ROWS][COLS]; 
unsigned int res_g[ROWS][COLS]; 
unsigned int res_b[ROWS][COLS]; 
unsigned int height; unsigned int width;
unsigned int s_height; unsigned int s_width;

provided_read_png(ref_filename,ref_r,ref_g,ref_b,&width,&height);
provided_read_png(hid_filename,hid_r,hid_g,hid_b,&s_width,&s_height);
//if reference and hidden image don't have the same dimensions
if(s_width != width || s_height != height)
{
    fprintf(stderr,"ERROR: reference image dimensions don't match hidden image\
 dimensions\n");
}
//else they have the same dimensions
else
{
    hide_image(ref_r,ref_g,ref_b,hid_r,hid_g,hid_b,res_r,res_g,res_b,
    width,height);

    provided_write_png(enc_filename,res_r,res_g,res_b,width,height);
}}
/* decode
 * extracts the hidden file from the encrypted file
 * inputs:
 *   char *enc_filename: name of encoded image file
 *   char *hid_filename: name of hidden image file
 * outputs:
 *   writes hidden image to hidden image file
 */
void decode(char *enc_filename, char *hid_filename)
{
    unsigned int enc_r[ROWS][COLS]; 
    unsigned int enc_g[ROWS][COLS]; 
    unsigned int enc_b[ROWS][COLS]; 
    unsigned int hid_r[ROWS][COLS]; 
    unsigned int hid_g[ROWS][COLS]; 
    unsigned int hid_b[ROWS][COLS]; 
    unsigned int height; unsigned int width;
    
provided_read_png(enc_filename,enc_r,enc_g,enc_b,&width,&height);

extract_image(enc_r,enc_g,enc_b,hid_r,hid_g,hid_b,height,width);
provided_write_png(hid_filename,hid_r,hid_g,hid_b,width,height);   
}

