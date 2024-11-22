#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void manageCoupons() {
    srand(time(NULL));
    const char *filename = "coupons.csv";
    FILE *file, *tempFile;
    int choice;

    do {
        printf("\n--- Coupon Management ---\n");
        printf("[1] Create Coupon\n");
        printf("[2] View Coupons\n");
        printf("[3] Delete Coupon\n");
        printf("[4] Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: {
                char code[5], finalCode[10], expirationDate[11], buffer[255];
                float discountPercentage;
                int isDuplicate = 0;

                const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
                for (int i = 0; i < 4; i++) {
                    code[i] = charset[rand() % (sizeof(charset) - 1)];
                }
                code[4] = '\0'; 
                snprintf(finalCode, sizeof(finalCode), "CPE-%s", code);

                printf("Generated Coupon Code: %s\n", finalCode);

                file = fopen(filename, "r");
                if (file != NULL) {
                    while (fgets(buffer, sizeof(buffer), file) != NULL) {
                        char existingCode[50];
                        sscanf(buffer, "%[^,]", existingCode);
                        if (strcmp(existingCode, finalCode) == 0) {
                            isDuplicate = 1;
                            break;
                        }
                    }
                    fclose(file);
                }

                if (isDuplicate) {
                    printf("Error: Coupon code '%s' already exists.\n", finalCode);
                    break;
                }

                printf("Enter Discount Percentage: ");
                scanf("%f", &discountPercentage);
                printf("Enter Expiration Date (YYYY.MM.DD): ");
                scanf("%s", expirationDate);

                int year, month, day;
                if (sscanf(expirationDate, "%d.%d.%d", &year, &month, &day) != 3) {
                    printf("Error: Invalid date format. Please use YYYY.MM.DD.\n");
                    break;
                }

                time_t t = time(NULL);
                struct tm tm = *localtime(&t);

                if (year < (tm.tm_year + 1900) ||
                    (year == (tm.tm_year + 1900) && month < (tm.tm_mon + 1)) ||
                    (year == (tm.tm_year + 1900) && month == (tm.tm_mon + 1) && day < tm.tm_mday)) {
                    printf("Error: Expiration date must be in the future.\n");
                    break;
                }

                file = fopen(filename, "a");
                if (file == NULL) {
                    printf("Error: Could not open file.\n");
                    break;
                }
                fprintf(file, "%s,%.2f,%s\n", finalCode, discountPercentage, expirationDate);
                fclose(file);

                printf("Coupon added successfully!\n");
                break;
            }
            case 2: {
                char buffer[255];
                int hasValidCoupons = 0;

                file = fopen(filename, "r");
                if (file == NULL) {
                    printf("No coupons found or file could not be opened.\n");
                    break;
                }

                tempFile = fopen("temp.csv", "w");
                if (tempFile == NULL) {
                    printf("Error: Could not create temporary file.\n");
                    fclose(file);
                    break;
                }

                time_t t = time(NULL);
                struct tm tm = *localtime(&t);

                printf("\n--- List of Coupons ---\n");

                while (fgets(buffer, sizeof(buffer), file) != NULL) {
                    char code[50], expirationDate[11];
                    float discountPercentage;

                    sscanf(buffer, "%[^,],%f,%[^,\n]", code, &discountPercentage, expirationDate);

                    int expYear, expMonth, expDay;
                    if (sscanf(expirationDate, "%d.%d.%d", &expYear, &expMonth, &expDay) != 3) {
                        continue;
                    }

                    if (expYear < (tm.tm_year + 1900) || 
                        (expYear == (tm.tm_year + 1900) && expMonth < (tm.tm_mon + 1)) ||
                        (expYear == (tm.tm_year + 1900) && expMonth == (tm.tm_mon + 1) && expDay < tm.tm_mday)) {
                        continue;
                    }

                    fprintf(tempFile, "%s,%.2f,%s\n", code, discountPercentage, expirationDate);
                    printf("%-7s %-6.2f %-6s\n", code, discountPercentage, expirationDate);
                    hasValidCoupons = 1;
                }

                fclose(file);
                fclose(tempFile);

                remove(filename);
                rename("temp.csv", filename);

                if (!hasValidCoupons) {
                    printf("No valid coupons available.\n");
                }
                break;
            }
            case 3: {
                char codeToDelete[50], buffer[255];
                printf("Enter Coupon Code to Delete: ");
                scanf("%s", codeToDelete);

                tempFile = fopen("temp.csv", "w");
                if (tempFile == NULL) {
                    printf("Error: Could not create temporary file.\n");
                    break;
                }

                file = fopen(filename, "r");
                if (file == NULL) {
                    printf("No coupons found or file could not be opened.\n");
                    fclose(tempFile);
                    break;
                }

                int found = 0;
                while (fgets(buffer, sizeof(buffer), file) != NULL) {
                    char currentCode[50];
                    sscanf(buffer, "%[^,]", currentCode);
                    if (strcmp(currentCode, codeToDelete) != 0) {
                        fputs(buffer, tempFile);
                    } else {
                        found = 1;
                    }
                }

                fclose(file);
                fclose(tempFile);

                if (found) {
                    remove(filename);
                    rename("temp.csv", filename);
                    printf("Coupon '%s' deleted successfully!\n", codeToDelete);
                } else {
                    remove("temp.csv");
                    printf("Coupon '%s' not found.\n", codeToDelete);
                }
                break;
            }
            case 4:
                printf("Exiting Coupon Management.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}

int main() {
    manageCoupons();
    return 0;
}
