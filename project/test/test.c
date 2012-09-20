/*******************************************************************
Name            : Raghav Bali
Description     : Test File for n_array_trees
Date            : Sep 20 2012
Version         : NA
*******************************************************************/

#include "main.h"

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
    insert_node(&head,&fd_temp);
    printf("\n Enter a value : ");
    gets(fd_val1.file_name);
    fd_temp=&fd_val1;
    printf("\n%p",&fd_val1);
    insert_node(&head,&fd_temp);
/*
    do{
		insert_node(head,fd_temp);
        printf("\n Enter a value : ($ to exit) : ");
        gets(fd_val.fileName);
        fd_temp=&fd_val;
        printf("\n %s",fd_val.fileName);
    }while(filename[0]!='$');

*/
  display(head);

    return 0;
}

