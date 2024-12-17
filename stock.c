#include "stock.h"

// Global stock array definition
Stock stock[STOCK_ARRAY_SIZE];
int amount = 0;

void printheader()
{
    printf("%-4s %-4s %-18s %-11s %-10s %-70s %-10s %-5s\n",
           "Class", "ID", "Name", "Quantity", "Price", "Description", "Threshold", "Max");
}

void bubblesort(int amount_of_items, int array[], int array2[])
{
    for (int i = 0; i < amount_of_items - 1; i++)
    {
        for (int j = 0; j < amount_of_items - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                int temp2 = array2[j];
                array[j] = array[j + 1];
                array2[j] = array2[j + 1];
                array[j + 1] = temp;
                array2[j + 1] = temp2;
            }
        }
    }
}

void printtable()
{
    printheader();
    for (int i = 0; i < amount; ++i)
        printf("%-5c %-5d %-20s %-10d %-10.2lf %-70s %-10.2lf %-5d\n",
               stock[i].class, stock[i].id, stock[i].name, stock[i].quantity, stock[i].price, stock[i].description, stock[i].threshold, stock[i].max);
    printf("\n\n");
}

void printcheader()
{
    printf("%-4s %-18s %-11s %-10s %-70s\n",
           "ID", "Name", "Quantity", "Price", "Description");
}

void printctable()
{
    printcheader();
    for (int i = 0; i < amount; ++i)
        printf("%-5d %-20s %-10d %-10.2lf %-70s\n",
               stock[i].id, stock[i].name, stock[i].quantity, stock[i].price, stock[i].description);
    printf("\n\n");
}

void readfile()
{
    FILE *stockfile;
    stockfile = fopen("stock.csv", "r");

    if (stockfile == NULL)
    {
        printf("Cannot open stock file bro!\n");
        exit(1);
    }

    // Skip header line
    fscanf(stockfile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,\n]", temp, temp, temp, temp, temp, temp, temp, temp);

    int i = 0;
    while (!feof(stockfile))
    {
        fscanf(stockfile, " %c,%d, %[^,],%d,%lf, %[^,],%lf,%d",
               &stock[i].class, &stock[i].id, stock[i].name, &stock[i].quantity, &stock[i].price, stock[i].description, &stock[i].threshold, &stock[i].max);
        ++i;
    }
    amount = i - 1;
    fclose(stockfile);
}
void savefile()
{
    FILE *stockfile;
    stockfile = fopen("stocksave.csv", "w");

    if (stockfile == NULL)
    {
        printf("Cannot open file for saving!\n");
        return;
    }

    fprintf(stockfile, "Class,ID,Name,Quantity,Price,Description,Threshold,Max\n");

    for (int i = 0; i < amount; ++i)
        fprintf(stockfile, "%c,%d,%s,%d,%.2lf,%s,%.2lf,%d\n",
                stock[i].class, stock[i].id, stock[i].name, stock[i].quantity, stock[i].price, stock[i].description, stock[i].threshold, stock[i].max);

    fclose(stockfile);
    printf("Stock data saved to stocksave.csv.\n");
}

