#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void)
{
    char c = 'c';
    printf("%c\n", c);
    printf("c + 1 is %c\n", c + 1);
}


if (isupper(secret[i]))
                {
                    while (secret[i] + key > 90)
                    {
                        
                        key -= 26;
                   /}
                    printf("%c", secret[i] + key);
                }
                else if (islower(secret[i]))
                {
                    while (secret[i] + key > 122)
                    {
                        key -= 26;
                    }
                    printf("%c", secret[i] + key); 
                }