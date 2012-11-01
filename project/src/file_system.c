/*************************************************************************************************************
* File Name 		:	file_system.c
* Description		:	file_system functions to be used in integrate.c
* Author		    :	Raghav Bali
* Date			    :	Oct 11 2012
* Version		    :	0.3
* Updates           :   [Raghav Bali Oct 11 2012]: Added methods to update free list, move, delete and list
                        directories and files.
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
                //printf("Node inserted for %s at %p\n",fd_temp->loc_path,fd_temp);
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
int insert_tokenized_file_descriptor(char* P1, char *P2, int type)
{
    file_descriptor_t *fd_temp;
    int flag=0; //flag=1 refers to node insertion
    char str[100] ;
    char delims[] = "/";
    char *result = NULL;
    char temp1[100];
    char name[100],path[100];

    strcpy(name,P1);
    strcpy(path,P2);

    /* to counter the addtional '/' in the beginning of the path */
    // if(strlen(path)!=1) path++;
    if(strcmp(path,"/"))
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
        strcpy(temp1,"/");
        strcat(temp1,result);
        //printf("\nBefore tokenize temp1=%s and result=%s\n",temp1,result);
        /* If File/Directory is not at root level */
        if(strcmp(path,temp1))
        {
            //create_file_descriptor(&fd_dummy,temp1,-1) ;
            if (insert(result,temp1,type)==TRUE)
                flag=SUCCESS;
            else
            {
                //free(fd_dummy);
                flag=1;/* unable to create new dir */
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
                    flag=SUCCESS;
                else
                {
                    //free(fd_dummy);
                    flag=1;/* unable to create new dir */
                }

            }
        }
        /* Insert the actual node */
        //printf("\n\n\nInserting actual node name=%s path=%s",name,path);
        if(strlen(temp1)>0 && insert(name, path, type))
            flag=SUCCESS;
        else
            flag=3;/* directory already exists */
        /* return statements */
    }
    else
        flag=3;/* directory already exists */

    if(flag!=1000)
        return flag;
    else return SUCCESS;
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
    int status=0;
    // name++;

    if(strcmp(name,"/"))
    {
        create_file_descriptor(&fd_temp,name,name,-1);
printf("\nloc=%d and name=%s\n",fd_temp->loc_number,fd_temp->loc_path);
        if ((loc_number=search_node(&head->leftchild,&fd_temp))!=-1)
        {
            free(fd_temp);
            fd_temp=NULL;
            fd_temp=&(/*vfs_header.*/file_descriptors[loc_number]);
            printf("\nloc=%d and name=%s\n",fd_temp->loc_number,fd_temp->loc_path);
            status=delete_node(&head->leftchild,&fd_temp);
            if(status==1)
            {
                /*vfs_header.*/free_list[loc_number]='0';
                vfs_header.used_file_descriptors--;
                update_free_list();
                return SUCCESS;
            }
            else if(status==2)
                return 2;/* directory is not empty */
            else
                return 1;/* directory/path not found */
        }
        else
            return 1;/* directory/path not found */
    }
    else
        return 2;/* cannot delete root */
}



/*
*   Description :   list the directory structure into a specified file
*   Input       :   Directory Path, Flag (0-Non recirsive, 1-Recirsive), Text File path to print output to
*   Output      :   NA
*/
void list_directory(char *dir_path,int flag,char *text_file_path)
{
    file_descriptor_t *fd_temp;
    narry_tree_t *source_ptr;
    FILE *fptr;

    source_ptr=head;
    create_file_descriptor(&fd_temp,dir_path,dir_path,-1);
    /* find source */
    if((source_ptr=(narry_tree_t *)find_node(&source_ptr,&fd_temp))!=NULL)
    {
        //free(fd_temp);
        if((fptr=fopen(text_file_path,"w")) == NULL)
        {
            printf("\nError occured in file opening\n");
            //return FALSE;
        }
        else
        {
            if(source_ptr)
            {
                fprintf(fptr,"%s\n",source_ptr->file_desc->loc_path);
                list_dir(source_ptr->leftchild,flag,fptr,1);
                fclose(fptr);
                //free(source_ptr);
            }
        }

    }
    else
    {
        printf("\nNo such directory found\n");
    }
}


