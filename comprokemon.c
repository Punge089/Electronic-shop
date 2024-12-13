#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct account{
    char username[1000];
    char password[1000];
}account[1];

struct stock{
    char class;
    int id;
    char name[1000];
    int quantity;
    double price;
    char description[1000];
    double threshold;
    int max;
}stock[1000];

struct coupon {
    char code[100];
    double discount; // Discount percentage
    char expiry[11]; // Expiry date in YYYY-MM-DD format
}coupons[100];

char temp[1000];

int amount;

void printheader(){
    printf("%-4s %-4s %-18s %-11s %-10s %-70s %-10s %-5s\n", 
           "Class","ID", "Name", "Quantity", "Price", "Description", "Threshold", "Max");
}

void printtable(){
    printheader();
    for(int i=0;i<amount;++i) printf("%-5c %-5d %-20s %-10d %-10.2lf %-70s %-10.2lf %-5d\n", 
            stock[i].class,stock[i].id, stock[i].name, stock[i].quantity,stock[i].price, stock[i].description, stock[i].threshold,stock[i].max);
    printf("\n\n");
}

void readfile(){
    
    FILE *stockfile;
    stockfile = fopen("C:\\Users\\User\\OneDrive\\Desktop\\stock.csv","r");

    if(stockfile == NULL){
        printf("Cannot open stock file bro!");
        exit(1);
    }
    
    fscanf(stockfile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,\n]",temp,temp,temp,temp,temp,temp,temp,temp);

    int i=0;

    while(!feof(stockfile)){
        fscanf(stockfile, " %c,%d, %[^,],%d,%lf, %[^,],%lf,%d", 
            &stock[i].class,&stock[i].id, stock[i].name,&stock[i].quantity, &stock[i].price, stock[i].description, &stock[i].threshold,&stock[i].max);
        ++i;
    }
    amount = i-1;
    fclose(stockfile);
    return;
}

void savefile(){
    FILE *stockfile;
    stockfile = fopen("C:\\Users\\User\\OneDrive\\Desktop\\stocksave.csv","w");

    fprintf(stockfile,"Class,ID,Name,Quantity,Price,Description,Threshold,Max\n");
    
    for(int i=0;i<amount;++i) fprintf(stockfile,"%c,%d,%s,%d,%.2lf,%s,%.2lf,%d\n", 
        stock[i].class,stock[i].id, stock[i].name, stock[i].quantity,stock[i].price, stock[i].description, stock[i].threshold,stock[i].max);

    fclose(stockfile);
}

void readcouponfile(){
    FILE *couponfile;
    couponfile = fopen("C:\\Users\\User\\OneDrive\\Desktop\\coupon.csv","r");

    if(couponfile == NULL){
        printf("Cannot open coupon file bro!");
        exit(1);
    }
    
    fscanf(couponfile, "%[^,],%[^,],[^,\n]",temp,temp,temp);

    int i=0;

    while(!feof(stockfile)){
        fscanf(stockfile, " %c,%d, %[^,],%d,%lf, %[^,],%lf,%d", 
            &stock[i].class,&stock[i].id, stock[i].name,&stock[i].quantity, &stock[i].price, stock[i].description, &stock[i].threshold,&stock[i].max);
        ++i;
    }
    fclose(couponfile);
    return;
}

