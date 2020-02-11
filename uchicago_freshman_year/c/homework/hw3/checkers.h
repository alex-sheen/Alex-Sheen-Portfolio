#ifndef CHECKERS_H
#define CHECKERS_H
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
void print_board( char board[NUM_ROWS][NUM_COLS] );

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

/* min
 * returns minimum of two unsigned ints
 * inputs:
 *   uint f : first num
 *   uint s : second num
 * outputs:
 *   uint : minimum of the two nums
 */
unsigned int min(unsigned int f, unsigned int s);

/* max
 * returns maximum of two unsigned ints
 * inputs:
 *   uint f : first num
 *   uint s : second num
 * outputs:
 *   uint : maximum of the two nums
 */
unsigned int max(unsigned int f, unsigned int s);


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

/* check_move
 * checks if move is valid
 * inputs:
 *   char piece : current player piece
 *   uint startrow : start row
 *   uint startcol : start column
 *   int endrow : end row
 *   int endcol : end column
 *   char board[][] : board array
 * outputs:
 *   uint : 0 = not valid
 *          1 = valid
 */
unsigned int check_move(char piece, unsigned int startrow,unsigned int startcol
,int endrow, int endcol, char board[NUM_ROWS][NUM_COLS]);

/* check_moves
 * checks if there are any valid moves froma  position
 * inputs:
 * char board[][] : board array
 *   uint row : starting row
 *   uint col : starting column
 * outputs:
 *   uint : 
 *          0 = not valid
 *          1 = valid
 */
unsigned int check_moves(char board[NUM_ROWS][NUM_COLS],unsigned int row,
unsigned int col);

/* player_won
 * checks if recent player move resulted in a win
 * player can win either by capturing all opponents pieces or if opponent
 * has no valid moves left
 * inputs:
 *   char board[][] : board array
 *   char player : player that just moved
 * output:
 *   0 if no win
 *   1 if win
 */
int player_won(char board[NUM_ROWS][NUM_COLS], char player);

/* do_move
 * performs a move if it is valid, performs validity checks
 * checks:
 *   start and end locations must be valid
 *   blue moves down, white moves up, unless kings
 *   checkers move diagonally
 *   move one space into blank or two if jumping an opponent
 *   jumping an opponent grants another move
 *   reaching the end results in a king (capital letter)
 * inputs:
 *   char player : player turn
 *   uint startrow : start row
 *   uint startcol : start column
 *   uint endrow : end row
 *   uint endcol : end column
 *   char board[][] : board array
 * output:
 *   0 : invalid move
 *   1 : valid move that moved one space
 *   2 : valid move that jumped an opponent
 */
unsigned int do_move(char player, unsigned int startrow, unsigned int startcol,
unsigned int endrow, unsigned int endcol, char board[8][8]);

/* test_checkers()
 * calls all test functions
 * inputs:
 *   none
 * output:
 *   none
 */
void test_checkers();

/* play_checkers
 * runs the checkers game
 * inputs:
 *   none
 * output:
 *   prints game states
 */
void play_checkers();
#endif
