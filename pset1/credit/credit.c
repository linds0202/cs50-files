#include <stdio.h>
#include <cs50.h>

//declare functions
int digits(long card);

int get_start_digits(int len, long cardstart);

int evens(int evendigit);

int digit_sum(int length, long number);

bool check_last(int sum);

int main(void)
{
    //get customer's card
    long cardnum = get_long("Number: ");
    
    //Find # of digits in card
    int cardlength = digits(cardnum);
    
    int startdigits = get_start_digits(cardlength, cardnum);
    
    int totalsum = digit_sum(cardlength, cardnum);

    //check for American express
    if (cardlength == 15)
    {
        if (startdigits == 34 || startdigits == 37)
        {
            if (check_last(totalsum))
            {
                printf("AMEX\n");
            }
            else 
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (cardlength == 16 || cardlength == 13)
    {   
        if (startdigits > 50 && startdigits < 56)
        {
            if (check_last(totalsum))
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (startdigits > 39 && startdigits < 50)
        {
            if (check_last(totalsum))
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

//check digit #
int digits(long card)
{
    int digitCounter = 0;
    while (card != 0)
    {
        card = card / 10;
        digitCounter++;
    }
    return (digitCounter);
}

//return first 2 digits
int get_start_digits(int len, long cardstart)
{
    for (int i = 0; i < len - 2; i++)
    {
        cardstart = cardstart / 10;
    }
    return cardstart;
}

// Sum up digits
int digit_sum(int length, long number)
{
    long tempnum = 0;
    int evensum = 0;
    int oddsum = 0;
    for (int i = 1; i <= length; i++)
    {
        tempnum = number % 10;
        number = number / 10;
        if (i % 2 == 1)
        {
            oddsum = oddsum + tempnum;
        }
        else
        {
            evensum = evensum + evens(tempnum);
        }
    }
    return (oddsum + evensum);
}

int evens(int evendigit)
{
    int evenTemp = 0;
    int evensum = 0;
    evendigit = evendigit * 2;
    while (evendigit > 9)
    {
        evenTemp = evendigit % 10;
        evensum = evensum + evenTemp;
        evendigit = evendigit / 10;
    }
    return (evensum + evendigit);
}

bool check_last(int sum)
{
    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}