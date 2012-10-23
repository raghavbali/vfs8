/*************************************************************************************************************
* File Name 		:	file_system.c
* Description		:	file_system functions to be used in integrate.c
* Author		    :	Raghav Bali
* Date			    :	Oct 11 2012
* Version		    :	0.2
* Updates           :
**************************************************************************************************************/

#include "../include/main.h"

/*
*   Description :   This function initializes the narray tree
*   Input       :   NA
*   Output      :   True(1) if successful, FALSE(0) otherwise
*/
int init_tree()
{
    file_descriptor_t *fd_temp;
    int i;

    /* create head node for tree */
    insert_file_descriptor("/","/",1,0);
    fd_temp=&(/*vfs_header.*/file_descriptors[0]);

    if(create_node(&head,&fd_temp)==TRUE)
    {
        fd_temp=NULL;
        /* creating n-arry tree */
        for(i=1; i</*MAXFILEDESCRIPTORS*/max_file_descriptors; i++)
        {
            if(/*vfs_header.*/free_list[i]!='0')
            {
                fd_temp=&(/*vfs_header.*/file_descriptors[i]);
                /* Actual Node insertion */
                if (tokenizer(&head,&fd_temp)==TRUE);
                else
                    return FALSE;
            }

        }
        return TRUE;
    }
    else
        return FALSE;
}


/*
*   Description :   This function inserts into fd array and update narray tree
*   Input       :   name of the directory, type : 1-directory and 2-file
*   Output      :   True(1) if successful, FALSE(0) otherwise
*/
int insert(char* name, char *path, int type)
{
    int index=0;
    int flag=0;
    file_descriptor_t *fd_temp;
   // printf("\nInsert : with name=%s and path=%s\n",name,path);
    /* search the free list and return the index of the first free block */
    if ((index=search_free_list(name,path,type)))
    {
        //printf("Found a free slot at position %d\n",index);
        if(insert_file_descriptor(name,path,type,index)==TRUE)
        {
            fd_temp=NULL;
            fd_temp=&(/*vfs_header.*/file_descriptors[index]);
            /* Actual Node insertion into the tree*/
            if (insert_node(&head,&fd_temp)==TRUE)
            {
               // printf("Node inserted for %s at %p\n",fd_temp->loc_path,fd_temp);
                flag=TRUE;
            }
            /* node could not be inserted */
            else
            {
                flag=FALSE;
            }
        }
        else
        {
            flag=FALSE;
        }
    }
    else
        flag=FALSE;
    return flag;
}

/*
*   Description :   This function inserts into fd array after tokenizing(directory at each level)
*   Input       :   name of the directory, type : 1-directory and 2-file
*   Output      :   True(1) if successful, FALSE(0) otherwise
*/
int insert_tokenized_file_descriptor(char* name, char *path, int type)
{
    file_descriptor_t *fd_temp;
    int flag=0; //flag=1 refers to node insertion
    char str[100] ;
    char delims[] = "/";
    char *result = NULL;
    char temp1[100];

    /* to counter the addtional '/' in the beginning of the path */
    if(strlen(path)!=1) path++;
    // if(strcmp(path,"/"))
    strcat(path,"/");
    //  if(strcmp(path,"/"))
    strcat(path,name);
    //   else
    //     strcpy(path,name);
    /* cannot create another root directory */
    if(strcmp(path,"/"))
    {

        /* Tokenizer and dummy node insertion */
        strcpy(str,path);
        result = strtok( str, delims );
        strcpy(temp1,result);
        /* If File/Directory is not at root level */
        if(strcmp(path,temp1))
        {
            //create_file_descriptor(&fd_dummy,temp1,-1) ;
            if (insert(result,temp1,type)==TRUE)
                flag=1;
            else
            {
                //free(fd_dummy);
                flag=0;
            }
            /* Insert dummy nodes for all levels above the required file */
            while( result != NULL && strcmp(path,temp1) )
            {
                result = strtok( NULL, delims );

                if(result)
                {
                    strcat(temp1,"/");
                    strcat(temp1,result);
                }
                //create_file_descriptor(&fd_dummy,temp1,-1) ;
                /* Do not insert if reached the required level */
                //printf("\nInside while result=%s temp1=%s\n",result,temp1);
                if ( strcmp(path,temp1) && insert(result,temp1,type)==TRUE)
                    flag=1;
                else
                {
                    //free(fd_dummy);
                    flag=0;
                }

            }
        }
        /* Insert the actual node */
        //printf("\n\n\nInserting actual node name=%s path=%s",name,path);
        if(strlen(temp1)>0 && insert(name, path, type))flag=1;
        /* return statements */
    }
    else
        flag=FALSE;

    if(flag!=1)
        return FALSE;
    else return TRUE;
}


