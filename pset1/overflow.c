#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <cs50.h>

int main(void)
{
    //iterativley double i
    int i = 1;
    while(true)
    {
        printf("%i\n", i);
        sleep(1);
        i *=2;
    }
}