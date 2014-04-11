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
#include <math.h>

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
 * Defines the hash table to be an array of nodes whose size is a primitive
 */
node* hashTable[4021];

/**
 * Number of filled entries in the hash table
 */
 int count = 0;
 
 /**
  * Takes in two arguments a and b and returns a to the power of b,
  * if the two arguments are nonnegative
  */
int power(int a, int b) {
    int result = 1;
    if (a > 0 && b > 0) {
        for (int i = 0; i < b; i++) {
            result *= a;
        }
    }
    return result;
}

/**
 * Returns an integer which is the result of hashing the given word
 * Hashing method adds the numeric value of the characters and takes the
 * modulo hash table size of them.
 * Idea for this hash function from:
 * http://computinglife.wordpress.com/2008/11/20/why-do-hash-functions-use-prime-numbers/
 */
unsigned int hash(const char* word) {
    int hashed = 0;
    int charNum = 0;
    for (int i = 0; i < strlen(word); i++) {
        charNum = (int) word[i];
        hashed = hashed + charNum*pow(31, strlen(word) - 1 - i);
    }
    hashed = hashed % 4021;
    
    // Sometimes the modulus operator can return negative values
    // make sure all values returned are nonnegative
    if(hashed < 0) {
        return hashed*-1;
    } else {
        return hashed;
    }
    // return hashed;
    //return 0;
}


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{   
    char lowerLetter;
    char hashableWord[strlen(word)];
    // Convert given word to lowercase before checking whether it's in the dict
    for (int i = 0; i < strlen(word); i++) {
        lowerLetter = tolower(word[i]);
        hashableWord[i] = (char) lowerLetter;
    }
    hashableWord[strlen(word)] = '\0';
    
    // Calculates the index of the word with the hash function
    int index = hash(hashableWord);
   //  printf("checking word index : %i\n", index);
   
   
    node* currentNode = hashTable[index];
    
    // If the node at INDEX is NULL, the word is not in the dictionary
    if (currentNode == NULL) {
        return false;
    }
    // Else, keep looking until the word is found, or the last node points to NULL
    while (strcmp(currentNode->word, hashableWord)) {
        if (currentNode->next == NULL) {
            return false;
        }
        currentNode = currentNode->next;
    }
    return true;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // Open the file in a read-only manner
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
        //printf("loading dict index : %i\n", index);
        
        // Allocate memory for the node and correctly instantiate the node
        node* newLemma = malloc(sizeof(node));
        // Allocate maximum length of the word + 1 (for '\0') as memory
        newLemma->word = malloc(strlen(word) + 1);
        strcpy(newLemma->word, word);
        newLemma->next = NULL;
        
        // If the hash table entry is empty, put the new word there
        if(hashTable[index] == NULL) {
            hashTable[index] = newLemma;
        // Else, prepend the new word to the chained list, properly taking care
        // of links
        } else {
            // node* currentNode = hashTable[index];
            newLemma->next = hashTable[index];
            hashTable[index] = newLemma;            
        }
        //fscanf(fp, "%s\n", word);
        count++;
    }
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
    for (int i = 0; i < 4021; i++) {
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
