// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

void append_word(int bucket_val, char *passed_word);

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table. 1125 represents the largest ascii values for a 45 letter word wherein A = 0 and Z = 25.
const unsigned int N = 1125;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int bucket_val = hash(word);
    char lowercase[LENGTH + 1] = "";
    for(int i = 0; i < LENGTH; i++)
    {
        if(word[i] == '\0')
        {
            lowercase[i] = '\0';
            break;
        }
        else
        {
        lowercase[i] = tolower(word[i]);
        }
    }
    if (table[bucket_val] == NULL)
    {
        return false;
    }
    node *ptr = table[bucket_val];
    if (strcmp(ptr->word, lowercase) == 0)
    {
        return true;
    }
    while (ptr->next != NULL)
    {
        if (strcmp(ptr->next->word, lowercase) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

// Hashes word to an ascii value, wherein A = 0 and Z = 25. Does not count apostrophes towards total.
unsigned int hash(const char *word)
{
    int ascii_sum = 0;
    int index = 0;
    while (word[index] != '\0')
    {
        if (word[index] == '\'')
        {
            index++;
        }
        else
        {
        ascii_sum = ascii_sum + (toupper(word[index]) - 'A');
        index++;
        }
    }
    return ascii_sum;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dictionary_file = fopen(dictionary, "r");
    char letter;
    int word_index = 0;
    char current_word[LENGTH + 1];
    int bucket = 0;

    while (fread(&letter, sizeof(char), 1, dictionary_file))
    {
        if (word_index > LENGTH)
        {
            while (fread(&letter, sizeof(char), 1, dictionary_file) && isalpha(letter))
                ;
            word_index = 0;
        }
        if (isalpha(letter) || (letter == '\'' && word_index > 0))
        {
            current_word[word_index] = letter;
            word_index++;
        }
        else if (word_index > 0)
        {
            current_word[word_index] = '\0';
            bucket = hash(current_word);
            word_index = 0;
            append_word(bucket, current_word);
        }
    }

    if (feof(dictionary_file))
    {
        fclose(dictionary_file);
        return true;
    }
    else
    {
        fclose(dictionary_file);
        return false;
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // We are not passed the loaded bool, and size() is only executed after loaded is checked. For the time being I will assume we
    // do not need to check if the dictionary was loaded within this function.
    unsigned int total = 0;
    node *temp;
    for (int i = 0; i < N; i++)
    {
        if (table[i] == NULL)
        {
            continue;
        }
        else
        {
            temp = table[i];
            total++;
        }
        while (temp->next != NULL)
        {
            total++;
            temp = temp->next;
        }
    }
    return total;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int out = 0; out < N; out++)
    {
        if (table[out] == NULL)
        {
            continue;
        }
        else
        {
            node *ptr = table[out];
            node *placeholder = table[out]->next;
            while (placeholder != NULL)
            {
                free(ptr);
                ptr = placeholder;
                placeholder = placeholder->next;
            }
            free(ptr);
        }
    }
    return true;
}

void append_word(int bucket_val, char *passed_word)
{
    node *new_word = malloc(sizeof(node));
    new_word->next = NULL;

    //Initializes the new_word to have an empty word array.
    for(int initialize = 0; initialize < LENGTH; initialize++)
    {
        new_word->word[initialize] = '\0';
    }

    // Copy passed word into new word node
    int index = 0;
    while (passed_word[index] != '\0')
    {
        new_word->word[index] = passed_word[index];
        index++;
    }
    passed_word[index] = '\0';

    // Traverse linked list to append new word

    if (table[bucket_val] == NULL)
    {
        table[bucket_val] = new_word;
    }
    else
    {
        node *ptr = table[bucket_val];
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = new_word;
    }
    return;
}
