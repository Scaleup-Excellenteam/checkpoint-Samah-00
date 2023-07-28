#include "encrypt.h"


// Encryption and decryption functions
// Function to encrypt a character using a shift cipher
char encryptChar(char ch, int shift) {
    if (('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z')) {
        if ('A' <= ch && ch <= 'Z') {
            ch = ((ch - 'A' + shift) % 26) + 'A';
        }
        else {
            ch = ((ch - 'a' + shift) % 26) + 'a';
        }
    }
    return ch;
}


// Function to encrypt the file using a shift cipher
void encryptFile(FILE* inputFile, FILE* outputFile, int shift) {
    char ch;
    while ((ch = fgetc(inputFile)) != EOF) {
        ch = encryptChar(ch, shift);
        fputc(ch, outputFile);
    }
}


// Function to decrypt a character using a shift cipher
char decryptChar(char ch, int shift) {
    if (('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z')) {
        if ('A' <= ch && ch <= 'Z') {
            ch = ((ch - 'A' + (26 - shift)) % 26) + 'A';
        }
        else {
            ch = ((ch - 'a' + (26 - shift)) % 26) + 'a';
        }
    }
    return ch;
}


// Function to decrypt the file using a shift cipher
void decryptFile(FILE* inputFile, FILE* outputFile, int shift) {
    char ch;
    while ((ch = fgetc(inputFile)) != EOF) {
        ch = decryptChar(ch, shift);
        fputc(ch, outputFile);
    }
}
