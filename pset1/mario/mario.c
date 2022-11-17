#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Get height from user
    int height;
    do
    {
        height = get_int("Enter pyramid height: ");    
    }
    while (height < 1 || height > 8);
    
    //Print pyramid
    for (int i = height - 1; i >= 0; i--)
    {
        //print reverse pyramid
        for (int j = 0; j < height; j++)
        {
            if (j < i)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        
        //print middle gap
        printf("  ");
        
        //print reg pyramid
        for (int j = height - 1; j >= 0; j--)
        {
            if (j >= i)
            {
                printf("#");
            }
        }
        printf("\n");
    }
}