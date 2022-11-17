#include <stdio.h>
#include <cs50.h>

//constant
const int TOTAL = 3;

//Prototype
float average (int length, int array[]);

int main(void)
{
    //Get scores from user
    int scores[TOTAL];
    for (int i = 0; i < TOTAL; i++)
    {
        scores[i] = get_int("Score: ");
    }
    
    //Print average
    printf("Average: %f\n", average(TOTAL, scores));
    
}

//Calculate average
float average (int length, int array[])
{
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += array[i];
    }
    return sum / (float) length;
}