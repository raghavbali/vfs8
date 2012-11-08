/*******************************************************************
Name            : Raghav Bali
Description     : Test File for n_array_trees
                  Updated the function return types to int
                  from void
Date            : Sep 20 2012
Version         : NA
*******************************************************************/

#include "../include/main.h"

int main()
{
    narry_tree_t *head;
    char filename[30];
    file_descriptor_t *fd_temp;
    file_descriptor_t fd_val,fd_val1,fd_val_head;

    strcpy(fd_val.file_name,"raghav");
    strcpy(fd_val_head.file_name,"/");

    head=malloc(sizeof(narry_tree_t));
    head->file_desc=&fd_val_head;
    head->leftchild=NULL;
    head->rightsibling=NULL;

    //fd_temp=malloc(sizeof(fileDescriptor));
    fd_temp=&fd_val;
    printf("\n%p",&fd_val);
    if (insert_node(&head,&fd_temp)!=TRUE)
        printf("\n Node not inserted\n");
    else
        printf("\n Node inserted successfully\n");

    printf("\n Enter a value : ");
    gets(fd_val1.file_name);
    fd_temp=&fd_val1;
    printf("\n%p",&fd_val1);

    if(insert_node(&head,&fd_temp)!=TRUE)
        printf("\n Node not inserted\n");
    else
        printf("\n Node inserted successfully\n");

  display(head);
printf("\n");
    return 0;
}

