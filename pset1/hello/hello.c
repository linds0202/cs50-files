#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Get name from user & print
    string name = get_string("What's your name? \n");
    printf("hello, %s\n", name);
}