void ownersearch()
{
    system("cls");
    printtable();

    int choice;

    while (1)
    {
        printf("=====================\n");
        printf("Search Menu\n");
        printf("=====================\n");
        printf("[1] Name\n");
        printf("[2] Category\n");
        printf("[3] Price range\n");
        printf("[4] Exit\n");
        printf("Please make your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Search by name: ");
            scanf(" %[^\n]", temp);

            system("cls");
            printheader();

            int found = 0;
            for (int i = 0; i < amount; ++i)
            {
                if (strstr(stock[i].name, temp) != NULL)
                {
                    printf("%-5c %-5d %-20s %-10d %-10.2lf %-70s %-10.2lf %-5d\n",
                           stock[i].class, stock[i].id, stock[i].name, stock[i].quantity, stock[i].price, stock[i].description, stock[i].threshold, stock[i].max);
                    found = 1;
                }
            }
            if (!found)
                printf("No items found matching the name.\n\n");
        }
        else if (choice == 2)
        {
            char category;
            printf("Enter category: ");
            scanf(" %c", &category);

            system("cls");
            printheader();

            int found = 0;
            for (int i = 0; i < amount; ++i)
            {
                if (stock[i].class == category)
                {
                    printf("%-5c %-5d %-20s %-10d %-10.2lf %-70s %-10.2lf %-5d\n",
                           stock[i].class, stock[i].id, stock[i].name, stock[i].quantity, stock[i].price, stock[i].description, stock[i].threshold, stock[i].max);
                    found = 1;
                }
            }
            if (!found)
                printf("No items found in the given category.\n\n");
        }
        else if (choice == 3)
        {
            double start_price, end_price;
            printf("Enter start price: ");
            scanf("%lf", &start_price);
            printf("Enter end price: ");
            scanf("%lf", &end_price);

            system("cls");
            printheader();

            int found = 0;
            for (int i = 0; i < amount; ++i)
            {
                if (stock[i].price >= start_price && stock[i].price <= end_price)
                {
                    printf("%-5c %-5d %-20s %-10d %-10.2lf %-70s %-10.2lf %-5d\n",
                           stock[i].class, stock[i].id, stock[i].name, stock[i].quantity, stock[i].price, stock[i].description, stock[i].threshold, stock[i].max);
                    found = 1;
                }
            }
            if (!found)
                printf("No items found in the specified price range.\n\n");
        }
        else if (choice == 4)
        {
            return;
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }
    }
}
void addstock()
{
    printf("=====================\n");
    printf("Add stock\n");
    printf("=====================\n\n");

    // Class Input
    printf("Class (A, B, C, D): ");
    scanf(" %c", &stock[amount].class);

    while (stock[amount].class != 'A' && stock[amount].class != 'B' &&
           stock[amount].class != 'C' && stock[amount].class != 'D')
    {
        printf("Invalid choice! Please enter A, B, C, or D: ");
        scanf(" %c", &stock[amount].class);
    }

    // Auto-increment ID
    stock[amount].id = amount + 1;

    // Name Input
    printf("Name: ");
    scanf(" %[^\n]", stock[amount].name);

    // Max Input
    printf("Max: ");
    scanf("%d", &stock[amount].max);

    // Quantity Input
    printf("Quantity: ");
    scanf("%d", &stock[amount].quantity);

    // Price Input
    printf("Price: ");
    scanf("%lf", &stock[amount].price);

    // Description Input
    printf("Description: ");
    scanf(" %[^\n]", stock[amount].description);

    // Threshold Input
    printf("Threshold: ");
    scanf("%lf", &stock[amount].threshold);

    // Confirmation
    int choice;
    printf("\n[1] Confirm\n");
    printf("[2] Cancel\n");
    printf("Please make your choice: ");

    while (1)
    {
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: // Confirm
            ++amount;
            printf("Stock item added successfully!\n");
            return;

        case 2: // Cancel
            printf("Operation cancelled. No stock was added.\n");
            return;

        default:
            printf("Invalid choice! Please enter 1 (Confirm) or 2 (Cancel): ");
        }
    }
}
void printstockpage()
{
    system("cls");
    printf("=====================\n");
    printf("Stock\n");
    printf("=====================\n\n");

    printtable();

    printf("Make your choice:\n");
    printf("[1] Add product\n");
    printf("[2] Edit product\n");
    printf("[3] Delete product\n");
    printf("[4] Search\n");
    printf("[5] Return to menu\n");
    printf("Please make your choice: ");
}

