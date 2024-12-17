#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#define ARRAYVALUE 1000

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
} stock[ARRAYVALUE];

struct coupon
{
    char code[100];
    double discount; // Discount percentage
    char expiry[11]; // Expiry date in YYYY-MM-DD format
} coupons[100];

int cart[ARRAYVALUE];
int cartamount[ARRAYVALUE];
int icart=0;

char temp[ARRAYVALUE];
int tempy[ARRAYVALUE];

time_t now;
int amount,i;

double totalIncome = 0.0;
char logDetails[256]; // Allocate enough space for the formatted string

// Function to log actions to a file
void writeLog(const char *action, const char *details) {
    FILE *logFile = fopen("log.txt", "a");
    if (logFile == NULL) {
        printf("Error: Could not open log file.\n");
        return;
    }

    // Get the current time
    time_t now = time(NULL);
    struct tm *localTime = localtime(&now);

    // Write the log entry to the file
    fprintf(logFile, "[%04d-%02d-%02d %02d:%02d:%02d] %s: %s\n",
            localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday,
            localTime->tm_hour, localTime->tm_min, localTime->tm_sec,
            action, details);

    // Close the file
    fclose(logFile);

    // Provide feedback to the user that the log has been written
    printf("Log entry written successfully: [%04d-%02d-%02d %02d:%02d:%02d] %s: %s\n",
            localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday,
            localTime->tm_hour, localTime->tm_min, localTime->tm_sec,
            action, details);
}

// Save purchase history and log purchases
void savePurchaseHistory(const char *purchasedItems, double totalPrice, double discountAmount) {
    FILE *historyFile = fopen("purchase_history.csv", "a");
    if (historyFile == NULL) {
        printf("Error opening purchase history file.\n");
        return;
    }

    fprintf(historyFile, "\"%s\",%.2lf,%.2lf\n", purchasedItems, totalPrice, discountAmount);
    fclose(historyFile);

    // Log the purchase
    char logDetails[500];
    sprintf(logDetails, "Items: %s", purchasedItems);
    writeLog("Customer Purchase", logDetails);

    // Update total income
    totalIncome += totalPrice;
}

// View report system
void viewReport() {
    system("cls");
    printf("========== View Report ==========\n");

    FILE *historyFile = fopen("purchase_history.csv", "r");
    if (historyFile == NULL) {
        printf("No purchase history found.\n");
        writeLog("Report Error", "No purchase history available");
        return;
    }

    char buffer[500];
    char items[1000];
    double totalPrice, discountAmount;
    double totalSales = 0.0, averageSales = 0.0;
    int transactionCount = 0;
    int productSales[ARRAYVALUE] = {0}; // To track quantity sold per product

    while (fgets(buffer, sizeof(buffer), historyFile)) {
        if (sscanf(buffer, "\"%[^\"]\",%lf,%lf", items, &totalPrice, &discountAmount) == 3) {
            totalSales += totalPrice;
            transactionCount++;

            // Parse items and update product sales
            char *token = strtok(items, ",");
            while (token != NULL) {
                for (int i = 0; i < amount; i++) {
                    if (strstr(token, stock[i].name)) {
                        int qty = 0;
                        sscanf(token, "%*s x%d", &qty);
                        productSales[i] += qty;
                        break;
                    }
                }
                token = strtok(NULL, ",");
            }
        }
    }

    fclose(historyFile);

    // Find the most sold product
    int maxSoldIndex = 0;
    for (int i = 1; i < amount; i++) {
        if (productSales[i] > productSales[maxSoldIndex]) {
            maxSoldIndex = i;
        }
    }

    // Calculate average sales
    if (transactionCount > 0) {
    averageSales = totalSales / transactionCount;
    } else {
    averageSales = 0;
    }

    // Display Report
    printf("\n--- Daily Summary ---\n");
    printf("Total Sales: %.2lf\n", totalSales);
    printf("Total Transactions: %d\n", transactionCount);
    printf("Average Transaction Value: %.2lf\n", averageSales);

    printf("\n--- Most Sold Product ---\n");
    printf("Product: %s, Quantity Sold: %d\n", stock[maxSoldIndex].name, productSales[maxSoldIndex]);

    // Log report generation
    writeLog("Report", "Daily Summary");

    // Prompt user to exit
    printf("\nPress [0] to return: ");
    int returnChoice;
    scanf("%d", &returnChoice);
    if (returnChoice == 0) {
        return; // Exit the function
    }
}

