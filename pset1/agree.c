#include <cs50.h>
#include <stdio.h>

int main(void)
{
    char c = get_char("Do you agree? ");
    
    if (c == 'y'|| c == 'Y')
    {
        printf("agree\n");
    }
    else if (c== 'n'|| c == 'N')
    {
        printf("disagree\n");
    }
}