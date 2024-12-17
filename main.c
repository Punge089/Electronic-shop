#include "owner.h"
#include "customer.h"
#include "coupon.h"
#include "stock.h"
#include "utility.h"

void printmainmenu();

void mainmenu()
{
    int choice;
    while (1)
    {
        printmainmenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            customerPage();
            break;

        case 2:
            ownerscreen(); // Call to ownerscreen
            break;

        case 3:
            printf("Exiting program...\n");
            return;

        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
}

void printmainmenu()
{
    printf("=====================\n");
    printf("Main Menu\n");
    printf("=====================\n");
    printf("[1] Customer Page\n");
    printf("[2] Owner Page\n");
    printf("[3] Exit\n");
    printf("Please make your choice: ");
}

int main(void)
{
    clearcart();
    readfile();
    readCoupons();

    mainmenu();
    return 0;
}
