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

/**
 * returns the contents of the file 'fname'
 *//*
char* loadFileText(char* fname) {
	FILE *file;
	char buffer[BUFFER_SIZE];
	char *fileText = NULL;
	unsigned int size = 0;

	file = fopen(fname, "r");
	while(fgets(buffer, sizeof(char) * BUFFER_SIZE, file)) {
		if(buffer[0] == '#')
			continue;
		fileText = realloc(fileText, (size_t)(BUFFER_SIZE * ++size));
		strcat(fileText, buffer);

	}
	fclose(file);
	return fileText;
}*/

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
	/*AddressBookArray *array;
	int i;
	char *testPhone = "3543252366";*/
	
	AddressBookList *list;
	/*int nodeCount = 1;
	int i;
	AddressBookNode *tempNode;
	char tempStr[20];
	char *testPhone = "3543252366";*/
	showStudentInformation();

	/*printf("creating list\n");*/
	/*list = createAddressBookList();
	commandDisplay(list);*/
	/*printf("creating fake nodes\n");*/
	/*for(i = 0; i < nodeCount; i++) {
		sprintf(tempStr, "node: %d", i);
		tempNode = createAddressBookNode(i, tempStr);
		addTelephone(tempNode->array, "0123456789");
		addTelephone(tempNode->array, "3423454346");
		addTelephone(tempNode->array, testPhone);
		addTelephone(tempNode->array, "3196432827");
		removeTelephone(tempNode->array, testPhone);
		insertNode(list, tempNode);
	}*/
	/*printf("sizeof array: %d\n", (int)sizeof(list->head->array));*/
	/*commandDisplay(list);
	freeAddressBookList(list);*/

	list = commandLoad("sml.txt");
	if(list == NULL)
		return EXIT_FAILURE;
	commandDisplay(list);
	/*printf("\nFREEING\n");*/

	freeAddressBookList(list);

	list = createAddressBookList();
	commandDisplay(list);

	/*
	array = createAddressBookArray();
	printf("size: %d\n", (int)sizeof(*array));
	addTelephone(array, "1234567890");
	addTelephone(array, "0219874353");
	addTelephone(array, testPhone);
	addTelephone(array, "8921568302");
	removeTelephone(array, testPhone);
	printf("size: %d\n", (int)sizeof(*array));

	printf("int: %d\n", array->size);
	for(i = 0; i < array->size; i++) {
		printf("string at %d: %s\n", i, array->telephones[i]);
		printf("size: %d\n", (int)sizeof(array->telephones[i]));
		printSize(array, i);
	}

	freeAddressBookArray(array);
*/



    return EXIT_SUCCESS;
}
