#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int startsize;
    do
    {
        startsize = get_int("Starting population: "); 
    }
    while (startsize < 9);

    // TODO: Prompt for end size
    int endsize;
    do
    {
        endsize = get_int("Ending population: ");
    }
    while (endsize < startsize);
    
    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    int llamas = startsize;
    while (llamas < endsize)
    {
        llamas = llamas + llamas / 3 - llamas / 4;
        years++;
    }
    
    // TODO: Print number of years
    printf("Years: %i\n", years);
}