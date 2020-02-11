#include <stdio.h>
#include <stdlib.h>

/* convert_length
 * convert length from centimeters to inches
 * inputs:
 *    double centimeters
 * return value:
 *    double - the same number converted to inches
 */
double convert_length(double centimeters)
{
	if (centimeters < 0)
	{
	fprintf (stderr, "ERROR: convert_length: length a negative value\n");
	return -1;
	}
	
	return (centimeters * 0.3937);
}

/* trapezoid_area
 * calculate the area of a trapezoid
 * inputs:
 *   unsigned int height - height of the trapezoid
 *   unsigned int base1 - length of base 1 of the trapezoid
 *   unsigned int base2 - length of base 2 of the trapezoid
 * return value:
 *   double - calculated area of the trapezoid
 */
double trapezoid_area(unsigned int height, unsigned int base1, unsigned int base2)
{
	if (height == 0 || base1 == 0 || base2 == 0)
	{
	fprintf (stderr, "ERROR: trapezoid_area: received an input of zero\n");
	return 0;
	}

return (height * (base1 + base2) / 2.0 );
}


/* fact
 * computes factorials
 * inputs:
 *    unsigned int n
 * return value:
 *    unsigned int - computed factorial
 */
unsigned int fact(unsigned int n)
{
	if(n > 0)
	{
	return (n * fact(n-1));
	}
	else
	{
	return 1;
	}
}


/* get_entry
 * returns entry in Pascal Triangle for given row and column
 * inputs:
 *    unsigned int row - current row
 *    unsigned int col - current column
 * return value:
 *    unsigned int - entry at that row and column
 */
unsigned int get_entry(unsigned int row, unsigned int col)
{
	unsigned int nom = fact(row);
	unsigned int dom = fact(col)*fact(row-col);
	return (nom/dom);
}

/* print_triangles_entry
 * print out each row of a number triangle
 * inputs:
 *    unsigned int start_num - number of triangle
 *    unsigned int row - current row of triangle
 *    unsigned int col - current column of triangle
 * return value:
 *    none - output is printed to the screen
 * output:
 *    print out the current row of the triangle
 */
void print_triangles_entry(unsigned int start_num, unsigned int row, unsigned int col)
{
if(row <=4 )
{
        if(col == 0){
                for(int i = 0; i<4-row; i++)
                {
                printf("\t");
                }
        }

	unsigned int entry = start_num*get_entry(row,col);
	
	if(entry<100)
	{
	printf(" ");
	}
	if(entry<10)
	{
	printf(" ");
	}
        if(col == row)
        {
        printf("%d\n", entry);
        print_triangles_entry(start_num,row+1,0);
        }
        else
        {
        printf("%d\t\t", entry);
        print_triangles_entry(start_num,row,col+1);
        }
}}


/* print_number_triangle
 * print out the first 5 rows of a number triangle 
 * inputs:
 *    unsigned int start_num
 * return value:
 *    none - output is printed to the screen
 * output
 *    print out the first 5 rows of a number triangle
 */
void print_number_triangle(unsigned int start_num)
{
	if(start_num >= 999)
	{
	fprintf(stderr, "ERROR (print_number_triangle)\
	: Numbers larger than 3 digits not supported\n");
	}
	
	else
	{
	print_triangles_entry(start_num, 0, 0);
	}
}




/***********************************************************
********** PLACE OTHER TEST FUNCTIONS HERE *****************
***********************************************************/

/* test_convert_length
 * This tests the convert_length function
 * inputs:
 *    double centimeters - centimeters to convert
 *    double expected - expected result
 *    double wiggle_room - amount result can be wrong
 * outputs:
 *    unsigned int success - 0 for failure, 1 for success
 */
unsigned int test_convert_length(double centimeters, double expected, double wiggle_room)
{
	double result = convert_length(centimeters);
	// notice we don't compare a double or float with ==
	if ((result >= expected - wiggle_room) &&
	    (result <= expected + wiggle_room))
	{
		printf("convert_length(%f) = %f. Success\n",
			centimeters, result);
		return 1;
	}
	else
	{
		printf("convert_length(%f) = %f. Expected %f. FAILURE\n",
			centimeters, result, expected);
		return 0;
	}

}

