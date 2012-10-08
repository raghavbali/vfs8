/*************************************************************************************************************
* File Name 		:	narray_tree.h
* Description		:	This contains implementation of n-arry functions to insert and display
* Author		    :	Raghav Bali
* Date			    :	Sep 21 2012
* Version		    :	0.9
* Updates           :   [Raghav Bali Oct 08 2012]: Added create_node(), free_tree(),
                        create_file_descriptor() and minimized memory leaks
                        [Raghav Bali Oct 07 2012]: Added tokenizer function for dummy insertions
                        [Raghav Bali Oct 07 2012]: Random order insertion possible now.
                        Using file_desc->loc_number=-1 to identify dummy nodes.
                        [Raghav Bali Sep 25 2012]: Bug Fix-insert_node()->root node insertion streamlined
                        [Raghav Bali Sep 21 2012]: Bug Fix for node insertion as sibling
                        [Raghav Bali Sep 20 2012]: Updated funtion return types to int from void
                        [Raghav Bali Sep 20 2012]: Updated Data Structuress as required
                        [Raghav Bali Sep 20 2012]: Updated the formatting to Indian Hill
**************************************************************************************************************/

#include "../include/main.h"

/*
*   Description :   This function creates a new node
*   Input       :   Node to be created, file descriptor to be attached
*   Output      :   True(1) if successful, FALSE(0) otherwise
*/
int create_node(narry_tree_t **node,file_descriptor_t **file_desc)
{
    if(*node=(narry_tree_t *)malloc(sizeof(narry_tree_t)))
    {
        (*node)->file_desc=*file_desc;
        (*node)->leftchild= NULL;
        (*node)->rightsibling=NULL;
        return TRUE;
    }
    else
        return FALSE;
}


/*
*   Description :   This function creates a new file descriptor node
*   Input       :   File descriptor to be created, file_name, loc number
*   Output      :   True(1) if successful, FALSE(0) otherwise
*/
int create_file_descriptor(file_descriptor_t **file_desc,char * str,int loc_number)
{
    if((*file_desc)=(file_descriptor_t*)malloc(sizeof(file_descriptor_t)))
    {
        strcpy((*file_desc)->file_name,str);
        (*file_desc)->loc_number=loc_number;
        return TRUE;
    }
    else
        return FALSE;

}


/*
*   Description :   Locates and inserts node at correct position.
*                   Replace dummy node(file_desc.loc_number=-1) with actual node
*                   when available
*   Input       :   Head node ,Node to be inserted
*   Output      :   True(1) if successful, FALSE(0) otherwise
*/
int insert_pos(narry_tree_t **head,narry_tree_t **fresh)
{
    narry_tree_t *temp;

    temp=*head;

    if(temp)
    {
        /* possible candidate for right child */
        if(strncmp(temp->file_desc->file_name,(*fresh)->file_desc->file_name,strlen(temp->file_desc->file_name))
                || (strlen((*fresh)->file_desc->file_name) > strlen(temp->file_desc->file_name) && (*fresh)->file_desc->file_name[strlen(temp->file_desc->file_name)]!='/'))
        {
            if(strcmp(temp->file_desc->file_name,(*fresh)->file_desc->file_name))
            {

                if(temp->rightsibling)
                    return insert_pos(&(temp->rightsibling),fresh);
                else
                {
                    temp->rightsibling=*fresh;
                    return TRUE;
                }
            }
            else
            {
                free((*fresh)->file_desc);
                free(*fresh);
                return FALSE;
            }

        }
        /* possible candidate for left child */
        else if(!strncmp(temp->file_desc->file_name,(*fresh)->file_desc->file_name,strlen(temp->file_desc->file_name)))
        {
            if(strcmp(temp->file_desc->file_name,(*fresh)->file_desc->file_name))
            {

                if(temp->leftchild)
                    return insert_pos(&(temp->leftchild),fresh);
                else
                {
                    temp->leftchild=*fresh;
                    return TRUE;
                }
            }
            else
            {
                /* Replace dummy node with actual node */
                if(-1 != (*fresh)->file_desc->loc_number && -1 == temp->file_desc->loc_number)
                {
                    free(temp->file_desc);
                    temp->file_desc=(*fresh)->file_desc;
                    return TRUE;

                }
                /* Duplicate */
                else
                {
                    free((*fresh)->file_desc);
                    free(*fresh);
                    return FALSE;
                }
            }
        }
    }

}



