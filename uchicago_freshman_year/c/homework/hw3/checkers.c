#include <stdlib.h>
#include <stdio.h>
#include "warmup3.h"
/* Alex Sheen, alexsheen */
/* CS152, Winter 2019 */
/* hw 3 */


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
}
/* min
 * returns minimum of two unsigned ints
 * inputs:
 *   uint f : first num
 *   uint s : second num
 * outputs:
 *   uint : minimum of the two nums
 */
unsigned int min(unsigned int f, unsigned int s)
{
if(f<s)
{
return f;
}
return s;
}

/* max
 * returns maximum of two unsigned ints
 * inputs:
 *   uint f : first num
 *   uint s : second num
 * outputs:
 *   uint : maximum of the two nums
 */
unsigned int max(unsigned int f, unsigned int s)
{
if(f>s)
{
return f;
}
return s;
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
,int endrow, int endcol, char board[NUM_ROWS][NUM_COLS])
{
//one space moves
if(abs((int) startrow - endrow) == 1 && abs((int) startcol - endcol == 1))
{
    char other_piece = board[endrow][endcol];
    //if move is on to a blank space
    if(other_piece == '*')
    {
        return 1;
    }
    //else space is occupied
    else
    {
        return 0;
    }
}
//two space moves
else if(abs((int) startrow - endrow) == 2 && abs((int) startcol - endcol) == 2)
{
    char other_piece = board[endrow][endcol];
    char jumped_piece = board
                        [startrow + (endrow - (int) startrow)/2]
                        [startcol + (endcol - (int) startcol)/2];
    //printf("\ninside two space move, player:%c, other:%c, jumped:%c, end:%u,%u\n"
    //,piece,other_piece,jumped_piece,endrow,endcol);
    //initial check that piece is jumping to a blank space
    if(other_piece == '*')
    {
        if((piece == 'w' || piece == 'W') 
            && (jumped_piece == 'b' || jumped_piece == 'B'))
        {
            return 1;
        }
        else if((piece == 'b' || piece == 'B')
            && (jumped_piece == 'w' || jumped_piece == 'W'))
        {
            return 1;
        } 
    }
    //else jumping to occupied space
    else
    {
        return 0;
    }
}
//else, the input move should be ignored because it was an invalid move
//      made at the border of the board
return 0;
}

/* check_moves
 * checks if there are any valid moves froma  position
 * inputs:
 * char board[][] : board array
 *   uint row : starting row
 *   uint col : starting column
 * outputs:
 *   uint : 
 *          0 = no valid moves
 *          1 = at least one valid move
 */
