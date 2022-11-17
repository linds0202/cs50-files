#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//prototypes
bool check_for_digits(string arg);
void print_cipher(int key, string secret);

//cipher text based on key
int main(int argc, string argv[])
{
    //Check that program was run w/1 command line prompt
    if (argc == 2)
    {
        //Check that prompt is valid
        if (check_for_digits(argv[1]))
        {
            //set command line prompt to int as key for cipher
            int k = atoi(argv[1]);
            
            //prompt user for plaintext
            string message = get_string("plaintext: ");
            printf("ciphertext: ");
            
            //iterate and adjust by key
            print_cipher(k, message);
            printf("\n");
            return 0;
        }
        else
        {
            //return 1 for not valid command line
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    else
    {
        //return 1 if not valid command line
        printf("Incorrect # of command line arguments\n");
        return 1;
    }
}


// check if command line argument is all digits
bool check_for_digits(string arg)
{
    for (int i = 0, n = strlen(arg); i < n; i++)
    {
        if (!isdigit(arg[i]))
        {
            return false;
        }
    }
    return true;
}

// iterate & adjust by Key then print cipher text
void print_cipher(int key, string secret)
{
    for (int i = 0, n = strlen(secret); i < n; i++)
    {
        //check for uppercase
        if (isupper(secret[i]))
        {
            int up = key;
            while (secret[i] + up > 90)
            {
                up -= 26;
            }
            printf("%c", secret[i] + up);
        }
        //check for lowercase
        else if (islower(secret[i]))
        {
            int low = key;
            while (secret[i] + low > 122)
            {
                low -= 26;
            }
            printf("%c", secret[i] + low); 
        }
        //else print non alpha charcater
        else
        {
            printf("%c", secret[i]);
        }
    }
}

