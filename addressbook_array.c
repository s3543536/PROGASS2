#include "addressbook_array.h"

/**
* Note this file is NOT to contain console output,
* meaning printf's are NOT to be present in this file.
*/

char * h_concatPhones(AddressBookArray * array) {
	int commasLen = (array->size-1) * 2;
	int allNumsLen = (TELEPHONE_LENGTH-1)*array->size + NULL_SPACE;
	char * output = malloc(maxInt(commasLen + allNumsLen, 2));
	char * outputCpy = malloc(maxInt(commasLen + allNumsLen, 2));
	int i;

	if(array->size == 0) {
		sprintf(output, " ");
		free(outputCpy);
		return output;
	}/* else if(array->size == 1) {
		sprintf(output, "%s", telephones[0]);
		return output;
	}*/

	sprintf(output, "%s", array->telephones[0]);
	for(i = 1; i < array->size; i++) {
		strcpy(outputCpy, output);
		sprintf(output, "%s, %s", outputCpy, array->telephones[i]);
	}
	free(outputCpy);
	return output;
}

AddressBookArray * createAddressBookArray()
{
    /**
     * Allocates and initialises a new AddressBookArray.
     * malloc or calloc are expected to be used to create the
     * AddressBookArray memory.
     * 
     * If memory cannot be allocated for the array NULL is returned.
     * 
     * Note telephones should be initialised to NULL.
     */
	AddressBookArray *array;

	array = malloc(sizeof(*array));/*give memory for each value */
	if(array == NULL) {
		return NULL;
	}
	array->size = 0;
	array->telephones = NULL;
	return array;

}

void freeAddressBookArray(AddressBookArray * array)
{
    /**
     * Free's all telephones within the array and the AddressBookArray itself.
     */
	int i;

	for(i = 0; i < array->size; i++) {
		free(array->telephones[i]);
	}
	free(array->telephones);
	free(array);
}

Boolean validateTelephone(char * telephone) {
	char* endptr = NULL;
	char* m;

	/* not NULL */
	if(telephone == NULL) {
		printf("telephone is NULL\n");
		return FALSE;
	}

	/* is a number */
	strtol(telephone, &endptr, 10);
	if(*endptr != '\0') {
		printf("telephone is not a number\n");
		return FALSE;
	}

	/* correct length */
	if(strlen(telephone) + NULL_SPACE != TELEPHONE_LENGTH) {
		printf("telephone is incorrect length: %d, correct: %d\n", (int)strlen(telephone), TELEPHONE_LENGTH - NULL_SPACE);
		return FALSE;
	}

	return TRUE;
}

Boolean addTelephone(AddressBookArray * array, char * telephone)
{
    /**
     * Adds the provided telephone to the telephones array and returns TRUE.
     * 
     * If the telephone already exists or memory cannot be allocated
     * then FALSE is returned.
     * 
     * malloc or calloc are expected to be used to create memory for
     * the new telephone - do not forget to copy the provided telephone over.
     * Here is some sample code:
     * 
     * char * newTelephone = malloc(TELEPHONE_LENGTH);
     * strcpy(newTelephone, telephone);
     * 
     * After this it is expected you use *realloc* to make the telephones
     * array grow by 1. Here is some sample code:
     * 
     * array->telephones = realloc(array->telephones,
     *                     sizeof(*array->telephones) * (array->size + 1));
     * 
     * Once the array has grown by 1 you can store the new telephone in it
     * at the end. Here is some sample code:
     * 
     * array->telephones[array->size] = newTelephone;
     * array->size++;
     */
	int pos = array->size;
	char* m;

	if(!validateTelephone(telephone)) {
		printf("Can't add invalid telephone: '%s'\n", telephone);
		return FALSE;
	}

	if(findTelephone(array, telephone)) {
		printf("telephone already in list\n");
		return FALSE;
	}

	/* grow array of pointers */
    array->telephones = realloc(array->telephones,
                         sizeof(*array->telephones) * (array->size + 1));
	if(array->telephones == NULL) {
		return FALSE;/* no more memory */
	}
    array->size++;

	/* create telephone memory */
    array->telephones[pos] = malloc(sizeof(*array->telephones[pos]) * 
							TELEPHONE_LENGTH);
	if(array->telephones[pos] == NULL) {
		return FALSE;/* no more memory */
	}

	/* copy telephone into new memory */
    strcpy(array->telephones[pos], telephone);

	return TRUE;
}

Boolean removeTelephone(AddressBookArray * array, char * telephone)
{
   /**
    * Removes the provided telephone from the telephones array and
    * returns TRUE.
    * 
    * If the telephone does not exist or memory cannot be reallocated
    * then FALSE is returned.
    * 
    * It is expected you use *realloc* to shrink the telephones
    * array by 1. Here is some sample code:
    * 
    * array->telephones = realloc(array->telephones,
    *                     sizeof(*array->telephones) * (array->size - 1));
    * array->size--;
    * 
    * Note for this to work you will first have to ensure the telephone
    * to remove is at the end of the array.
    * 
    * Also note you will need to free(...) the removed telephone as well.
    * 
    * If you are removing the LAST telephone in the array then you will need to
    * free telephones itself and set it to NULL. Here is some sample code:
    * 
    * free(array->telephones);
    * array->telephones = NULL;
    */
	char * telephoneToRemove;

	telephoneToRemove = findTelephone(array, telephone);
	if(telephoneToRemove == NULL) {
		return FALSE;/* telephone isn't in array */
	}

	/* move last telephone to old spot */
	if(telephoneToRemove != array->telephones[array->size-1])
		strcpy(telephoneToRemove, array->telephones[array->size-1]);

	/* free last spot */
	free(array->telephones[array->size-1]);

	/* shrink pointer array */
    array->telephones = realloc(array->telephones,
                        sizeof(*array->telephones) * (array->size - 1));
    array->size--;

	/* account for empty array */
	if(array->size == 0) {
		free(array->telephones);
		array->telephones = NULL;
	}

    return TRUE;
}

char * findTelephone(AddressBookArray * array, char * telephone)
{
    /**
     * Returns the telephone that matches the telephone provided.
     * 
     * If no telephone exists then NULL is returned.
     */
	int i;
	if(telephone == NULL)
		return NULL;

	for(i = 0; i < array->size; i++) {
		/* the strings are in different locations so we cant just compare
		 * pointers */
		if(strcmp(array->telephones[i], telephone) == 0) {
			return array->telephones[i];
		}
	}

    return NULL;
}
