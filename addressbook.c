#include "addressbook.h"

/**
* This file is to contain the main menu loop and thus it will have console
* output, meaning printf's are expected to be seen in this file.
* 
* After the user enters a command, then the corresponding function is to be
* called from commands.c, e.g., "forward" corresponds to "commandForward(...)".
*/
#include <stdio.h>
#define BUFFER_SIZE 200
#define STR_LEN 200
#define STATE_UNLOADED 0
#define DELIM " "

void showStudentInformation() {
	char* name = "Student Name: Angel English";
	char* number = "Student Number: 3543536";
	char* apt = "Advanced Programming Techniques, "
				"Assignment 2, Semester 1 2017";
	char* line = charLine('-', strlen(apt));
	printf("%s\n", line);
	printf("%s\n", name);
	printf("%s\n", number);
	printf("%s\n", apt);
	printf("%s\n", line);
	free(line);
}

void printSize(AddressBookArray * arr, int i) {
	printf("size: %d\n", (int)sizeof(arr->telephones[i]));
}

int main(int argc, char ** argv)
{
	AddressBookList *list;

	list = commandLoad("sml.txt");
	if(list == NULL)
		return EXIT_FAILURE;
	commandDisplayV(list);
	/*printf("\nFREEING\n");*/

	commandSort(list, compareName);
	commandDisplay(list);
	commandSort(list, compareID);
	commandDisplay(list);

	freeAddressBookList(list);

	menu();

    return EXIT_SUCCESS;
}

void menu() {
	char ** tokens;
	char str[STR_LEN];
	int menu_state = STATE_UNLOADED;


	for(;;) {

		/*printMenu(menu_sate);*/
		showStudentInformation();

		if(getStr(str, STR_LEN)) {

			/* tokens is the address of the first position */
			tokens = h_token(str, DELIM);
			
			/*load command*/	
			if(strcmp(COMMAND_LOAD, tokens[0]) == 0 && 
					menu_state == STATE_UNLOADED) {
			/*quit command*/
			} else if(strcmp(COMMAND_QUIT, tokens[0]) == 0) {
				free(tokens);
				return;	
			/*no command found*/
			} else {
				printf("Invalid Input\n");
			}
			free(tokens);
		}
	}
}

