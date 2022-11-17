// Implements a dictionary's functionality

#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <cs50.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table 45 length of word, if all lower z's would be 
const unsigned int N = (LENGTH + 1) * 'z';

// initialise (positive) hash table word count 
unsigned int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
   //get the hash index
   int index = hash(word);
   
   node *cursor = table[index];
   
   while (cursor != NULL)
   {
       //if matching string found, return true
       if (strcasecmp(cursor->word, word) == 0)
       {
           return true;
       }
       
       cursor = cursor->next;
    }
   
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);        
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open the dictionary
    FILE *file = fopen(dictionary, "r");
    
    //If file fails to open, return false
    if (file == NULL)
    {
        return false;
    }
    
    //read file one word @ a time
    
    //create storage space for word (LENGTH = 45 in dictionary.h +1 for NULL char)
    char word[LENGTH + 1];
    
    //scan file to find words
    while (fscanf(file, "%s", word) != EOF)
    {
        //allocate memory for new node
        node *n = malloc(sizeof(node));
        
        //if malloc returns NULL, return false
        if (n == NULL)
        {
            return false;
        }
        
        //create pointer to next node
        strcpy(n->word, word);
        n->next = NULL;
        
        //get hashing index
        int index = hash(word);
        if (table[index] == NULL)
        {
            table[index] = n;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }
        
        //increment for size count
        word_count++;
    }
    
    
    //close file
    fclose(file);
    
    //if dictionary loaded, return true
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    //check if how many words
    if (word_count > 0)
    {
        //return word_count value
        return word_count;
    }
    //else returnt that there are no words
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //iterate through linked buckets
    for (int i = 0; i < N; i++)
    {
        //set cursor to this for each bucket
        node *head = table[i];
        node *cursor = head;
        node *tmp = head;
        
        //if cursor if not NULL, free the memory
        while (cursor != NULL)
        {
            //advance cursor pointer
            cursor = cursor->next;
            //free the memory
            free(tmp);
            tmp = cursor;
        }
        
    }
    return true;
}
