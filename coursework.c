#include <stdio.h>
#include <stdlib.h>
#include <msString.h>

/* printBytes() prototype */
void printBytes(void *ptr, int numBytes);

int main(int argc, char *argv[]){

	/* Task1 */
	printf("Solution to task 1:\n");
	printf("\n");


	int arr[4] = {10, 20, 30, 145};
        int* pointer = &arr[0];
        printBytes(pointer, 4);
	printf("\n");
	printf("\n");


	/* Task2 */
	printf("Solution to task 2:\n");	
	printf("\n");


        if (argc != 3){
                fprintf(stderr, "Usage: %s fileIn fileOut\n", argv[0]);
                return 1;
        }

        FILE *fileIn = fopen(argv[1], "r");
        if (fileIn == NULL){
                perror("Error opening input file");
                return 1;
        }

        FILE *fileOut =fopen(argv[2], "w");
        if (fileOut == NULL){
                perror("Error opening output file");
                fclose(fileIn);
                return 1;
        }


        /* Read characters from fileIn and store them in reverse order */
        fseek(fileIn, 0, SEEK_END);
        long fileSize = ftell(fileIn);
        rewind(fileIn);
        char *buffer = (char *)malloc(fileSize + 1);
        if (buffer == NULL){
                perror("Memory allocation failed");
                fclose(fileIn);
                fclose(fileOut);
                return 1;
        }
	printf("Input file %s successfully read!\n", argv[1]);
	printf("\n");

        fread(buffer, 1, fileSize, fileIn);
        buffer[fileSize] = '\0';

        /* write characters from buffer to file Out in reverse order */
        int i;
        for (i = fileSize - 1; i >= 0; i--){
                fputc(buffer[i], fileOut);
        }
	printf("Output file %s successfully written to\n", argv[2]);
	printf("\n");
	printf("\n");

        free(buffer);
        fclose(fileIn);
        fclose(fileOut);


	/* Task 3 */
	printf("Solution to task 3:\n");
	printf("\n");

	msString ms = msSetString("Hello");
        msString ms2 = msSetString(" World!");
        msString mscopy = NULL;

        printf("String |%s| is %d characters long (%p).\n", msGetString(ms), msLength(ms), ms);
        msCopy(&mscopy, ms);
        printf("Copied string |%s| is %d characters long (%p).\n", msGetString(mscopy), msLength(mscopy), mscopy);

        printf("Compare ms with mscopy: %d\n", msCompare(ms, mscopy));
        printf("Compare ms with ms2: %d\n", msCompare(ms, ms2));
        printf("Compare ms with Hello: %d\n", msCompareString(ms, "Hello"));
        printf("Compare ms with HelloX: %d\n", msCompareString(ms, "HelloX"));
        printf("Compare ms with Hella: %d\n", msCompareString(ms, "Hella"));

        msConcatenate(&mscopy, ms2);
        printf("Concatenated string |%s| is %d characters long (%p).\n", msGetString(mscopy), msLength(mscopy), mscopy);
        /* Memory leak occured here: the memory allocated for mscopy was not deallocated before exiting the program */

        /* free memory allocated mscopy to prevent memory leak */
        free(mscopy);


        return 0;
}


void printBytes(void *ptr, int numBytes){
        int i;

        printf("Starting at memory address %p:\n", ptr);

        for ( i = 0; i < numBytes; i++) {
                printf("%03d: %d\n", i + 1, *((int*)ptr));
                ptr = (int*)ptr + 1;
        }
}

