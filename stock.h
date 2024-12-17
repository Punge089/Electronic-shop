#ifndef STOCK_H
#define STOCK_H

#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define STOCK_ARRAY_SIZE 1000
#define STOCK_NAME_LEN 1000
#define STOCK_DESC_LEN 1000

// Stock structure
typedef struct stock
{
    char class;
    int id;
    char name[STOCK_NAME_LEN];
    int quantity;
    double price;
    char description[STOCK_DESC_LEN];
    double threshold;
    int max;
} Stock;

// Global Variables
extern Stock stock[STOCK_ARRAY_SIZE];
extern int amount;

// Function Prototypes
void printheader();
void printtable();
void printcheader();
void printctable();
void readfile();
void savefile();
void ownersearch();
void bubblesort(int amount_of_items, int array[], int array2[]);
void addstock();
void deleteproduct();
void printstockpage();
void printeditproduct();
void editproduct();

#endif // STOCK_H
