#ifndef OPERATIONS_H
#define OPERATIONS_H


#include <stdio.h>
#include "build_data.h"
#include "structures.h"


void addNewStudent(struct Level* levels, int levelNumber, int classNumber);
void deleteStudent(struct Level* levels);
void editStudent(struct Level* levels);
void searchStudent(struct Level* levels);
void displayAllStudents(struct Level* levels);
void printMenu();
void freeMemory(struct Level* levels);
struct Student* searchStudentByName(struct Level* levels, const char* firstName, const char* lastName);


#endif
