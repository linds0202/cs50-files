#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//prototypes
bool check_alpha(string message);
bool check_duplicates(int length, string check);
void decipher(string decode, string key);

int main(int argc, string argv[])
{
    //check for cammand line args
    if (argc == 2)
    {
        int len = strlen(argv[1]);
        //check for key length of 26
        if (len != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        //check for non alphanumerics
        if (!check_alpha(argv[1]))
        {
            printf("Key contains non-aphanumeric characters\n");
            return 1;
        }
        //check for duplicates
        if (!check_duplicates(len, argv[1]))
        {
            printf("Key contains duplicate characters\n");
            return 1;
        }
        else
        {
            //get message form user
            string secret = get_string("plaintext: ");
            
            printf("ciphertext: ");
            
            //decipher text
            decipher(secret, argv[1]);
            
            //print newline
            printf("\n");
            return 0;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

//check alpha in string
bool check_alpha(string message)
{
    for (int i = 0; i < 26; i++)
    {
        //check for non alpha chars
        if (!isalpha(message[i]))
        {
            return false;
        }
    }
    return true;
}

//check for duplicates
bool check_duplicates(int length, string check)
{
    for (int i = 0; i < length; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            //check for duplicates
            if (check[i] == check[j])
            {
                return false;   
            }
        }
    }
    return true;
}

//decipher & print message
void decipher(string decode, string key)
{
    int codelength = strlen(decode);
    int keycode = 0;
    for (int i = 0; i < codelength; i++)
    {
        //check & handle uppercase
        if (isupper(decode[i]))
        {
            keycode = decode[i] - 65;
            printf("%c", toupper(key[keycode]));
        }
        //check & handle lowercase
        else if (islower(decode[i]))
        {
            keycode = decode[i] - 97;
            printf("%c", tolower(key[keycode]));
        }
        //handle non alphanumeric chars
        else
        {
            printf("%c", decode[i]);
        }
    }
}