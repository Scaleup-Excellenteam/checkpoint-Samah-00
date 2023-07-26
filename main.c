#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEVELS 12
#define MAX_CLASSES 10
#define MAX_COURSES 20
#define MAX_NAME_LEN 100
#define MAX_GRADE 100
#define MIN_GRADE 0
#define DEFAULT_GRADE 0

const char* courseNames[] = {
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


// Structure for Course
struct Course {
    char courseName[MAX_NAME_LEN];
    int grade; // Variable to store the grade for this course
};

// Structure for Student
struct Student {
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    int phoneNumber;
    int level;
    int class;
    struct Course courses[MAX_COURSES]; // Array of size 20 for courses
    struct Student* nextStudent; // Linked list pointer
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


// Structure for Class
struct Class {
    // Add class-specific data here
    // char className[50];
    struct Student* studentsHead;
};

// Structure for Level
struct Level {
    int levelNumber;
    struct Class classes[MAX_CLASSES]; // Array of size 10 for classes in this level
};

struct Course* createCourse(const char* name) {
    struct Course* newCourse = (struct Course*)malloc(sizeof(struct Course));
    // Copy the name into the courseName field
    strncpy(newCourse->courseName, name, sizeof(newCourse->courseName) - 1);
    newCourse->courseName[sizeof(newCourse->courseName) - 1] = '\0'; // Ensure null-terminated
    return newCourse;
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



int main() {
    // ... main function code ...

    // Open the file for reading
    FILE* file = fopen("students_with_class.txt", "r");
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
    struct Level levels[MAX_LEVELS];
    for (int i = 0; i < MAX_LEVELS; i++) {
        // Initialize the studentsHead to NULL for all classes in this level
        for (int j = 0; j < MAX_CLASSES; j++) {
            levels[i].classes[j].studentsHead = NULL;
        }
        // Read students' data from the file and create the student structures for this level
        readStudentsFromFile(file, levels);
    }

    // Close the file after reading
    fclose(file);

    // Printing the data of all students to the terminal
    for (int i = 0; i < MAX_LEVELS; i++) {
        for (int j = 0; j < MAX_CLASSES; j++) {
            struct Student* currentStudent = levels[i].classes[j].studentsHead;
            while (currentStudent) {
                printf("Name: %s %s\n", currentStudent->firstName, currentStudent->lastName);
                printf("Phone Number: %d\n", currentStudent->phoneNumber);
                printf("Level: %d\n", currentStudent->level);
                printf("Class: %d\n", currentStudent->class);
                for (int k = 0; k < MAX_COURSES; k++) {
                    printf("%s Grade: %d\n", currentStudent->courses[k].courseName, currentStudent->courses[k].grade);
                }
                printf("\n");
                currentStudent = currentStudent->nextStudent;
            }
        }
    }
    return 0;
}
