#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    //Open csv file
    FILE *file = fopen("phonebook.csv", "a");
    if (!file)
    {
        return 1;
    }
    
    char *name = get_string("name: ");
    char *number = get_string("number: ");
    
    fprintf(file, "%s, %s\n", name, number);
    
    fclose(file);
}