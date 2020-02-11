#ifndef WARMUP4_H
#define WARMUP4_H

#define ROWS 50
#define COLS 50

/* count_vowels
 * search through str and count the number of vowels.
 * input: char *str - a string
 * output: int - the number of vowels in the string str
 */
int count_vowels(char *str);

/* make_lowercase
 * modify str such that all alphabetic characters are lower case
 * input: char *str - a string
 * output: no return value - str is out parameter
 */
void make_lowercase(char *str);

/* make_horizontal_stripes
 *   This produces an image stored in the red, green, and blue 2-d arrays.
 *   The image contains black and colored stripes. All stripes are 
 *   stripe_height. The stripe colors are indicated by stripe_color.
 *   The top stripe is colored. The image is heightxwidth.
 * inputs: 
 *   unsigned int red[ROWS][COLS],  - red component of resulting image pixels
 *   unsigned int green[ROWS][COLS], - green component of resulting image pixels
 *   unsigned int blue[ROWS][COLS],  - blue component of resulting image pixels
 *   unsigned int stripe_height,  - height of a single stripe
 *   unsigned int stripe_red,  - red component of stripe pixel
 *   unsigned int stripe_green,  - green component of stripe pixel
 *   unsigned int stripe_blue,  - blue component of stripe pixel
 *   unsigned int width,  - width of resulting image
 *   unsigned int height); - height of resulting image
 * 
 */
void make_horizontal_stripes( 
	unsigned int red[ROWS][COLS], 
	unsigned int green[ROWS][COLS], 
	unsigned int blue[ROWS][COLS], 
	unsigned int stripe_height, 
	unsigned int stripe_red, 
	unsigned int stripe_green, 
	unsigned int stripe_blue, 
	unsigned int width, 
	unsigned int height);

/* make_checker_board
 *   This produces an image stored in the red, green, and blue 2-d arrays.
 *   The image contains white and colored squares. All squares are 
 *   square_width x square_width. The square colors are indicated by 
 *   square_color. The image is heightxwidth. The top-left square is colored.
 * inputs: 
 *   unsigned int red[ROWS][COLS],  - red component of resulting image pixels
 *   unsigned int green[ROWS][COLS], - green component of resulting image pixels
 *   unsigned int blue[ROWS][COLS],  - blue component of resulting image pixels
 *   unsigned int square_height,  - height of a single square
 *   unsigned int square_red,  - red component of square pixel
 *   unsigned int square_green,  - green component of square pixel
 *   unsigned int square_blue,  - blue component of square pixel
 *   unsigned int width,  - width of resulting image
 *   unsigned int height); - height of resulting image
 * 
 */
void make_checker_board( 
        unsigned int red[ROWS][COLS],
        unsigned int green[ROWS][COLS],
        unsigned int blue[ROWS][COLS],
        unsigned int square_width,
        unsigned int square_red,
        unsigned int square_green,
        unsigned int square_blue,
        unsigned int width,
        unsigned int height);


#endif
