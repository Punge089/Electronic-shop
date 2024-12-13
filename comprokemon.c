#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct account
{
    char username[1000];
    char password[1000];
} account[1];

struct stock
{
    char class;
    int id;
    char name[1000];
    int quantity;
    double price;
    char description[1000];
    double threshold;
    int max;
} stock[1000];

struct coupon
{
    char code[100];
    double discount; // Discount percentage
    char expiry[11]; // Expiry date in YYYY-MM-DD format
} coupons[100];

char temp[1000];

int amount;

void printheader()
{
    printf("%-4s %-4s %-18s %-11s %-10s %-70s %-10s %-5s\n",
           "Class", "ID", "Name", "Quantity", "Price", "Description", "Threshold", "Max");
}

void printtable()
{
    printheader();
    for (int i = 0; i < amount; ++i)
        printf("%-5c %-5d %-20s %-10d %-10.2lf %-70s %-10.2lf %-5d\n",
               stock[i].class, stock[i].id, stock[i].name, stock[i].quantity, stock[i].price, stock[i].description, stock[i].threshold, stock[i].max);
    printf("\n\n");
}

void readfile()
{

    FILE *stockfile;
    stockfile = fopen("C:\\coding Portee\\Electronic_store\\stock.csv", "r");

    if (stockfile == NULL)
    {
        printf("Cannot open stock file bro!");
        exit(1);
    }

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
    return;
}

void savefile()
{
    FILE *stockfile;
    stockfile = fopen("C:\\Users\\User\\OneDrive\\Desktop\\stocksave.csv", "w");

    fprintf(stockfile, "Class,ID,Name,Quantity,Price,Description,Threshold,Max\n");

    for (int i = 0; i < amount; ++i)
        fprintf(stockfile, "%c,%d,%s,%d,%.2lf,%s,%.2lf,%d\n",
                stock[i].class, stock[i].id, stock[i].name, stock[i].quantity, stock[i].price, stock[i].description, stock[i].threshold, stock[i].max);

    fclose(stockfile);
}

