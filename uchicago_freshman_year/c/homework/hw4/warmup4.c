#include <stdio.h>
#include <stdlib.h>
#include "warmup4.h"
#include "hw4_provided.h"
/* Alex Sheen, alexsheen */
/* CS152, Winter 2019 */
/* warmup 4 */

/* count_vowels
 * search through str and count the number of vowels.
 * input: char *str - a string
 * output: int - the number of vowels in the string str
 */
int count_vowels(char *str)
{
int count = 0;
int i =0;
//runs through string until it reaches the end char '\0'
while(str[i] != '\0')
{
    //if the current char is a vowel
    if(str[i] == 'a'
    || str[i] == 'A'
	|| str[i] == 'e'
	|| str[i] == 'E'
	|| str[i] == 'i'
	|| str[i] == 'I'
	|| str[i] == 'o'
	|| str[i] == 'O'
	|| str[i] == 'u'
	|| str[i] == 'U')
    {
	count++;
    }
i++;
}
return count;
}
/* make_lowercase
 * modify str such that all alphabetic characters are lower case
 * input: char *str - a string
 * output: no return value - str is out parameter
 */
void make_lowercase(char *str)
{
int i = 0;
while(str[i] != '\0')
{
    //if current char is an uppercase letter, change to lowercase
    if(str[i] >= 'A' && str[i] <= 'Z')
    {
	str[i]+=32;
    }
i++;
}
}

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
	unsigned int height)
{
//error checks width and height
if(width > COLS || height > ROWS)
{
    fprintf(stderr, "ERROR: make_horizontal_stripes given width or height \
out of bounds");
}
int i;
int j;
//runs through all the rows to set it default to black
for(i = 0; i < height; i++)
{
    //runs through all the columns to set it default to black
    for(j = 0; j < width; j++)
    {
	red[i][j] = 0;
        green[i][j] = 0;
        blue[i][j] = 0;
    }
}
int start;
//runs through all starting height coords for the colored stripes
for(start = 0; start < height; start+=stripe_height+stripe_height)
{
    //runs through every height pixel for that stripe
    for(i = 0; i < stripe_height && i < height; i++)
    {
        //runs through every width pixel for that stripe
        for(j = 0; j < width; j++)
        {
            red[start+i][j] = stripe_red;
            green[start+i][j] = stripe_green;
            blue[start+i][j] = stripe_blue;
        }
    }
}
}

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
        unsigned int height)
{
//error checks width and height
if(width > COLS || height > ROWS)
{
    fprintf(stderr,"ERRPR: make_checker_board given width or height \
out of bounds");
}
int i;
int j;
//runs through all the rows to set it default to white
for(i = 0; i < height; i++)
{
    //runs through all the columns to set it default to white
    for(j = 0; j < width; j++)
    {
	red[i][j] = 255;
	green[i][j] = 255;
	blue[i][j] = 255;
    }
}
int start_h;
int start_c;
//runs through all starting height coords for the colored squares
for(start_h = 0; start_h < height; start_h+=square_width)
{
    //runs through every height pixel for that square
    for(i = 0; i < square_width && i < height; i++)
    {
	//if even row
	if((start_h / square_width) % 2 == 0)
	{
	//runs through even starting width coords for the colored squares
	    for(start_c = 0;
                start_c < width; start_c+=square_width+square_width)
	    {
	        //runs through every width pixel for that square
	        for(j = 0; j < square_width && j < width; j++)
	        {
		    red[start_h+i][start_c+j] = square_red;
		    green[start_h+i][start_c+j] = square_green;
		    blue[start_h+i][start_c+j] = square_blue;
	        }
	    }
	}
	//else it is an odd row
	else
	{
	    //runs through odd starting width coords for the colored squares
	    for(start_c = square_width; 
                start_c < width; start_c+=square_width+square_width)
	    {
	        //runs through every width pixel for that square
	        for(j = 0; j < square_width && j < width; j++)
	        {
		    red[start_h+i][start_c+j] = square_red;
		    green[start_h+i][start_c+j] = square_green;
		    blue[start_h+i][start_c+j] = square_blue;
	        }
	    }    
        }
    }
}
}




