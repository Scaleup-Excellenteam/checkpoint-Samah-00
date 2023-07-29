#include "operations.h"
#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


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
        // Student found, display information using printStudentInfo function
        printStudentInfo(student);
    } else {
        printf("Student not found.\n");
    }
}


// Function to display all students
void displayAllStudents(struct Level* levels) {
    for (int i = 0; i < MAX_LEVELS; i++) {
        for (int j = 0; j < MAX_CLASSES; j++) {
            struct Student* currentStudent = levels[i].classes[j].studentsHead;
            while (currentStudent) {
                printStudentInfo(currentStudent);
                currentStudent = currentStudent->nextStudent;
            }
        }
    }
}


// Function to print student information
void printStudentInfo(struct Student* student) {
    printf("Name: %s %s\n", student->firstName, student->lastName);
    printf("Phone Number: %d\n", student->phoneNumber);
    printf("Level: %d\n", student->level);
    printf("Class: %d\n", student->class);
    for (int k = 0; k < MAX_COURSES; k++) {
        printf("%s Grade: %d\n", student->courses[k].courseName, student->courses[k].grade);
    }
    printf("\n");
}

// Function to find students who are candidates for departure based on a threshold grade and level
void findCandidatesForDeparture(struct Level* levels) {
    int threshold;
    printf("Enter the threshold grade for departure: ");
    scanf("%d", &threshold);

    int levelNumber;
    printf("Enter the level number to search for candidates: ");
    scanf("%d", &levelNumber);

    if (levelNumber < 1 || levelNumber > MAX_LEVELS) {
        printf("Invalid level number. Exiting the function.\n");
        return;
    }

    printf("Candidates for Departure in Level %d:\n", levelNumber);

    // Check if the level is valid
    if (levelNumber >= 1 && levelNumber <= MAX_LEVELS) {
        for (int j = 0; j < MAX_CLASSES; j++) {
            struct Student* currentStudent = levels[levelNumber - 1].classes[j].studentsHead;
            while (currentStudent) {
                bool isCandidate = false;
                for (int k = 0; k < MAX_COURSES; k++) {
                    if (currentStudent->courses[k].grade < threshold) {
                        isCandidate = true;
                        break;
                    }
                }
                if (isCandidate) {
                    printStudentInfo(currentStudent);
                }
                currentStudent = currentStudent->nextStudent;
            }
        }
    } else {
        printf("Invalid level number. Cannot find candidates.\n");
    }
}

// Function to calculate the average grade per course per level
void calculateAveragePerCoursePerLayer(struct Level* levels) {
    printf("Average Grade Per Course Per Level:\n");

    for (int i = 0; i < MAX_LEVELS; i++) {
        printf("Level %d:\n", i + 1);
        for (int k = 0; k < MAX_COURSES; k++) {
            double totalGrade = 0.0;
            int numStudents = 0;
            struct Student* currentStudent = levels[i].classes[0].studentsHead;
            while (currentStudent) {
                totalGrade += currentStudent->courses[k].grade;
                numStudents++;
                currentStudent = currentStudent->nextStudent;
            }
            if (numStudents > 0) {
                double averageGrade = totalGrade / numStudents;
                printf("%s Average Grade: %.2f\n", courseNames[k], averageGrade);
            } else {
                printf("%s Average Grade: No data available.\n", courseNames[k]);
            }
        }
        printf("\n");
    }
}

// Function to export the entire database to a file
void exportDatabaseToFile(struct Level* levels) {
    const char* fileName = "database_export.txt";
    FILE* file = fopen(fileName, "w");
    
    if (file == NULL) {
        printf("Error creating the export file.\n");
        return;
    }

    for (int i = 0; i < MAX_LEVELS; i++) {
        for (int j = 0; j < MAX_CLASSES; j++) {
            struct Student* currentStudent = levels[i].classes[j].studentsHead;
            while (currentStudent) {
                printStudentToFile(file, currentStudent);
                currentStudent = currentStudent->nextStudent;
            }
        }
    }

    fclose(file);
    printf("Database exported to %s successfully.\n", fileName);
}

// Function to print student information to a file
void printStudentToFile(FILE* file, struct Student* student) {
    fprintf(file, "Name: %s %s\n", student->firstName, student->lastName);
    fprintf(file, "Phone Number: %d\n", student->phoneNumber);
    fprintf(file, "Level: %d\n", student->level);
    fprintf(file, "Class: %d\n", student->class);
    for (int k = 0; k < MAX_COURSES; k++) {
        fprintf(file, "%s Grade: %d\n", student->courses[k].courseName, student->courses[k].grade);
    }
    fprintf(file, "\n");
}

// Function to print the main menu
void printMenu() {
    printf("\n==== Main Menu ====\n");
    printf("1. Add a new student\n");
    printf("2. Delete a student\n");
    printf("3. Edit student information\n");
    printf("4. Search for a student\n");
    printf("5. Display all students\n");
    printf("6. Find candidates for departure\n");
    printf("7. Calculate average per course per level\n");
    printf("8. Export the entire DB to a file\n");
    printf("9. Exit\n");
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
