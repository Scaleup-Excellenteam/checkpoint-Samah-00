#ifndef BUILD_DATA_H
#define BUILD_DATA_H


#include "operations.h"
#include "structures.h"


int decryptData();
int buildDatabase(struct Level* levels);
void readStudentsFromFile(FILE* file, struct Level* levels);


#endif
