#ifndef ENCRYPT_H
#define ENCRYPT_H


#include <stdio.h>
#include <openssl/evp.h>


void encryptFile(FILE* inputFile, FILE* outputFile, int shift);
void decryptFile(FILE* inputFile, FILE* outputFile, int shift);
char encryptChar(char ch, int shift);
char decryptChar(char ch, int shift);
int encrypt_file_openssl(const char *input_file, const char *output_file, const unsigned char *key, const unsigned char *iv);
int decrypt_file_openssl(const char *input_file, const char *output_file, const unsigned char *key, const unsigned char *iv);


#endif