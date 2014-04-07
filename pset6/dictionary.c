/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include "dictionary.h"

/**
 * Defines the struct node to be used in a linked list datastructure
 */
 typedef struct node {
    char word[LENGTH+1];
    struct node* next;
 } 
 node;
 
/**
 * Defines the hash table to be an array of nodes
 */
node* hashtable[4000];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    
    // to do do
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
