#include <stdio.h>
#include <cs50.h>

//prototype
void meow(int n);

int main(void)
{
    int numMeows = get_int("How many meows? \n");
    meow(numMeows);
}

//meow 'n' times
void meow(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("meow\n");
    }
}
