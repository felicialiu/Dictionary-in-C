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
    char* word;
    struct node* next;
 } 
 node;
 
/**
 * Defines the hash table to be an array of nodes
 */
node* hashTable[4000];

/**
 * Number of filled entries in the hash table
 */
 int count = 0;

/**
 * Returns an integer which is the result of hashing the given word
 */
int hash(const char* word) {
    return 0;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{   
    char lowerLetter;
    char hashableWord[strlen(word)];
    for (int i = 0; i < strlen(word); i++) {
        lowerLetter = tolower(word[i]);
        hashableWord[i] = (char) lowerLetter;
    }
    hashableWord[strlen(word)] = '\0';
    int index = hash(hashableWord);
    node* temp = hashTable[index];
    while (strcmp(temp->word, hashableWord)) {
        if (temp->next == NULL) {
            return false;
        }
        temp = temp->next;
    }
    return true;
    /*
    do {
        strcpy(hashedWord, hashTable[index]->word);
        if(strcmp(hashedWord, word)) {
            return true;
        }
    } while(!strcmp(hashedWord, word));
    return false;
    */
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
        printf("Specified file name could not be opened\n");
        return false;
    }
    char word[LENGTH+1];
    
    // For each word in the dictionary, hash it and add it to the hash table
    while(fscanf(fp, "%s\n", word) != EOF) {
        int index = hash(word);
        //printf("index : %i\n", index);
        node* newLemma = malloc(sizeof(node));
        newLemma->word = malloc(strlen(word) + 1);
        strcpy(newLemma->word, word);
        if(hashTable[index] == NULL) {
            hashTable[index] = newLemma;
            newLemma->next = NULL;
        } else {
            node* currentNode = hashTable[index];
            newLemma->next = currentNode;
            hashTable[index] = newLemma;            
        }
        //fscanf(fp, "%s\n", word);
        count++;
    }
    //printf("all ok? done reading the dict file\n");
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{   
    for (int i = 0; i < 4000; i++) {
        node* cursor = hashTable[i];
        while (cursor != NULL) {
            node* temp = cursor;
            cursor = cursor->next;
            free(temp->word);
            free(temp);
        }
    }
    return true;
}
