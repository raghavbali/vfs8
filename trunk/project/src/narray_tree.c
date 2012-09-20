/*************************************************************************************************************
* File Name 		:	file_system.h
* Description		:	This contains implementation of n-arry functions to insert and display
* Author		    :	Raghav Bali
* Date			    :	Sep 20 2012
* Version		    :	0.2
* Updates           :   [Raghav Bali Sep 20 2012]: Updated Data Structuress as required
                        [Raghav Bali Sep 20 2012]: Updated the formatting to Indian Hill
**************************************************************************************************************/

#include "../include/main.h"

/* Locates the correct position and inserts */
void insert_pos(narry_tree_t **head,narry_tree_t **fresh)
{
    narry_tree_t *temp;

    temp=*head;

    if(temp)
    {
        /* possible candidate for right child */
        if(strncmp(temp->file_desc->file_name,(*fresh)->file_desc->file_name,strlen(temp->file_desc->file_name)))
            if(temp->rightsibling)
                insert_pos(&(temp->rightsibling),fresh);
            else
            {
                temp->rightsibling=*fresh;
            }
        /* possible candidate for left child */
        else if(!strncmp(temp->file_desc->file_name,(*fresh)->file_desc->file_name,strlen(temp->file_desc->file_name)))
        {
			if(strcmp(temp->file_desc->file_name,(*fresh)->file_desc->file_name))
			{

				if(temp->leftchild)
					insert_pos(&(temp->leftchild),fresh);
				else
				{
					temp->leftchild=*fresh;
				}
			}
			else
				{
					printf("\n Error!!! File/Directory already exists");
					exit(0);
				}
		}
    }
}




/* Creates a node and then calls insert_pos for insertion */
void insert_node(narry_tree_t **head,file_descriptor_t **file_desc)
{
    narry_tree_t *temp, *fresh;
    file_descriptor_t fd1;

    fresh=malloc(sizeof(narry_tree_t));
    fresh->file_desc=*file_desc;
    fresh->leftchild= NULL;
    fresh->rightsibling=NULL;

    temp=*head;

    if(temp->leftchild==NULL)
    {
        //strcpy(fd1.file_name,"/");
        //temp->file_desc=&fd1;
        temp->leftchild=fresh;
        temp->rightsibling=NULL;
        *head=temp;
    }
    else
    {

        /* move to 1st node */
        temp=temp->leftchild;

        /* insert at correct place */
        insert_pos(&temp,&fresh);

    }
}

/* Display the tree : level then left child */
void display(narry_tree_t  *head)
{
    narry_tree_t *temp;

    temp=head;

    if(temp)
    {
        printf("%s",temp->file_desc->file_name);
        if(temp->rightsibling)
        {
            printf("->\t");
            display(temp->rightsibling);
        }
        if(temp->leftchild)
        {
            printf("\n(%s) ",temp->file_desc->file_name);
            display(temp->leftchild);
        }

    }

}
