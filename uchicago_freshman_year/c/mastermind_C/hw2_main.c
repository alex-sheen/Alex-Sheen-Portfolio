#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "hw2.h"  // see how we're including the file again?
#include "mastermind.h" // another one!?! So that this code can be separate

// remember to create a test function for each function you 
// are implementing. This test function will call the function
// and compare the result to the expected result.

unsigned int print_menu()
{
	unsigned int result;
	printf("\t0: Exit\n");
	printf("\t1: Play Mastermind\n");
	printf("\t2: Test Mastermind Functions\n");
	printf("What would you like to play? ");
	scanf("%u", &result);

	return result;
}

int main()
{
    int choice = 0;

    do 
    {
	choice = print_menu();

	switch (choice) {
	   case (1): play_mastermind(); break;
	   case (2): test_mastermind(); break;
	   case (0): break;
	   default: printf("Invalid choice. Try again.\n");
	}
	
    } while (choice != 0);
}

