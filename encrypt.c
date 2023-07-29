#include "encrypt.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Link with the OpenSSL library
// gcc encrypt_decrypt_file.c -o encrypt_decrypt_file -lssl -lcrypto

// Function to encrypt data using EVP AES-256-CBC
int encrypt_file_openssl(const char *input_file, const char *output_file, const unsigned char *key, const unsigned char *iv) {
    FILE *in_file = fopen(input_file, "rb");
    FILE *out_file = fopen(output_file, "wb");

    if (!in_file || !out_file) {
        fprintf(stderr, "Error opening files.\n");
        return -1;
    }

    // Initialize the encryption context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    // Setup the output buffer
    int block_size = EVP_CIPHER_CTX_block_size(ctx);
    unsigned char in_block[block_size];
    unsigned char out_block[block_size + EVP_MAX_BLOCK_LENGTH];
    int out_len;

    // Encrypt the input file and write to the output file
    while (1) {
        int bytes_read = fread(in_block, 1, block_size, in_file);
        EVP_EncryptUpdate(ctx, out_block, &out_len, in_block, bytes_read);
        fwrite(out_block, 1, out_len, out_file);

        if (bytes_read < block_size)
            break;
    }

    // Finalize the encryption
    EVP_EncryptFinal_ex(ctx, out_block, &out_len);
    fwrite(out_block, 1, out_len, out_file);

    // Clean up
    EVP_CIPHER_CTX_free(ctx);
    fclose(in_file);
    fclose(out_file);
    return 0;
}

// Function to decrypt data using EVP AES-256-CBC
int decrypt_file_openssl(const char *input_file, const char *output_file, const unsigned char *key, const unsigned char *iv) {
    FILE *in_file = fopen(input_file, "rb");
    FILE *out_file = fopen(output_file, "wb");

    if (!in_file || !out_file) {
        fprintf(stderr, "Error opening files.\n");
        return -1;
    }

    // Initialize the decryption context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    // Setup the output buffer
    int block_size = EVP_CIPHER_CTX_block_size(ctx);
    unsigned char in_block[block_size + EVP_MAX_BLOCK_LENGTH];
    unsigned char out_block[block_size];
    int out_len;

    // Decrypt the input file and write to the output file
    while (1) {
        int bytes_read = fread(in_block, 1, block_size + EVP_MAX_BLOCK_LENGTH, in_file);
        EVP_DecryptUpdate(ctx, out_block, &out_len, in_block, bytes_read);
        fwrite(out_block, 1, out_len, out_file);

        if (bytes_read < block_size + EVP_MAX_BLOCK_LENGTH)
            break;
    }

    // Finalize the decryption
    EVP_DecryptFinal_ex(ctx, out_block, &out_len);
    fwrite(out_block, 1, out_len, out_file);

    // Clean up
    EVP_CIPHER_CTX_free(ctx);
    fclose(in_file);
    fclose(out_file);
    return 0;
}





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
