#ifndef STRUCTURES_H
#define STRUCTURES_H


#include "constants.h"


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


// Structure for Class
struct Class {
    struct Student* studentsHead;
};


// Structure for Level
struct Level {
    int levelNumber;
    struct Class classes[MAX_CLASSES]; // Array of size 10 for classes in this level
};


// Function prototypes
struct Student* createStudent(const char* firstName, const char* lastName, int phoneNumber, int level, int class, const int* grades);
struct Course* createCourse(const char* name);


#endif





