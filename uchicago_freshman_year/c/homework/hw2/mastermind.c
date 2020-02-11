#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mastermind.h"
/* Alex Sheen, alexsheen */
/* CS152, Winter 2019 */
/* hw 2 */

/* extract_digit
 * returns value at digit in given pattern
 * inputs:
 *   uint pattern : given number sequence
 *   uint digit : digit of value
 * output:
 *   uint value at digit in pattern
 *   error if digit is greater than 3
 */
unsigned int extract_digit(unsigned int pattern, unsigned int digit)
{
	return (pattern / (int)  pow(10, digit) % 10);	
}

/* num_of_color
 * computes how many instances of a color there are in a pattern
 * inputs:
 *   uint pattern : given pattern
 *   uint color : int 1-6
 * outputs:
 *   uint : number of instances of given color
 */
unsigned int num_of_color(unsigned int pattern, unsigned int color)
{
    unsigned int counter = 0;
    //for each digit in pattern
	for(int i = 0; i<4; i++)
    {
        //if the color at that digit equals the color input
        if(extract_digit(pattern, i) == color)
        {
            counter++;
        }
    }
	return counter;
}

/* count_exact_matches
 * count how many digits match solution in both color and position
 * inputs:
 *   uint guess : guess pattern
 *   uint solution : solution pattern
 * output:
 *   number of digits that match solution
 */
unsigned int count_exact_matches(unsigned int guess, unsigned int solution)
{
	unsigned int counter = 0;
    //for each digit in pattern
    for(int i = 0; i<4; i++)
    {
        //if colors match at the same digit in guess and solution
        if(extract_digit(guess,i) == extract_digit(solution,i))
        {
        counter++;
        }
    }
    return counter;
}

/* count_color_matches
 * count how many digits in guess match solution in color,
 * regardless of position.
 * inputs:
 *   uint guess : guess pattern
 *   uint solution : solution pattern
 * outputs:
 *   number of digits that match in color
 */ 
unsigned int count_color_matches(unsigned int guess, unsigned int solution)
{
	int color_counter_g[] = {0,0,0,0,0,0};
    int color_counter_s[] = {0,0,0,0,0,0};
    //for each digit in pattern
    for(int i = 0; i<4; i++)
    {
        color_counter_g[extract_digit(guess,i)-1] += 1;
        color_counter_s[extract_digit(solution,i)-1] += 1;
    }
    int count = 0;
    //for each possible color
    for(int i = 0; i<6; i++)
    {
        //if and else work together to get minimum
        //of target color in guess and solution
        if(color_counter_g[i] > color_counter_s[i])
        {
        count+= color_counter_s[i];
        }
        else
        {
        count+= color_counter_g[i];
        }
    }
	return (count-count_exact_matches(guess,solution));
}

/* get_guess_feedback
 * error checks guess and solution, then returns exact and color matches
 * inputs:
 *   uint guess : guess pattern
 *   uint solution : solution pattern
 * output:
 *   uint, 1's place is incorrect placement, correct color
 *        10's place is correct placement, correct color
 */
unsigned int get_guess_feedback(unsigned int guess, unsigned int solution)
{
    //if guess or solution has the wrong number of digits
	if(guess > 9999 || solution > 9999 || guess < 1000 || solution < 1000)
    {
        fprintf(stderr, "ERROR, get_guess_feedback : guess or solution\
        over 4 digits long");
    }
    //for each digit in pattern
    for(int i = 0; i<4; i++)
    {
        //if color in guess or solution is above 6
        if(extract_digit(guess,i) > 6 || extract_digit(solution,i) > 6)
        {
            fprintf(stderr, "ERROR, get_guess_feedback : guess or solution\
             has digits of value over 6");
        }
    }
	return 10 * count_exact_matches(guess,solution) +
             count_color_matches(guess,solution);
}


/* test_extract_digit
 * This is a test function for test_extract_digit
 * inputs:
 *   unsigned int pattern : given pattern
 *   unsigned int digit : digit to return
 *   unsigned int expected : expected result
 * outputs:
 *   prints a success message if passed
 *   raises error if failed
 */
void test_extract_digit(
unsigned int pattern, unsigned int digit, unsigned int expected)
{
//if extract_digit gives expected result
if((extract_digit(pattern,digit)) == expected)
{
    printf("test_extract_digit(%u,%u)==%u, SUCCESS\n",pattern,digit,expected);    
}
else
{
    printf("test_extract_digit(%u,%u), expected %u, got %u, FAILURE\n",pattern,
    digit, expected, extract_digit(pattern,digit));
}
}

