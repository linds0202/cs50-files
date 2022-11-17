#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
}
person;

int main(void)
{
    person people[2];
    
    people[0].name = "Brian";
    people[0].number = "+1-617-495-1000";
    
    people[1].name = "David";
    people[1].number = "+1-949-468-2750";
    
    //search for david
    for (int i = 0; i < 2; i++)
    {
        if (strcmp(people[i].name, "David") == 0)
        {
            printf("Found %s\n", people[i].name);
            return 0;
        }
    }
    printf("Not Found");
    return 1;
}