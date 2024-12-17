#ifndef COUPON_H
#define COUPON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COUPONS 100

typedef struct coupon
{
    char code[100];   // Coupon code
    double discount;  // Discount percentage
    char expiry[11];  // Expiry date in YYYY-MM-DD format
} Coupon;

// Global Variables
extern Coupon coupons[MAX_COUPONS];
extern int couponCount;
extern double totalIncome;

// Function Prototypes
void readCoupons();
int validateCoupon(const char *couponCode, double *discount);

#endif // COUPON_H
