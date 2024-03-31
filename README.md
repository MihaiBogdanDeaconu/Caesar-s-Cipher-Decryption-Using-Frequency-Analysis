# Caesar's Cipher Decryption Using Frequency Analysis

## Abstract

This project implements a decryption method for Caesar's Cipher using frequency analysis. Caesar's Cipher is a simple substitution cipher where each letter in the plaintext is shifted a certain number of places down or up the alphabet. Frequency analysis relies on the fact that some letters (or combination of letters) occur more frequently in a language, and uses this information to decrypt the text.

## Motivation

This project is inspired by Practical Cryptography's article on using the Chi Squared test to crack a Caesar Shift code. The Chi Squared test is a statistical method commonly used to determine the goodness of fit between observed and expected frequencies. By applying this method to ciphertexts encrypted with Caesar's Cipher, we can efficiently decrypt them.

## Methodology

### The decryption process involves several steps:

The idea of this method is to compare the frequency of the letters with the Chi-Squared distance:

### $χ^2 (C, E) = \sum_{i='a'}^{i='z'} \frac{(C_i - E_i)^2}{E}$, 

where $C_i$ represents the occurrence of the $i$-th character, and $E_i$ is the expected count of the $i$-th character of the alphabet.

The formula seems complicated at first glance, but it is not. For each possible character (i goes from 'a' to 'z'), we measure the discrepancy between how often it appeared in the encrypted text ($C_i$) and how often it is expected to appear in English texts ($E_i$); the difference $C_i - E_i$ is squared such that we remove negative signs. The division by $E_i$ is simply a normalization factor.

The lower the Chi-square distance χ² (C, E), the more similar the histograms C and E are.

### Step by step implementation:

**Frequency Analysis**: Calculate the frequency of each letter in the encrypted text.

**Expected Values**: Determine the expected frequency of each letter based on the English language.

**Chi Squared Calculation**: Compute the Chi Squared distance between the observed and expected frequencies for each letter.

**Shift Analysis**: Shift the encrypted text through all possible permutations and calculate the Chi Squared distance for each permutation.

**Decryption**: Select the permutation with the lowest Chi Squared distance as the decrypted solution.

## Installation

To use this project, follow these steps:

1. Clone the repository to your local machine:
    ```bash
    git clone https://github.com/MihaiBogdanDeaconu/Caesar-s-Cipher-Decryption-Using-Frequency-Analysis-C
    ```

2. Compile the source files:
    ```bash
    cd caesars-cipher-decryption
    gcc ui.c chiSquared.c -o decryptor
    ```

3. Run the executable:
    ```bash
    ./decryptor
    ```

## Usage
Upon running the executable, you'll be presented with a menu:

1. Decrypt text from keyboard.
2. Decrypt text from 'encryptedText.txt' file.
0. Exit.
   
Choose an option by entering the corresponding number:

**Option 1**: Enter the text you want to decrypt from the keyboard. The program will then output the decrypted text.

**Option 2**: The program will read the encrypted text from the encryptedText.txt file, decrypt it, and output the decrypted text.

**Option 0**: Exit the program.


## Contributions
Contributions are welcome! If you find any bugs or want to add new features, feel free to open an issue or submit a pull request.



## Additional Resources
Practical Cryptography

Code Breakers Wanted by the NSA

RSA Public Key Encryption
https://ibmathsresources.com/2014/06/15/using-chi-squared-to-crack-codes/
