#ifndef UTILITY_H
#define UTILITY_H

#define TEMP_ARRAY_SIZE 1000

extern char temp[TEMP_ARRAY_SIZE];
extern int tempy[TEMP_ARRAY_SIZE];

void clearcart();
void arranger(int amount, int array[], int array2[]);
int maxvalue(int amount, int array[]);
int universalscanf(int max);

#endif // UTILITY_H
