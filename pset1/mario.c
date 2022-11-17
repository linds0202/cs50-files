#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    //get pos int from user
    do
    {
        n = get_int("Width: ");
    }
    while (n<1);
    
    //print 'n' ?'s
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("#");   
        }
        printf("\n");
    }
    printf("\n");
}