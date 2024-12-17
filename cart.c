#include "cart.h"

// Global cart definitions
int cart[CART_ARRAY_SIZE];
int cartamount[CART_ARRAY_SIZE];
int icart = 0;

// Clear cart function
void clearcart()
{
    for (int i = 0; i < icart; ++i)
    {
        cart[i] = '\0';
        cartamount[i] = '\0';
    }
    icart = 0;
}