/*
*   Description :   Creates a node and then calls insert_pos for insertion
*                   when available
*   Input       :   Head node ,File descriptor to be attached
*   Output      :   True(1) if successful, FALSE(0) otherwise
*/
int insert_node(narry_tree_t **head,file_descriptor_t **file_desc)
{
    narry_tree_t *temp, *fresh;

    create_node(&fresh,file_desc);
    temp=*head;

    if(temp->leftchild==NULL)
    {
        temp->leftchild=fresh;
        temp->rightsibling=NULL;
        return TRUE;
    }
    else
    {

        /* move to 1st node */
        temp=temp->leftchild;

        /* insert at correct place */
        return insert_pos(&temp,&fresh);

    }
}


/*
*   Description :   Display the tree : level then left child
*   Input       :   NOde to begin display with
*   Output      :   NA
*/
void display(narry_tree_t  *head)
{
    narry_tree_t *temp;

    temp=head;

    if(temp)
    {
        printf("%s[%d]",temp->file_desc->file_name,temp->file_desc->loc_number);
        if(temp->rightsibling)
        {
            printf("->\t");
            display(temp->rightsibling);
        }
        if(temp->leftchild)
        {
            printf("\n(%s)",temp->file_desc->file_name);
            display(temp->leftchild);
        }

    }

}



/*
*   Description :   Tokenizes the node's name and inserts with the help of insert_node()
*                   file_descriptor.loc_number = -1 signifies dummy node
*                   file_descriptor.loc_number = -2 signifies root node
*   Input       :   Head Node, file descriptor to be attached
*   Output      :   NA
*/
int tokenizer(narry_tree_t **head,file_descriptor_t **file_desc)
{

    file_descriptor_t *fd_dummy;
    file_descriptor_t *fd_temp;
    int flag=0; //flag=1 refers to node insertion
    char str[30] ;
    char delims[] = "/";
    char *result = NULL;
    char temp1[50];

    fd_temp=*file_desc;

    /* Tokenizer and dummy node insertion */
    strcpy(str,fd_temp->file_name);
    result = strtok( str, delims );
    strcpy(temp1,result);

    /* If File/Directory is not at root level */
    if(strcmp(fd_temp->file_name,temp1))
    {

        create_file_descriptor(&fd_dummy,temp1,-1) ;

        if (insert_node(head,&fd_dummy)==TRUE)
            flag=1;
        else
        {
            free(fd_dummy);
            flag=0;
        }
        /* Insert dummy nodes for all levels above the required file */
        while( result != NULL && strcmp(fd_temp->file_name,temp1) )
        {
            result = strtok( NULL, delims );
            if(result)
            {
                strcat(temp1,"/");
                strcat(temp1,result);
            }
            create_file_descriptor(&fd_dummy,temp1,-1) ;
            /* Do not insert if reached the required level */
            if ( strcmp(fd_temp->file_name,temp1) && insert_node(head,&fd_dummy)==TRUE)
                flag=1;
            else
            {
                free(fd_dummy);
                flag=0;
            }

        }
    }
    /* Insert the actual node */
    if (insert_node(head,&fd_temp)==TRUE)
        flag=1;
    else
    {
        printf("\n Could not create node actual\n");
        flag=0;
    }


    /* return statements */
    if(flag!=1)
        return FALSE;
    else return TRUE;
}


/*
*   Description :   Recursively deallocate the tree nodes before unmounting
*   Input       :   Head Node
*   Output      :   NA
*/
void free_tree(narry_tree_t  *head)
{
    narry_tree_t *temp;

    temp=head;
    if(temp)
    {
        if(temp->rightsibling)
        {
            free_tree(temp->rightsibling);
        }
        if(temp->leftchild)
        {
            free_tree(temp->leftchild);
        }
        free(temp);

    }
}

