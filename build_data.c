#include "build_data.h"
#include "operations.h"
#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Function to decrypt the data from the encrypted file
int decryptData() {
    FILE* encryptedFile = fopen("encrypted_students.bin", "rb");
    if (encryptedFile == NULL) {
        printf("Error opening the encrypted file.\n");
        return 1;
    }


    FILE* decryptedFile = fopen("decrypted_students.txt", "w");
    if (decryptedFile == NULL) {
        printf("Error creating the decrypted file.\n");
        fclose(encryptedFile);
        return 1;
    }


    int shift = 3; // You should use the correct shift value used during encryption
    decryptFile(encryptedFile, decryptedFile, shift);


    fclose(encryptedFile);
    fclose(decryptedFile);


    return 0;
}

// Function to read the students' data from the file and create the student structures
void readStudentsFromFile(FILE* file, struct Level* levels) {
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    int phoneNumber;
    int levelNumber;
    int classNumber;
    int grades[MAX_COURSES];

    while (fscanf(file, "%s %s %d %d %d", firstName, lastName, &phoneNumber, &levelNumber, &classNumber) == 5) {
        for (int k = 0; k < MAX_COURSES; k++) {
            fscanf(file, "%d", &grades[k]);
        }

        // Find the corresponding level and class for the current student
        if (levelNumber >= 1 && levelNumber <= MAX_LEVELS &&
            classNumber >= 1 && classNumber <= MAX_CLASSES) {
            struct Student* newStudent = createStudent(firstName, lastName, phoneNumber, levelNumber, classNumber, grades);
            // Add the new student to the linked list of students in the corresponding class of the level
            newStudent->nextStudent = levels[levelNumber - 1].classes[classNumber - 1].studentsHead;
            levels[levelNumber - 1].classes[classNumber - 1].studentsHead = newStudent;
        }
        else {
            printf("Invalid level or class number for the student: %s %s\n", firstName, lastName);
        }
    }
}

// Function to build the structures and read students' data from the file
int buildDatabase(struct Level* levels) {
    // Open the decrypted file for reading
    FILE* file = fopen("decrypted_students.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Creating courses
    struct Course* courses[MAX_COURSES];
    for (int i = 0; i < MAX_COURSES; i++) {
        courses[i] = createCourse(courseNames[i]);
    }

    // Create the level structures
    for (int i = 0; i < MAX_LEVELS; i++) {
        // Initialize the studentsHead to NULL for all classes in this level
        for (int j = 0; j < MAX_CLASSES; j++) {
            levels[i].classes[j].studentsHead = NULL;
        }
        // Read students' data from the file and create the student structures for this level
        readStudentsFromFile(file, &levels[i]);
    }

    // Close the file after reading
    fclose(file);
    // Delete the decrypted file
    remove("decrypted_students.txt");

    return 0;
}
