#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"header.h"
#include<ctype.h>

int create(Slist *head, hash_t *arr)
{
    char word[25];// To store each word read from file
    Slist *temp = head;// Pointer to traverse file linked list
    while (temp != NULL)// Traverse through each file in Slist
    {
        FILE *fptr = fopen(temp->filename, "r");// Open file in read mode
        while ((fscanf(fptr, "%s", word)) != EOF)// Read words from file
        {
            int index = tolower(word[0]) - 'a';// Calculate hash index
            if (index < 0 || index > 25)// If not alphabet
                index = 26;// Store in last index
            if (arr[index].link == NULL)// If index is empty
            {
                main_node_t *main = create_main_node(word);// Create main node
                if (main == NULL)
                    return FAILURE;
                sub_node_t *sub = create_sub_node(temp->filename);// Create sub node
                if (sub == NULL)
                    return FAILURE;
                main->sublink = sub;// Attach sub node
                arr[index].link = main;// Attach main node to hash table
            }
            else
            {
                main_node_t *main_node_temp = arr[index].link;// Traverse main list
                main_node_t *main_node_prev = NULL;
                while (main_node_temp != NULL)// Search word in main list
                {
                    if (strcmp(word, main_node_temp->word) == 0)
                        break;
                    main_node_prev = main_node_temp;
                    main_node_temp = main_node_temp->link;
                }
                if (main_node_temp != NULL)// Word already exists
                {
                    sub_node_t *sub_node_temp = main_node_temp->sublink;// Traverse sub list
                    sub_node_t *sub_node_prev = NULL;
                    while (sub_node_temp != NULL)// Search filename in sub list
                    {
                        if (strcmp(temp->filename, sub_node_temp->filename) == 0)
                            break;
                        sub_node_prev = sub_node_temp;
                        sub_node_temp = sub_node_temp->link;
                    }
                    if (sub_node_temp != NULL)// File already exists
                    {
                        sub_node_temp->word_count++;// Increment word count
                    }
                    else
                    {
                        sub_node_t *sub = create_sub_node(temp->filename);// Create new sub node
                        if (sub == NULL)
                            return FAILURE;

                        if (sub_node_prev == NULL)
                            main_node_temp->sublink = sub;// Insert at beginning
                        else
                            sub_node_prev->link = sub;// Insert at end

                        main_node_temp->file_count++;// Increment file count
                    }
                }
                else
                {
                    main_node_t *main = create_main_node(word);// Create new main node
                    if (main == NULL)
                        return FAILURE;
                    sub_node_t *sub = create_sub_node(temp->filename);// Create sub node
                    if (sub == NULL)
                        return FAILURE;
                    main->sublink = sub;// Attach sub node
                    main_node_prev->link = main;// Attach main node to list
                }
            }
        }
        fclose(fptr);// Close current file
        temp = temp->link;// Move to next file
    }
    return SUCCESS;// Return success after creating database
}

main_node_t *create_main_node(char *word)
{
    main_node_t *new = malloc(sizeof(main_node_t)); // Allocate memory
    if (new == NULL)
        return NULL;

    new->file_count = 1;       // Initialize file count
    strcpy(new->word, word);   // Store word
    new->sublink = NULL;       // Initialize sub link
    new->link = NULL;          // Initialize next main link

    return new;                // Return main node
}

sub_node_t *create_sub_node(char *filename)
{
    sub_node_t *new2 = malloc(sizeof(sub_node_t)); // Allocate memory
    if (new2 == NULL)
        return NULL;

    new2->word_count = 1;          // Initialize word count
    strcpy(new2->filename, filename); // Store filename
    new2->link = NULL;             // Initialize next sub link

    return new2;                   // Return sub node
}