unsigned int check_moves(char board[NUM_ROWS][NUM_COLS],unsigned int row,
unsigned int col)
{
int y_offset = 1;
char player = board[row][col];
//prepares y_offset to be used to check valid moves
if(player == 'w')
{
    //set to -1 because 'w' can only move up the board
    y_offset = -1;
}
//pos and neg target columns, min and max are to prevent array errors
//if start pos is 0 or 7, which could cause index out of bounds
int target_col_pos_1 = min(7, max(0, ((int)col + 1)));  
int target_col_neg_1 = min(7, max(0, ((int)col - 1)));
int target_col_pos_2 = min(7, max(0, ((int)col + 2)));
int target_col_neg_2 = min(7, max(0, ((int)col - 2)));

int target_row_1 = min(7,max(0,((int)row+y_offset)));
int target_row_2 = min(7,max(0,((int)row+y_offset*2))); 

int target_row_pos_1 = min(7,max(0,((int)row+1)));
int target_row_neg_1 = min(7,max(0,((int)row-1)));
int target_row_pos_2 = min(7,max(0,((int)row+2)));
int target_row_neg_2 = min(7,max(0,((int)row-2)));

//if it's a non-king piece
if(player == 'w' || player == 'b')
{
    //checks first diagonal
    if(check_move(player,row,col,target_row_1,target_col_pos_1,board) == 1)
    {
        return 1;
    }
   //if other diagonal is valid
    if(check_move(player,row,col,target_row_1,target_col_neg_1,board) == 1)
    { 
        return 1;
    }
    //if diagonal jump valid
    if(check_move(player,row,col,target_row_2,target_col_pos_2,board) == 1)
    {
        return 1;
    }
    //if other diagonal jump valid
    if(check_move(player,row,col,target_row_2,target_col_neg_2,board) == 1)
    {
        return 1;
    } 
}
//checks for '*' at the surrounding diagonals one away from king
if(player == 'W' || player == 'B'){
    if(
    (board[target_row_pos_1][target_col_pos_1] == '*'
        && abs((int) row - target_row_pos_1) == 1
        && abs((int) col - target_col_pos_1) == 1)    
    || (board[target_row_pos_1][target_col_neg_1] == '*'
        && abs((int) row - target_row_pos_1) == 1
        && abs((int) col - target_col_neg_1) == 1)
    || (board[target_row_neg_1][target_col_pos_1] == '*'
        && abs((int) row - target_row_neg_1) == 1
        && abs((int) col - target_col_pos_1) == 1)
    || (board[target_row_neg_1][target_col_neg_1] == '*'
        && abs((int) row - target_row_neg_1) == 1
        && abs((int) col - target_col_neg_1) == 1))
    {
        return 1;
    }
    //checks for '*' at the surrounding diagonals two away from king, for jumps
    else if(check_move
            (player,row,col,target_row_pos_2,target_col_pos_2,board)== 1)
    {
        return 1;
    }
    else if(check_move
            (player,row,col,target_row_pos_2,target_col_neg_2,board)== 1)
    {
        return 1;
    }
    else if(check_move
            (player,row,col,target_row_neg_2,target_col_pos_2,board)== 1)
    {
        return 1;
    }
    else if(check_move
            (player,row,col,target_row_neg_2,target_col_neg_2,board)== 1)
    {
        return 1;
    }
}

//else, invalid move
return 0;
}
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
int player_won(char board[NUM_ROWS][NUM_COLS], char player)
{
//switches based on player
switch (player)
{
    case 'B':
        //runs through every pos in board
        for(int i = 0; i<NUM_ROWS; i++)
        {
            for(int j = 0; j<NUM_COLS; j++)
            {
                //if starting pos is white
                if(board[i][j] == 'w' || board[i][j] == 'W')
                {
                    if(check_moves(board,i,j) == 1)
                    {
                        return 0;
                    }
                }
            }
        }
        break;
    case 'W':
        //runs through every pos in board
        for(int i = 0; i<NUM_ROWS; i++)
        {
            for(int j = 0; j<NUM_COLS; j++)
            {
                //if starting pos is black
                if(board[i][j] == 'b' || board[i][j] == 'B')
                {
                    if(check_moves(board,i,j) == 1)
                    {
                        return 0;
                    }
                }
            }
        }
        break;
    default:
        return 0;
        break;
}
return 1;
}

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
unsigned int endrow, unsigned int endcol, char board[8][8])
{
//checks if start character is the correct player
unsigned int curr_p = board[startrow][startcol];
if((player == 'B' && curr_p != 'b' && curr_p != 'B') 
|| (player == 'W' && curr_p != 'w' && curr_p != 'W'))
{
    printf("bad starting position\n");
    return 0;
}
char end_char = board[startrow+1]
                [(startcol + ((int) endcol - (int) startcol)/2)];
unsigned int midrow = (startrow + ((int) endrow - (int) startrow)/2);
unsigned int midcol = (startcol + ((int) endcol - (int) startcol)/2);
//switch based on start piece      
switch (board[startrow][startcol])
{

    case 'b': // if blue start
        //checks if it's a one space move
        if(abs((int) startcol - (int) endcol) == 1 &&
             (int)endrow - (int) startrow == 1 &&
             board[endrow][endcol] == '*')
        {
            //checks if it should become a king
            if(endrow == 7)
            {
                place_piece(board,'B',endrow,endcol);
            }
            //else it should stay a regular piece
            else
            {
                place_piece(board,'b',endrow,endcol);
            }
            board[startrow][startcol] = '*';
            return 1;
        }
        //checks if it's a jump move
       else if(abs((int) startcol - (int) endcol) == 2 &&
            (int)endrow - (int)startrow == 2 &&
            board[endrow][endcol] == '*' &&
             (end_char == 'w' || end_char == 'W'))
        {
            board[startrow][startcol] = '*';
            board[startrow+1]
                      [(startcol + ((int) endcol - (int) startcol)/2)] = '*';
            //checks if it should become a king
            if(endrow == 7)
            {
                place_piece(board,'B',endrow,endcol);
            }
            //else it should stay a regular piece
            else
            {
                place_piece(board,'b',endrow,endcol);
            }
            return 2;
        }
        break;
    case 'w': // if white start 
        end_char = board[startrow-1]
                        [(startcol + ((int) endcol - (int) startcol)/2)]; 
        //checks if its a one space move
        if(abs((int) startcol - (int) endcol) == 1 &&
             (int)startrow - (int) endrow == 1 &&
             board[endrow][endcol] == '*')
        {
            board[startrow][startcol] = '*';
            //checks if it should become a king
            if(endrow == 0)
            {
                place_piece(board,'W',endrow,endcol);
            }
            //else it should stay a regular piece
            else
            {
                place_piece(board,'w',endrow,endcol);
            }
            return 1;
        } 
        else if(abs((int) startcol - (int) endcol) == 2 &&
            (int)startrow - (int)endrow == 2 &&
            board[endrow][endcol] == '*' && 
            (end_char == 'b' || end_char == 'B'))
        {
            board[startrow][startcol] = '*';
            board[startrow-1]
                      [(startcol + ((int) endcol - (int) startcol)/2)] = '*';
            //if it should become a king
            if(endrow == 0)
            {
                place_piece(board,'W',endrow,endcol);
            }
            else
            {
                place_piece(board,'w',endrow,endcol);
            }
            return 2;
        }
        break;
    case '*': // if start position is *
        break;
    default: // else, it is a blue or white king
        //checks if its a one space move
        if(abs((int) startcol - (int) endcol) == 1 &&
             abs((int)startrow - (int) endrow) == 1 &&
             board[endrow][endcol] == '*')
        {
            place_piece(board,board[startrow][startcol],endrow,endcol);
            board[startrow][startcol] = '*';
            return 1;
        }
        else if(abs((int) startcol - (int) endcol) == 2
            && abs((int)startrow - (int)endrow) == 2 
            && board[endrow][endcol] == '*' 
            && board[midrow][midcol] != (player=='B'?'b':'w')
            && board[midrow][midcol] != '*'
            && board[midrow][midcol] != (player=='B'?'B':'W'))
        {
            place_piece(board,board[startrow][startcol],endrow,endcol);
            board[startrow][startcol] = '*';
            board[midrow][midcol] = '*';
            return 2;
        }
        break;

}
return 0;
}

