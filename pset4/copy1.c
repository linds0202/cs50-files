#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *s = get_string("s: ");
    
    //check that input has length
    if (f == NULL)
    {
        return 1;
    }
    
    //create memory for new string, must be +1 for null character
    char *t = malloc(strlen(s) + 1);
    
    //check that string has length of at least 1
    if (t == NULL)
    {
        return 1;
    }

    //copy s into t
    strcpy(t, s);
    
    //change 1st letter to uppercase
    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    //print both strings
    printf("s: %s\n", s);
    printf("t: %s\n", t);
    
    //release memory from malloc
    free(t);
    return 0;
}