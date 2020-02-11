#ifndef HW4_H
#define HW4_H

#define ROWS 50
#define COLS 50
typedef unsigned int uint;

/* hide_image
 * combines a reference image and a hidden data image into a third image output
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
	unsigned int height, unsigned int width);

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
	unsigned int height, unsigned int width);

/* encode
 * encodes an image into a reference image, producing a third encoded image
 * inputs:
 *   char *ref_filename : name of reference file
 *   char *hid_filename : name of hidden image file
 *   char *enc_filename : name of encoded image file
 * output:
 *   writes encoded image to encoded image file (enc_filename) 
 */
void encode(char *ref_filename, char *hid_filename, char *enc_filename);
/* decode
 * extracts the hidden file from the encrypted file
 * inputs:
 *   char *enc_filename: name of encoded image file
 *   char *hid_filename: name of hidden image file
 * outputs:
 *   writes hidden image to hidden image file
 */
void decode(char *enc_filename, char *hid_filename);

#endif



