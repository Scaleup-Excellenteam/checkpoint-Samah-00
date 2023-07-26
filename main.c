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
    return newCourse;
}

// Function to read the students' data from the file and create the student structures
void readStudentsFromFile(FILE* file, struct Level* level) {
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    int phoneNumber;
    int levelNumber;
    int classNumber;
    int grades[MAX_COURSES];

    for (int i = 0; i < MAX_CLASSES; i++) {
        for (int j = 0; j < MAX_LEVELS; j++) {
            fscanf(file, "%s %s %d %d %d", firstName, lastName, &phoneNumber, &levelNumber, &classNumber);
            for (int k = 0; k < MAX_COURSES; k++) {
                fscanf(file, "%d", &grades[k]);
            }
            struct Student* newStudent = createStudent(firstName, lastName, phoneNumber, levelNumber, classNumber, grades);
            // Add the new student to the linked list of students in the current class
            newStudent->nextStudent = level->classes[i].studentsHead;
            level->classes[i].studentsHead = newStudent;
        }
    }
}




int main() {
    // ... main function code ...
    /*
    // Creating courses and linking them to a student
    struct Course* courses[MAX_COURSES];
    for (int i = 0; i < MAX_COURSES; i++) {
        courses[i] = createCourse(courseNames[i]);
        // Link this course to a student or do other necessary operations
    }

    // ... rest of main function code ...
    */
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

    // Create the level structure
    struct Level level;
    // Initialize the studentsHead to NULL for all classes
    for (int i = 0; i < MAX_CLASSES; i++) {
        level.classes[i].studentsHead = NULL;
    }

    // Read students' data from the file and create the student structures
    readStudentsFromFile(file, &level);

    // Close the file after reading
    fclose(file);

    // Printing the data of the first 10 students to the terminal
    for (int i = 0; i < MAX_CLASSES; i++) {
        printf("Class %d:\n", i + 1);
        struct Student* currentStudent = level.classes[i].studentsHead;
        int count = 0;
        while (currentStudent && count < 10) {
            printf("Name: %s %s\n", currentStudent->firstName, currentStudent->lastName);
            printf("Phone Number: %d\n", currentStudent->phoneNumber);
            printf("Level: %d\n", currentStudent->level);
            printf("Class: %d\n", currentStudent->class);
            for (int j = 0; j < MAX_COURSES; j++) {
                printf("%s Grade: %d\n", currentStudent->courses[j].courseName, currentStudent->courses[j].grade);
            }
            printf("\n");
            currentStudent = currentStudent->nextStudent;
            count++;
        }
    }
    return 0;
}