#include <stdio.h>
#include "header.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
int display(hash_t *arr)
{
    int flag = 0;//declaring the flag variable 
    for (int i = 0; i < 27; i++)//Traverse all 27 hash table indexes
    {
        if (arr[i].link != NULL)//checking if any index hs main node
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0)//if no data found in entire table
        return FAILURE;//return failure
    printf("\n=====================================================================\n");
    printf("%-6s %-12s %-15s %-12s %-15s\n",
           "Index", "FileCount", "Word", "WordCount", "FileName");
    printf("=====================================================================\n");
    for (int i = 0; i < 27; i++)//traverse each index
    {
        if (arr[i].link != NULL)// If main node exists at this index
        {
            main_node_t *main_node_temp = arr[i].link;//point to first main node
            while (main_node_temp != NULL)//traverse main node list
            {
                sub_node_t *sub_node_temp = main_node_temp->sublink;//point to first sub node
                while (sub_node_temp != NULL)//traverse sub node list
                {
                    printf("%-6d %-12d %-15s %-12d %-15s\n",
                           arr[i].index,
                           main_node_temp->file_count,
                           main_node_temp->word,
                           sub_node_temp->word_count,
                           sub_node_temp->filename);//printing the contents
                    sub_node_temp = sub_node_temp->link;//move to next sub node
                }
                main_node_temp = main_node_temp->link;//move to next main node
            }
        }
    }
    printf("=====================================================================\n");
    return SUCCESS;
}
int save(hash_t *arr)
{
    int flag = 0;// Flag to check whether database is created
    // Check if any index has main node
    for(int i = 0; i < 27; i++)
    {
        if(arr[i].link != NULL)
        {
            flag = 1;
            break;
        }
    }
    if(flag == 0)   // If no main node exists
    {
        return FAILURE;
    }
    char save[30];//string to store the filename
    printf("Enter the file name to Save Database : \n");
    scanf("%s", save);//reading the filename
    char *fptr = strstr(save, ".");
    if (fptr == NULL || strcmp(fptr, ".txt") != 0)//checking if it is a .txt file or not
    {
        printf("Enter a valid file name\n");
        return FAILURE;
    }
    FILE *qtr = fopen(save, "w");//opening the file in write mode
    if (qtr == NULL)//checking the filepointer is null or not
        return FAILURE;
    for (int i = 0; i < 27; i++)//traversing each node
    {
        if (arr[i].link != NULL)//checking if the main node is present or not
        {
            main_node_t *main_node_temp = arr[i].link;//point to first main node
            while (main_node_temp != NULL)//traversing the main node
            {
                fprintf(qtr, "#%d;%d;%s;", arr[i].index, main_node_temp->file_count, main_node_temp->word);//printing the main node contents in the file
                sub_node_t *sub_node_temp = main_node_temp->sublink;//pointing to first sub node
                while (sub_node_temp != NULL)//traversing the sub node
                {
                    fprintf(qtr, "%d;%s;", sub_node_temp->word_count, sub_node_temp->filename);//printing the sub node contents in the file
                    sub_node_temp = sub_node_temp->link;//move to next subnode
                }
                fprintf(qtr, "#\n");
                main_node_temp = main_node_temp->link;//move to next main node
            }
        }
    }
    fclose(qtr);//closing the file
    return SUCCESS;
}
int search(hash_t *arr)
{
    int flag = 0;// Flag to check whether database is created
    // Check if any index has main node
    for(int i = 0; i < 27; i++)
    {
        if(arr[i].link != NULL)
        {
            flag = 1;
            break;
        }
    }
    if(flag == 0)   // If no main node exists
    {
        printf("Database not created !\n");
        return FAILURE;
    }
    char word[25];//string for storing the word to be searched
    printf("Enter the word you want to search\n");
    scanf("%s", word);//reading the word
    int index = tolower(word[0]) - 'a';//finding the index
    if (index < 0 || index > 25)
        index = 26;
    if (arr[index].link == NULL)//checking if that pariticular index has main node
    {
        printf("Data not found !\n");
        return FAILURE;
    }
    main_node_t *main_node_temp = arr[index].link;//point to first main node
    while (main_node_temp != NULL)//traversing the main node
    {
        if (strcmp(word, main_node_temp->word) == 0)//checking if the word is present or not
        {
            printf("word %s present in %d files\n", main_node_temp->word, main_node_temp->file_count);//printing
            sub_node_t *sub_node_temp = main_node_temp->sublink;//point to first sub node
            while (sub_node_temp != NULL)//traversing the subnode
            {
                printf("In %s %d times\n", sub_node_temp->filename, sub_node_temp->word_count);//printing
                sub_node_temp = sub_node_temp->link;//move to next subnode
            }
            return SUCCESS;
        }
        main_node_temp = main_node_temp->link;//move to next main node
    }
    printf("Data not found\n");
    return FAILURE;
}
int update(Slist**head,hash_t*arr)
{
    char file[30];//to store the filename
    printf("Enter a file to update\n");
    scanf("%s", file);//reading the filename
    char *fptr = strstr(file, ".");
    if (fptr == NULL || strcmp(fptr, ".txt") != 0)//checking if it is a .txt file
    {
        printf("Enter a valid file name\n");
        return FAILURE;
    }
    FILE *qtr = fopen(file, "r");//opening the file in read mode
    if (qtr == NULL)//check if the file opened successfully 
        return FAILURE;
    char line[100];//to store each word read from file
    while (fscanf(qtr, "%s", line) == 1)//read file word by word
    {
        int len = strlen(line);
        if (line[0] == '#' && line[len - 1] == '#')//check if line starts and ends with #
        {
            char *token = strtok(&line[1], ";");//extracts index
            int index = atoi(token);//convert index to integer
            if (index < 0 || index >= 27)//validate index range
                continue;
            token = strtok(NULL, ";");//extract file count
            int filecount = atoi(token);//convert to integer
            token = strtok(NULL, ";");//extract word
            char word[25];
            strcpy(word, token);
            main_node_t *main = create_main_node(word);//create main node
            if (main == NULL)
                return FAILURE;
            main->file_count = filecount;//assign file count
            if (arr[index].link == NULL)
                arr[index].link = main;//insert main into hash table
            else
            {
                main_node_t *temp = arr[index].link;//declare a temp to traverse
                while (temp->link != NULL)//traversing to last node
                    temp = temp->link;
                temp->link = main;//attach new main node
            }
            while ((token = strtok(NULL, "#;")) != NULL)// Process sub nodes (word_count and filename)
            {
                int word_count = atoi(token);//extract word count
                token = strtok(NULL, "#;");//extract filename
                if (token == NULL)
                    break;
                char sub_filename[30];
                strcpy(sub_filename, token);
                sl_delete_element(head,sub_filename);//deleting the filenames which are already present
                sub_node_t *sub = create_sub_node(sub_filename);//creating the sub node
                if (sub == NULL)
                    return FAILURE;
                sub->word_count = word_count;//assign the word count
                sub->link = NULL;
                if (main->sublink == NULL)
                    main->sublink = sub;//insert sub node into main node's sublink
                else
                {
                    sub_node_t *sub_temp = main->sublink;//declaring the temp
                    while (sub_temp->link != NULL)//traversing to the last sub node
                        sub_temp = sub_temp->link;
                    sub_temp->link = sub;//attach the sub node
                }
            }
        }
    }
    fclose(qtr);//close file
    return SUCCESS;
}