/* test_num_of_color
 * This is a test function for test_num_of_color
 * inputs:
 *   unsigned int pattern : given pattern
 *   unsigned int digit : digit to return
 *   unsigned int expected : expected result
 * outputs:
 *   prints a success message if passed
 *   raises error if failed
 */
void test_num_of_color(
unsigned int pattern, unsigned int digit, unsigned int expected)
{
//if num_of_color gives expected result
if((num_of_color(pattern,digit)) == expected)
{
    printf("num_of_color(%u,%u)==%u, SUCCESS\n", pattern, digit, expected);    
}
else
{
    printf("num_of_color(%u,%u), expected %u, got %u, FAILURE\n", pattern,
    digit, expected, num_of_color(pattern,digit));
}
}

/* test_count_exact_matches
 * This is a test function for test_exact_matches
 * inputs:
 *   uint guess : guess pattern
 *   uint solution : solution pattern
 *   uint expected : expected result
 * outputs:
 *   prints a success message if passed
 *   raises error if failed
 */
void test_count_exact_matches(
unsigned int guess, unsigned int solution, unsigned int expected)
{
//if count_exact_matches gives expected result
if((count_exact_matches(guess,solution)) == expected)
{
    printf("count_exact_matches(%u,%u)==%u, \
    SUCCESS\n",guess,solution,expected);    
}
else
{
    printf("count_exact_matches(%u,%u), expected %u, got %u, FAILURE\n", guess,
    solution, expected, count_exact_matches(guess,solution));
}
}


/* test_count_color_matches
 * This is a test function for test_color_matches
 * inputs:
 *   uint guess : guess pattern
 *   uint solution : solution pattern
 *   uint expected : expected result
 * outputs:
 *   prints a success message if passed
 *   raises error if failed
 */
void test_count_color_matches(
unsigned int guess, unsigned int solution, unsigned int expected)
{
//if count_color_matches gives the expected result
if((count_color_matches(guess,solution)) == expected)
{
    printf("count_color_matches(%u,%u)==%u,\
         SUCCESS\n",guess,solution,expected);    
}
else
{
    printf("count_color_matches(%u,%u), expected %u, got %u, FAILURE\n", guess,
    solution, expected, count_color_matches(guess,solution));
}
}

/* test_get_guess_feedback
 * This is a test function for test_get_guess_feedback
 * inputs:
 *   uint guess : guess pattern
 *   uint solution : solution pattern
 *   uint expected : expected result
 * outputs:
 *   prints a success message if passed
 *   raises error if failed
 */
void test_get_guess_feedback(
unsigned int guess, unsigned int solution, unsigned int expected)
{
//if get_guess_feedback gives expected result
if((get_guess_feedback(guess,solution)) == expected)
{
    printf("get_guess_feedback(%u,%u)==%u, SUCCESS\n",guess,solution,expected);    
}
else
{
    printf("get_guess_feedback(%u,%u), expected %u, got %u, FAILURE\n", guess,
    solution, expected, get_guess_feedback(guess,solution));
}
}

/* test_mastermind
 * This is the test function that has 3+ good test cases for this function in
 * your  mastermind program. This verifies that the bits are working so that
 *  if you find a bug you can more easily localize it.
 * inputs:
 *   none. Tests are hard coded.
 * outputs:
 *   none. Test results are printed out.
 */
