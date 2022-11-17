#include <stdio.h>

int main(void)
{
    //list of size 3
    int list[3];
    
    //initialize list w/#'s
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;
    
    //print list
    for (int i = 0; i < 3; i++)
    {
        printf("%i\n", list[i]);
    }
}