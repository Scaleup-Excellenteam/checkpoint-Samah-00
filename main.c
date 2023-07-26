#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEVELS 7
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
    int phone_number;
    int level;
    int class;
    struct Course courses[MAX_COURSES]; // Array of size 20 for courses
    struct Student* nextStudent; // Linked list pointer
};

struct Student* createStudent(const char* firstName, const char* lastName, int level, int class, const int* grades) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    strncpy(newStudent->firstName, firstName, sizeof(newStudent->firstName) - 1);
    newStudent->firstName[sizeof(newStudent->firstName) - 1] = '\0'; // Ensure null-terminated
    strncpy(newStudent->lastName, lastName, sizeof(newStudent->lastName) - 1);
    newStudent->lastName[sizeof(newStudent->lastName) - 1] = '\0'; // Ensure null-terminated

    newStudent->level = level;
    newStudent->class = class;

    for (int i = 0; i < MAX_COURSES; i++) {
        strncpy(newStudent->courses[i].courseName, courseNames[i], sizeof(newStudent->courses[i].courseName) - 1);
        newStudent->courses[i].courseName[sizeof(newStudent->courses[i].courseName) - 1] = '\0'; // Ensure null-terminated
        // Fill in actual grades if they exist
        if (grades[i] >= MIN_GRADE && grades[i] <= MAX_GRADE) {
            newStudent->courses[i].grade = grades[i];
        }
        // Initialize grades to 0
        else {
            newStudent->courses[i].grade = DEFAULT_GRADE;
        }
    }

    return newStudent;
}


// Structure for Class
struct Class {
    // Add class-specific data here
    // For example: char className[50];
    struct Student* studentsHead;
};

// Structure for Level
struct Level {
    // Add level-specific data here
    // For example: int levelNumber;
    struct Class classes[MAX_CLASSES]; // Array of size 10 for classes in this level
};

struct Course* createCourse(const char* name) {
    struct Course* newCourse = (struct Course*)malloc(sizeof(struct Course));
    // Copy the name into the courseName field
    strncpy(newCourse->courseName, name, sizeof(newCourse->courseName) - 1);
    newCourse->courseName[sizeof(newCourse->courseName) - 1] = '\0'; // Ensure null-terminated
    newCourse->nextCourse = NULL;
    return newCourse;
}


int main() {
    // ... main function code ...

    // Creating courses and linking them to a student
    struct Course* courses[MAX_COURSES];
    for (int i = 0; i < MAX_COURSES; i++) {
        courses[i] = createCourse(courseNames[i]);
        // Link this course to a student or do other necessary operations
    }

    // ... rest of main function code ...

    return 0;
}