#ifndef ACCOUNT_H
#define ACCOUNT_H

#define USERNAME_LEN 1000
#define PASSWORD_LEN 1000

// Account structure
typedef struct account
{
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} Account;

// Global account variable
extern Account account[1];

#endif // ACCOUNT_H