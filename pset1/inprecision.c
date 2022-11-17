#include <stdio.h>
#include <cs50.h>

int main(void)
{
    float x = get_float("X: \n");
    float y = get_float("Y: \n");
    
    printf("%.50f\n", x / y);
}