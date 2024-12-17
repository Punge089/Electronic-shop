#include "utility.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

char temp[TEMP_ARRAY_SIZE];
int tempy[TEMP_ARRAY_SIZE];

void clearcart()
{
    for (int i = 0; i < TEMP_ARRAY_SIZE; ++i)
    {
        tempy[i] = 0;
    }
}

void arranger(int amount, int array[], int array2[])
{
    for (int i = 0; i < amount; ++i)
    {
        array[i] = array[i + 1];
        array2[i] = array2[i + 1];
    }
}

int maxvalue(int amount, int array[])
{
    int max = array[0];
    for (int i = 0; i < amount; ++i)
    {
        if (array[i] > max)
            max = array[i];
    }
    return max;
}

int universalscanf(int max)
{
    int choice = 0;
    scanf(" %[^\n]", temp);
    for (int i = 0; i < strlen(temp); ++i)
        choice = (choice * pow(10, i)) + (temp[i] - '0');
    if (choice >= 0 && choice <= max)
        return choice;
    else
    {
        printf("Choose valid!\n");
        return universalscanf(max);
    }
}
