#include "addressbook.h"

/**
* This file is to contain the main menu loop and thus it will have console
* output, meaning printf's are expected to be seen in this file.
* 
* After the user enters a command, then the corresponding function is to be
* called from commands.c, e.g., "forward" corresponds to "commandForward(...)".
*/

void showStudentInformation() {
	printf("%s%s\n", DASH_LINE, DASH_LINE);
	printf("Student Name: Angel English\n");
	printf("Student Number: 3543536\n");
	printf("Advanced Programming Techniques, Assignment 2, Semester 1 2017\n");
	printf("%s%s\n", DASH_LINE, DASH_LINE);
}

int main(int argc, char ** argv)
{

	showStudentInformation();
    printf("> Goodbye. \n\n");

    return EXIT_SUCCESS;
}
