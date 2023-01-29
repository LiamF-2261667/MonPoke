#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>


#define TEXT_FILE "text.txt"
#define MAX_TEXT_LENGHT 100
#define TEXT_START "~~~:"
#define TEXT_END ":~~~"


/* puts but without the '\n' */
void printString(char* str) {
    for(int i = 0; i < strlen(str); i++) {
        printf("%c", str[i]);
    }
}


/* Generate the label based on TEXT_START */
char* generateLabel(char* text) {
    char* label = malloc(MAX_TEXT_LENGHT + 2); /* +2 for '\n' and '\0' */
    if (label == NULL) {
        #ifdef DEBUG
        printf("ERROR: Allocating label!");
        #endif
        return label;
    }

    strcpy(label, TEXT_START);
    strcpy(label + strlen(TEXT_START), text);
    label[strlen(TEXT_START) + strlen(text)] = '\n';
    label[strlen(TEXT_START) + strlen(text) + 1] = '\0';

    return label;
}

/* Free a label from the heap */
void freeLabel(char* label) {
    free(label);
}

/* Print prewritten text from the text file*/
void printPrewritten(char* text) {
    FILE* f = fopen(TEXT_FILE, "r");
    if(f != NULL) {
        char buffer[MAX_TEXT_LENGHT + 1]; /* +1 for the '\n' */

        char* label = generateLabel(text);
        bool startReading = false;

        // Go over every line
        while(!feof(f)) {
            fgets(buffer, MAX_TEXT_LENGHT, f);

            // Write the buffer while inside the label
            if (startReading == true) {
                if (strncmp(TEXT_END, buffer, strlen(TEXT_END)) == 0)
                    startReading = false;
                else
                    printString(buffer);
            }
            
            // Compare the label to the line
            else if (strcmp(label, buffer) == 0) 
                startReading = true;
        }

        freeLabel(label);
        fclose(f);
    }

    else {
        #ifdef DEBUG
        printf("ERROR: opening text.txt file!\n");
        #endif
    }
}


/* Clear the entire screen */
void clearScreen() {
    system("cls");
}


/* Ask the user to press a key to continue */
void waitForInput() {
	printf("\nPress any key to continue...\n");
	getch();
}