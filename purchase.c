#include "purchase.h"

void savePurchaseHistory(const char *purchasedItems, double totalPrice, double discountAmount)
{
    FILE *historyFile = fopen("purchase_history.csv", "a");
    if (historyFile == NULL)
    {
        printf("Error opening purchase history file.\n");
        return;
    }

    fprintf(historyFile, "\"%s\",%.2lf,%.2lf\n", purchasedItems, totalPrice, discountAmount);
    fclose(historyFile);

    // Update total income (global variable from coupon.h)
    totalIncome += totalPrice;
}

void buyNow()
{
    int productID, quantity, couponOption;
    double totalPrice = 0.0, discount = 0.0, discountAmount = 0.0;
    char purchasedItems[1000] = "", couponCode[100];

    system("cls");
    printf("====================\n");
    printf("Buy Now\n");
    printf("====================\n\n");

    while (1)
    {
        // Display available products
        printctable();

        // Ask for Product ID
        printf("Enter the Product ID to choose: ");
        scanf("%d", &productID);

        // Validate Product ID
        if (productID < 1 || productID > amount)
        {
            printf("Invalid Product ID! Please choose again.\n");
            continue;
        }

        // Ask for quantity
        printf("Enter quantity to purchase: ");
        scanf("%d", &quantity);

        // Validate quantity
        if (quantity > stock[productID - 1].quantity || quantity <= 0)
        {
            printf("Invalid quantity! Either not enough stock or invalid input.\n");
            continue;
        }

        // Add item to total
        double itemTotalPrice = quantity * stock[productID - 1].price;
        totalPrice += itemTotalPrice;

        // Add to purchased items
        char itemDetails[200];
        sprintf(itemDetails, "%s x%d (%.2lf), ", stock[productID - 1].name, quantity, itemTotalPrice);
        strcat(purchasedItems, itemDetails);

        printf("\nCurrent Total Price: %.2lf\n", totalPrice);
        printf("Purchased Items So Far: %s\n\n", purchasedItems);

        // User decision: Add more items or proceed
        printf("[1] Proceed to Payment\n[2] Add More Items\n[3] Cancel and Return to Customer Page\n\n");
        int action;
        scanf("%d", &action);

        if (action == 1)
            break;
        else if (action == 3)
        {
            printf("Returning to Customer Page...\n");
            sleep(2);
            return;
        }
    }

    // Coupon validation
    while (1)
    {
        printf("\n====================\n");
        printf("[1] Apply a Coupon\n[2] Skip Coupon\n");
        printf("Please make your choice: ");
        scanf("%d", &couponOption);

        if (couponOption == 1)
        {
            printf("Enter coupon code: ");
            scanf("%s", couponCode);

            if (validateCoupon(couponCode, &discount))
            {
                discountAmount = (totalPrice * discount / 100);
                totalPrice -= discountAmount;

                printf("\nCoupon Applied!\n");
                printf("Discount: %.2lf\n", discountAmount);
                printf("Final Total Price: %.2lf\n\n", totalPrice);
                break;
            }
            else
            {
                printf("Invalid or Expired Coupon! Try again or skip.\n");
            }
        }
        else if (couponOption == 2)
        {
            break;
        }
        else
        {
            printf("Invalid choice! Please try again.\n");
        }
    }

    // Confirm payment
    printf("Confirm payment? [1] Yes / [2] No: ");
    int confirm;
    scanf("%d", &confirm);

    if (confirm == 1)
    {
        // Deduct stock quantity
        for (int i = 0; i < amount; i++)
        {
            if (strstr(purchasedItems, stock[i].name))
            {
                stock[i].quantity -= quantity;
            }
        }

        savefile(); // Save updated stock

        // Save purchase history
        savePurchaseHistory(purchasedItems, totalPrice, discountAmount);

        // Print receipt
        printf("\n==========================\n");
        printf("Receipt\n");
        printf("==========================\n");
        printf("Purchased Items: %s\n", purchasedItems);
        printf("Subtotal: %.2lf\n", totalPrice + discountAmount);
        if (discountAmount > 0)
            printf("Discount Applied: %.2lf\n", discountAmount);
        printf("Total Price: %.2lf\n", totalPrice);
        printf("==========================\n");

        printf("\nThank you for your purchase!\n");
        int returnToMenu;
        do
        {
            printf("Press [0] to return to Customer Page: ");
            scanf("%d", &returnToMenu);
        } while (returnToMenu != 0);
    }
    else
    {
        printf("Payment canceled. Returning to menu...\n");
        sleep(2);
    }
}
