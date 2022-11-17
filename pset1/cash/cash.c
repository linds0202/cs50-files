#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //get amount of change from user
    float change;
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);
    
    //change input to cents
    int cents = round(change * 100);
    
    //calculate coins
    int numcoins = 0;
    
    //quarters
    while (cents >= 25)
    {
        cents -= 25;
        numcoins += 1;
    }
    
    //dimes
    while (cents >= 10)
    {
        cents -= 10;
        numcoins++;
    }
    
    //nickels
    while (cents >= 5)
    {
        cents -= 5;
        numcoins++;
    }
    
    //pennies
    while (cents >= 1)
    {
        cents -= 1;
        numcoins++;
    }
    
    printf("%i\n", numcoins);
}