void ownersearch()
{
    system("cls");
    printtable();

    int a;

    while (1)
    {

        printf("=====================\n");
        printf("Search\n");
        printf("================////\n\n");
        printf("Make your choice:\n");
        printf("[1] Name\n");
        printf("[2] Category\n");
        printf("[3] Price range\n");
        printf("[4] Exit\n\n");
        printf("Please make your choice: ");

        scanf("%d", &a);

        int count, j, k, z;
        char tempchr;

        if (a == 1)
        {
            printf("Search name: ");
            scanf("%s", temp);
            system("cls");
            printheader();
            count = 0;
            for (int i = 0; i < amount; ++i)
            {

                if (strlen(temp) <= strlen(stock[i].name))
                {
                    for (j = 0; j < (strlen(stock[i].name) - strlen(temp) + 1); ++j)
                    {
                        for (k = j, z = 0; k < (strlen(temp) + j); ++k, ++z)
                        {
                            if ((temp[z] != stock[i].name[k]) && (temp[z] != (stock[i].name[k] + 'A' - 'a')) && (temp[z] != (stock[i].name[k] + 'a' - 'A')))
                            {
                                break;
                            }
                        }

                        if (z == strlen(temp))
                        {
                            printf("%-5c %-5d %-20s %-10d %-10.2lf %-70s %-10.2lf %-5d\n",
                                   stock[i].class, stock[i].id, stock[i].name, stock[i].quantity, stock[i].price, stock[i].description, stock[i].threshold, stock[i].max);
                            ++count;
                            break;
                        }
                    }
                }
                /*else{  //didn't use, but incase we need it in future(wrong a little bit in printf)
                    for(j=0;j<(strlen(temp));++j){
                            if((temp[j] != stock[i].name[j]) && (temp[j] != (stock[i].name[j]+'A'-'a')) && (temp[j] != (stock[i].name[j]+'a'-'A'))){
                                break;
                            }
                        }

                    if(j==strlen(temp)){
                            system("cls");
                            printheader();
                            printf("%-5c %-5d %-20s %-10d %-10.2lf %-70s %-10.2lf %-5d\n",
                            stock[i].class,stock[i].id, stock[i].name, stock[i].quantity,stock[i].price, stock[i].description, stock[i].threshold,stock[i].max);
                            ++count;
                            break;
                        }
                }*/
            }
            printf("\n");
            if (count == 0)
            {
                system("cls");
                for (int i = 0; i < 5; ++i)
                {
                    printf("No item found! ");
                }
                printf("No item found!\n\n");
            }
        }
        else if (a == 2)
        {
            printf("Make your choice:\n");
            printf("[1] Phone\n");
            printf("[2] Gadgets\n");
            printf("[3] est\n");
            printf("[4] Exit\n\n");
            printf("Please make your choice: ");
            while (1)
            {

                scanf("%d", &a);

                if (a == 1)
                {
                    tempchr = 'A';
                    break;
                }
                else if (a == 2)
                {
                    tempchr = 'A';
                    break;
                }
                else if (a == 3)
                {
                    tempchr = 'A';
                    break;
                }
                else if (a == 4)
                    return;
                else
                {
                    printf("Please make invalid choice!\n");
                    printf("Please make your choice: ");
                }
            }
            count = 0;
            for (int i = 0; i < amount; ++i)
            {
                if (stock[i].class == tempchr)
                    ++count;
            }
            if (count == 0)
            {
                system("cls");
                printf("No item found!\n\n");
            }
            else
            {
                printheader();
                for (int i = 0; i < amount; ++i)
                {
                    if (stock[i].class == tempchr)
                        printf("%-5c %-5d %-20s %-10d %-10.2lf %-70s %-10.2lf %-5d\n",
                               stock[i].class, stock[i].id, stock[i].name, stock[i].quantity, stock[i].price, stock[i].description, stock[i].threshold, stock[i].max);
                }
                printf("\n\n");
            }
        }
        else if (a == 3)
        {
            double startprice, endprice;
            printf("Start price: ");
            scanf("%lf", &startprice);
            printf("End price: ");
            scanf("%lf", &endprice);

            system("cls");
            printheader();
            count = 0;
            for (int i = 0; i < amount; ++i)
            {
                if (stock[i].price >= startprice && stock[i].price <= endprice)
                {
                    printf("%-5c %-5d %-20s %-10d %-10.2lf %-70s %-10.2lf %-5d\n",
                           stock[i].class, stock[i].id, stock[i].name, stock[i].quantity, stock[i].price, stock[i].description, stock[i].threshold, stock[i].max);
                    ++count;
                    continue;
                }
            }
            printf("\n");
            if (count == 0)
            {
                system("cls");
                for (int i = 0; i < 5; ++i)
                {
                    printf("No item found! ");
                }
                printf("No item found!\n\n");
            }
        }
        else if (a == 4)
            return;
        else
        {
            printf("Please make invalid choice!\n");
            printf("Please make your choice: ");
        }
    }
}

void addstock()
{

    printf("=====================\n");
    printf("Add stock\n");
    printf("================////\n\n");

    printf("Class(M,H,S,P) :");
    scanf(" %c", &stock[amount].class);

    while (1)
    {
        if (stock[amount].class != 'A')
        {
            printf("Please make invalid choice!\n");
            printf("Please make your choice:");
            scanf(" %c", &stock[amount].class);
        }
        else
            break;
    }

    stock[amount].id = amount + 1;

    printf("Name :");
    scanf("%s", stock[amount].name);

    printf("Max :");
    scanf("%d", &stock[amount].max);

    printf("Quantity :");
    scanf("%d", &stock[amount].quantity);

    printf("Price :");
    scanf("%lf", &stock[amount].price);

    printf("Description :");
    scanf(" %[^\n]", stock[amount].description);

    printf("Threshold :");
    scanf("%lf", &stock[amount].threshold);

    int a;
    printf("[1] Comfirm\n");
    printf("[2] Cancel\n");
    printf("Please make your choice: ");

    while (1)
    {
        scanf("%d", &a);

        switch (a)
        {
        case 1: // confirm
            ++amount;
            // addstock();
            return;
            break;
        case 2: // cancel
            // addstock();
            return;
            break;
        default:
            printf("Please make invalid choice!\n");
            printf("Please make your choice: ");
        }
    }
}

