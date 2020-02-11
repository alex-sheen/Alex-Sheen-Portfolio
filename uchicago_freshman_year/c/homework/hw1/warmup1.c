
#include <stdio.h>
#include <stdlib.h>

/* print_stuff: prints several variables of different types
 * purpose is to illustrate printf and the types C provides 
 * void means it doesn't return a value - it does something instead
 * inputs:
 *    int ival - integer value that will be printed out as an integer
 *    float fval - floating-point value that will be printed out as a float
 *    double dval - more precise fp value that will be printed as a long float
 *    char cval - char value that will be printed out as a character
 */
void print_stuff(int ival, float fval, double dval, char cval)
{
	printf("Integer: %d\n",ival);
	printf("Float: %f\n",fval);
	printf("Double is a more precise float: %lf\n",dval);
	printf("Char is a letter %c\n",cval);
        printf("You can also control how a float is printed out: %3.2f\n",
		62.937491287);
}

/* do_some_math: purpose is to do math and show the outcomes for 
 * various operations that illustrate how C works
 * inputs:
 * 	int ival - integer value for performing random operations
 * 	float fval - float value for performing random operations
 * 	char cval - character showing character arithmetic
 */
void do_some_math(int ival, float fval, char cval)
{
	printf("%d + 5 = %d\n",ival,ival+5);
	printf("%c + 5 = %c\n",cval,cval+5);
	printf("%d %% 5 = %d\n",ival,ival%5);
	printf("%c %% 5 = %c! Not useful!\n",cval,cval%5);
	ival = 3;
	fval = 3.0;
	printf("%d / 5 = %d! Be careful!\n",ival,ival/5);
	printf("%f / 5 = %f. They work differently!\n",fval,fval/5);
	printf("%d / 5.0 = %f! Now it works!\n",ival,ival/5.0);
}

/* return_a_value: purpose is to show how to declare values,
 * calculate a result, and return that result to the caller 
 * inputs:
 * 	int ival - integer value we will multiply by 5
 * outputs:
 *      int result - the original input multiplied by 5
 */
int return_a_value(int ival)
{
	int result = ival*5;
	return result;
}

/* f_to_c: convert a temperature in fahrenheit to celsius
 * NOTE: This has a BUG in it!!!
 * inputs:
 *     float fahr - the temperature in fahrenheit
 * outputs:
 *     float - the temperature in celsius
 */
float f_to_c(float fahr)
{
	float cel;
	cel = (fahr-32) * (5.0/9.0);
	return cel;
}

/* Principle 3: Make a helper function that helps check the function
 */
void check_f_to_c(float input, float expected_output)
{
	float output = f_to_c(input);
	printf("f_to_c(%f) = %f, expected %f\n",
			input, output, expected_output);
}

/* Principle 2: Design a good set of test cases
 * they check the base case (0), right above the base case (1), well
 * above the base case (5, 8). We would also normally check
 * error cases like -1 or -5, but because our type is unsigned int,
 * we know we won't get negative cases.
 */
int main()
{
	int input, output; // declared, but not initialized
	printf("Your example program has begun.\n");

	/* these two are just showing function calls, 
   	 * not good programming principles */
	print_stuff(5, 7.5, 8.9, 'a');
	input = 10;
	output = return_a_value(input);
	printf("return_a_value(%d) is %d\n",input,output);
	input = 20;
	output = return_a_value(input);
	printf("return_a_value(%d) is %d\n",input,output);
	input = 0;
	output = return_a_value(input);
	printf("return_a_value(%d) is %d\n",input,output);

	printf("Now let's do some math. This illustrates some calculations in C.\n");
	do_some_math(10, 3.5, 'f');

	printf("Test cases for f_to_c\n");
	/* this part shows good design principles */
	check_f_to_c(32,0);
	check_f_to_c(212,100);
	check_f_to_c(-13, -25);
	printf("Example program exiting.\n");
}

