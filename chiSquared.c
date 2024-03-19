#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <float.h>
#include <math.h>

#define cap 100 // Maximum capacity for character buffer


/**
 * @brief Reads the distribution of letters from a file and stores it into an array.
 * 
 * Reads the distribution of letters from a file named "distribution.txt".
 * Each line in the file represents the frequency of a letter, with 'a' corresponding to the first line,
 * 'b' to the second line, and so on.
 * 
 * @param distribution Array to store the distribution of letters.
 */
void readDistribution(float distribution[])
{
    FILE *file;
    file = fopen("distribution.txt", "r");

    if(file == NULL)
        perror("Error opening file!");

    for (int i = 0; i < 26; ++i)
        fscanf(file, "%f", &distribution[i]);

    fclose(file);
}


/**
 * @brief Reads the encrypted text from a file and stores it into a character array.
 * 
 * Reads the encrypted text from a file named "encryptedText.txt".
 * 
 * @param encrypted Array to store the encrypted text.
 */
void readEncryptedText(char encrypted[])
{
    FILE *file;
    char buffer[cap];
    file = fopen("encryptedText.txt", "r");

    if(file == NULL)
        printf("Error opening file!");

    while(fgets(buffer, cap, file) != NULL)
        strcat(encrypted, buffer);
    fclose(file);
}


/**
 * @brief Counts the number of letters in the given text.
 * 
 * Counts the number of letters (alphabetic characters) in the given text.
 * 
 * @param encrypted The text to count letters in.
 * @param length Length of the text.
 * @return Number of letters in the text.
 */
int getNoLetters(char encrypted[], int length)
{
    --length;
    int count = 0;
    while(length >= 0)
    {
        if(isalpha(encrypted[length]))
            ++count;
        --length;
    }
    return count;
}


/**
 * @brief Counts the actual number of occurrences of a specific character in the given text.
 * 
 * Counts the actual number of occurrences of a specific character (case-insensitive) in the given text.
 * 
 * @param encrypted The text to search for occurrences.
 * @param character The character to search for.
 * @param length Length of the text.
 * @return Number of occurrences of the character in the text.
 */
int getActualNumberOfChar(char encrypted[], char character, int length)
{
    --length;
    int count = 0;
    while(length >= 0)
    {
        if(encrypted[length] == character || encrypted[length] == character - 32)
            ++count;
        --length;
    }
    return count;
}


/**
 * @brief Shifts the alphabetic characters in the given text by one position.
 * 
 * Shifts the alphabetic characters in the given text one position to the left (circular shift).
 * 
 * @param encrypted The text to shift characters in.
 * @param length Length of the text.
 */
void shift(char encrypted[], int length)
{
    --length;
    while(length >= 0)
    {
        if(isalpha(encrypted[length]))
        {
            if(encrypted[length] == 'A' || encrypted[length] == 'a')
                encrypted[length] += 'Z' - 'A';
            else encrypted[length] -= 1;
        }
        --length;
    }
}


/**
 * @brief Computes the normalized frequency of a character based on its expected frequency.
 * 
 * Computes the normalized frequency of a character in the given text based on its expected frequency
 * according to the distribution of letters in English.
 * 
 * @param position Position of the character in the alphabet (0 for 'a', 1 for 'b', etc.).
 * @param distribution Array containing the distribution of letters.
 * @param encrypted The encrypted text.
 * @param nrLetters Number of letters in the text.
 * @param length Length of the text.
 * @return Normalized frequency of the character.
 */
float getNormalizedFrequency(int position, float distribution[], char encrypted[], int nrLetters, int length)
{
    char cur_letter = 'a' + position;
    int actualNumber = getActualNumberOfChar(encrypted, cur_letter, length);

    if(actualNumber == 0)
        return 0;

    float expectedNumber = (nrLetters * distribution[position]) / 100;
    float normalizedFrequency = pow((expectedNumber - actualNumber), 2) / actualNumber;
    return normalizedFrequency;
}


/**
 * @brief Computes the Chi-squared distance between the expected and actual frequencies of letters.
 * 
 * Computes the Chi-squared distance between the expected frequencies of letters according to the
 * distribution in English and the actual frequencies in the given text.
 * 
 * @param distribution Array containing the distribution of letters.
 * @param encrypted The encrypted text.
 * @param nrLetters Number of letters in the text.
 * @param length Length of the text.
 * @return The Chi-squared distance.
 */
float getChiSquared(float distribution[], char encrypted[], int nrLetters, int length)
{
    float sum = 0, normalizedFrequency;
    
    for(int i = 0; i < 26; ++i)
    {
        normalizedFrequency = getNormalizedFrequency(i, distribution, encrypted, nrLetters, length);
        sum += normalizedFrequency;
    }
    return sum;
}


/**
 * @brief Performs frequency shift analysis to decrypt the text using Caesar's Cipher.
 * 
 * Performs frequency shift analysis by shifting the alphabetic characters in the encrypted text
 * through all possible permutations (1 to 25 shifts), computing the Chi-squared distance between
 * each permutation and the expected distribution of letters in English, and selecting the permutation
 * with the lowest Chi-squared distance as the solution.
 * 
 * @param distribution Array containing the distribution of letters.
 * @param encrypted The encrypted text.
 * @param length Length of the text.
 * @param minChiSquared Pointer to the minimum Chi-squared distance.
 * @param solution Array to store the decrypted solution.
 */
void frequencyShiftAnalysis(float distribution[], char encrypted[], int length, float *minChiSquared, char solution[])
{
    int localChiSquared, nrLetters = getNoLetters(encrypted, length);
    for(int i = 1; i <= 25 && *minChiSquared != 0; ++i)
    {
        localChiSquared = getChiSquared(distribution, encrypted, nrLetters, length);
        if(localChiSquared < *minChiSquared)
        {
            *minChiSquared = localChiSquared;
            strcpy(solution, encrypted);
        }
        shift(encrypted, length);
    }
}


/**
 * @brief Solves the Caesar's Cipher by decrypting the encrypted text.
 * 
 * Solves the Caesar's Cipher by decrypting the encrypted text using frequency analysis.
 * 
 * @param encrypted The encrypted text.
 * @param solution Array to store the decrypted solution.
 */
void solve(char encrypted[], char solution[])
{
    float distribution[27], minChiSquared = FLT_MAX;
    int length = strlen(encrypted);
    readDistribution(distribution);
    frequencyShiftAnalysis(distribution, encrypted, length, &minChiSquared, solution);
}


/**
 * @brief Solves the Caesar's Cipher from an encrypted text file.
 * 
 * Reads the encrypted text from a file, decrypts it using frequency analysis,
 * and stores the decrypted solution.
 * 
 * @param solution Array to store the decrypted solution.
 */
void solveFromFile(char solution[])
{
    char *encrypted = (char *)malloc(512 * sizeof(char));
    encrypted[0] = '\0';
    float distribution[27], minChiSquared = FLT_MAX;
    readDistribution(distribution);
    readEncryptedText(encrypted);
    int length = strlen(encrypted);
    frequencyShiftAnalysis(distribution, encrypted, length, &minChiSquared, solution);
    free(encrypted);
}