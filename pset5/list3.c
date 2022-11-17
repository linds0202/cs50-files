#include <stdio.h>
#include <stdlib.h>

//represents a node
typedef struct node
{
    int number;
    struct node *next;
}
node;



int main(void)
{
    //list of size 0
    node *list = NULL;
    
    //add number to list
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }
    
    n->number = 1;
    n->next = NULL;
    list = n;
    
    //add number to list
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list);
        return 1;
    }
    
    n->number = 2;
    n->next = NULL;
    list->next = n;
    
    //add number to list
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list->next);
        free(list);
        return 1;
    }
    
    n->number = 3;
    n->next = NULL;
    list->next->next = n;
    
    //Print list
    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }
    
    //free list
    while (list != NULL)
    {
        node *tmp = list->next;
        free(list);
        list = tmp;
    }
    
    return 0;
}