/* computer_move
 * computer decides the next moe
 * inputs:
 *   char board[][] : given board
 *   char player : the player turn
 *   uint *row : row of the move
 *   uint *col : column of the move
 * output:
 *    0 : no valid moves
 *    1 : made a move, modifies *row and *col
 */
int computer_move(char board[NUM_ROWS][NUM_COLS], char player, unsigned int
*row, unsigned int *col)
{
//if the other player own, then the computer has no valid moves
if(player_won(board, (player == 'B'?'W':'B')) == 1)
{
    return 0;
}
//else, there must be at least one piece with a valid move
unsigned int srows[NUM_ROWS*NUM_COLS];
unsigned int scols[NUM_ROWS*NUM_COLS];
unsigned int length = 0;
//runs through array looking for any valid starting positions
for(int i = 0; i<NUM_ROWS; i++)
{
    for(int j = 0; j<NUM_COLS; j++)
    {
        if(board[i][j] == (player == 'B'?'b':'w')
            || board[i][j] == (player == 'W'?'W':'B'))
        {
            srows[length] = i;
            scols[length] = j;
            length++;
        }
    }
}
unsigned int moved = 0;
//while a move has not been made yet
while(moved == 0)
{
unsigned int index = rand() % length;
unsigned int sr = srows[index];
unsigned int sc = scols[index];
    //checks if it's a valid starting place with at least one valid move
if(check_moves(board,sr,sc) == 1)
{
    //runs through possible end coords
    for(int dr = -2; dr<=2; dr++)
    {
        for(int dc = -2; dc<=2;dc++)
        {
            //makes sure end coordinates are within bounds
            //and if the move is valid
            if(sr+dr >= 0 && sr+dr <= 7 && sc+dc >= 0 &&
                sc+dc <= 7
                && do_move(player,sr,sc,sr+dr,sc+dc,board) >= 1)
            {
                *row = sr+dr;
                *col = sc+dc;
                return 1;
            }
        }
    }
}
}
return 0;
}



