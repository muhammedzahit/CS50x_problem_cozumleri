// dictionary.h dosyasında bir şey değiştirmedim
// attığım çözüm dictionary.c dosyasıdır.

// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;

int wordNum;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    
    wordNum = 0;
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        wordNum++;
        node* temp = root;
        int index = 0;
        while (word[index] != '\0')
        {
            int curr;
            if (word[index] == 39) curr = 26;  // kesme işareti karakteri
            else curr = tolower(word[index]) - 'a';
            if (temp && !temp->children[curr])
            {
                temp->children[curr] = malloc(sizeof(node));
                temp->children[curr]->is_word = false;
                for (int i=0; i<N; i++) temp->children[curr]->children[i] = NULL;
            }
            temp = temp->children[curr];
            
            index++;
        }
        
        temp->is_word = true;
        
        
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordNum;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    if(!root) return false;
    
    node* temp = root;
    int index = 0;
    
    while (word[index] != '\0')
    {
        
        int curr;
        if (word[index] == 39) curr = 26;  // kesme işareti karakteri
        else curr = tolower(word[index]) - 'a';
        
        if (!temp->children[curr]) return false; 
        
        temp = temp->children[curr];
        
        index++;
    }
    
    return temp->is_word;
}

void rm(node* temp)
{
    if(!temp) return;
    
    for(int i=0; i<N; i++)
    {
        if(temp->children[i]) rm(temp->children[i]);
    }
    
    free(temp);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if (!root) return false;
    
    rm(root);
    
    return true;
}
