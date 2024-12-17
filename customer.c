#include "customer.h"
#include "stock.h"
#include "utility.h"

int cart[100];          // Cart storage
int cartamount[100];    // Amount per cart item
int icart = 0;          // Index for cart

void buylater()
{
    int choice = 0, quantity = 0, count = 0;
    while (1)
    {
        system("cls");
        printf("=====================\n");
        printf("Cart Management\n");
        printf("=====================\n\n");

        // Print cart
        double total = 0.0;
        if (icart == 0)
        {
            printf("Your cart is empty!\n");
            printf("Press any key to return...\n");
            universalscanf(0);
            return;
        }
        else
        {
            printcheader();
            for (int i = 0; i < icart; ++i)
            {
                printf("%-5d %-20s %-10d %-10.2lf %-70s\n",
                       stock[cart[i]].id, stock[cart[i]].name, cartamount[i],
                       stock[cart[i]].price, stock[cart[i]].description);
                total += stock[cart[i]].price * cartamount[i];
            }
            printf("\nTotal Price: %.2lf\n", total);
        }

        printf("\nMake your choice:\n");
        printf("[1] Add to Cart\n");
        printf("[2] Edit Cart\n");
        printf("[3] Return to Customer Page\n");
        printf("Please make your choice: ");
        choice = universalscanf(3);

        if (choice == 1)
        {
            while (1)
            {
                printctable();
                printf("Select Product ID to Add to Cart (or 0 to exit): ");
                int productID = universalscanf(amount);
                if (productID == 0)
                    break;

                printf("Enter Quantity [1-%d]: ", stock[productID - 1].quantity);
                quantity = universalscanf(stock[productID - 1].quantity);

                count = 0;
                for (int i = 0; i < icart; ++i)
                {
                    if (cart[i] == productID - 1)
                    {
                        cartamount[i] += quantity;
                        count = 1;
                        break;
                    }
                }
                if (!count)
                {
                    cart[icart] = productID - 1;
                    cartamount[icart] = quantity;
                    icart++;
                }
            }
        }
        else if (choice == 2)
        {
            printf("Select Product ID to Edit (or 0 to exit): ");
            int productID = universalscanf(icart);
            if (productID == 0)
                break;

            for (int i = 0; i < icart; ++i)
            {
                if (cart[i] == productID - 1)
                {
                    printf("Enter New Quantity [1-%d]: ", stock[cart[i]].quantity);
                    cartamount[i] = universalscanf(stock[cart[i]].quantity);

                    if (cartamount[i] == 0)
                    {
                        arranger(icart, cart, cartamount);
                        --icart;
                    }
                    break;
                }
            }
        }
        else if (choice == 3)
        {
            return;
        }
    }
}

void customerPage()
{
    int choice;
    while (1)
    {
        system("cls");
        printf("=====================\n");
        printf("Customer Page\n");
        printf("=====================\n\n");
        printf("Make your choice:\n");
        printf("[1] Buy Now\n");
        printf("[2] Buy Later\n");
        printf("[3] Exit to Main Menu\n\n");
        printf("Please make your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            buyNow();
            break;
        case 2:
            buylater();
            break;
        case 3:
            printf("Returning to Main Menu...\n");
            return;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
}