void printstockpage()
{
    system("cls");
    printf("=====================\n");
    printf("Stock\n");
    printf("================////\n\n");

    printtable();

    printf("Make your choice:\n");
    printf("[1] Add product\n");
    printf("[2] Edit product\n");
    printf("[3] Delete product\n");
    printf("[4] Search\n");
    printf("[5] Return menu\n");
    printf("Please make your choice: ");
}

void deleteproduct()
{
    system("cls");
    printf("=====================\n");
    printf("Delete product\n");
    printf("================////\n\n");
    printtable();

    int delete, a;

    printf("\n\n");
    printf("Make your choice: \n");
    printf("[1-%d] Remove product\n", amount);
    printf("[0] Return menu\n");

    while (1)
    {
        printf("Please make your choice: ");
        scanf("%d", &delete);

        if (delete == 0)
        {
            return;
        }
        else if (delete > 0 && delete <= amount)
        {

            printf("[1] Comfirm\n");
            printf("[2] Cancel\n");
            printf("Please make your choice: ");

            while (1)
            {
                scanf("%d", &a);

                switch (a)
                {
                case 1: // confirm
                    for (int i = delete -1; i < amount; ++i)
                    {
                        stock[i].class = stock[i + 1].class;
                        stock[i].id = i + 1;
                        strcpy(stock[i].name, stock[i + 1].name);
                        stock[i].quantity = stock[i + 1].quantity;
                        stock[i].price = stock[i + 1].price;
                        strcpy(stock[i].description, stock[i + 1].description);
                        stock[i].threshold = stock[i + 1].threshold;
                        stock[i].max = stock[i + 1].max;
                    }
                    --amount;
                    deleteproduct();
                    return;
                    break;
                case 2: // cancel
                    deleteproduct();
                    return;
                    break;
                default:
                    printf("Please make invalid choice!\n");
                    printf("Please make your choice: ");
                }
            }
        }
        else
        {
            printf("Please make invalid choice!\n");
        }
    }
}

void printeditproduct()
{
    system("cls");
    printf("=====================\n");
    printf("Edit product\n");
    printf("================////\n\n");
    printtable();

    printf("Please make your choice: ");
    printf("[1] Name\n");
    printf("[2] Quantity\n");
    printf("[3] Price\n");
    printf("[4] Description\n");
    printf("[5] Threshold\n");
    printf("[6] Max\n");
    printf("[7] Return\n");
    printf("Please make your choice: ");
}

