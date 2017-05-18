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
	AddressBookList *list = NULL;

	
	menu();

	return 1;
	list = createAddressBookList();
	commandLoad("sml.txt", list);

	if(list == NULL)
		return EXIT_FAILURE;

	commandDisplay(list);
	/*printf("\nFREEING\n");*/

	/*commandSort(list, compareName);
	commandDisplay(list);
	commandSort(list, compareID);
	commandDisplay(list);*/
	
	commandUnload(list);
	commandDisplay(list);

	freeAddressBookList(list);


    return EXIT_SUCCESS;
}

void menu() {
	char ** tokens;
	char str[STR_LEN];
	AddressBookList *list;
	int (*compare)(const void*, const void*);

/*
#define COMMAND_SORT "sort"
#define COMMAND_SORT_NAME "name"
#define COMMAND_SORT_ID "id"
#define COMMAND_QUIT "quit"
*/

/*
#define COMMAND_FORWARD "forward"
#define COMMAND_BACKWARD "backward"
#define COMMAND_INSERT "insert"
#define COMMAND_ADD "add"
#define COMMAND_FIND "find"
#define COMMAND_DELETE "delete"
#define COMMAND_REMOVE "remove"
#define COMMAND_SAVE "save"
*/

	showStudentInformation();

	list = createAddressBookList();
	while(TRUE) {

		if(getStr(str, STR_LEN)) {

			/* tokens is the address of the first position */
			tokens = h_token(str, DELIM);

			/*load*/	
			if(strcmp(COMMAND_LOAD, tokens[0]) == 0) {
				commandLoad(tokens[1], list);

			/* unload */
			} else if(strcmp(COMMAND_UNLOAD, tokens[0]) == 0) {
				commandUnload(list);

			/* display */
			} else if(strcmp(COMMAND_DISPLAY, tokens[0]) == 0) {
				commandDisplay(list);

			/* sort */
			} else if(strcmp(COMMAND_SORT, tokens[0]) == 0) {
				compare = NULL;
				/* check tokens1 is there */
				if(tokens[1] != NULL) {
					/* check what command it is */
					if(strcmp(COMMAND_SORT_NAME, tokens[1]) == 0) {
						compare = compareName;
					} else if(strcmp(COMMAND_SORT_ID, tokens[1]) == 0) {
						compare = compareID;
					} else {
						printf("invalid sort condition. valid ones are:\nname\nid\n");
					}
				} else {
					printf("invalid sort condition. valid ones are:\nname\nid\n");
				}

				if(compare != NULL)
					commandSort(list, compare);

			/*quit */
			} else if(strcmp(COMMAND_QUIT, tokens[0]) == 0) {
				free(tokens);
				break;
			/*not a command*/
			} else {
				printf("Invalid Input\n");
			}
			free(tokens);
		}
	}
	freeAddressBookList(list);
}
