/*
*   Description :   Insert and update file descriptor array
*   Input       :   name of the directory, type : 1-directory and 2-file and index
*   Output      :   True(1) if successful, FALSE(0) otherwise
*/
int insert_file_descriptor(char* name, char *path,int type,int index)
{
    if(index</*MAXFILEDESCRIPTORS*/max_file_descriptors && strlen(name)>0)
    {
        /*vfs_header.*/free_list[index]='1';
        strcpy(/*vfs_header.*/file_descriptors[index].file_name,name);
        strcpy(file_descriptors[index].loc_path,path);
        /*vfs_header.*/
        file_descriptors[index].loc_number=index;
        /*vfs_header.*/
        file_descriptors[index].file_type=type;
        vfs_header.used_file_descriptors++;
        return TRUE;
    }
    else
        return FALSE;
}


/*
*   Description :   search the free list
*   Input       :   name of the directory, type : 1-directory and 2-file
*   Output      :   index of the first free block or FALSE(0)
*/
int search_free_list(char *name,char *path, int type)
{
    int i=0;
    int flag=FALSE;
    file_descriptor_t *fd_temp;

    /* create root node in tree if this is the first directory/file */
    if(head==NULL)
    {
        flag=FALSE;
    }
    /* head node already present/ not the first directory/file to be inserted */
    else
        flag=TRUE;

    if(flag)
    {
        flag=FALSE;
        create_file_descriptor(&fd_temp,name,path,-1);
        if ((search_node(&head->leftchild,&fd_temp))==-1)
        {
            for(i=1; i</*MAXFILEDESCRIPTORS*/max_file_descriptors; i++)
            {
                free(fd_temp);
                fd_temp=NULL;
                /* search for an empty slot */
                if(/*vfs_header.*/free_list[i]=='0')
                {
                    flag=i;
                    break;

                }
                /* if file_descriptor array could not be updated */
                else
                {
                    flag=FALSE;
                }
            }
        }

    }
    else
    {
        flag=FALSE;
        free(fd_temp);
    }
    return flag;
}


/*
*   Description :   updates free list and markes all dummy nodes as free
*   Input       :   NA
*   Output      :   NA
*/
void update_free_list()
{
    int i=0;
    int flag=FALSE;

    /* create root node in tree if this is the first directory/file */
    if(head==NULL)
    {
        flag=FALSE;
    }
    /* head node already present/ not the first directory/file to be inserted */
    else
        flag=TRUE;

    if(flag)
    {
        for(i=1; i</*MAXFILEDESCRIPTORS*/max_file_descriptors; i++)
        {

            /* search for an empty slot */
            if(/*vfs_header.*/file_descriptors[i].loc_number==-1)
            {
                /* add entry to file_descriptor array */
                /*vfs_header.*/free_list[i]='0';
                /*vfs_header.*/
                file_descriptors[i].loc_number=0;
                vfs_header.used_file_descriptors--;
            }
        }


    }

}



/*
*   Description :   delete a file descriptor
*   Input       :   name of the directory, type : 1-directory and 2-file
*   Output      :   True(1) if successful, FALSE(0) otherwise
*/
int del(char *name,int type)
{
    int loc_number=0;
    file_descriptor_t *fd_temp;
    name++;
    printf("\n%s\n",name);

    if(strcmp(name,"/"))
    {

        create_file_descriptor(&fd_temp,name,name,-1);

        if ((loc_number=search_node(&head->leftchild,&fd_temp))!=-1)
        {

            free(fd_temp);
            fd_temp=NULL;
            fd_temp=&(/*vfs_header.*/file_descriptors[loc_number]);
            if(delete_node(&head->leftchild,&fd_temp))
            {
                /*vfs_header.*/free_list[loc_number]='0';
                vfs_header.used_file_descriptors--;
                update_free_list();
                return TRUE;
            }
            else
                return FALSE;
        }
        else
            return FALSE;
    }
    else
        return FALSE;
}

/*
*   Description :   list the directory structure
*   Input       :   NA
*   Output      :   NA
*/
void list_directory()//char *name)
{
    int loc_number=0;
    file_descriptor_t *fd_dummy;
    narry_tree_t *temp;
    /*
        create_file_descriptor(&fd_dummy,name,-1);
        temp=head;
        printf("\n%s %d\n",head->file_desc->file_name,head->file_desc->loc_number);
        if ((loc_number=search_nodes(temp->leftchild,&fd_dummy))!=-1)
        {
            printf("\n%s %d\n",temp->file_desc->file_name,temp->file_desc->loc_number);
            free(fd_dummy);
            fd_dummy=NULL;
            //fd_dummy=&(vfs_header.file_descriptors[loc_number]);*/
    display(head);
    //  }
}


void fd_array_dump(char condition)
{
    int i;

    printf("\n\n For condition : %c :\n",condition);
    printf("\n\n Index\t\tloc_path\t\tfile_name\t\tloc_number");
    for(i=0; i<max_file_descriptors; i++)
    {
        /* search for an empty slot */
        if(free_list[i]==condition)
        {
            printf("\n\n %d\t\t%-30s\t\t%-30s\t\t%d",i,file_descriptors[i].loc_path,file_descriptors[i].file_name,file_descriptors[i].loc_number);
        }
    }
}


