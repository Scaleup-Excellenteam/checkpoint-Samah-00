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
void findCandidatesForDeparture(struct Level* levels);
void printStudentInfo(struct Student* student);
void calculateAveragePerCoursePerLayer(struct Level* levels);
void exportDatabaseToFile(struct Level* levels);
void printStudentToFile(FILE* file, struct Student* student);

#endif
