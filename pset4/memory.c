#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *x = malloc(4);
    x[0] = 'H';
    x[1] = 'i';
    x[2] = '!';
    x[3] = '\0';
    
    printf("%s\n", x);
    
    free(x);
}