void test_mastermind()
{
	printf("\n ------- Beginning Testing ----- \n");
    printf("\n ----- test_extract_digit ----- \n");
    test_extract_digit(3413,2,4);
    test_extract_digit(2345,0,5);
	test_extract_digit(1234,1,3);
	test_extract_digit(5679,2,6);
	test_extract_digit(9385,3,9);
    printf("\n ----- test_num_of_color ----- \n");
    test_num_of_color(3413,1,1);
    test_num_of_color(1234,1,1);
    test_num_of_color(1167,1,2);
    test_num_of_color(1117,1,3);
    test_num_of_color(1111,1,4);
    test_num_of_color(3141,1,2);
    test_num_of_color(3141,4,1);
    printf("\n ----- test_count_exact_matches ----- \n");
    test_count_exact_matches(3413,2315,1);
    test_count_exact_matches(1234,1234,4);
    test_count_exact_matches(1234,2111,0);
    test_count_exact_matches(1234,1987,1);
    test_count_exact_matches(1314,1917,2);
    test_count_exact_matches(7899,1299,2);
    test_count_exact_matches(5678,2678,3);
    printf("\n ----- test_count_color_matches ----- \n");
    test_count_color_matches(3413,2315,1);
    test_count_color_matches(1111,1111,0);
    test_count_color_matches(1234,2316,3);
    test_count_color_matches(1234,4321,4);
    test_count_color_matches(1646,6164,4);
    test_count_color_matches(1456,2312,1);
    test_count_color_matches(1234,5555,0);
    printf("\n ----- test_get_guess_feedback ----- \n");
    test_get_guess_feedback(3413,2315,11);
    test_get_guess_feedback(1534,1355,12);
    test_get_guess_feedback(1124,1234,21);
    test_get_guess_feedback(1234,1234,40);
    test_get_guess_feedback(1234,4321,4);
    printf("\n ------- Testing Concluded ----- \n\n");
    test_count_color_matches(2415,1425,4);
    test_count_color_matches(2445,2451,3);
    test_count_color_matches(2435,6416,1);
    test_extract_digit(1635,5,0);
    test_get_guess_feedback(7642,5343,0);
    
}

/* print_mastermind_instructions
 * This prints out user instructions to play mastermind.
 * inputs:
 *   none
 * outputs:
 *   none. Insructions are printed to screen.
 */
void print_mastermind_instructions()
{
	printf("Welcome to mastermind. I am thinking of a 4-number\n");
	printf("sequence. All four numbers are between 1 and 6.\n");
	printf("You have 12 guesses to guess it correctly.\n");
	printf("Each time you guess, I'll tell two things.\n");
	printf("1. How many numbers are correct and in the correct position.\n");
	printf("2. How many other numbers\
 are correct but in the wrong position.\n");
	printf("Let's get started!!!\n");
}

/* get_new_code
 * Generates a 4-digit number, with each digit a number from 1 to 6, inclusive.
 * inputs:
 *   none
 * outputs:
 *   unsigned int - 4-digit number with each digit from 1 to 6
 */
unsigned int get_new_code()
{
	int i;
	int result = 0;
	//for each digit in a pattern
    for (i = 0; i < 4; i++)
	{
		result = result * 10;
		result = result + ((rand() % 6) + 1);
	}
	return result;
}


/* play_mastermind
 * This is the game loop to play mastermind. All print statements are provided so that you 
 * have consistent messages for grading purposes. An example of how to do error checking is 
 * provided so you can model that.
 * inputs:
 *  none. Users play interactively
 * outputs:
 *  none. Everything is printed.
 */
void play_mastermind()
{

	unsigned int guess_num = 12;
	unsigned int solution = 0;
	unsigned int guess = 0;
	unsigned int feedback = 0;
    unsigned int feedback_valid = 0;
	print_mastermind_instructions();
	solution = get_new_code();
	printf("solution: %u\n",solution);

    //while there are still guesses remaining
	while(guess_num>0)
	{
        printf("\n");
        feedback_valid = 0;
	    //loops until user gives a valid guess input
        do
        {
            printf("Guess %d - ",guess_num);
	        printf("Input your 4-digit guess: ");
	        scanf("%u",&guess);
            feedback_valid = 0;
            //for each digit in a pattern
            for(int i = 0; i<4; i++)
            {
                if(extract_digit(guess,i) > 6)
                {   
                     feedback_valid=1;
                }
            }
            //if guess has the wrong number of digits
            if(guess>9999 || guess < 1000)
            {
                feedback_valid=1;
            }
            //if the guess is invalid
            if(feedback_valid==1)
            {
                printf("%u is an invalid guess. Make sure your guess is a\
                 4-digit number, each digit between 1-6.\n", guess);
            }
        } while(feedback_valid==1);
	
    feedback = get_guess_feedback(guess,solution);

	// report the feedback
	printf("Feedback:\n%u correct placement, correct color,\n",
		feedback / 10);
	printf("%u incorrect placement, correct color\n",
		feedback % 10);
	         

    // if correct guess, print out congrats and return from this function
	if(guess == solution)
	{
	printf("Congratulations! Your guess of %u was correct!\n",
		guess);
	return;
	}

	//if incorrect, print out number of guesses left
	guess_num--;
    if(guess_num==0)
    {
	printf("Not quite - you still have %u guesses left!\n",
		guess_num);
	}
    }

	// only print this out if they ran out of guesses didn't win.
	printf("Sorry, you did not guess it! The solution was %u\n",solution);
	return;
}


