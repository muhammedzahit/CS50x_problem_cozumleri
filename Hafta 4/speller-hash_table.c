// dictinory.h da bir şey değiştirmedim.
// buraya attığım dictinory.c dosyasıdır.

// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"
#include <stdlib.h>

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

int wordNum;

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

void makeLower(char *word)
{
    for (int i=0; i<LENGTH+1 ; i++)
    {
        if (word[i] == '\0') break;
        word[i] = tolower(word[i]);
    }
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    wordNum = 0;

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        wordNum++;
        node* temp = hashtable[hash(word)];
        if (!temp)
        {
            temp = (node*)malloc(sizeof(node));
            makeLower(word);
            strcpy(temp->word,word);
            temp->next = NULL;
            hashtable[hash(word)] = temp;
        }
        else {
            while(temp->next) temp = temp->next;
            temp->next = (node*)malloc(sizeof(node));
            makeLower(word);
            strcpy(temp->next->word,word);
            temp->next->next = NULL;
        }
        for (int i=0; i<LENGTH+1 ; i++) word[i] = '\0';
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (wordNum) return wordNum;
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char word2[LENGTH+1];
    strcpy(word2,word);
    makeLower(word2);
    node* temp = hashtable[hash(word2)];
    while (temp)
    {
        if (strcmp(temp->word,word2) == 0) return true;
        temp = temp->next;
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i=0; i<N ; i++){
        node* temp = hashtable[i];
        while (temp)
        {
            node* temp2 = temp->next;
            free(temp);
            temp = temp2;
        }
    }
    return true;
}
