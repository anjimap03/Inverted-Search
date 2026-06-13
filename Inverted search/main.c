/*
 Name        : Anjima P
 Date        : 28-02-2026

 Description :
 This project implements an Inverted Search System using a Hash Table
 and Linked Lists in C. It creates an index of words from multiple
 text files and allows efficient searching of words across files.

 The system avoids repeated file scanning by storing:
   - The word
   - Number of files in which the word appears
   - File names where the word is present
   - Number of occurrences in each file

 Hashing Technique:
   - A hash table of size 27 is used.
   - Index 0–25  -> Words starting with alphabets (a–z)
   - Index 26    -> Words starting with special characters or numbers
   - Hash Function: index = tolower(word[0]) - 'a'
 The following functions are implemented:
   - validate_input()     : Validates input files
   - create()             : Creates the inverted index database
   - display()            : Displays the entire database
   - search()             : Searches for a word in the database
   - save()               : Saves the database into a file
   - update()             : Updates the database from a saved file
*/
#include<stdio.h>
#include<string.h>
#include"header.h"
int main(int argc, char*argv[])
{
    if(argc==1)//checking the argument count
    {
        printf("Insufficient arguments !\n");
        return 0;
    }
    Slist*head=NULL;//declaring the single linked list to store filename
    for(int i=1;i<argc;i++)//running loop upto argument count
    {
        char*p=strstr(argv[i],".");
        if(p==NULL||strcmp(p,".txt")!=0)//checking the file is .txt or not
        {
            printf("%s is not .txt file !\n",argv[i]);
            continue;
        }
        FILE*fptr=fopen(argv[i],"r");//opening the file
        if(fptr==NULL)//checking if the file is present or not
        {
            printf("File is not present\n");
            continue; 
        }
        fseek(fptr,0,SEEK_END);//moving the offset from zero to end of the file
        long size=ftell(fptr);
        if(size==0)//checking if the file is empty or not
        {
            printf("%s is empty !\n",argv[i]);
            fclose(fptr);
            continue;
        }
        fclose(fptr);//closing the file
        insert_at_last(&head,argv[i]);//storing to sll
    }
    printf("INFO : Input File Names\n");
    print_list(head);
    printf("INFO : Successfully Validated the Input Files ✅\n");
    hash_t arr[27];//declaring the hash table
    for(int i=0;i<27;i++)
    {
        arr[i].index=i;//assigning the index value
        arr[i].link=NULL;//assigning the link as NULL
    }
    int opt;
    while (1)
    {
        printf("\n=====================================\n");
        printf("        INVERTED SEARCH MAIN MENU      \n");
        printf("=====================================\n");
        printf("1. Create Database\n");
        printf("2. Search Database\n");
        printf("3. Update Database\n");
        printf("4. Display Database\n");
        printf("5. Save Database\n");
        printf("6. Exit\n");
        printf("-------------------------------------\n");
        printf("Enter your choice : ");

        scanf("%d", &opt);

        printf("=====================================\n");

        switch (opt)
        {
            case 1:
                printf("Creating Database...\n");
                create(head, arr);//create function call
                printf("Database Created Successfully ✅\n");
                break;

            case 2:
                search(arr);//search function call
                break;

            case 3:
                printf("Updating Database...\n");
                update(&head, arr);//update function call
                printf("Database Updated Successfully ✅\n");
                break;

            case 4:
            {
                if (display(arr)== 0)//checking if database exist or not
                    printf("No Database Exists !\n");
                break;
            }
            case 5:
                if (save(arr) == 1)//checking if database is saved successfully
                    printf("Database Saved Successfully ✅\n");
                else
                    printf("Failed to Save Database !\n");
                break;

            case 6:
                printf("Exiting Program...\n");
                return 0;//exiting

            default:
                printf("Invalid Input! Please Try Again.\n");
                break;
        }
    }
}