void editproduct()
{
    system("cls");
    printf("=====================\n");
    printf("Edit product\n");
    printf("================////\n\n");
    printtable();

    int edit, a, b, inttemp;

    char strtemp[1000], chrtemp;

    double fltemp;

    printf("\n\n");
    printf("Make your choice: \n");
    printf("[1-%d] Edit product\n", amount);
    printf("[0] Return menu\n");

    while (1)
    {
        printf("Please make your choice: ");
        scanf("%d", &edit);

        if (edit == 0)
        {
            return;
        }
        else if (edit > 0 && edit <= amount)
        {

            --edit;

            while (1)
            {

                system("cls");
                printf("=====================\n");
                printheader();

                printf("%-5c %-5d %-20s %-10d %-10.2lf %-70s %-10.2lf %-5d\n",
                       stock[edit].class, stock[edit].id, stock[edit].name, stock[edit].quantity, stock[edit].price, stock[edit].description, stock[edit].threshold, stock[edit].max);
                printf("================////\n\n");

                printf("Make your choice: \n");
                printf("[1] Class\n");
                printf("[2] Name\n");
                printf("[3] Quantity\n");
                printf("[4] Price\n");
                printf("[5] Description\n");
                printf("[6] Threshold\n");
                printf("[7] Max\n");
                printf("[8] Return\n");

                while (1)
                {
                    printf("Please make your choice:");
                    scanf("%d", &a);
                    if (a > 8 || a < 1)
                    {
                        printf("Please make invalid choice!\n");
                        printf("Please make your choice:");
                    }
                    else
                    {
                        switch (a)
                        {
                        case 1:
                            printf("New class: ");
                            scanf(" %c", &chrtemp);
                            while (1)
                            {
                                if (chrtemp != 'A')
                                {
                                    printf("Please make invalid choice!\n");
                                    printf("Please make your choice:");
                                    scanf(" %c", &chrtemp);
                                }
                                else
                                    break;
                            }
                            break;
                        case 2:
                            printf("New name: ");
                            scanf(" %[^\n]", &strtemp);
                            break;
                        case 3:
                            printf("New quantity: ");
                            scanf("%d", &inttemp);
                            break;
                        case 4:
                            printf("New price: ");
                            scanf("%lf", &fltemp);
                            break;
                        case 5:
                            printf("New description: ");
                            scanf("%s", &strtemp);
                            break;
                        case 6:
                            printf("New threshold: ");
                            scanf("%lf", &fltemp);
                            break;
                        case 7:
                            printf("New max: ");
                            scanf("%d", &inttemp);
                            break;
                        case 8:
                            editproduct();
                            return;
                            break;
                        default:
                            break;
                        }
                        break;
                    }
                }

                printf("[1] Comfirm\n");
                printf("[2] Cancel\n");
                printf("Please make your choice: ");

                while (1)
                {
                    scanf("%d", &b);
                    if (b == 1)
                    {
                        switch (a)
                        {
                        case 1:
                            stock[edit].class = chrtemp;
                            break;
                        case 2:
                            strcpy(stock[edit].name, strtemp);
                            break;
                        case 3:
                            stock[edit].quantity = inttemp;
                            break;
                        case 4:
                            stock[edit].price = fltemp;
                            break;
                        case 5:
                            strcpy(stock[edit].description, strtemp);
                            break;
                        case 6:
                            stock[edit].threshold = fltemp;
                            break;
                        case 7:
                            stock[edit].max = inttemp;
                            break;
                        default:
                            break;
                        }
                        break;
                    }
                    else if (b == 0)
                        break;
                    else
                    {
                        printf("Please make invalid choice!\n");
                        printf("Please make your choice: ");
                    }
                }
            }
        }
        else
        {
            printf("Please make invalid choice!\n");
        }
    }
}

void stockpage()
{

    printstockpage();
    int a;

    while (1)
    {

        scanf("%d", &a);

        switch (a)
        {
        case 1: // create product

            addstock();
            savefile();
            printstockpage();
            break;
        case 2: // edit
            editproduct();
            printstockpage();
            break;
        case 3: // delete
            deleteproduct();
            savefile();
            printstockpage();
            break;
        case 4: // search
            ownersearch();
            printstockpage();
            break;
        case 5: // return menu
            return;
            break;
        default:
            printf("Please make invalid choice!\n");
            printf("Please make your choice: ");
        }
    }
}

void printownerscreen()
{
    system("cls");
    printf("=====================\n");
    printf("Owner menu\n");
    printf("================////\n\n");
    printf("Make your choice:\n");
    printf("[1] Manage stock\n");
    printf("[2] Manage coupon\n");
    printf("[3] View report\n");
    printf("[4] Logging\n");
    printf("[5] Return to menu\n\n");
    printf("Please make your choice: ");
}

void ownerscreen()
{

    printownerscreen();

    int a;

    while (1)
    {

        scanf("%d", &a);

        switch (a)
        {
        case 1: // manage stock
            stockpage();
            printownerscreen();
            break;
        case 2: // manage coupon

            break;
        case 3: // view report

            break;
        case 4: // logging

            break;
        case 5: // return menu
            system("cls");
            return;
            break;
        default:
            printf("Please make invalid choice!\n");
            printf("Please make your choice: ");
        }
    }
}