void deleteproduct()
{
    system("cls");
    printf("=====================\n");
    printf("Delete Product\n");
    printf("=====================\n\n");

    printtable();

    int delete, confirm_choice;

    printf("\nMake your choice:\n");
    printf("[1-%d] Remove product\n", amount);
    printf("[0] Return to menu\n");

    while (1)
    {
        printf("Please make your choice: ");
        scanf("%d", &delete);

        if (delete == 0)
        {
            return; // Return to previous menu
        }
        else if (delete > 0 && delete <= amount)
        {
            printf("[1] Confirm\n");
            printf("[2] Cancel\n");
            printf("Please make your choice: ");

            while (1)
            {
                scanf("%d", &confirm_choice);

                switch (confirm_choice)
                {
                case 1: // Confirm deletion
                    for (int i = delete - 1; i < amount - 1; ++i)
                    {
                        stock[i] = stock[i + 1]; // Shift elements left
                        stock[i].id = i + 1;    // Update IDs
                    }
                    --amount;
                    printf("Product successfully deleted.\n\n");
                    return;
                case 2: // Cancel
                    printf("Deletion cancelled.\n\n");
                    return;
                default:
                    printf("Invalid choice! Please enter 1 (Confirm) or 2 (Cancel): ");
                }
            }
        }
        else
        {
            printf("Invalid choice! Please select between 1 and %d, or 0 to return.\n", amount);
        }
    }
}
void printeditproduct()
{
    system("cls");
    printf("=====================\n");
    printf("Edit Product Menu\n");
    printf("=====================\n");
    printtable();

    printf("\nPlease make your choice:\n");
    printf("[1] Class\n");
    printf("[2] Name\n");
    printf("[3] Quantity\n");
    printf("[4] Price\n");
    printf("[5] Description\n");
    printf("[6] Threshold\n");
    printf("[7] Max\n");
    printf("[8] Return to main menu\n");
    printf("Please make your choice: ");
}

void editproduct()
{
    system("cls");
    printf("=====================\n");
    printf("Edit Product\n");
    printf("=====================\n\n");
    printtable();

    int edit_choice, edit_option, confirm;
    char strtemp[STOCK_NAME_LEN], chrtemp;
    int inttemp;
    double fltemp;

    printf("\n[1-%d] Edit product\n", amount);
    printf("[0] Return to menu\n");

    while (1)
    {
        printf("Please make your choice: ");
        scanf("%d", &edit_choice);

        if (edit_choice == 0)
        {
            return; // Return to main menu
        }
        else if (edit_choice > 0 && edit_choice <= amount)
        {
            int index = edit_choice - 1; // Adjust index

            while (1)
            {
                printeditproduct();
                printf("\nEditing product %d:\n", edit_choice);
                printheader();
                printf("%-5c %-5d %-20s %-10d %-10.2lf %-70s %-10.2lf %-5d\n",
                       stock[index].class, stock[index].id, stock[index].name, stock[index].quantity,
                       stock[index].price, stock[index].description, stock[index].threshold, stock[index].max);

                scanf("%d", &edit_option);

                switch (edit_option)
                {
                case 1: // Class
                    printf("New class (A-D): ");
                    scanf(" %c", &chrtemp);
                    while (chrtemp < 'A' || chrtemp > 'D')
                    {
                        printf("Invalid choice! Enter a valid class (A-D): ");
                        scanf(" %c", &chrtemp);
                    }
                    break;
                case 2: // Name
                    printf("New name: ");
                    scanf(" %[^\n]", strtemp);
                    break;
                case 3: // Quantity
                    printf("New quantity: ");
                    scanf("%d", &inttemp);
                    break;
                case 4: // Price
                    printf("New price: ");
                    scanf("%lf", &fltemp);
                    break;
                case 5: // Description
                    printf("New description: ");
                    scanf(" %[^\n]", strtemp);
                    break;
                case 6: // Threshold
                    printf("New threshold: ");
                    scanf("%lf", &fltemp);
                    break;
                case 7: // Max
                    printf("New max: ");
                    scanf("%d", &inttemp);
                    break;
                case 8: // Return
                    return;
                default:
                    printf("Invalid choice! Try again.\n");
                    continue;
                }

                // Confirm changes
                printf("\n[1] Confirm\n[2] Cancel\n");
                printf("Please make your choice: ");
                scanf("%d", &confirm);

                if (confirm == 1)
                {
                    switch (edit_option)
                    {
                    case 1:
                        stock[index].class = chrtemp;
                        break;
                    case 2:
                        strcpy(stock[index].name, strtemp);
                        break;
                    case 3:
                        stock[index].quantity = inttemp;
                        break;
                    case 4:
                        stock[index].price = fltemp;
                        break;
                    case 5:
                        strcpy(stock[index].description, strtemp);
                        break;
                    case 6:
                        stock[index].threshold = fltemp;
                        break;
                    case 7:
                        stock[index].max = inttemp;
                        break;
                    }
                    printf("Product updated successfully!\n\n");
                }
                else
                {
                    printf("Edit cancelled.\n\n");
                }
                break; // Break to allow further edits or return
            }
        }
        else
        {
            printf("Invalid choice! Please enter a valid product number.\n");
        }
    }
}