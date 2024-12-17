#include "owner.h"
#include "stock.h"   // For stock-related functions like printstockpage, addstock, savefile, etc.
#include <stdio.h>   // For printf and scanf
#include <stdlib.h>  // For system()

void printownerscreen()
{
    system("cls"); // Clear the screen (works on Windows)
    printf("=====================\n");
    printf("Owner Menu\n");
    printf("=====================\n\n");
    printf("Make your choice:\n");
    printf("[1] Manage Stock\n");
    printf("[2] Manage Coupon\n");
    printf("[3] View Report\n");
    printf("[4] Logging\n");
    printf("[5] Return to Menu\n\n");
    printf("Please make your choice: ");
}

void ownerscreen()
{
    int choice;

    printownerscreen();

    while (1)
    {
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: // Manage Stock
            stockpage(); // Call to manage stock
            printownerscreen();
            break;

        case 2: // Manage Coupon
            printf("Manage coupon feature not implemented yet.\n\n");
            break;

        case 3: // View Report
            printf("View report feature not implemented yet.\n\n");
            break;

        case 4: // Logging
            printf("Logging feature not implemented yet.\n\n");
            break;

        case 5: // Return to Main Menu
            return;

        default:
            printf("Invalid choice! Please try again: ");
        }
    }
}

void stockpage()
{
    int choice;

    printstockpage(); // Function from stock.h

    while (1)
    {
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: // Add Product
            addstock();   // Function from stock.h
            savefile();   // Save updated stock data
            printstockpage();
            break;

        case 2: // Edit Product
            editproduct(); // Edit stock data
            printstockpage();
            break;

        case 3: // Delete Product
            deleteproduct(); // Delete a product from stock
            savefile();
            printstockpage();
            break;

        case 4: // Search Product
            ownersearch(); // Search stock
            printstockpage();
            break;

        case 5: // Return to Owner Menu
            return;

        default:
            printf("Invalid choice! Please try again: ");
        }
    }
}
