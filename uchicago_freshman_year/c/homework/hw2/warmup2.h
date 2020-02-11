#ifndef WARMUP2_H
#define WARMUP2_H

/* print_asterisk_letter
 * Given a character, print the corresponding upper-case letter of the 
 * alphabet using asterisks. The letter can be 'S', 'T', 'U', 'V'.
 * input: 
 *   char letter - the letter to print out
 * output: 
 *   nothing returned, just printed to the screen.
 */
void print_asterisk_letter(char letter);

/* draw_hourglass_rec
 * draws a hourglass with asterisks. implemented recursively.
 * inputs:
 *   uint height - the number of rows to print of the hourglass
 * outputs:
 *   nothing returned, just printed to the screen
 */

void draw_hourglass_rec(unsigned int height);

/* draw_hourglass_iter
 * draws a hourglass with asterisks. implemented iteratively.
 * inputs:
 *   uint height - the number of rows to print of the hourglass
 * outputs:
 *   nothing returned, just printed to the screen
 */

void draw_hourglass_iter(unsigned int height);



#endif