// ---------------------------- Test Function ---------------------------------


/* clear_board
 * sets the checkerboard to all '*' for testing purposes
 * An 8x8 board looks like this: 
 * inputs:
 *    char board[NUM_ROWS][NUM_COLS] - an NUM_ROWSxNUM_COLS board
 * outputs:
 *    none.
 */
void clear_board(char board[NUM_ROWS][NUM_COLS])
{
//initializing *
for(int i = 0; i < NUM_ROWS; i++)
{
    for(int j = 0; j < NUM_COLS; j++)
    {
    board[i][j] = '*';
    }
}
}

/* test_place_piece
 * test function for place_piece
 * inputs:
 *   char board[][] : board array
 *   char player : player character
 *   uint row : target row
 *   uint col : target column
 *   uint expected : expected result, 1 = valid, 0 = invalid
 */
void test_place_piece(char board[NUM_ROWS][NUM_COLS], char player,
unsigned int row, unsigned int col, unsigned int expected)
{
//if test_place_piece gives expected result
if((place_piece(board,player,row,col)) == expected)
{
    printf("test_place_piece(board below,%c,%u,%u)==%u, SUCCESS\n",
    player,row,col,expected);
    print_board(board);    
}

else
{
    printf("place_piece(board below,%c,%u,%u),\
 expected %u, got %u, FAILURE\n", player, row, col,
 expected, place_piece(board,player,row,col));
    print_board(board);
}
//resets the board so it can be used in further testing
init_board(board);
}

/* test_do_move
 * test function for do_move
 * inputs:
 *   char player : player character
 *   uint startrow : start row
 *   uint startcol : start column
 *   uint endrow : end row
 *   uint endcol : end col
 *   char board[][] : board array
 *   uint expected : expected result, 0 = invalid, 1 = 1 space, 2 = jump
 */
void test_do_move(char player, unsigned int startrow, unsigned int startcol,
unsigned int endrow, unsigned int endcol, char board[NUM_ROWS][NUM_COLS],
unsigned int expected)
{
printf("initial board to test:\n");
print_board(board);
//if test_do_move gives expected result
if((do_move(player,startrow,startcol,endrow,endcol,board)) == expected)
{
    printf("do_move(%c,%u,%u,%u,%u,board above)==%u, SUCCESS\n",
    player,startrow,startcol,endrow,endcol,expected);
    print_board(board);    
}
else
{    
    printf("do_move(%c,%u,%u,%u,%u,board above) expected %u, got %u, FAILURE\n"
    ,player,startrow,startcol,endrow,endcol,expected,
    do_move(player,startrow,startcol,endrow,endcol,board));
}
//resets the board so it can be used in further testing
init_board(board);
}

/* test_player_won
 * test function for player_won
 * inputs:
 *   char board[][] : board array
 *   char player : player character
 *   uint expected : expected result, 0 = no win, 1 = win
 */
void test_player_won(char board[NUM_ROWS][NUM_COLS], char player,
unsigned int expected)
{
//if test_player_won gives expected result
if((player_won(board,player)) == expected)
{
    printf("player_won(board below, %c)==%u, SUCCESS\n",
    player,expected);
    print_board(board);    
}
else
{    
    printf("player_won(board below, %c) expected %u, got %u, FAILURE\n"
    ,player,expected,
    player_won(board,player));
    print_board(board);
}
//clears the board so it can be used in further testing
clear_board(board);
}

/* test_computer_move
 * test function for computer_move
 * inputs:
 *   char board[][] : board
 *   char player : player character
 *   uint expected : expected result, 1 = made move, 0 = no valid moves
 * outputs:
 *   prints the before and after board as well as the end row and col that
 *   the computer decided on
 */
