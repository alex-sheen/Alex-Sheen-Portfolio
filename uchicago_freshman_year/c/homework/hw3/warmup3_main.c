
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "warmup3.h"

/* test_remove_max
 * test function for remove_max
 * inputs:
 *   int array[] : given array
 *   uint length : length of array
 *   int expected_result : expected return value
 *   int expected_array : expected array
 *   uint expected_length : expected array length
 */
void test_remove_max(int array[], unsigned int length,
int expected_result,int expected_array[], unsigned int expected_length)
{
unsigned int result = remove_max(array,length);
//if test_remove_max gives expected result
if(result == expected_result)
{
    unsigned int valid = 1;
    //tests if remove_max results in expected array
    int i;
    for(i = 0; i<expected_length; i++)
    {
        //checks to make sure value at index matches in both arrays
        if(array[i] != expected_array[i])
        {
            valid = 0;
        }
    }
    //checks if the arrays matches
    if(valid == 1)
    {
        printf("remove_max(array,%u)) == %d, SUCCESS\n",
        length,expected_result);    
    }
    else
    {
        printf("remove_max(array,%u)) did not result in the right array,\
FAILURE\n",length);
    }
}
else
{    
    printf("remove_max(array,%u) expected %u, got %u, FAILURE\n",
    length,expected_result,result);
}
}

/* test_area_perimeter
 * test function for area_perimeter
 * inputs:
 *   double height : height
 *   double length : length
 *   double expected_area : expected area
 *   double expected_perimeter : expected perimeter
 *   double wiggle_room : wiggle room for double calculations
 * outputs:
 *   prints results of testing
 */
void test_area_perimeter(double height, double length, double expected_area,
double expected_perimeter,double wiggle_room)
{
double area;
double perimeter;
area_and_perimeter(height,length,&area,&perimeter);
//checks to see if area is correct
if(area <= expected_area - wiggle_room ||
   area >= expected_area + wiggle_room)
{
    printf("area_and_perimeter(%lf,%lf) resulted in area : %lf, expected %lf,\
 FAILURE\n",height,length,area,expected_area);
}
//checks to see if perimeter is correct
else if(perimeter <= expected_perimeter - wiggle_room ||
        perimeter >= expected_perimeter + wiggle_room)
{
    printf("area_and_perimeter(%lf,%lf) resulted in perimeter : %lf, expected %lf,\
 FAILURE\n",height,length,perimeter,expected_perimeter);
}
//else it must be correct
else
{
    printf("area_and_perimeter(%lf,%lf) resulted in area : %lf, perimeter :\
 %lf, SUCCESS\n",height,length,area,perimeter);
}
}


/* test_remove_max_in_out
 * test function for remove_max
 * inputs:
 *   int array[] : given array
 *   uint length : length of array
 *   int expected_result : expected return value
 *   int expected_array : expected array
 *   uint expected_length : expected array length
 */
void test_remove_max_in_out(int array[], unsigned int length,
int expected_result,int expected_array[], unsigned int expected_length)
{
unsigned int length_pointer = length;
unsigned int result = remove_max_in_out(array,&length_pointer);
//checks if remove_max_in_out correctly modified the length
if(length_pointer != expected_length)
{
    printf("remove_max_in_out(array,%u) resulted in length %u, expected \
%u, FAILURE\n",length,length_pointer,expected_length);
}

//if test_remove_max gives expected result
if(result == expected_result)
{
    unsigned int valid = 1;
    //tests if remove_max results in expected array
    int i;
    for(i = 0; i<expected_length; i++)
    {
        //checks to make sure value at index matches in both arrays
        if(array[i] != expected_array[i])
        {
            valid = 0;
        }
    }
    //checks if the arrays matches
    if(valid == 1)
    {
        printf("remove_max_in_out(array,%u)) == %d, SUCCESS\n",
        length,expected_result);    
    }
    else
    {
        printf("remove_max_int_out(array,%u)) did not result in the right \
array, FAILURE\n",length);
    }
}
else
{    
    printf("remove_max_in_out(array,%u) expected %u, got %u, FAILURE\n",
    length,expected_result,result);
}
}



/* test_warmup3
 * tests warmup3 functions
 * inputs:
 *   none
 * output:
 *   prints results of testing
 */
void test_warmup3()
{
char board[8][8] = { {'*','*','*','*','*','*','*','*'},
                             {'*','*','*','*','*','*','*','*'},
                             {'*','*','*','*','*','*','*','*'},
                             {'*','*','*','*','*','*','*','*'},
                             {'*','*','*','*','*','*','*','*'},
                             {'*','*','*','*','*','*','*','*'},
                             {'*','*','*','*','*','*','*','*'},
                             {'*','*','*','*','*','*','*','*'}  };
print_board(board);
init_board(board);

int test_array1[6] = {1,2,4,3,6,5};
int expected_array1[5] = {1,2,4,3,5};
test_remove_max(test_array1,6,6,expected_array1,5);
int test_array2[5] = {9,1,9,2,1};
int expected_array2[3] = {1,2,1};
test_remove_max(test_array2,5,9,expected_array2,3);
int test_array3[3] = {-1,-9,-2};
int expected_array3[2] = {-9,-2};
test_remove_max(test_array3,3,-1,expected_array3,2);
int test_array4[3] = {2,2,2};
int expected_array4[0] = {};
test_remove_max(test_array4,3,2,expected_array4,0);

test_area_perimeter(2,4,8,12,0.01);
test_area_perimeter(10.5,3.8,39.9,28.6,0.01);

int test_array5[6] = {1,2,4,3,6,5};
test_remove_max(test_array5,6,6,expected_array1,5);
int test_array6[5] = {9,1,9,2,1};
test_remove_max(test_array6,5,9,expected_array2,3);
int test_array7[3] = {-1,-9,-2};
test_remove_max(test_array7,3,-1,expected_array3,2);
int test_array8[3] = {2,2,2};
test_remove_max(test_array8,3,2,expected_array4,0);
}

//main
int main()
{
test_warmup3();
}
