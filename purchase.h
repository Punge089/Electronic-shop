#ifndef PURCHASE_H
#define PURCHASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "stock.h"
#include "coupon.h"

// Function Prototypes
void savePurchaseHistory(const char *purchasedItems, double totalPrice, double discountAmount);
void buyNow();

#endif // PURCHASE_H