#include "operations.h"
#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Function to add a new student to the level and class
void addNewStudent(struct Level* levels, int levelNumber, int classNumber) {
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    int phoneNumber;
    int grades[MAX_COURSES];


    printf("Enter first name: ");
    scanf("%s", firstName);
    printf("Enter last name: ");
    scanf("%s", lastName);
    printf("Enter phone number: ");
    scanf("%d", &phoneNumber);


    for (int i = 0; i < MAX_COURSES; i++) {
        printf("Enter grade for %s: ", courseNames[i]);
        scanf("%d", &grades[i]);
    }


    // Find the corresponding level and class for the new student
    if (levelNumber >= 1 && levelNumber <= MAX_LEVELS &&
        classNumber >= 1 && classNumber <= MAX_CLASSES) {
        struct Student* newStudent = createStudent(firstName, lastName, phoneNumber, levelNumber, classNumber, grades);
        // Add the new student to the linked list of students in the corresponding class of the level
        newStudent->nextStudent = levels[levelNumber - 1].classes[classNumber - 1].studentsHead;
        levels[levelNumber - 1].classes[classNumber - 1].studentsHead = newStudent;
        printf("New student added successfully.\n");
    }
    else {
        printf("Invalid level or class number. Failed to add the student.\n");
    }
}


// Function to search for a student by first and last name
// Returns a pointer to the found student, or NULL if not found
struct Student* searchStudentByName(struct Level* levels, const char* firstName, const char* lastName) {
    for (int i = 0; i < MAX_LEVELS; i++) {
        for (int j = 0; j < MAX_CLASSES; j++) {
            struct Student* currentStudent = levels[i].classes[j].studentsHead;
            while (currentStudent) {
                if (strcmp(currentStudent->firstName, firstName) == 0 && strcmp(currentStudent->lastName, lastName) == 0) {
                    // Student found, return the pointer to the student
                    return currentStudent;
                }
                currentStudent = currentStudent->nextStudent;
            }
        }
    }
    // Student not found
    return NULL;
}


// Function to delete a student by first and last name
void deleteStudent(struct Level* levels) {
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];




    printf("Enter first name of the student to delete: ");
    scanf("%s", firstName);
    printf("Enter last name of the student to delete: ");
    scanf("%s", lastName);




    // Search for the student
    struct Student* studentToDelete = searchStudentByName(levels, firstName, lastName);
    if (studentToDelete) {
        // Student found, proceed with deletion
        for (int i = 0; i < MAX_LEVELS; i++) {
            for (int j = 0; j < MAX_CLASSES; j++) {
                struct Student* currentStudent = levels[i].classes[j].studentsHead;
                struct Student* prevStudent = NULL;
                while (currentStudent) {
                    if (currentStudent == studentToDelete) {
                        // Student found, delete them
                        if (prevStudent) {
                            prevStudent->nextStudent = currentStudent->nextStudent;
                        }
                        else {
                            levels[i].classes[j].studentsHead = currentStudent->nextStudent;
                        }
                        free(currentStudent);
                        printf("Student deleted successfully.\n");
                        return;
                    }
                    prevStudent = currentStudent;
                    currentStudent = currentStudent->nextStudent;
                }
            }
        }
    }
    else {
        printf("Student not found. Deletion failed.\n");
    }
}


// Function to edit a grade of a given student
void editStudent(struct Level* levels) {
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    int newGrade;
    int courseNumber;




    printf("Enter first name of the student to edit: ");
    scanf("%s", firstName);
    printf("Enter last name of the student to edit: ");
    scanf("%s", lastName);
    printf("Enter course number to update grade (1 to 20): ");
    scanf("%d", &courseNumber);




    if (courseNumber < 1 || courseNumber > MAX_COURSES) {
        printf("Invalid course number.\n");
        return;
    }




    printf("Enter new grade for %s: ", courseNames[courseNumber - 1]);
    scanf("%d", &newGrade);




    if (newGrade >= MIN_GRADE && newGrade <= MAX_GRADE) {
        // Search for the student
        struct Student* studentToEdit = searchStudentByName(levels, firstName, lastName);
        if (studentToEdit) {
            // Student found, proceed with grade update
            studentToEdit->courses[courseNumber - 1].grade = newGrade;
            printf("Grade updated successfully.\n");
        }
        else {
            printf("Student not found. Grade update failed.\n");
        }
    }
    else {
        printf("Invalid grade. Grade update failed.\n");
    }
}


// Function to search for a student by first and last name and display all information about him
void searchStudent(struct Level* levels) {
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];




    printf("Enter first name of the student to search: ");
    scanf("%s", firstName);
    printf("Enter last name of the student to search: ");
    scanf("%s", lastName);




    struct Student* student = searchStudentByName(levels, firstName, lastName);
    if (student) {
        // Student found, display information
        printf("Name: %s %s\n", student->firstName, student->lastName);
        printf("Phone Number: %d\n", student->phoneNumber);
        printf("Level: %d\n", student->level);
        printf("Class: %d\n", student->class);
        for (int k = 0; k < MAX_COURSES; k++) {
            printf("%s Grade: %d\n", student->courses[k].courseName, student->courses[k].grade);
        }
    }
    else {
        printf("Student not found.\n");
    }
}


// Function to display all students
void displayAllStudents(struct Level* levels) {
    for (int i = 0; i < MAX_LEVELS; i++) {
        for (int j = 0; j < MAX_CLASSES; j++) {
            struct Student* currentStudent = levels[i].classes[j].studentsHead;
            while (currentStudent) {
                printf("Name: %s %s\n", currentStudent->firstName, currentStudent->lastName);
                printf("Phone Number: %d\n", currentStudent->phoneNumber);
                printf("Level: %d\n", currentStudent->level);
                printf("Class: %d\n", currentStudent->class);
                for (int k = 0; k < MAX_COURSES; k++) {
                    printf("%s Grade: %d\n",
                        currentStudent->courses[k].courseName,
                        currentStudent->courses[k].grade);
                }
                printf("\n");
                currentStudent = currentStudent->nextStudent;
            }
        }
    }
}


// Function to print the main menu
void printMenu() {
    printf("\n==== Main Menu ====\n");
    printf("1. Add a new student\n");
    printf("2. Delete a student\n");
    printf("3. Edit student information\n");
    printf("4. Search for a student\n");
    printf("5. Display all students\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}


// Function to free memory for all students
void freeMemory(struct Level* levels) {
    for (int i = 0; i < MAX_LEVELS; i++) {
        for (int j = 0; j < MAX_CLASSES; j++) {
            struct Student* currentStudent = levels[i].classes[j].studentsHead;
            while (currentStudent) {
                struct Student* temp = currentStudent;
                currentStudent = currentStudent->nextStudent;
                free(temp);
            }
        }
    }
}
