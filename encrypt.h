#ifndef ENCRYPT_H
#define ENCRYPT_H


#include <stdio.h>


void encryptFile(FILE* inputFile, FILE* outputFile, int shift);
void decryptFile(FILE* inputFile, FILE* outputFile, int shift);
char encryptChar(char ch, int shift);
char decryptChar(char ch, int shift);


#endif