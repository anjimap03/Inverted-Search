#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
typedef struct node
{
    char filename[30];
    struct node*link;
}Slist;
typedef struct node1
{
    int word_count;
    char filename[25];
    struct node1*link;
}sub_node_t;
typedef struct node2
{
    int file_count;
    char word[30];
    struct node1*sublink;
    struct node2*link;
}main_node_t;
typedef struct node3
{
    int index;
    struct node2*link;
}hash_t;
#define SUCCESS 1;
#define FAILURE 0;
#define DATA_NOT_FOUND -1;
int insert_at_last(Slist **head,char*data);
void print_list(Slist *head);
int sl_delete_element(Slist **head,char*filename);
int create(Slist*head,hash_t*arr);
main_node_t*create_main_node(char*word);
sub_node_t* create_sub_node(char*filename);
int display(hash_t*arr);
int save(hash_t*arr);
int search(hash_t*arr);
int update(Slist**head,hash_t*arr);
#endif