void test_computer_move(char board[NUM_ROWS][NUM_COLS], char player,
unsigned int expected)
{
unsigned int row = 0;
unsigned int col = 0;
printf("initial board: %c's turn\n",player);
print_board(board);
//if test_computer_move gives expected result
unsigned int computer_result = computer_move(board,player,&row,&col);
if(computer_result == expected)
{
    printf("computer_move(board above,%c,%u,%u)==%u, SUCCESS\n",
    player,row,col,expected);
    print_board(board);    
}

else
{
    printf("computer_move(board below,%c,%u,%u),\
 expected %u, got %u, FAILURE\n", player, row, col,
 expected, computer_result);
}
//resets the board so it can be used in further testing
clear_board(board);
}

/* test_checkers()
 * calls all test functions
 * inputs:
 *   none
 * output:
 *   none
 */
void test_checkers()
{
char test_board[8][8] = { {'*','b','*','b','*','b','*','b'},                      
                           {'b','*','b','*','b','*','b','*'},                     
                           {'*','b','*','b','*','b','*','b'},                     
                           {'*','*','*','*','*','*','*','*'},                     
                           {'*','*','*','*','*','*','*','*'},                     
                           {'w','*','w','*','w','*','w','*'},                     
                           {'*','w','*','w','*','w','*','w'},                     
                           {'w','*','w','*','w','*','w','*'}  };

printf("----- Test Functions -----\n");
printf("\n ----- test_place_piece ----- \n");
test_place_piece(test_board,'b',1,1,1);
test_place_piece(test_board,'b',1,0,0);
test_place_piece(test_board,'b',5,0,0);
test_place_piece(test_board,'w',1,1,1);
test_place_piece(test_board,'w',1,0,0);
test_place_piece(test_board,'w',5,0,0);
printf("\n ----- test_do_move ----- \n");
//testing one space moves
test_do_move('B',2,1,3,0,test_board,1);
test_do_move('B',2,1,3,2,test_board,1);
test_do_move('B',2,1,3,1,test_board,0);
test_do_move('W',5,0,4,1,test_board,1);
test_do_move('W',5,2,4,1,test_board,1);
test_do_move('W',5,2,4,2,test_board,0);
test_do_move('W',5,2,5,1,test_board,0);
place_piece(test_board,'w',3,2);
test_do_move('W',3,2,4,3,test_board,0);
printf(" **** testing piece to king **** \n");
clear_board(test_board);
place_piece(test_board,'w',1,0);
test_do_move('W',1,0,0,1,test_board,1);
clear_board(test_board);
place_piece(test_board,'b',6,1);
test_do_move('B',6,1,7,2,test_board,1);
//testing jumps
place_piece(test_board,'w',3,2);//jump diagonally right
test_do_move('B',2,1,4,3,test_board,2);
place_piece(test_board,'w',3,2);//jump diagonally left
test_do_move('B',2,3,4,1,test_board,2);
place_piece(test_board,'w',3,2);//vertical test
test_do_move('B',2,3,4,3,test_board,0);
place_piece(test_board,'w',4,2);//backwards
place_piece(test_board,'b',3,1);
test_do_move('B',3,1,2,0,test_board,0);
place_piece(test_board,'b',4,1);//jump diagonally right
test_do_move('W',5,0,3,2,test_board,2);
place_piece(test_board,'b',4,1);//jump diagonally left
test_do_move('W',5,2,3,0,test_board,2);
place_piece(test_board,'b',4,1);//vertical test
test_do_move('W',5,2,3,2,test_board,0);
place_piece(test_board,'b',4,2);//backward test
place_piece(test_board,'w',3,1);
test_do_move('W',3,1,5,3,test_board,0);
//testing king one space move
place_piece(test_board,'W',3,1);//white diagonals
test_do_move('W',3,1,4,0,test_board,1);
place_piece(test_board,'W',3,1);
test_do_move('W',3,1,4,2,test_board,1);
place_piece(test_board,'W',3,1);
test_do_move('W',3,1,2,0,test_board,1);
place_piece(test_board,'W',3,1);
test_do_move('W',3,1,2,2,test_board,1);
place_piece(test_board,'W',3,1);
test_do_move('W',3,1,2,1,test_board,0);
place_piece(test_board,'W',3,2);
test_do_move('W',3,1,3,2,test_board,0);
place_piece(test_board,'B',3,1);//black diagonals
test_do_move('B',3,1,4,0,test_board,1);
place_piece(test_board,'B',3,1);
test_do_move('B',3,1,4,2,test_board,1);
place_piece(test_board,'B',3,1);
test_do_move('B',3,1,2,0,test_board,1);
place_piece(test_board,'B',3,1);
test_do_move('B',3,1,2,2,test_board,1);
place_piece(test_board,'B',3,1);
test_do_move('B',3,1,2,1,test_board,0);
place_piece(test_board,'B',3,1);
test_do_move('B',3,1,3,2,test_board,0);
place_piece(test_board,'B',3,1);
test_do_move('B',3,1,6,2,test_board,0);
//testing king jumps
place_piece(test_board,'B',3,1);
place_piece(test_board,'w',4,2);
test_do_move('B',3,1,5,3,test_board,2);
place_piece(test_board,'B',3,1);
place_piece(test_board,'W',4,2);
test_do_move('B',3,1,5,3,test_board,2);
place_piece(test_board,'B',3,1);
place_piece(test_board,'b',4,2);
test_do_move('B',3,1,5,3,test_board,0);
place_piece(test_board,'B',3,1);
place_piece(test_board,'B',4,2);
test_do_move('B',3,1,5,3,test_board,0);
printf("\n ----- player_won -----\n");
clear_board(test_board);
test_player_won(test_board,'B',1);
test_player_won(test_board,'W',1);
place_piece(test_board,'w',4,3);
test_player_won(test_board,'B',0);
place_piece(test_board,'b',4,3);
test_player_won(test_board,'W',0);
place_piece(test_board,'b',4,3);
place_piece(test_board,'w',3,2);
place_piece(test_board,'w',3,4);
place_piece(test_board,'w',5,2);
place_piece(test_board,'w',5,4);
place_piece(test_board,'w',2,1);
place_piece(test_board,'w',2,5);
place_piece(test_board,'w',6,1);
place_piece(test_board,'w',6,5);
test_player_won(test_board,'W',1);
place_piece(test_board,'b',4,3);
place_piece(test_board,'w',3,2);
place_piece(test_board,'w',3,4);
place_piece(test_board,'w',5,2);
place_piece(test_board,'w',5,4);
place_piece(test_board,'w',2,1);
place_piece(test_board,'w',2,5);
place_piece(test_board,'w',6,1);
test_player_won(test_board,'W',0);
place_piece(test_board,'w',4,3);
place_piece(test_board,'b',3,2);
place_piece(test_board,'b',3,4);
place_piece(test_board,'b',5,2);
place_piece(test_board,'b',5,4);
place_piece(test_board,'b',2,1);
place_piece(test_board,'b',2,5);
place_piece(test_board,'b',6,1);
test_player_won(test_board,'B',1);
place_piece(test_board,'W',4,3);
place_piece(test_board,'b',3,2);
place_piece(test_board,'b',3,4);
place_piece(test_board,'b',5,2);
place_piece(test_board,'b',5,4);
place_piece(test_board,'b',2,1);
place_piece(test_board,'b',2,5);
place_piece(test_board,'b',6,1);
test_player_won(test_board,'B',0);
printf("\n ----- computer_move -----\n");
clear_board(test_board);
place_piece(test_board,'w',4,3);
test_computer_move(test_board,'W',1);
place_piece(test_board,'b',4,3);
test_computer_move(test_board,'B',1);
place_piece(test_board,'b',4,3);
place_piece(test_board,'w',3,2);
place_piece(test_board,'w',3,4);
place_piece(test_board,'w',5,2);
place_piece(test_board,'w',5,4);
place_piece(test_board,'w',2,1);
place_piece(test_board,'w',2,5);
place_piece(test_board,'w',6,1);
place_piece(test_board,'w',6,5);
test_computer_move(test_board,'B',0);
place_piece(test_board,'b',4,3);
place_piece(test_board,'w',3,2);
place_piece(test_board,'w',3,4);
place_piece(test_board,'w',5,2);
place_piece(test_board,'w',5,4);
place_piece(test_board,'w',2,1);
place_piece(test_board,'w',2,5);
place_piece(test_board,'w',6,1);
test_computer_move(test_board,'B',1);
place_piece(test_board,'W',4,3);
place_piece(test_board,'b',3,2);
place_piece(test_board,'b',3,4);
place_piece(test_board,'b',5,2);
place_piece(test_board,'b',5,4);
place_piece(test_board,'b',2,1);
place_piece(test_board,'b',2,5);
place_piece(test_board,'b',6,1);
test_computer_move(test_board,'W',1);
place_piece(test_board,'w',4,3);
place_piece(test_board,'b',3,2);
place_piece(test_board,'b',3,4);
place_piece(test_board,'b',5,2);
place_piece(test_board,'b',5,4);
place_piece(test_board,'b',2,1);
place_piece(test_board,'b',2,5);
place_piece(test_board,'b',6,1);
test_computer_move(test_board,'W',0);
init_board(test_board);
test_computer_move(test_board,'B',1);
place_piece(test_board,'b',3,4);
place_piece(test_board,'w',4,5);
test_computer_move(test_board,'B',1);
place_piece(test_board,'B',5,6);
place_piece(test_board,'w',4,5);
test_computer_move(test_board,'B',1);
place_piece(test_board,'B',5,6);
place_piece(test_board,'W',4,5);
test_computer_move(test_board,'B',1);



printf("\n ----- End of Testing ----- \n\n"); 

}


