/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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
 * Returns an integer which is the result of hashing the given word
 */
int hash(char word[]) {
    return 0;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // doing
    FILE *fp;
    fp = fopen(dictionary, "r");
    if (fp == NULL) {
        printf("Help null file\n");
        return false;
    }
    char word[LENGTH+1];
    
    // For each word in the dictionary, hash it and add it to the hash table
    while(fscanf(fp, "%s\n", word) != EOF) {
        int index = hash(word);
        node* newLemma = malloc(sizeof(node));
        //newLemma->word = malloc(strlen(word)) + 1;
        strcpy(newLemma->word, word);
        if(hashtable[index] == NULL) {
            hashtable[index] = newLemma;
        } else {
            node* currentNode = hashtable[index];
            newLemma->next = currentNode;            
        }
        fscanf(fp, "%s\n", word);
    }
    printf("all ok?\n");
    return true;
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
