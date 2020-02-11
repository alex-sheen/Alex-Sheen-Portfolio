#include <stdlib.h>
#include <stdio.h>
#include "warmup3.h"
#include <limits.h>
/* print_board
 * prints the contents of the checkerboard.
 * The pieces are 'b', 'w', the kinged ones
 * are 'B'and 'W', and empty spaces are '*'
 * inputs:
 *    char board[NUM_ROWS][NUM_COLS] - an NUM_ROWSxNUM_COLS board
 * outputs:
 *    none. prints the results.
 */
void print_board( char board[NUM_ROWS][NUM_COLS] )
{
        unsigned int i, j;
        printf("   ");
        for(j=0;j<NUM_COLS;j++)
        {
                printf("%u ",j);
        }
        printf("\n");
        for(i=0;i<NUM_ROWS;i++)
        {
                printf("%u: ",i);
                for(j=0;j<NUM_COLS;j++)
                {
                        printf("%c ",board[i][j]);
                }
                printf("\n");
        }
}

/* remove_max
 * removes all instances of the maximum item in an array
 * returns the maximum value
 * inputs:
 *   int array[] : an integer array
 *   uint length : length of array
 * output:
 *   int : maximum value in array
 */
int remove_max(int array[], unsigned int length)
{
if(length == 0)
{
return INT_MIN;
}
int max = array[0];
//runs through rest of array looking for max value
for(int i = 1; i<length; i++)
{
    //if array value > current max
    if(array[i] > max)
    {
        max = array[i];
    }
}
//runs through rest of array again
unsigned int index = 0;
for(int i = 0; i<length; i++)
{
    //if array value != max
    if(array[i] != max)
    {
    array[index] = array[i];
    index++;
    }
}
return max;
}

/* init_board
 * initializes the contents of the checkerboard.
 * The blue pieces occupy rows 0 to (NUM_ROWS/2 - 2), and
 * the white pieces occupy rows (NUM_ROWS / 2 + 1) to NUM_ROWS-1
 * An 8x8 board looks like this:
   * b * b * b * b
   b * b * b * b *
   * b * b * b * b
   * * * * * * * *
   * * * * * * * *
   w * w * w * w *
   * w * w * w * w
   w * w * w * w *
 * inputs:
 *    char board[NUM_ROWS][NUM_COLS] - an NUM_ROWSxNUM_COLS board
 * outputs:
 *    none. prints the results.
 */
void init_board(char board[NUM_ROWS][NUM_COLS])
{
//initializing '*'
for(int i = 0; i < NUM_ROWS; i++)
{
    for(int j = 0; j < NUM_COLS; j++)
    {
        board[i][j] = '*';
    }
}

//initializing 'b'
for(int i = 0; i <= (NUM_ROWS/2-2); i++)
{
    for(int j = (i+1)%2; j < NUM_COLS; j+=2)
    {
    board[i][j] = 'b';
    }
}
//initializing 'w'
for(int i = (NUM_ROWS/2 + 1); i<= NUM_ROWS-1; i++)
{
    for(int j = (i+1)%2; j < NUM_COLS; j+=2)
    {
    board[i][j] = 'w';
    }
}
print_board(board);
}
/* place_piece
 * checks if spot is valid
 * if yes, places character at that spot and returns 1
 * if no, leaves board unchanged and returns 0
 * inputs:
 *   char board[][] : 2D array
 *   char player : player character
 *   uint row : row of array
 *   uint col : column of array
 */
unsigned int place_piece(char board[NUM_ROWS][NUM_COLS],char player,
 unsigned int row, unsigned int col)
{
if(board[row][col] == '*')
{
    board[row][col] = player;
    return 1;
}
return 0;
}

/* area_and_perimeter
 * calculates area and perimeter of rectangle
 * inputs:
 *   double height : height of rect
 *   double length : length of rect
 * outputs:
 *   double *area : area
 *   double *perimeter : perimeter
 */
void area_and_perimeter(double height, double length, double *area,\
double *perimeter)
{
*area = height*length;
*perimeter = height+height+length+length;
}

/* remove_max_in_out
 * removes maximum value from an array and updates its length
 * inputs:
 *   int array[] : an integer array
 *   uint *length : length of array
 * outputs:
 *   uint *length : new length of array
 */
int remove_max_in_out(int array[], unsigned int *length)
{
int max = array[0];
//runs through rest of array looking for max value
for(int i = 1; i<*length; i++)
{
    //if array value > current max
    if(array[i] > max)
    {
        max = array[i];
    }
}
//runs through rest of array again
unsigned int index = 0;
unsigned int new_length = 0;
for(int i = 0; i<*length; i++)
{
    //if array value != max
    if(array[i] != max)
    {
    array[index] = array[i];
    index++;
    new_length++;
    }
}
*length = new_length;
return max;
}


