#include "coupon.h"

Coupon coupons[MAX_COUPONS];
int couponCount = 0;
double totalIncome = 0.0;

void readCoupons()
{
    FILE *couponFile = fopen("C:\\coding Portee\\Electronic_store\\coupons.csv", "r");
    if (couponFile == NULL)
    {
        printf("Cannot open coupons file!\n");
        return;
    }

    char buffer[200]; // Buffer to store each line

    // Read and skip the header line
    if (fgets(buffer, sizeof(buffer), couponFile) == NULL)
    {
        printf("Error reading header or file is empty!\n");
        fclose(couponFile);
        return;
    }

    int i = 0;
    while (fgets(buffer, sizeof(buffer), couponFile) != NULL)
    {
        if (i >= MAX_COUPONS)
        {
            printf("Maximum coupon limit reached. Some coupons will not be loaded.\n");
            break;
        }

        // Parse the line into the coupon structure
        if (sscanf(buffer, "%99[^,],%lf,%10s",
                   coupons[i].code, &coupons[i].discount, coupons[i].expiry) == 3)
        {
            i++;
        }
        else
        {
            printf("Skipping invalid line: %s", buffer);
        }
    }

    couponCount = i; // Update the total number of coupons loaded
    printf("Loaded %d coupon(s) successfully.\n", couponCount);
    fclose(couponFile);
}

int validateCoupon(const char *couponCode, double *discount)
{
    for (int i = 0; i < couponCount; ++i)
    {
        if (strcmp(coupons[i].code, couponCode) == 0)
        {
            // Parse expiry date (YYYY-MM-DD)
            int expiryYear, expiryMonth, expiryDay;
            sscanf(coupons[i].expiry, "%d-%d-%d", &expiryYear, &expiryMonth, &expiryDay);

            // Get the current date
            time_t now = time(NULL);
            struct tm *currentTime = localtime(&now);

            // Check expiry
            if ((expiryYear > currentTime->tm_year + 1900) ||
                (expiryYear == currentTime->tm_year + 1900 && expiryMonth > currentTime->tm_mon + 1) ||
                (expiryYear == currentTime->tm_year + 1900 && expiryMonth == currentTime->tm_mon + 1 &&
                 expiryDay >= currentTime->tm_mday))
            {
                *discount = coupons[i].discount;
                return 1; // Valid coupon
            }
            else
            {
                printf("Coupon has expired.\n");
                return 0; // Expired coupon
            }
        }
    }

    printf("Coupon not found.\n");
    return 0; // Invalid coupon
}
