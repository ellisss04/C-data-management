#include "msString.h"

msString msSetString(char *str) {
	long int length = strlen(str);
	/* Allocate memory for the string data */
    	char *data = (char*)malloc(length * sizeof(char));
    	if (data == NULL) {
        	msError("Memory allocation failed");
        	exit(1);
    	}
	/* Copy the input string into the allocated memory */
    	strcpy(data, str);

    	/* Allocate memory for the msString object */
    	msString ms = (msString)malloc(sizeof(long int) + length * sizeof(char));
    	if (ms == NULL) {
        	msError("Memory allocation failed");
        	free(data);
        	exit(1);
    	}
    	memcpy(ms, &length, sizeof(long int));
    	memcpy(ms + sizeof(long int), data, length * sizeof(char));
    	free(data);
    
    	return ms;
}

char* msGetString(msString ms) {
    	long int length;
    	memcpy(&length, ms, sizeof(long int));

	/* Allocate memory for the standard C string */
    	char *str = (char*)malloc((length + 1) * sizeof(char));
    	if (str == NULL) {
        	msError("Memory allocation failed");
        	exit(1);
    	}
    	memcpy(str, ms + sizeof(long int), length * sizeof(char));
    	
	/* Adds null terminator for the returned C string */
	str[length] = '\0';
    	return str;
}

void msCopy(msString *dest, msString src) {
    	long int length;
    	memcpy(&length, src, sizeof(long int));

	/* Allocate memory for the destination msString */
    	*dest = (msString)malloc(sizeof(long int) + length * sizeof(char));
    	if (*dest == NULL) {
        	msError("Memory allocation failed");
        	exit(1);
    	}

	/* Copy the source msString to the destination */
    	memcpy(*dest, src, sizeof(long int) + length * sizeof(char));
}

void msConcatenate(msString *dest, msString src) {
    	long int destLength, srcLength;
    	memcpy(&destLength, *dest, sizeof(long int));
    	memcpy(&srcLength, src, sizeof(long int));
    
	/* Reallocate memory for the destination msString */
    	*dest = (msString)realloc(*dest, sizeof(long int) + (destLength + srcLength) * sizeof(char));
    	if (*dest == NULL) {
        	msError("Memory allocation failed");
        	exit(1);
    	}

	/* Copy the data from the source msString to the end of the destination msString */
    	memcpy(*dest + sizeof(long int) + destLength, src + sizeof(long int), srcLength * sizeof(char));
    	
	/* Update the length of the destination msString */
	destLength += srcLength;
    	memcpy(*dest, &destLength, sizeof(long int));
}

long int msLength(msString ms) {
    	long int length;
    	memcpy(&length, ms, sizeof(long int));
    	return length;
}

int msCompare(msString ms1, msString ms2) {
    	long int length1, length2;
    	memcpy(&length1, ms1, sizeof(long int));
    	memcpy(&length2, ms2, sizeof(long int));

	/* Compare the lengths of the msStrings */
    	if (length1 != length2)
        	return 1;

	/* Compare the data of the msStrings */
    	int result = memcmp(ms1 + sizeof(long int), ms2 + sizeof(long int), length1 * sizeof(char));
	
	return result != 0;
}

int msCompareString(msString ms, char *str) {
	/* Extract the length of the msString */
    	long int length;
    	memcpy(&length, ms, sizeof(long int));

	/* Get the length of the standard C string */
    	long int strLength = strlen(str);

	/* Compare the lengths of the msString and the standard C string */
    	if (length != strLength)
        	return 1;

	/* Compare the data of the msString and the standard C string */
    	int result = memcmp(ms + sizeof(long int), str, length * sizeof(char));
	
	return result != 0;
}

static void msError(char *msg) {
    	fprintf(stderr, "Error: %s\n", msg);
}

