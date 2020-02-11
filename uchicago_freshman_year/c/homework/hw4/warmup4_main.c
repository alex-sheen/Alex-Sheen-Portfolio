#include <stdio.h>
#include <stdlib.h>
#include "hw4_provided.h"
#include "warmup4.h"
/* test_count_vowels
 * test function for count_vowels
 * inputs:
 *   char str[] : given string
 *   uint expected : expected number of vowels
 * outputs:
 *   prints results of test
 */
void test_count_vowels(char str[], unsigned int expected)
{
	unsigned int result = count_vowels(str);
	//if count_vowels has expected result
	if(result == expected)
	{
		printf("test_count(string) == %u\n", result);
	}
	//else test failed
	else
	{
		printf("test_count(string) == %u, expected %u, FAILURE\n",
		result,expected);
	}
	
}
/* test_make_lowercase
 * test function for make_lowercase
 * inputs:
 *   char str[] : given string
 *   char str_expected[] : expected string
 * outputs:
 *   prints results of test
 */
void test_make_lowercase(char str[], char str_expected[])
{
	make_lowercase(str);
	int i = 0;
    unsigned int valid = 1;
    //while loop checks if each character is the same in the 2 arrays
    while(str[i] != '\0' && str_expected[i] != '\0')
    {
        printf("str : %c | exp : %c\n",str[i],str_expected[i]);
        //if chars don't match
        if(str[i] != str_expected[i])
        {
            valid = 0;
        }
    i++;
    }
    //checks to make sure the two arrays have the same length
    if(str[i] != '\0' || str_expected[i] != '\0')
    {
        valid = 0;
    }
    //if the two arrays match
    if(valid == 1)
	{
		printf("test_make_lowercase(str) was a SUCCESS\n");
	}
	//else test failed
	else
	{
		printf("test_make_lowercase(str) was a FAILURE\n");
	}
	
}




int main()
{
	// declare variables
	unsigned int r[ROWS][COLS];
        unsigned int g[ROWS][COLS];
        unsigned int b[ROWS][COLS];
        unsigned int width;
        unsigned int length;
	char str1[] = {'H','o','w','d','y',' ','T','H','E','R','E','!','\0'};
	char str2[] = {'a','B','E','U','u','d','b','!','3','z','\0'};
	char str3[] = {'b','n','!','k','\0'};

	char str1_lower[] = 
		{'h','o','w','d','y',' ','t','h','e','r','e','!','\0'};
	char str2_lower[] = {'a','b','e','u','u','d','b','!','3','z','\0'}; 

    printf("----- count_vowels ----- \n");
	test_count_vowels(str1,3);
	test_count_vowels(str2,4);
	test_count_vowels(str3,0);
    
    printf("----- make_lowercase ----- \n");
	test_make_lowercase(str1,str1_lower);
    test_make_lowercase(str2,str2_lower);
	
    printf("----- make_horizontal_stripes -----\n");
	make_horizontal_stripes(r, g, b, 1, 30, 144, 255, ROWS, COLS);
	provided_print_image_to_html("my_horiz_stripes.html",r,g,b,ROWS, COLS);
    make_horizontal_stripes(r, g, b, 3, 255, 0, 0, ROWS, COLS);
    provided_print_image_to_html("my_horiz_stripes_red.html",r,g,b,ROWS,COLS);
	
    printf("----- make_checker_board -----\n");
	make_checker_board(r,g,b,4,30,144,255, 12, 12);
	provided_print_image_to_html("my_checkboard.html",r,g,b,12, 12);
    make_checker_board(r,g,b,2,255,0,0,12,12);
    provided_print_image_to_html("my_checkboard_red.html",r,g,b,12,12);

}
