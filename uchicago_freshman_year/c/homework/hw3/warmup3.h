#ifndef WARMUP3_H
#define WARMUP3_H
#define NUM_ROWS 8
#define NUM_COLS 8
/* print_board
 * prints the contents of the checkerboard.
 * The pieces are 'b', 'w', the kinged ones
 * are 'B'and 'W', and empty spaces are '*'
 * inputs:
 *    char board[NUM_ROWS][NUM_COLS] - an NUM_ROWSxNUM_COLS board
 * outputs:
 *    none. prints the results.
 */
void print_board(char board[NUM_ROWS][NUM_COLS]);

/* remove_max
 * removes all instances of the maximum item in an array
 * returns the maximum value
 * inputs:
 *   int array[] : an integer array
 *   uint length : length of array
 * output:
 *   int : maximum value in array
 */
int remove_max(int array[], unsigned int length);

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
void init_board(char board[NUM_ROWS][NUM_COLS]);

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
unsigned int row, unsigned int col);

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
double *perimeter);

/* remove_max_in_out
 * removes maximum value from an array and updates its length
 * inputs:
 *   int array[] : an integer array
 *   uint *length : length of array
 * outputs:
 *   uint *length : new length of array
 */
int remove_max_in_out(int array[], unsigned int *length);

#endif
