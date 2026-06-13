#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"header.h"
int insert_at_last(Slist **head,char*data)
{
    //create the node
    Slist*new=malloc(sizeof(Slist));
    if(new==NULL)//check if memmory is allocated or not.
    return FAILURE;
    strcpy(new->filename,data);//assigning the data to be inserted to new node data
    new->link=NULL;//assigning the new link as null
    if(*head==NULL)//checking the list is empty or not
    {
        *head=new;//assigning the new node address to head
        return SUCCESS;
    }
        Slist*temp=*head;//creating a temporary node and assigning the head to it
        while(temp!=NULL)//run the loop upto last node
        {
            if(strcmp(temp->filename,data)==0)
            {
                printf("duplicate filenames present\n");
                free(new);
                return FAILURE;
            }
            if(temp->link==NULL)
            break;
            temp=temp->link;//assigning the next node address to temp
        }
        temp->link=new;//assigning the address of new node to last node link
    return SUCCESS;
}
void print_list(Slist *head)
{
	if (head == NULL)//checking the list is empty or not
	{
		printf("INFO : List is empty\n");
	}
    else
    {
	    while (head)//traversing the loop		
	    {
		    printf("%s -> ", head -> filename);//printing the list
		    head = head -> link;//updating
	    }

	    printf("NULL\n");
    }
}
int sl_delete_element(Slist **head,char*file_name)
{
    if(*head==NULL)// Check if list is empty
    return FAILURE;
    Slist*temp=*head;// Initialize temp to head
    Slist*prev=NULL;// Initialize previous pointer
    while(temp!=NULL)// Traverse the list
    {
        if(strcmp(temp->filename,file_name)==0)// Check if file name matches
        {
            if(prev==NULL)// If node to delete is head
            {
                *head=temp->link;
            }
            else
            prev->link=temp->link;//Bypass current node
            free(temp);//free deleted node
            return SUCCESS;
        }
        else
        {
            prev=temp;// Move prev to current node
            temp=temp->link;// Move temp to next node
        }
    }
    return DATA_NOT_FOUND;
}