/*
*   Description :   Move a directory from source path to destination path
*   Input       :   Source directory path, destination directory path
*   Output      :   True for Success and False for Failure
*/
int move_dir(char *src, char *dest)
{
    file_descriptor_t *fd_temp_src,*fd_temp_dest,*fd_temp;
    narry_tree_t *source_ptr,*dest_ptr;
    char name[100];


    /* if src is missing */
    if(!strlen(src))
        return 3;
    /* if destination is missing */
    if(!strlen(dest))
        return 4;

    source_ptr=head;
    //source_ptr=source_ptr->leftchild;

    create_file_descriptor(&fd_temp_src,src,src,-1);

    /* find source */
    if((source_ptr=(narry_tree_t *)find_node(&source_ptr,&fd_temp_src))!=NULL)
    {
        dest_ptr=head;

        create_file_descriptor(&fd_temp_dest,dest,dest,-1);
        /* find destination */
        if((dest_ptr=(narry_tree_t *)find_node(&dest_ptr,&fd_temp_dest))!=NULL)
        {
            strcpy(name,"/");
            if(strcmp(source_ptr->file_desc->file_name,"/"))
                strcat(name,source_ptr->file_desc->file_name);

            create_file_descriptor(&fd_temp,source_ptr->file_desc->file_name,name,-1);
            /* add a method to check if destination is a file. return failure if it is a file*/

            /* check if destination already has same named file/dir as is the source */
            if ((search_node(&dest_ptr->leftchild,&fd_temp))!=-1)
            {
                if(fd_temp_src)
                    free(fd_temp_src);
                if(fd_temp_dest)
                    free(fd_temp_dest);
                if(fd_temp)
                    free(fd_temp);
                return 5;/* destination path already has specified directory */
            }
            if(update_pointers(&source_ptr))
            {
                move_node(&source_ptr,&dest_ptr);
                update_familypaths(&source_ptr);
            }

        }
        else
        {
            /* destination not found */
            free(fd_temp_src);
            free(fd_temp_dest);
            return 2;
        }
    }
    else
    {
        /* source not found */
        free(fd_temp_src);
        return 1;
    }
    if(fd_temp_src)
        free(fd_temp_src);
    if(fd_temp_dest)
        free(fd_temp_dest);
    if(fd_temp)
        free(fd_temp);
    return SUCCESS;
}


/*
*   Description :   Create a file in vfs from a file in the main OS with the specified file name
*   Input       :   Destination directory path, filename(to be created), filepath (to read data from)
*   Output      :   True for Success and False for Failure
*/
int create_file(char *dest_dir_path,char *file_name,char *data_file_path)
{
    //file_descriptor_t *fd_temp;
    //narry_tree_t *source_ptr;
    char fullpath[100];
    int index=0;
    unsigned int metaheader_size=0;

    strcpy(fullpath,dest_dir_path);
    if(strcmp(fullpath,"/"))
        strcat(fullpath,"/");
    strcat(fullpath,file_name);


    /* find source */
    if(!(index=search_free_list(file_name,fullpath,2)))
    {
        return FALSE;
    }
    else
    {
        if(insert(file_name, fullpath, 2)==TRUE)
        {
            //index=source_ptr->file_desc->loc_number;
            if(index!=0)
            {
                metaheader_size=sizeof(vfs_header)+sizeof(char)*max_file_descriptors+sizeof(file_descriptor_t)*max_file_descriptors;
                if(write_block(read_text_from_user_file ( data_file_path ),metaheader_size ,index)==TRUE)
                {
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
}


/*
*   Description :   Copy a file from source path to destination path
*   Input       :   Source file path, destination directory path
*   Output      :   True for Success and False for Failure
*/
int copy_file(char *src, char *dest)
{
    file_descriptor_t *fd_temp;
    narry_tree_t *source_ptr,*dest_ptr;
    char fullpath[100];
    int index=0;
    unsigned int metaheader_size=0;

    source_ptr=head;
    //source_ptr=source_ptr->leftchild;

    create_file_descriptor(&fd_temp,src,src,-1);

    /* find source */
    if((source_ptr=(narry_tree_t *)find_node(&source_ptr,&fd_temp))!=NULL)
    {
        free(fd_temp);
        dest_ptr=head;

        create_file_descriptor(&fd_temp,dest,dest,-1);
        /* find destination */
        if((dest_ptr=(narry_tree_t *)find_node(&dest_ptr,&fd_temp))!=NULL)
        {
            /* add a method to check if destination is a file. return failure if it is a file*/
            strcpy(fullpath,dest_ptr->file_desc->loc_path);
            if(strcmp(fullpath,"/"))
                strcat(fullpath,"/");
            strcat(fullpath,source_ptr->file_desc->file_name);

            /* find free index */
            if(!(index=search_free_list(source_ptr->file_desc->file_name,fullpath,2)))
            {
                return FALSE;
            }
            else
            {
                if(insert(source_ptr->file_desc->file_name, fullpath, 2)==TRUE)
                {
                    if(index!=0)
                    {
                        metaheader_size=sizeof(vfs_header)+sizeof(char)*max_file_descriptors+sizeof(file_descriptor_t)*max_file_descriptors;
                        if(write_block(read_block ( metaheader_size ,source_ptr->file_desc->loc_number ),metaheader_size ,index)==TRUE)
                        {
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

        }
        else
        {
            /* destination not found */
            free(fd_temp);
            return 0;
        }

    }
    else
    {
        /* source not found */
        free(fd_temp);
        return 0;
    }

    if(fd_temp)
        free(fd_temp);
    return 1;
}



/* This is a debuggin function to view FD array data */
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