void arranger(int amount,int array[],int array2[]){
    int a;
    for(a=0;a<amount;++a) if(a == 0) break;
    for(i=a;i<amount;++i){
        array[i]=array[i+1];
        array2[i]=array2[i+1];
    }
    array[i]='\0';
    array2[i]='\0';
}

int maxvalue(int amount ,int array[]){
    int max=array[0];
    for(int i=0;i<amount;++i){
        if(max<array[i]) max = array[i];
    }
    return max;
}

int universalscanf(int max){
    int choice=0;
    if(max==0) max = 999;
    scanf(" %[^\n]",temp);
    for(int i=0;i<strlen(temp);++i) choice = (choice*pow(10,i))+(temp[i]-'0');
    if(choice>=0 && choice<=max) return choice;
    else{
        printf("Choose valid!");
        universalscanf(max);
    }
}

void clearcart(){
    for(int i=0;i<icart;++i){
        cart[i]='\0';
        cartamount[i]='\0';
    }
    icart=0;
}

void printheader()
{
    printf("%-4s %-4s %-18s %-11s %-10s %-70s %-10s %-5s\n",
           "Class", "ID", "Name", "Quantity", "Price", "Description", "Threshold", "Max");
}

void bubblesort(int amount_of_items, int array[], int array2[]) {
    for (int i = 0; i < amount_of_items - 1; i++) {
        for (int j = 0; j < amount_of_items - i - 1; j++) {
            if (array[j] > array[j + 1]) {
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

void printcheader(){
    printf("%-4s %-18s %-11s %-10s %-70s\n",
            "ID", "Name", "Quantity", "Price", "Description");
}

void printctable(){
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
    stockfile = fopen("stock.csv", "w");

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
    printf("[1] Confirm\n");
    printf("[2] Cancel\n");
    printf("Please make your choice: ");

    while (1)
    {
        scanf("%d", &a);

        switch (a)
        {
        case 1: // confirm
        savefile();
            // Log the new stock details
            {
                char logDetails[512];
                sprintf(logDetails, "New stock added - ID: %d, Name: '%s', Class: '%c', Max: %d, Quantity: %d, Price: %.2lf, Threshold: %.2lf",
                        stock[amount].id, stock[amount].name, stock[amount].class, stock[amount].max,
                        stock[amount].quantity, stock[amount].price, stock[amount].threshold);
                writeLog("Report", logDetails);
            }

            ++amount;
            return; // Return after adding stock
            break;

        case 2: // cancel
            return; // Return without adding stock
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
            // Format the log message for product deletion
            char logDetails[256];
            sprintf(logDetails, "Product ID %d named '%s' is being deleted", stock[delete - 1].id, stock[delete - 1].name);
            writeLog("Report", logDetails);

            printf("[1] Confirm\n");
            printf("[2] Cancel\n");
            printf("Please make your choice: ");

            while (1)
            {
                scanf("%d", &a);

                switch (a)
                {
                case 1: // confirm
                    // Log the deletion before shifting
                    for (int i = delete - 1; i < amount - 1; ++i)
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
                    deleteproduct();  // Recursively call to allow for continuous deletion
                    savefile();
                    return;
                    break;

                case 2: // cancel
                    deleteproduct();  // Recursively call to go back to the delete menu
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
            {   savefile();
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
                            // Format the log message
                            char logDetails[256];
                            sprintf(logDetails, "Class for product ID %d changed from '%c' to '%c'", stock[edit].id, stock[edit].class, chrtemp);
                            writeLog("Report", logDetails);
                            break;

                        case 2:
                            printf("New name: ");
                            scanf(" %[^\n]", &strtemp);
                            // Format the log message
                            sprintf(logDetails, "Name for product ID %d changed from '%s' to '%s'", stock[edit].id, stock[edit].name, strtemp);
                            writeLog("Report", logDetails);
                            break;

                        case 3:
                            printf("New quantity: ");
                            scanf("%d", &inttemp);
                            // Format the log message
                            sprintf(logDetails, "Quantity for product ID %d changed from %d to %d", stock[edit].id, stock[edit].quantity, inttemp);
                            writeLog("Report", logDetails);
                            break;

                        case 4:
                            printf("New price: ");
                            scanf("%lf", &fltemp);
                            // Format the log message
                            sprintf(logDetails, "Price for product ID %d changed from %.2lf to %.2lf", stock[edit].id, stock[edit].price, fltemp);
                            writeLog("Report", logDetails);
                            break;

                        case 5:
                            printf("New description: ");
                            scanf("%s", &strtemp);
                            // Format the log message
                            sprintf(logDetails, "Description for product ID %d changed from '%s' to '%s'", stock[edit].id, stock[edit].description, strtemp);
                            writeLog("Report", logDetails);
                            break;

                        case 6:
                            printf("New threshold: ");
                            scanf("%lf", &fltemp);
                            // Format the log message
                            sprintf(logDetails, "Threshold for product ID %d changed from %.2lf to %.2lf", stock[edit].id, stock[edit].threshold, fltemp);
                            writeLog("Report", logDetails);
                            break;

                        case 7:
                            printf("New max: ");
                            scanf("%d", &inttemp);
                            // Format the log message
                            sprintf(logDetails, "Max for product ID %d changed from %d to %d", stock[edit].id, stock[edit].max, inttemp);
                            writeLog("Report", logDetails);
                            break;

                        case 8:
                        savefile();
                            editproduct();
                            return;
                            break;

                        default:
                            break;
                        }
                        break;
                    }
                }

                printf("[1] Confirm\n");
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

void checkLowStockAndRestock() {
    system("cls");
    printf("===== Low Stock Notification =====\n");
    int lowStockFound = 0;

    // Check each product's stock using threshold percentage
    for (int i = 0; i < amount; ++i) {
        double calculatedThreshold = (stock[i].threshold / 100.0) * stock[i].max; // Calculate threshold dynamically

        if (stock[i].quantity < calculatedThreshold) {
            printf("⚠️ Product ID: %d | Name: %s | Quantity: %d | Threshold: %.0lf (%.2lf%% of Max: %d)\n",
                   stock[i].id, stock[i].name, stock[i].quantity, calculatedThreshold,
                   stock[i].threshold, stock[i].max);
            lowStockFound = 1;
        }
    }

    if (!lowStockFound) {
        printf("✅ All products have sufficient stock.\n");
        sleep(2);
        return;
    }

    // Prompt to restock
    int choice, quantityToAdd;
    printf("\nDo you want to restock products? [1] Yes / [2] No: ");
    scanf("%d", &choice);

    if (choice == 1) {
        while (1) {
            printf("\nEnter the Product ID to restock (0 to exit): ");
            scanf("%d", &choice);
            if (choice == 0) break;

            if (choice > 0 && choice <= amount) {
                printf("Current Quantity: %d | Max: %d\n", stock[choice - 1].quantity, stock[choice - 1].max);
                printf("Enter quantity to add: ");
                scanf("%d", &quantityToAdd);

                if (quantityToAdd > 0) {
                    stock[choice - 1].quantity += quantityToAdd;
                    printf("✅ Stock updated successfully!\n");
                    savefile();
                    writeLog("Stock Restock", stock[choice - 1].name);
                } else {
                    printf("❌ Invalid quantity entered!\n");
                }
            } else {
                printf("❌ Invalid Product ID!\n");
            }
        }
    }
}

void manageCoupons() {
    srand(time(NULL));
    const char *filename = "coupons.csv";
    FILE *file, *tempFile;
    int choice;

    do {
        // Clear screen for a fresh view
        system("cls");

        // Display the list of coupons at the top of the menu
        printf("\n============== List of Coupons ==============\n");
        file = fopen(filename, "r");
        if (file == NULL) {
            printf("No coupons found or file could not be opened.\n\n");
        } else {
            char buffer[255];
            int hasValidCoupons = 0;
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);

            printf("%-10s %-15s %-15s\n", "Code", "Discount(%)", "Expiration");
            printf("------------------------------------------\n");

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

                printf("%-10s %-15.2f %-15s\n", code, discountPercentage, expirationDate);
                hasValidCoupons = 1;
            }
            fclose(file);

            if (!hasValidCoupons) {
                printf("No valid coupons available.\n\n");
            }
        }

        // Display menu options
        printf("\n--- Coupon Management ---\n");
        printf("[1] Create Coupon\n");
        printf("[2] Delete Coupon\n");
        printf("[3] Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char code[5], finalCode[10], expirationDate[11], buffer[255];
                float discountPercentage;
                int isDuplicate = 0;

                // Generate random coupon code
                const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
                for (int i = 0; i < 4; i++) {
                    code[i] = charset[rand() % (sizeof(charset) - 1)];
                }
                code[4] = '\0';
                snprintf(finalCode, sizeof(finalCode), "CPE-%s", code);

                printf("\nGenerated Coupon Code: %s\n", finalCode);

                // Check for duplicates in the file
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

                // Get user input for discount and expiration date
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

                // Append new coupon to the file
                file = fopen(filename, "a");
                if (file == NULL) {
                    printf("Error: Could not open file.\n");
                    break;
                }
                fprintf(file, "%s,%.2f,%s\n", finalCode, discountPercentage, expirationDate);
                fclose(file);
                sprintf(logDetails, "Coupon %s added", finalCode); // Format the string with finalCode
                writeLog("Report", logDetails); // Pass the formatted string to writeLog
                printf("Coupon added successfully!\n");
                break;
            }
            case 2: {
                char codeToDelete[50], buffer[255];
                printf("\nEnter Coupon Code to Delete: ");
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
                    sprintf(logDetails, "Coupon %s deleted", codeToDelete); // Format the string
                    writeLog("Report", logDetails); // Pass the formatted string
                    printf("Coupon '%s' deleted successfully!\n", codeToDelete);
                } else {
                    remove("temp.csv");
                    printf("Coupon '%s' not found.\n", codeToDelete);
                }
                break;
            }
            case 3:
                printf("Exiting Coupon Management.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

        if (choice != 3) {
            // Wait for user to press 0 to continue
            int waitChoice = -1;
            while (waitChoice != 0) {
                printf("\nPress [0] to continue: ");
                scanf("%d", &waitChoice);
            }
        }

    } while (choice != 3);
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
    printf("[5] Check Low Stock & Restock\n");
    printf("[6] Return to menu\n\n");
    printf("Please make your choice: ");
}

void ownerscreen() {
    printownerscreen();
    int a;

    while (1) {
        // Clear any remaining characters in the input buffer before reading input
        while (getchar() != '\n'); 

        scanf("%d", &a);
        switch (a) {
            case 1: // manage stock
                stockpage();
                printownerscreen();
                break;
            case 2: // manage coupon
                manageCoupons();
                printownerscreen();
                break;
            case 3: // view report
                viewReport();
                printownerscreen();
                break;
            case 4: // logging
                system("cls");
                printf("========== View Logs ==========\n");
                FILE *logFile = fopen("log.txt", "r");
                if (logFile == NULL) {
                    printf("No logs found.\n");
                } else {
                    char logLine[500];
                    while (fgets(logLine, sizeof(logLine), logFile)) {
                        printf("%s", logLine);
                    }
                    fclose(logFile);
                }
                printf("\nPress [0] to return: ");
                int returnChoice;
                while (returnChoice != 0) {
                    scanf("%d", &returnChoice);
                }
                printownerscreen();
                break;
            case 5: // Check Low Stock & Restock
                checkLowStockAndRestock();
                printownerscreen();
                break;
            case 6: // return menu
                system("cls");
                return;
            default:
                printf("Please make a valid choice!\n");
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

void printcart(){
    double total=0;
    if(icart==0) return;
    bubblesort(icart,cart,cartamount);
    printcheader();
    for (int i = 0; i < icart; ++i){
        printf("%-5d %-20s %-10d %-10.2lf %-70s\n",
               stock[cart[i]].id, stock[cart[i]].name, cartamount[i], stock[cart[i]].price, stock[cart[i]].description);

        total+=(stock[cart[i]].price*cartamount[i]);
    }  
    printf("\n");
    printf("Total price: %.2lf",total);
    printf("\n\n");
}

void buylater()
{
    int choice,quantity,count=0;
    while (1)
    {
        system("cls");
        printf("=====================\n");
        printf("Cart\n");
        printf("================////\n\n");
        printcart();
        printf("Make your choice:\n");
        printf("[1] Add cart\n");
        printf("[2] Edit cart\n");
        printf("[3] Buy Later\n");
        printf("[4] Exit\n\n");
        printf("Please make your choice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            while(1){
                //system("cls");
                printctable();
                printf("=====================\n");
                printf("Add cart\n");
                printf("================////\n\n");
                printcart();
                
                printf("Make your choice:\n");
                printf("Exit[0]: ");
                printf("Please make your choice[1-%d]: ",amount);
                choice = universalscanf(amount);
                if(choice==0) break;
                --choice;
                printf("Quantity[1-%d]: ",stock[choice].quantity);
                quantity = universalscanf(stock[choice].quantity);
                
                while(1){
                    if(quantity>=1 && quantity<= stock[choice].quantity) break;
                    else{
                        printf("Choose valid!");
                        scanf("%d", &quantity);
                    }
                }
                count=0;
                for(int i=0;i<=icart;++i){
                    if(choice==cart[i]){
                        cartamount[i]+=quantity;
                        ++count;
                    }
                }
                if(count==0){
                    cart[icart]=choice;
                    cartamount[icart]=quantity;
                }

                for(int i=0;i<=icart;++i){
                    printf("\n%d===%d %d===\n",icart,cart[i],cartamount[i]);
                }
                ++icart;
            }

        } 
        else if (choice == 2) {
            if(icart==0){
                printf("=====================\n");
                printf("Edit cart\n");
                printf("================////\n\n");
                printf("No cart to edit!\n");
                printf("[∞]Press any to exit: ");
                universalscanf(0);
                return;
            }
            else{
                 while(1){
                //system("cls");
                printctable();
                printf("=====================\n");
                printf("Edit cart\n");
                printf("================////\n\n");
                printcart();
                
                printf("Make your choice:\n");
                printf("Exit[0]: \n");
                printf("Please make your choice[ID]: ");
                printf("Reset cart[%d]: ",maxvalue(icart,cart)+2);

                int max=maxvalue(icart,cart);
                int count =0;
                int search;
                while(1){
                    choice = universalscanf(max+1);
                    if(choice==0) break;
                    for(search=0;search<icart;++search){
                        if(choice -1 == cart[search]){
                            ++count;
                            break;
                        }
                    }
                    if(count!=0) break;
                    else printf("choose valid");
                }
                if(choice==0) break;

                printcheader();
                printf("%-5d %-20s %-10d %-10.2lf %-70s\n",
                    stock[cart[search]].id, stock[cart[search]].name, cartamount[search], stock[cart[search]].price, stock[cart[search]].description);

                printf("Quantity[1-%d]: ",stock[choice].quantity);
                cartamount[search] = universalscanf(cartamount[search]+1);
                
                if(cartamount[search]==0){
                    arranger(icart,cart,cartamount);
                    --icart;
                }
                }
            }
            


        } 
        else if (choice == 3) {
            printf("Exiting cart management...\n");
            return;
        } 
        else {
            printf("Invalid choice! Please try again.\n");
        }

    }
}

int couponCount = 0; // Tracks the number of coupons loaded

void readCoupons()
{
    FILE *couponFile = fopen("coupons.csv", "r");
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

int validateCoupon(const char *couponCode, double *discount) {
    FILE *couponFile = fopen("coupons.csv", "r");
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

void buyNow() {
    int productID, quantity, couponOption;
    double totalPrice = 0.0, discount = 0.0, discountAmount = 0.0;
    char purchasedItems[1000] = "", couponCode[100];

    system("cls");
    printf("====================\n");
    printf("Buy Now\n");
    printf("====================\n\n");

    while (1) {
        // Display the product list for customers
        printctable();

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
        printf("[1] Proceed to Payment\n[2] Add More Items\n[3] Cancel and Return to Customer Page\n\n");
        printf("Please make your choice: ");
        int action;
        scanf("%d", &action);

        if (action == 1) {
            break;
        } else if (action == 3) {
            printf("Returning to Customer Page...\n");
            sleep(2); // Delay before returning
            return;
        } else if (action != 2) {
            printf("Invalid choice! Returning to menu.\n\n");
            sleep(2); // Delay before returning
            return;
        }
    }

    while (1) { // Loop for coupon validation
        // Ask user if they want to apply a coupon
        printf("\n====================\n");
        printf("[1] Apply a Coupon\n[2] Skip Coupon\n\n");
        printf("Please make your choice: ");
        scanf("%d", &couponOption);

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
                break;
            } else {
                printf("\nInvalid or Expired Coupon! Please try again or choose to skip.\n\n");
            }
        } else if (couponOption == 2) {
            break;
        } else {
            printf("Invalid choice! Please try again.\n\n");
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
        int returnToMenu;
        do {
            printf("Press [0] to return to Customer Page: ");
            scanf("%d", &returnToMenu);
        } while (returnToMenu != 0);

        return;
    } else {
        printf("Payment canceled. Returning to menu.\n\n");
        sleep(2); // Delay before returning
        return;
    }
}

void mainmenu();

void customerPage()
{
    int choice;
    while (1)
    {
        system("cls");
        printf("\n=====================\n");
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
            buylater();
            break;
        case 3:
            system("cls");
            mainmenu();
            return;
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
    clearcart();
    readfile();
    readCoupons();

    mainmenu();
}