void printmainmenu()
{
    // system("cls");
    printf("=====================\n");
    printf("Main menu\n");
    printf("================////\n\n");
    printf("Make your choice:\n");
    printf("[1] Customer page\n");
    printf("[2] Owner page\n");
    printf("[3] Exit\n\n");
    printf("Please make your choice: ");
}

void manageCart()
{
    int choice;
    while (1)
    {
        system("cls");
        printf("=====================\n");
        printf("Cart\n");
        printf("================////\n\n");
        printf("Make your choice:\n[1] Buy\n[2] Choose\n[3] Exit\n\n");
        printf("Please make your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Buying process initiated...\n");
            break;
        case 2:
            printf("Choose an item...\n");
            break;
        case 3:
            printf("Exiting cart management...\n");
            return;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
}

int couponCount = 0; // Tracks the number of coupons loaded

void readCoupons()
{
    FILE *couponFile = fopen("C:\\coding Portee\\Electronic_store\\coupons.csv", "r");
    if (couponFile == NULL)
    {
        printf("Cannot open coupons file!\n");
    }

    char buffer[200]; // Buffer to store each line
    // Read and skip the header line
    if (fgets(buffer, sizeof(buffer), couponFile) == NULL)
    {
        printf("Error reading header or file is empty!\n");
        fclose(couponFile);
    }

    int i = 0;
    while (fgets(buffer, sizeof(buffer), couponFile) != NULL)
    {
        if (i >= 100)
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
    fclose(couponFile);
}

double totalIncome = 0.0;

int validateCoupon(const char *couponCode, double *discount) {
    FILE *couponFile = fopen("C:\\coding Portee\\Electronic_store\\coupons.csv", "r");
    if (couponFile == NULL) {
        printf("Cannot open coupons file!\n");
        return 0;
    }

    char buffer[200];
    while (fgets(buffer, sizeof(buffer), couponFile) != NULL) {
        char fileCode[100];
        double fileDiscount;
        char expiry[11];

        // Parse the line
        if (sscanf(buffer, "%99[^,],%lf,%10s", fileCode, &fileDiscount, expiry) == 3) {
            if (strcmp(fileCode, couponCode) == 0) {
                // Parse expiry date (YYYY-MM-DD)
                int expiryYear, expiryMonth, expiryDay;
                sscanf(expiry, "%d-%d-%d", &expiryYear, &expiryMonth, &expiryDay);

                // Get the current date
                time_t now = time(NULL);
                struct tm *currentTime = localtime(&now);

                // Check expiry
                if ((expiryYear > currentTime->tm_year + 1900) ||
                    (expiryYear == currentTime->tm_year + 1900 && expiryMonth > currentTime->tm_mon + 1) ||
                    (expiryYear == currentTime->tm_year + 1900 && expiryMonth == currentTime->tm_mon + 1 &&
                     expiryDay >= currentTime->tm_mday)) {
                    *discount = fileDiscount;
                    fclose(couponFile);
                    return 1; // Valid coupon
                } else {
                    printf("Coupon has expired.\n");
                    fclose(couponFile);
                    return 0; // Expired coupon
                }
            }
        }
    }

    printf("Coupon not found.\n");
    fclose(couponFile);
    return 0; // Invalid coupon
}


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

    // Update total income
    totalIncome += totalPrice;
}

void buyNow() {
    int productID, quantity, couponOption;
    double totalPrice = 0.0, discount = 0.0;
    char purchasedItems[1000] = "", couponCode[100];

    system("cls");
    printf("====================\n");
    printf("Buy Now\n");
    printf("====================\n\n");

    while (1) {
        // Display the product list
        printtable();

        // Ask user to select a product to buy
        printf("Enter the Product ID to choose: ");
        scanf("%d", &productID);

        // Validate Product ID
        if (productID < 1 || productID > amount) {
            printf("Invalid Product ID! Please choose again.\n");
            continue;
        }

        // Ask for quantity
        printf("Enter quantity to purchase: ");
        scanf("%d", &quantity);

        // Validate quantity
        if (quantity > stock[productID - 1].quantity || quantity <= 0) {
            printf("Invalid quantity! Either not enough stock or invalid input.\n");
            continue;
        }

        // Add item to the total price
        double itemTotalPrice = quantity * stock[productID - 1].price;
        totalPrice += itemTotalPrice;

        // Add item details to purchased items
        char itemDetails[200];
        sprintf(itemDetails, "%s x%d (%.2lf), ", stock[productID - 1].name, quantity, itemTotalPrice);
        strcat(purchasedItems, itemDetails);

        printf("\nCurrent Total Price: %.2lf\n", totalPrice);
        printf("Purchased Items So Far: %s\n\n", purchasedItems);

        // Ask if the user wants to add more items or proceed to payment
        printf("[1] Proceed to Payment\n[2] Add more items\n\n");
        printf("Please make your choice: ");
        int action;
        scanf("%d", &action);

        if (action == 1) {
            break;
        } else if (action != 2) {
            printf("Invalid choice! Returning to menu.\n\n");
            return;
        }
    }

    // Ask user if they want to apply a coupon
    printf("\n====================\n");
    printf("[1] Apply a Coupon\n[2] Skip Coupon\n\n");
    printf("Please make your choice: ");
    scanf("%d", &couponOption);

    double discountAmount = 0.0;
    if (couponOption == 1) {
        printf("Enter coupon code: ");
        scanf("%s", couponCode);

        if (validateCoupon(couponCode, &discount)) {
            discountAmount = (totalPrice * discount / 100);
            totalPrice -= discountAmount;

            printf("\n=====================\n");
            printf("Coupon Applied!\n");
            printf("Discount: %.2lf\n", discountAmount);
            printf("Final Total Price: %.2lf\n", totalPrice);
            printf("=====================\n\n");
        } else {
            printf("\nInvalid or Expired Coupon!\n\n");
            return;
            
        }
    }

    // Confirm payment
    printf("Confirm payment? [1] Yes / [2] No: ");
    int confirm;
    scanf("%d", &confirm);
    if (confirm == 1) {
        // Deduct stock quantity and save updated stock to file
        for (int i = 0; i < amount; i++) {
            if (strstr(purchasedItems, stock[i].name)) {
                stock[i].quantity -= quantity;
            }
        }

        savefile();

        // Save purchase history
        savePurchaseHistory(purchasedItems, totalPrice, discountAmount);

        // Print receipt
        printf("\n==========================\n");
        printf("Receipt\n");
        printf("==========================\n");
        printf("Purchased Items: %s\n", purchasedItems);
        printf("Subtotal: %.2lf\n", totalPrice + discountAmount);
        if (discountAmount > 0) {
            printf("Discount Applied: %.2lf\n", discountAmount);
        }
        printf("Total Price: %.2lf\n", totalPrice);
        printf("==========================\n");

        printf("\nThank you for your purchase!\n");
        exit(0); // Terminate the program
    } else {
        printf("Payment canceled. Returning to menu.\n\n");
    }
}

void mainmenu();

void customerPage()
{
    int choice;
    while (1)
    {
        system("cls");
        printf("=====================\n");
        printf("Customer Page\n");
        printf("================////\n\n");
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
            manageCart();
            break;
        case 3:
            system("cls");
            mainmenu();
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
}

void mainmenu()
{

    printmainmenu();
    int a;

    while (1)
    {

        scanf("%d", &a);

        switch (a)
        {
        case 1: // customer screen
            customerPage();
            break;
        case 2: // owner screen
            ownerscreen();
            printmainmenu();
            break;
        case 3: // exit
            printf("=====================\n");
            printf("Exiting program!\n");
            printf("================////\n");
            exit(0);
            break;
        default:
            printf("Please make invalid choice!\n");
            printf("Please make your choice: ");
        }
    }
}

int main(void)
{

    readfile();
    readCoupons();
    mainmenu();
}