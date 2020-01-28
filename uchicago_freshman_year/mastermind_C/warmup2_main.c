#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "warmup2.h"  // note this new include file!!!

// TODO: Write a test function for each exercise

/* Principle 2: Design a good set of test cases
 * they check the base case (0), right above the base case (1), well
 * above the base case (5, 8), and error conditions (-1, -5).
 * -1, 0, 1 are the boundary test cases - base, base+1, base-1.
 */
int main()
{

	// I am only putting one line in for each to make sure it compiles
	// you need to write your own test code

	// TODO: Write 3+ good test cases. 
	// TODO: Replace these calls with call to test function
	print_asterisk_letter('S');
	print_asterisk_letter('T');
	print_asterisk_letter('U');
	print_asterisk_letter('V');
	draw_hourglass_rec(10);
	draw_hourglass_rec(9);
	draw_hourglass_rec(1);
        draw_hourglass_rec(2);
	draw_hourglass_rec(3);
	draw_hourglass_iter(10);
	draw_hourglass_iter(9);
	draw_hourglass_iter(1);
	draw_hourglass_iter(2);
	draw_hourglass_iter(3);
}