// --------------------------- Play Function ----------------------------------
void play_checkers()
{
        char again;
        char board[8][8] = { {'*','*','*','*','*','*','*','*'},
                             {'*','*','*','*','*','*','*','*'},
                             {'*','*','*','*','*','*','*','*'},
                             {'*','*','*','*','*','*','*','*'},
                             {'*','*','*','*','*','*','*','*'},
                             {'*','*','*','*','*','*','*','*'},
                             {'*','*','*','*','*','*','*','*'},
                             {'*','*','*','*','*','*','*','*'}  };
        init_board(board);
        print_board(board);
        int winner = 0;
        char player_turn = 'B';
        while (winner == 0)
        {
                unsigned int sr, sc, er, ec;
                unsigned int response;
                
                // obtain the player's move
                do {
                        printf("Player %c, in what row (0-7) is the piece you are moving located? ",player_turn);
                        scanf("%u",&sr);
                        if (sr >= NUM_ROWS)
                                printf("That is not a valid row. Try again.\n");
                } while (sr >= NUM_ROWS);
                do {
                        printf("Player %c, in what column (0-7) is the piece you are moving located? ",player_turn);
                        scanf("%u",&sc);
                        if (sc >= NUM_COLS)
                                printf("That is not a valid column. Try again.\n");
                } while (sc >= NUM_COLS);
                do {
                        printf("Player %c, to what row (0-7) do you want to move it? ",player_turn);
                        scanf("%u",&er);
                        if (er >= NUM_ROWS)
                                printf("That is not a valid row. Try again.\n");
                } while (er >= NUM_ROWS);
                do {
                        printf("Player %c, to what column (0-7) do you want to move it? ",player_turn);
                        scanf("%u",&ec);
                        if (ec >= NUM_COLS)
                                printf("That is not a valid column. Try again.\n");
                } while (ec >= NUM_COLS);

                // attempt to do the move
                response = do_move(player_turn, sr, sc, er, ec, board);

                // invalid move
                if (response == 0)
                {
                        printf("That is not a valid move. Try again.\n");
                }       
                // valid move, switch to other player
                else if (response == 1)
                {
                        winner = player_won(board, player_turn);
                        if (winner == 0)
                        {
                                printf("Valid move. Next player's turn\n");
                                print_board(board);
                                player_turn = (player_turn == 'B'?'W':'B');
                        }       
                        else
                                printf("Congratulations! Player %c won!\n",player_turn);
                }               
                // captured opponent's piece - gets another turn
                else // if (response == 2)
                {
                        winner = player_won(board, player_turn);
                        if (winner == 0)
                        {
                                printf("You jumped your opponent!\n");
                                do { 
                                        printf("Would you like to move again?\n");
                                        printf("Enter y for yes or n for no: \n");
                                        print_board(board);
                                        scanf(" %c",&again);
                                        if (again == 'n')
                                        {                
                                                player_turn = (player_turn == 'B'?'W':'B');
                                        }       
                                        else if (again != 'y')
                                        {
                                                printf("Invalid response.\n");
                                        }       
                                } while ((again == 'n') && (again == 'y'));
                        }       
                        else
                                printf("Congratulations! Player %c won!\n",player_turn);
                }   

        } // end of while no winner
}