/* test_trapezoid_area
 * This tests the trapezoid_area function
 * inputs:
 *    double height - height
 *    double base1 - base1
 *    double base2 - base2
 *    double expected - expected result
 *    double wiggle_room - amount result can be wrong
 * outputs:
 *    unsigned int success - 0 for failure, 1 for success
 */
unsigned int test_trapezoid_area(double height, double base1, double base2, double expected, double wiggle_room)
{
        double result = trapezoid_area(height, base1, base2);
        if ((result >= expected - wiggle_room) &&
            (result <= expected + wiggle_room))
        {
                printf("trapezoid_area(%f,%f,%f) = %f. Success\n",
                        height,base1,base2, result);
                return 1;
        }
        else
        {
                printf("trapezoid_area(%f,%f,%f) = %f. Expected %f. FAILURE\n",
                        height, base1, base2, result, expected);
                return 0;
        }

}

/* test_print_number_triangle
 * This tests the print_number_triangle function
 * input:
 *   unsigned int start_num - top of triangle
 * outputs:
 *   No return value. Prints info, calls function, returns.
 */
void test_print_number_triangle(unsigned int start_num)
{
	printf("number triangle: %d\n", start_num);
	print_number_triangle(start_num);
	printf("\n\n");

}

/* test_fact
 * This tests the fact function
 * inputs:
 *    unsigned int n - number of factorial
 *    unsigned int expected - expected result
 * outputs:
 *    unsigned int success - 0 for failure, 1 for success
 */
unsigned int test_fact(unsigned int n, unsigned int expected)
{
        unsigned int result = fact(n);
        // notice we don't compare a double or float with ==
        if (result == expected)
        {
                printf("fact(%d) = %d. Success\n",
                        n, result);
                return 1;
        }
        else
        {
                printf("fact(%d) = %d. Expected %d. FAILURE\n",
                        n, result, expected);
                return 0;
        }

}

/* test_get_entry
 * This tests the get_entry function
 * inputs:
 *    unsigned int row - row of factorial
 *    unsigned int col - column of factorial
 *    unsigned int expected - expected result
 * outputs:
 *    unsigned int success - 0 for failure, 1 for success
 */
unsigned int test_get_entry
(unsigned int row, unsigned int col, unsigned int expected)
{
        unsigned int result = get_entry(row, col);
        if (result == expected)
        {
                printf("get_entry(%d,%d) = %d. Success\n",
                        row, col, result);
                return 1;
        }
        else
        {
                printf("get_entry(%d,%d) = %d. Expected %d. FAILURE\n",
                        row, col, result, expected);
                return 0;
        }

}

/***********************************************************
********** ONLY MAIN GOES BELOW THIS POINT *****************
***********************************************************/

int main()
{
	/* I am putting in a call to each function - just to check compiling.
	 * You need to make check functions and create better more test cases.
	 * THIS IS NOT GOOD CHECKING CODE. JUST FOR COMPILING!!!
	 */
	printf("------ test_convert_length -----\n");
	test_convert_length(0, 0, 0.01);
	test_convert_length(1, 0.393, 0.01);
	test_convert_length(2, 0.787, 0.01);
	test_convert_length(101, 39.763, 0.01);
	test_convert_length(-20, -1, 0.01);
	
	printf("\n------ test_trapezoid_area -----\n");
	test_trapezoid_area(0, 1, 1, 0, 0.01);
	test_trapezoid_area(1, 0, 1, 0, 0.01);
	test_trapezoid_area(1, 1, 0, 0, 0.01);
	test_trapezoid_area(3, 4, 5, 13.5, 0.01);
	test_trapezoid_area(20, 32, 52, 840, 0.01);
	
	printf("\n------ test_fact -----\n");
	test_fact(1,1);
	test_fact(0,1);
	test_fact(2,2);
	test_fact(6,720);
	test_fact(8,40320);

	printf("\n------ test_get_entry ------\n");
	test_get_entry(0, 0, 1);
	test_get_entry(1, 0, 1);
	test_get_entry(1, 1, 1);
	test_get_entry(2, 0, 1);
	test_get_entry(2, 1, 2);
	test_get_entry(0, 0, 1);
	test_get_entry(3, 2, 3);
	// TODO: Write your own 3+ good test cases for trapezoid_area
	test_print_number_triangle(1);
	test_print_number_triangle(5);
	test_print_number_triangle(5000);
}
