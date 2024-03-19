#include <stdio.h>
#include "chiSquared.c"
#include <stdbool.h>
#include <stdlib.h>


/**
 * @brief Reads a command from the user.
 * 
 * Prompts the user to enter a command and reads the input from the standard input (stdin).
 * 
 * @return The integer representation of the command entered by the user.
 *         Returns -1 in case of errors or invalid input.
 */
int readCommand()
{
    int command;
    char buffer[16];
    printf("Enter a command: ");
    if (fgets(buffer, 16, stdin) == NULL)
    {
        printf("Error reading input! Try again!\n");
        return -1;
    }
        
    if (sscanf(buffer, "%d", &command) != 1)
    {
        printf("Please input an integer! Try again!\n");
        return -1;
    }

    if (command < 0 || command > 2)
    {
        printf("Invalid command! Try again!\n");
        return -1;
    }
    
    return command;
}


/**
 * @brief Reads a text string from the keyboard.
 * 
 * Reads a dynamically allocated character string from the keyboard until Enter is pressed.
 * 
 * @return A dynamically allocated character string containing the text entered by the user.
 */
char* readText() {
    int bufferSize = 100; 
    int length = 0; 
    char* buffer = (char*)malloc(bufferSize * sizeof(char)); 
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        buffer[length++] = c;

        if (length >= bufferSize) {
            bufferSize *= 2;
            buffer = (char*)realloc(buffer, bufferSize * sizeof(char));
        }
    }

    buffer[length] = '\0';
    return buffer;
}


/**
 * @brief Prints the menu options for the user.
 * 
 * Prints the available menu options for the user to choose from.
 */
void printMenu()
{
    printf("%s", "1. Decypher text from keyboard.\n");
    printf("%s", "2. Decypher text from 'encryptedText' file.\n");
    printf("%s", "0. Exit.\n");
}


/**
 * @brief Runs the user interface.
 * 
 * Executes the user interface for Caesar's Cipher decryption using frequency analysis.
 * Allows the user to choose between decrypting text entered from the keyboard or from a file,
 * and provides the decrypted solution.
 */
void run()
{
    char *text;
    char *solution = (char *)malloc(512 * sizeof(char));
    bool run = true;
    while(run)
    {
        printMenu();
        int command = readCommand();
        switch(command){
            case 1:
                text = readText();
                solve(text, solution);
                printf("%s\n", solution);
                break;
            case 2:
                solveFromFile(solution);
                printf("%s\n", solution);
                break;
            case 0:
                run = false;
                free(solution);
                free(text);
                break;
        }
    }
}


/**
 * @brief Main function.
 * 
 * Entry point of the program. Calls the run function to start the user interface.
 * 
 * @return 0 upon successful execution.
 */
int main()
{
    run();
    return 0;
}