void ownersearch(){
    system("cls");
    printtable();


    int a;

        while(1){

            printf("=====================\n");
            printf("Search\n");
            printf("================////\n\n");
            printf("Make your choice:\n");
            printf("[1] Name\n");
            printf("[2] Category\n");
            printf("[3] Price range\n");
            printf("[4] Exit\n\n");
            printf("Please make your choice: ");

            scanf("%d",&a);

int count,j,k,z;
char tempchr;

        if(a==1){
            printf("Search name: ");
            scanf("%s",temp);
            system("cls");
            printheader();
            count = 0;
            for(int i=0;i<amount;++i){

                if(strlen(temp)<=strlen(stock[i].name)){
                    for(j=0;j<(strlen(stock[i].name)-strlen(temp)+1);++j){
                        for(k=j,z=0;k<(strlen(temp)+j);++k,++z){
                            if((temp[z] != stock[i].name[k]) && (temp[z] != (stock[i].name[k]+'A'-'a')) && (temp[z] != (stock[i].name[k]+'a'-'A'))){
                                break;
                            }
                        }

                        if(z==strlen(temp)){
                            printf("%-5c %-5d %-20s %-10d %-10.2lf %-70s %-10.2lf %-5d\n", 
                            stock[i].class,stock[i].id, stock[i].name, stock[i].quantity,stock[i].price, stock[i].description, stock[i].threshold,stock[i].max);
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
            if(count == 0){
                system("cls");
                for(int i=0;i<5;++i){
                    printf("No item found! "); 
                }
                printf("No item found!\n\n");
            }
        }
        else if(a==2){
            printf("Make your choice:\n");
            printf("[1] Phone\n");
            printf("[2] Gadgets\n");
            printf("[3] est\n");
            printf("[4] Exit\n\n");
            printf("Please make your choice: ");
            while(1){

            scanf("%d",&a);

            if(a==1){
              tempchr = 'A';
              break;  
            } 
            else if(a==2){
              tempchr = 'A';  
              break;  
            }
            else if(a==3){
              tempchr = 'A';
              break;  
            }
            else if(a==4) return;  
            else{
                printf("Please make invalid choice!\n");
                printf("Please make your choice: ");
            }
            }
            count = 0;
            for(int i=0;i<amount;++i){
                if(stock[i].class==tempchr) ++count;
            }
            if(count == 0){
                system("cls");
                printf("No item found!\n\n");
            
            }
            else{
                printheader();
                for(int i=0;i<amount;++i){
                    if(stock[i].class==tempchr)printf("%-5c %-5d %-20s %-10d %-10.2lf %-70s %-10.2lf %-5d\n", 
                stock[i].class,stock[i].id, stock[i].name, stock[i].quantity,stock[i].price, stock[i].description, stock[i].threshold,stock[i].max);
                }
                printf("\n\n");
            }
            
        }
        else if(a==3){
            double startprice,endprice;
            printf("Start price: ");
            scanf("%lf",&startprice);
            printf("End price: ");
            scanf("%lf",&endprice);

            system("cls");
            printheader();
            count = 0;
            for(int i=0;i<amount;++i){
                if(stock[i].price>=startprice && stock[i].price<=endprice){
                    printf("%-5c %-5d %-20s %-10d %-10.2lf %-70s %-10.2lf %-5d\n", 
                    stock[i].class,stock[i].id, stock[i].name, stock[i].quantity,stock[i].price, stock[i].description, stock[i].threshold,stock[i].max);
                    ++count;
                    continue;
                }
            }
            printf("\n");
            if(count == 0){
                system("cls");
                for(int i=0;i<5;++i){
                    printf("No item found! "); 
                }
                printf("No item found!\n\n");
            }

        }
        else if(a==4) return;
        else{
            printf("Please make invalid choice!\n");
            printf("Please make your choice: ");
            }
    }
}

void addstock() {

    printf("=====================\n");
    printf("Add stock\n");
    printf("================////\n\n");

    printf("Class(M,H,S,P) :");
    scanf(" %c",&stock[amount].class);

    while(1){
        if(stock[amount].class != 'A'){
            printf("Please make invalid choice!\n");
            printf("Please make your choice:");
            scanf(" %c",&stock[amount].class);
        }
        else break;
    }

    stock[amount].id = amount+1;

    printf("Name :");
    scanf("%s",stock[amount].name);

    printf("Max :");
    scanf("%d",&stock[amount].max);

    printf("Quantity :");
    scanf("%d",&stock[amount].quantity);

    printf("Price :");
    scanf("%lf",&stock[amount].price);

    printf("Description :");
    scanf(" %[^\n]",stock[amount].description);

    printf("Threshold :");
    scanf("%lf",&stock[amount].threshold);

    int a;
    printf("[1] Comfirm\n");
    printf("[2] Cancel\n");
    printf("Please make your choice: ");

    while(1){
            scanf("%d",&a);

            switch (a) {
            case 1: //confirm
                ++amount;
                //addstock();
                return;
                break;
            case 2: //cancel
                //addstock();
                return;
                break;
            default:
                printf("Please make invalid choice!\n");
                printf("Please make your choice: ");
            }
        }
    }

void printstockpage() {
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

void deleteproduct(){
    system("cls");
    printf("=====================\n");
    printf("Delete product\n");
    printf("================////\n\n");
    printtable();

    int delete,a;

    printf("\n\n");
    printf("Make your choice: \n");
    printf("[1-%d] Remove product\n",amount);
    printf("[0] Return menu\n");

    while (1){
        printf("Please make your choice: ");
        scanf("%d",&delete);

        if(delete == 0){
            return;
        }
        else if(delete > 0 && delete <= amount){

            printf("[1] Comfirm\n");
            printf("[2] Cancel\n");
            printf("Please make your choice: ");

            while(1){
                scanf("%d",&a);

                switch (a) {
                case 1: //confirm
                    for(int i = delete-1 ;i < amount ;++i){
                        stock[i].class = stock[i+1].class; 
                        stock[i].id = i+1;
                        strcpy(stock[i].name, stock[i+1].name);
                        stock[i].quantity = stock[i+1].quantity;
                        stock[i].price = stock[i+1].price;
                        strcpy(stock[i].description, stock[i+1].description);
                        stock[i].threshold = stock[i+1].threshold;
                        stock[i].max = stock[i+1].max;
                    }                
                    --amount;
                    deleteproduct();
                    return;
                    break;
                case 2: //cancel
                    deleteproduct();
                    return;
                    break;
                default:
                    printf("Please make invalid choice!\n");
                    printf("Please make your choice: ");
                }
            }
        }
        else{
            printf("Please make invalid choice!\n");
        }
    }
    
}

void printeditproduct(){
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

void editproduct(){
    system("cls");
    printf("=====================\n");
    printf("Edit product\n");
    printf("================////\n\n");
    printtable();

    int edit,a,b,inttemp;

    char strtemp[1000],chrtemp;

    double fltemp;

    printf("\n\n");
    printf("Make your choice: \n");
    printf("[1-%d] Edit product\n",amount);
    printf("[0] Return menu\n");

    while (1){
        printf("Please make your choice: ");
        scanf("%d",&edit);

        if(edit == 0){
            return;
        }
        else if(edit > 0 && edit <= amount){

            --edit;

            while(1){

            system("cls");
            printf("=====================\n");
            printheader();

            printf("%-5c %-5d %-20s %-10d %-10.2lf %-70s %-10.2lf %-5d\n", 
            stock[edit].class,stock[edit].id, stock[edit].name, stock[edit].quantity,stock[edit].price, stock[edit].description, stock[edit].threshold,stock[edit].max);
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
            
                while(1){
                    printf("Please make your choice:");
                    scanf("%d",&a);
                    if(a > 8 || a < 1){
                        printf("Please make invalid choice!\n");
                        printf("Please make your choice:");
                    }
                    else{
                        switch(a) {
                        case 1: 
                            printf("New class: ");
                            scanf(" %c",&chrtemp);
                            while(1){
                                if(chrtemp != 'A'){
                                    printf("Please make invalid choice!\n");
                                    printf("Please make your choice:");
                                    scanf(" %c",&chrtemp);
                                }
                                else break;
                            }
                            break;
                        case 2: 
                            printf("New name: ");
                            scanf(" %[^\n]",&strtemp);
                            break;
                        case 3: 
                            printf("New quantity: ");
                            scanf("%d",&inttemp);
                            break;
                        case 4: 
                            printf("New price: ");
                            scanf("%lf",&fltemp);
                            break;
                        case 5: 
                            printf("New description: ");
                            scanf("%s",&strtemp);
                            break;
                        case 6: 
                            printf("New threshold: ");
                            scanf("%lf",&fltemp);
                            break;
                        case 7: 
                            printf("New max: ");
                            scanf("%d",&inttemp);
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

                while(1){
                        scanf("%d",&b);
                        if(b==1){
                            switch(a) {
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
                        else if(b==0) break;
                        else{
                            printf("Please make invalid choice!\n");
                            printf("Please make your choice: ");
                        }
                    }
                }
        }
        else{
            printf("Please make invalid choice!\n");
        }
    }
}

void stockpage() {

        printstockpage();
        int a;

        while(1){

            scanf("%d",&a);

            switch (a) {
            case 1: //create product

                addstock();
                savefile();
                printstockpage();
                break;
            case 2: //edit
                editproduct();
                printstockpage();
                break;
            case 3: //delete
                deleteproduct();
                savefile();
                printstockpage();
                break;
            case 4: //search
                ownersearch();
                printstockpage();
                break;
            case 5: //return menu
                return;
                break;
            default:
                printf("Please make invalid choice!\n");
                printf("Please make your choice: ");
            }
        }

    }

void printownerscreen(){
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

void ownerscreen() {

    printownerscreen();

        int a;

        while(1){

            scanf("%d",&a);

            switch (a) {
            case 1: //manage stock
                stockpage();
                printownerscreen();
                break;
            case 2: //manage coupon
                
                break;
            case 3: //view report
                
                break;
            case 4: //logging

                break;
            case 5: //return menu
                return;
                break;
            default:
                printf("Please make invalid choice!\n");
                printf("Please make your choice: ");
            }
        }

    }

void printmainmenu(){
    //system("cls");
    printf("=====================\n");
    printf("Main menu\n");
    printf("================////\n\n");
    printf("Make your choice:\n");
    printf("[1] Customer page\n");
    printf("[2] Owner page\n");
    printf("[3] Exit\n\n");
    printf("Please make your choice: ");

}





void manageCart() {
    int choice;
    while (1) {
        system("cls");
        printf("=====================\n");
        printf("Cart\n");
        printf("================////\n\n");
        printf("Make your choice:\n[1] Buy\n[2] Choose\n[3] Exit\n\n");
        printf("Please make your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: printf("Buying process initiated...\n"); break;
            case 2: printf("Choose an item...\n"); break;
            case 3: printf("Exiting cart management...\n"); return;
            default: printf("Invalid choice! Please try again.\n");
        }
    }
}

int couponCount = 0;
int readCoupons() {
    FILE *couponFile = fopen("C:\\Users\\KEN\\Desktop\\CPE100\\online shop\\coupons.csv", "r");
    if (couponFile == NULL) {
        printf("Cannot open coupons file!\n");
        return 0;
    }

    fscanf(couponFile, "%[^,],%[^,],%[^\n]\n", temp, temp, temp); // Skip header
    int i = 0;

    while (!feof(couponFile)) {
        fscanf(couponFile, "%[^,],%lf,%[^\n]\n", 
               coupons[i].code, &coupons[i].discount, coupons[i].expiry);
        i++;
    }

    couponCount = i;
    fclose(couponFile);
    return 1;
}

int validateCoupon(char *code, double *discount) {
    time_t now = time(NULL);
    struct tm expiryDate = {0};
    char *dateFormat = "%Y-%m-%d";
    char year[5], month[3], day[3];

    for (int i = 0; i < couponCount; i++) {
        if (strcmp(code, coupons[i].code) == 0) {
            // Manually parse the expiry date from the coupon structure
            strncpy(year, coupons[i].expiry, 4);
            year[4] = '\0';
            strncpy(month, coupons[i].expiry + 5, 2);
            month[2] = '\0';
            strncpy(day, coupons[i].expiry + 8, 2);
            day[2] = '\0';

            // Populate the expiryDate struct
            expiryDate.tm_year = atoi(year) - 1900; // tm_year is years since 1900
            expiryDate.tm_mon = atoi(month) - 1;   // tm_mon is 0-based
            expiryDate.tm_mday = atoi(day);

            time_t expiryTime = mktime(&expiryDate);

            if (difftime(expiryTime, now) > 0) { // Check if coupon is valid
                *discount = coupons[i].discount;
                return 1; // Valid coupon
            } else {
                printf("Coupon has expired!\n");
                return 0; // Expired coupon
            }
        }
    }
    printf("Invalid coupon code!\n");
    return 0; // Invalid coupon
}

void buyNow() {
    int productID, quantity, action, couponOption;
    double totalPrice = 0.0, discount = 0.0;
    char purchasedItems[1000] = "", couponCode[100];

    system("cls");
    printf("=====================\n");
    printf("Buy Now\n");
    printf("================////\n\n");

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

        // Show options
        printf("\nYou selected %s, Quantity: %d, Unit Price: %.2lf\n", 
               stock[productID - 1].name, quantity, stock[productID - 1].price);
        printf("[1] Buy this item and finish\n[2] Add this item and continue\n\n");
        printf("Please make your choice: ");
        scanf("%d", &action);

        if (action == 1 || action == 2) {
            // Add item to the total price and deduct stock
            totalPrice += quantity * stock[productID - 1].price;
            stock[productID - 1].quantity -= quantity;

            // Add item details to purchased items
            char itemDetails[200];
            sprintf(itemDetails, "%s x%d (%.2lf), ", stock[productID - 1].name, quantity, stock[productID - 1].price);
            strcat(purchasedItems, itemDetails);

            // Save updated stock
            savefile();

            if (action == 1) {
                // If the user chooses to buy and finish
                printf("\n=====================\n");
                printf("[1] Buy with a Coupon\n[2] Buy without a Coupon\n\n");
                printf("Please make your choice: ");
                scanf("%d", &couponOption);

                if (couponOption == 1) {
                    // Ask for coupon code
                    printf("Enter coupon code: ");
                    scanf("%s", couponCode);

                    // Validate coupon
                    if (validateCoupon(couponCode, &discount)) {
                        totalPrice -= (totalPrice * discount / 100);
                        printf("\n=====================\n");
                        printf("Final Total Price with Coupon: %.2lf\n", totalPrice);
                        printf("Purchased Items: %s\n", purchasedItems);
                        printf("=====================\n");
                    } else {
                        printf("\nPurchase canceled due to invalid coupon.\n");
                    }
                } else if (couponOption == 2) {
                    // No coupon logic
                    printf("\n=====================\n");
                    printf("Final Total Price: %.2lf\n", totalPrice);
                    printf("Purchased Items: %s\n", purchasedItems);
                    printf("=====================\n");
                } else {
                    printf("Invalid choice! Assuming no coupon applied.\n");
                }

                printf("Thank you for your purchase!\n");
                printf("Program will terminate now.\n");
                exit(0); // Terminate the program
            } else {
                // If the user chooses to continue, display the current total
                printf("\nItem added to total. Current Total Price: %.2lf\n", totalPrice);
                printf("Purchased Items So Far: %s\n\n", purchasedItems);
                continue;
            }
        } else {
            printf("Invalid choice! Returning to selection...\n\n");
        }
    }
}
void customerPage() {
    int choice;
    while (1) {
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
        switch (choice) {
            case 1: 
                buyNow(); 
                break;
            case 2: 
                manageCart(); 
                break;
            case 3: 
                printf("Returning to Main Menu...\n");
                return;
            default: 
                printf("Invalid choice! Please try again.\n");
        }
    }
}








void mainmenu() {

    printmainmenu();
        int a;

        while(1){

            scanf("%d",&a);

            switch (a) {
            case 1: //customer screen
                customerPage();
                break;
            case 2: //owner screen
                ownerscreen();
                printmainmenu();
                break;
            case 3: //exit
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

int main(void){

    readfile();
    readcouponfile();

    mainmenu();

}
