#include <stdlib.h>
#include <stdio.h>
#include "warmup2.h"

/* print_asterisk_letter
 * input: char letter - the letter to print out
 * output: nothing returned, just printed to the screen.
 * Given a character, print the corresponding upper-case letter of the 
 * alphabet using asterisks. The letter can be anything from 'N' to 'R'. 
 */
void print_asterisk_letter(char letter)
{
   switch(letter)
   {
    case('S'):
    printf(" ****\n");
    printf("*\n");
    printf(" ***\n");
    printf("    *\n");
    printf("****\n");
    break;
    case('T'):
    printf("*****\n");
    printf("  *\n");
    printf("  *\n");
    printf("  *\n");
    printf("  *\n");
    break;
    case('U'):
    printf("*   *\n");
    printf("*   *\n");
    printf("*   *\n");
    printf("*   *\n");
    printf(" ***\n");
    break;
    case('V'):
    printf("*   *\n");
    printf("*   *\n");
    printf("*   *\n");
    printf(" * *\n");
    printf("  *\n");
    break;
    default:
    fprintf(stderr, "ERROR (print_asterisk_letter)\
     letter out of range S-V)");
   }	
   return;
}

/* draw_hourglass_iter_helper
 * draws a hourglass with asterisks. implemented iteratively.
 * inputs:
 *  uint height - the number of rows to print of the wedge
 *  uint offset - amount of spaces that should be to the left of this hourglass
 * outputs:
 *  nothing returned, just printed to the screen
 */
void draw_hourglass_iter_helper(unsigned int height, unsigned int offset)
{
    unsigned int n = 0;
    while(n<offset)
    {
    printf(" ");
    n++;
    }
    n=0;
    while(n<2*(height-offset)-1)
    {
    printf("*");
    n++;
    }
    printf("\n");
    return;
}
/* draw_hourglass_rec_helper
 * draws a row of the hourglass. implemented recursively.
 * due to the nature of my solution, I modified the parameters of this function
 * inputs:
 *  uint asterisks - the number of asterisks to print
 *  uint offset - amount of spaces that should be to the left of this hourglass
 * outputs:
 *   nothing returned, just printed to the screen
 */

void draw_hourglass_rec_helper(unsigned int asterisks, unsigned int offset)
{ 
  
  if(offset>0)
  {
  printf(" ");
  draw_hourglass_rec_helper(asterisks,offset-1);
  }
  else if(asterisks>0)
  {
  printf("*");
  draw_hourglass_rec_helper(asterisks-1,offset);
  }
  else
  {
  printf("\n");
  return;
  }
}

/* hourglass_rec
 * recursively calls draw_hourglass_rec_helper to draw hourglass
 * inputs:
 * uint height - half original height
 * uint h_left - the number of rows left to half to print of the wedge
 * bool h_odd - whether original height was odd
 */
void hourglass_rec(unsigned int height, unsigned int h_left, 
unsigned int h_odd)
{
	if(h_left == 1 && h_odd == 1)
	{
	draw_hourglass_rec_helper(2*h_left-1,height-h_left); 
	}
	else if (h_left == 1)
	{
	draw_hourglass_rec_helper(2*h_left-1,height-h_left);
	draw_hourglass_rec_helper(2*h_left-1,height-h_left);
	}
	else
	{
	draw_hourglass_rec_helper(2*h_left-1,height-h_left);
	hourglass_rec(height,h_left-1,h_odd);
	draw_hourglass_rec_helper(2*h_left-1,height-h_left);
	}
}

/* draw_hourglass_rec
 * draws a hourglass with asterisks. implemented recursively.
 * inputs:
 *   uint height - the number of rows to print of the wedge
 * outputs:
 *   nothing returned, just printed to the screen
 */

void draw_hourglass_rec(unsigned int height)
{ 
	
    unsigned int h_odd = 0;
    if(height % 2 != 0)
    {
	h_odd = 1;
 	height+=1;
	}
	hourglass_rec(height/2,height/2,h_odd);
	return;
}

/* draw_hourglass_iter
 * draws a hourglass with asterisks. Implemented iteratively.
 * inputs:
 *   uint height - the number of rows to print of the wedge
 * outputs:
 *   nothing returned, just printed to the screen
 */

void draw_hourglass_iter(unsigned int height)
{ 
	unsigned int h_odd = 0;
	if(height% 2 != 0)
	{
	h_odd = 1;
	height+=1;
	}
	unsigned int count = 0;
	while(count<height/2-1)
	{
	draw_hourglass_iter_helper(height/2,count);
	count++;
	}
	if(h_odd == 0)
	{
	draw_hourglass_iter_helper(height/2,height/2-1);
	}
	draw_hourglass_iter_helper(height/2,height/2-1);
	count=2;
	while(count<=height/2)
	{
	draw_hourglass_iter_helper(height/2,height/2-count);
	count++;
	}
}
