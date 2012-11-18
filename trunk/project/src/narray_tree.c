/*************************************************************************************************************
* File Name 		:	narray_tree.h
* Description		:	This contains implementation of n-arry functions to insert and display
* Author		    :	Raghav Bali
* Date			    :	Sep 21 2012
* Version		    :	1.1
* Updates           :   [Raghav Bali Oct 11 2012]: Added search_node(), delete_node()
                        [Raghav Bali Oct 08 2012]: Added create_node(), free_tree(),
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
        (*node)->leftsibling=NULL;
        (*node)->parent=NULL;
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
int create_file_descriptor(file_descriptor_t **file_desc,char *name,char *path,int loc_number)
{
    if((*file_desc)=(file_descriptor_t*)malloc(sizeof(file_descriptor_t)))
    {
        strcpy((*file_desc)->file_name,name);
        strcpy((*file_desc)->loc_path,path);
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
        if(strncmp(temp->file_desc->loc_path,(*fresh)->file_desc->loc_path,strlen(temp->file_desc->loc_path))
                || (strlen((*fresh)->file_desc->loc_path) > strlen(temp->file_desc->loc_path) && (*fresh)->file_desc->loc_path[strlen(temp->file_desc->loc_path)]!='/'))
        {
            if(strcmp(temp->file_desc->loc_path,(*fresh)->file_desc->loc_path))
            {

                if(temp->rightsibling)
                    return insert_pos(&(temp->rightsibling),fresh);
                else
                {
                    temp->rightsibling=*fresh;
                    (*fresh)->leftsibling=temp;
                    (*fresh)->parent=temp->parent;
                    return TRUE;
                }
            }
            else
            {
                free(*fresh);
                return FALSE;
            }

        }
        /* possible candidate for left child */
        else if(!strncmp(temp->file_desc->loc_path,(*fresh)->file_desc->loc_path,strlen(temp->file_desc->loc_path)))
        {
            if(strcmp(temp->file_desc->loc_path,(*fresh)->file_desc->loc_path))
            {

                if(temp->leftchild)
                    return insert_pos(&(temp->leftchild),fresh);
                else
                {
                    temp->leftchild=*fresh;
                    (*fresh)->parent=temp;
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
    //printf("\ninsert_node head=%s and fd =%s\n",(*head)->file_desc->loc_path,(*file_desc)->loc_path);
    if(temp->leftchild==NULL)
    {
        temp->leftchild=fresh;
        temp->rightsibling=NULL;
        fresh->parent=temp;
        fresh->leftsibling=NULL;
        fresh->leftchild=NULL;
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
        printf("%s[%d]",temp->file_desc->loc_path,temp->file_desc->loc_number);
        if(temp->rightsibling)
        {
            printf("->\t");
            display(temp->rightsibling);
        }
        if(temp->leftchild)
        {
            printf("\n(%s)",temp->file_desc->loc_path);
            display(temp->leftchild);
        }

    }

}


/*
*   Description :   Display the tree : level then left child
*   Input       :   Node to begin display with, flag (0-non recursive and 1-recursive), file pointer, level(0-base)
*   Output      :   NA
*/
void list_dir(narry_tree_t  *head,int flag,FILE *fptr,int level)
{
    narry_tree_t *temp,*temp1;
    temp=head;
    int i;
    if(temp)
    {
        i = level;
        temp1=temp;

        for (i=level; i>0; i--)
        {
            if (i == 1)
                if (temp->rightsibling == NULL)
                    fprintf(fptr,"└── ");
                else
                    fprintf(fptr,"├── ");
            else if (temp->rightsibling != NULL)
                fprintf(fptr,"│   ");
            else
                fprintf(fptr,"|   ");
        }
        fprintf(fptr,"%s\n",temp->file_desc->loc_path);
        if(temp->leftchild!=NULL && flag==1)
        {
            //fprintf(fptr,"\n\t");//,temp->file_desc->loc_path);
            list_dir(temp->leftchild,flag,fptr,level+1);
        }
        if(temp->rightsibling)
        {
            //fprintf(fptr,"\t\t");
            list_dir(temp->rightsibling,flag,fptr,level);
        }

    }

}



/*
*   Description :   Tokenizes the node's name and inserts with the help of insert_node()
*                   file_descriptor.loc_number = -1 signifies dummy node
*                   file_descriptor.loc_number = -2 signifies root node
*   Input       :   Head Node, file descriptor to be attached
*   Output      :   True(1) if successful, FALSE(0) otherwise
*/
int tokenizer(narry_tree_t **head,file_descriptor_t **file_desc)
{

    file_descriptor_t *fd_dummy;
    file_descriptor_t *fd_temp;
    int flag=0; //flag=1 refers to node insertion
    char str[100] ;
    char delims[] = "/";
    char *result = NULL;
    char temp1[100];

    fd_temp=*file_desc;

    /* Tokenizer and dummy node insertion */
    strcpy(str,fd_temp->loc_path);
    result = strtok( str, delims );
    strcpy(temp1,"/");
    strcat(temp1,result);
    //printf("\ninside tokenizer for loc_path=%s temp1=%s and index=%d\n",fd_temp->loc_path,temp1,fd_temp->loc_number);
    /* If File/Directory is not at root level */
    if(strcmp(fd_temp->loc_path,temp1))
    {

        create_file_descriptor(&fd_dummy,result,temp1,-1) ;

        if (insert_node(head,&fd_dummy)==TRUE)
            flag=1;
        else
        {
            free(fd_dummy);
            flag=0;
        }
        /* Insert dummy nodes for all levels above the required file */
        while( result != NULL && strcmp(fd_temp->loc_path,temp1) )
        {
            result = strtok( NULL, delims );
            if(result)
            {
                strcat(temp1,"/");
                strcat(temp1,result);
            }
            create_file_descriptor(&fd_dummy,result,temp1,-1) ;
            /* Do not insert if reached the required level */
            if ( strcmp(fd_temp->loc_path,temp1) && insert_node(head,&fd_dummy)==TRUE)
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


/*
*   Description :   Recursively deallocate the tree nodes when delete is performed
*   Input       :   Head Node of the subtree
*   Output      :   NA (marks each node's loc_number as -1 : for deletion
*/
void delete_tree(narry_tree_t  *head)
{
    narry_tree_t *temp;

    temp=head;
    if(temp)
    {

        if(temp->rightsibling)
        {
            delete_tree(temp->rightsibling);
        }
        if(temp->leftchild)
        {
            delete_tree(temp->leftchild);
        }
        /* mark for deletion */
        temp->file_desc->loc_number=-1;
        free(temp);

    }
}


/*
*   Description :   Delete the specified tree node
*   Input       :   Head node, File Descriptor to be removed
*                   --Removes the complete subtree rooted at specified node
                    Removes the node if it is terminal
*                   Including the node itself.
*   Output      :   TRUE(1),FALSE(0) and NotPossible(2)
*/
int delete_node(narry_tree_t  **head,file_descriptor_t **file_desc)
{
    narry_tree_t *temp;

    temp=*head;

    if(temp)
    {
        /* possible candidate for right child */
        if(strncmp(temp->file_desc->loc_path,(*file_desc)->loc_path,strlen(temp->file_desc->loc_path))
                || (strlen((*file_desc)->loc_path) > strlen(temp->file_desc->loc_path) && (*file_desc)->loc_path[strlen(temp->file_desc->loc_path)]!='/'))
        {
            if(strcmp(temp->file_desc->loc_path,(*file_desc)->loc_path))
            {
                if(temp->rightsibling)
                {
                    return delete_node(&(temp->rightsibling),file_desc);
                }
                else
                {
                    return FALSE; //node to be deleted does not exist.
                }
            }
            else
            {
                /* Check: this case might never arise!!! */
                temp->parent->leftchild=temp->leftsibling;
                temp->leftsibling->rightsibling=temp->rightsibling;
                delete_tree(temp->leftchild);
                /* detach the node */
                temp->leftchild=NULL;
                temp->leftsibling=NULL;
                temp->parent=NULL;
                temp->rightsibling=NULL;
                delete_tree(temp);
                return TRUE;
            }

        }
        /* possible candidate for left child */
        else if(!strncmp(temp->file_desc->loc_path,(*file_desc)->loc_path,strlen(temp->file_desc->loc_path)))
        {
            if(strcmp(temp->file_desc->loc_path,(*file_desc)->loc_path))
            {
                if(temp->leftchild)
                {
                    return delete_node(&(temp->leftchild),file_desc);
                }
                else
                {
                    return FALSE;// node to be delted does not exist.
                }
            }
            else
            {
                /* Check if subtree is empty or not */
                if(temp->leftchild==NULL)
                {
                    /* if the node to be deleted is immidiate left child of its parent */
                    if(temp->parent->leftchild!=NULL && temp!=NULL && !strcmp(temp->parent->leftchild->file_desc->loc_path,temp->file_desc->loc_path))
                    {
                        if(temp->rightsibling)
                        {
                            temp->parent->leftchild=temp->rightsibling;
                            temp->rightsibling->leftsibling=NULL;
                        }
                        else
                            temp->parent->leftchild=NULL;
                    }

                    if(temp->leftsibling!= NULL)
                    {
                        if(temp->rightsibling==NULL)
                            temp->leftsibling->rightsibling=NULL;
                        else
                        {
                            temp->leftsibling->rightsibling=temp->rightsibling;
                            temp->rightsibling->leftsibling=temp->leftsibling;
                        }
                    }

                    /* delete the left sub tree of the node */

                    //delete_tree(temp->leftchild);

                    /* detach the node */
                    temp->leftchild=NULL;
                    temp->leftsibling=NULL;
                    temp->parent=NULL;
                    temp->rightsibling=NULL;

                    /* delete the node itself */
                    delete_tree(temp);
                    return TRUE;
                }
                else
                    return 2;/* Directory is not empty */
            }
        }
    }
}



/*
*   Description :   Search the tree
*   Input       :   Head node, filepath
*   Output      :   File descriptor's loc_number, else -1(dummy)
*/
int search_node(narry_tree_t  **head,file_descriptor_t **file_desc)
{
    narry_tree_t *temp;
    // printf("\nSearch node with value %s %s\n",(*file_desc)->loc_path,(*file_desc)->file_name);
    temp=*head;
//    printf("\ntemp=%s\n",temp->file_desc->loc_path);
    if(temp)
    {
        /* possible candidate for right child */
        if(strncmp(temp->file_desc->loc_path,(*file_desc)->loc_path,strlen(temp->file_desc->loc_path))
                || (strlen((*file_desc)->loc_path) > strlen(temp->file_desc->loc_path) && (*file_desc)->loc_path[strlen(temp->file_desc->loc_path)]!='/'))
        {
            if(strcmp(temp->file_desc->loc_path,(*file_desc)->loc_path))
            {
                if(temp->rightsibling)
                {
                    return search_node(&(temp->rightsibling),file_desc);
                }
                else
                {
                    return -1; //node to be ssearched does not exist.
                }
            }
            else
            {
                /* Check: this case might never arise!!! */
                file_desc=&temp->file_desc;
                return (*file_desc)->loc_number;
            }

        }
        /* possible candidate for left child */
        else if(!strncmp(temp->file_desc->loc_path,(*file_desc)->loc_path,strlen(temp->file_desc->loc_path)))
        {
            // printf("\nLeft child found temp=%s and fd=%s\n",temp->file_desc->loc_path,(*file_desc)->loc_path);
            if(strcmp(temp->file_desc->loc_path,(*file_desc)->loc_path))
            {
                if(temp->leftchild)
                {
                    return search_node(&(temp->leftchild),file_desc);
                }
                else
                {
                    return -1;// node to be searched does not exist.
                }
            }
            else
            {
                file_desc=&temp->file_desc;
                return (*file_desc)->loc_number;
            }
        }
    }
    else
        return -1;
}



/*
*   Description :   Search the tree
*   Input       :   Head node, file descriptor to be searched
*   Output      :   Pointer to narray node found
*/
narry_tree_t* find_node(narry_tree_t  **temp,file_descriptor_t **file_desc)
{
    if(*temp)
    {
        /* possible candidate for right child */

        if(strncmp((*temp)->file_desc->loc_path,(*file_desc)->loc_path,strlen((*temp)->file_desc->loc_path))
                || (strlen((*file_desc)->loc_path) > strlen((*temp)->file_desc->loc_path) && (*file_desc)->loc_path[strlen((*temp)->file_desc->loc_path)]!='/'))
        {
            if(strcmp((*temp)->file_desc->loc_path,(*file_desc)->loc_path))
            {
                if((*temp)->rightsibling)
                {
                    temp=&((*temp)->rightsibling);
                    return (narry_tree_t *)find_node(temp,file_desc);
                }
                else
                {
                    if(!strcmp((*temp)->file_desc->loc_path,"/"))
                    {
                        temp=&((*temp)->leftchild);
                        return (narry_tree_t *)find_node(temp,file_desc);
                    }
                    else
                        return NULL;//-1; //node to be ssearched does not exist.
                }
            }
            else
            {
                /* Check: this case might never arise!!! */
                file_desc=&(*temp)->file_desc;
                return (narry_tree_t *)(*temp);//return (*file_desc)->loc_number;
            }

        }
        /* possible candidate for left child */
        else if(!strncmp((*temp)->file_desc->loc_path,(*file_desc)->loc_path,strlen((*temp)->file_desc->loc_path)))
        {
            if(strcmp((*temp)->file_desc->loc_path,(*file_desc)->loc_path))
            {
                if((*temp)->leftchild)
                {
                    temp=&((*temp)->leftchild);
                    return (narry_tree_t *)find_node(temp,file_desc);
                }
                else
                {
                    return NULL;//-1;// node to be searched does not exist.
                }
            }
            else
            {
                file_desc=&(*temp)->file_desc;
                return (narry_tree_t *)(*temp);//return (*file_desc)->loc_number;
            }
        }
    }
    else
        return NULL;//-1;
}



/*
*   Description :   Move a node from source path to destination path
*   Input       :   Source pointer, Destination Pointer
*   Output      :   NA
*/
void move_node(narry_tree_t  **source,narry_tree_t  **destination)
{

    if((*destination))
    {
        /* if destination has a left sub tree */
        if((*destination)->leftchild)
        {
            (*source)->rightsibling=(*destination)->leftchild;
            (*source)->rightsibling->leftsibling=(*source);
            (*destination)->leftchild=(*source);
            (*source)->parent=(*destination);
        }
        /* if it does not have a left sub tree */
        else
        {
            (*destination)->leftchild=(*source);
            (*source)->parent=(*destination);
        }
    }
}


/*
*   Description :   Update pointers of narray node to be moved
*   Input       :   Source pointer to be moved
*   Output      :   True for success and False for Failure
*/
int update_pointers(narry_tree_t  **source)
{
    if((*source)->parent)
    {
        if((*source)->rightsibling==NULL)
        {
            if((*source)->parent->leftchild==(*source))
                (*source)->parent->leftchild=NULL;
            if((*source)->leftsibling)
                (*source)->leftsibling->rightsibling=NULL;
            return TRUE;

        }
        else
        {
            if((*source)->parent->leftchild==(*source))
                (*source)->parent->leftchild=(*source)->rightsibling;
            if((*source)->leftsibling)
            {
                (*source)->leftsibling->rightsibling=(*source)->rightsibling;
                (*source)->rightsibling->leftsibling=(*source)->leftsibling;
                (*source)->leftsibling=NULL;
            }

            (*source)->rightsibling=NULL;
            return TRUE;
        }
    }

    return FALSE;
}



/*
*   Description :   Update source pointer and its subtree's path after moving the node
*   Input       :   Source pointer
*   Output      :   NA
*/
void update_familypaths(narry_tree_t  **source)
{
    if((*source))
    {
        /* Copy Parent's locpath to source's loc_path */
        strcpy((*source)->file_desc->loc_path,(*source)->parent->file_desc->loc_path);
        /* append '/' at the end of source's loc path */
        if(strcmp((*source)->file_desc->loc_path,"/"))
            strcat((*source)->file_desc->loc_path,"/");
        /* add filename to source's loc_path */
        strcat((*source)->file_desc->loc_path,(*source)->file_desc->file_name);
    }

    if((*source)->leftchild)
    {
        update_familypaths(&(*source)->leftchild);

        if((*source)->leftchild->rightsibling)
        {
            update_familypaths(&(*source)->leftchild->rightsibling);
        }
    }

}


