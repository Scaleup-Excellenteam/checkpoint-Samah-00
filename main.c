#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "operations.h"
#include "encrypt.h"
#include "constants.h"

// to compile: gcc main.c operations.c build_data.c encrypt.c -g -o main -lssl -lcrypto

const char* courseNames[MAX_COURSES] = {
   "Course 1",
   "Course 2",
   "Course 3",
   "Course 4",
   "Course 5",
   "Course 6",
   "Course 7",
   "Course 8",
   "Course 9",
   "Course 10",
   "Course 11",
   "Course 12",
   "Course 13",
   "Course 14",
   "Course 15",
   "Course 16",
   "Course 17",
   "Course 18",
   "Course 19",
   "Course 20"
};


struct Student* createStudent(const char* firstName, const char* lastName, int phoneNumber, int level, int class, const int* grades) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    strncpy(newStudent->firstName, firstName, sizeof(newStudent->firstName) - 1);
    newStudent->firstName[sizeof(newStudent->firstName) - 1] = '\0'; // Ensure null-terminated
    strncpy(newStudent->lastName, lastName, sizeof(newStudent->lastName) - 1);
    newStudent->lastName[sizeof(newStudent->lastName) - 1] = '\0'; // Ensure null-terminated




    newStudent->level = level;
    newStudent->class = class;
    newStudent->phoneNumber = phoneNumber;




    for (int i = 0; i < MAX_COURSES; i++) {
        strncpy(newStudent->courses[i].courseName, courseNames[i], sizeof(newStudent->courses[i].courseName) - 1);
        newStudent->courses[i].courseName[sizeof(newStudent->courses[i].courseName) - 1] = '\0'; // Ensure null-terminated
        // Initialize grades to 0
        newStudent->courses[i].grade = DEFAULT_GRADE;
        // Fill in actual grades if they exist
        if (grades[i] >= MIN_GRADE && grades[i] <= MAX_GRADE) {
            newStudent->courses[i].grade = grades[i];
        }
    }




    return newStudent;
}


struct Course* createCourse(const char* name) {
    struct Course* newCourse = (struct Course*)malloc(sizeof(struct Course));
    // Copy the name into the courseName field
    strncpy(newCourse->courseName, name, sizeof(newCourse->courseName) - 1);
    newCourse->courseName[sizeof(newCourse->courseName) - 1] = '\0'; // Ensure null-terminated
    return newCourse;
}


int main() {
    // ... main function code ...


     // Decrypt the data from the encrypted file
    if (decryptData() != 0) {
        return 1; // Error occurred during decryption
    }


    // Create the level structures and read students' data from the file
    struct Level levels[MAX_LEVELS];
    if (buildDatabase(levels) != 0) {
        return 1; // Error occurred while building the database
    }


    // Main menu loop
    int choice;
    do {
        printMenu();
        scanf("%d", &choice);
        switch (choice) {
        case 1:
        {
            int levelNumber, classNumber;
            printf("Enter level number (1 to 12): ");
            scanf("%d", &levelNumber);
            printf("Enter class number (1 to 10): ");
            scanf("%d", &classNumber);
            addNewStudent(levels, levelNumber, classNumber);
        }
        break;
        case 2:
            deleteStudent(levels);
            break;
        case 3:
            editStudent(levels);
            break;
        case 4:
            searchStudent(levels);
            break;
        case 5:
            displayAllStudents(levels);
            break;
        
        case 6:
            findCandidatesForDeparture(levels);
            break;
        case 7:
            calculateAveragePerCoursePerLayer(levels);
            break;
        case 8:
            exportDatabaseToFile(levels);
            break;
        case 9:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);


    // Free memory for all students
    freeMemory(levels);


    return 0;
}

/*
int main() {
    const char *input_file = "students_with_class.txt";
    const char *encrypted_file = "encrypted.bin";
    const char *decrypted_file = "decrypted.txt";
    const char *key_file = "key.txt";
    const char *iv_file = "iv.txt";

    unsigned char key[EVP_MAX_KEY_LENGTH];
    unsigned char iv[EVP_MAX_IV_LENGTH];

    // Read the key from the key file
    if (read_hex_from_file(key_file, key, EVP_MAX_KEY_LENGTH) != 0) {
        fprintf(stderr, "Failed to read the key from file: %s\n", key_file);
        return -1;
    }

    // Read the IV from the IV file
    if (read_hex_from_file(iv_file, iv, EVP_MAX_IV_LENGTH) != 0) {
        fprintf(stderr, "Failed to read the IV from file: %s\n", iv_file);
        return -1;
    }

    // Encrypt the input file
    int result_encrypt = encrypt_file(input_file, encrypted_file, key, iv);
    if (result_encrypt != 0) {
        fprintf(stderr, "Encryption failed.\n");
        return -1;
    }

    printf("Encryption successful. Encrypted file created: %s\n", encrypted_file);

    // Decrypt the encrypted file
    int result_decrypt = decrypt_file(encrypted_file, decrypted_file, key, iv);
    if (result_decrypt != 0) {
        fprintf(stderr, "Decryption failed.\n");
        return -1;
    }

    printf("Decryption successful. Decrypted file created: %s\n", decrypted_file);

    return 0;
}
*/  

