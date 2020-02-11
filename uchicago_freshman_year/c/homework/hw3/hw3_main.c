#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "checkers.h"
 
unsigned int print_menu()
{
	unsigned int result;
	printf("\t0: Exit\n");
	printf("\t1: Play Checkers\n");
	printf("\t2: Test Checkers Functions\n");
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
	   case (1): play_checkers(); break;
	   case (2): test_checkers(); break;
	   case (0): break;
	   default: printf("Invalid choice. Try again.\n");
	}
	
    } while (choice != 0);
}

