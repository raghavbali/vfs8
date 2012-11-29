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
    insert_file_descriptor("/","/",1,0,0);
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
                if (tokenizer(&head,&fd_temp)==TRUE)
                {
                    // if(file_descriptors[i].file_type!=1)
                    //printf("\nfs:init tree for %s\n",file_descriptors[i].file_name);
                    insert_into_list(&file_descriptors[i]);
                }
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
int insert(char* name, char *path, int type,long fsize)
{
    int index=0;
    int flag=0;
    file_descriptor_t *fd_temp;
    //printf("\nInsert : with name=%s and path=%s\n",name,path);
    /* search the free list and return the index of the first free block */
    if ((index=search_free_list(name,path,type)))
    {
        //printf("Found a free slot at position %d\n",index);
        if(insert_file_descriptor(name,path,type,index,fsize)==TRUE)
        {
            fd_temp=NULL;
            fd_temp=&(/*vfs_header.*/file_descriptors[index]);
            /* Actual Node insertion into the tree*/
            if (insert_node(&head,&fd_temp)==TRUE)
            {
                //printf("Node inserted for %s at %p\n",fd_temp->loc_path,fd_temp);
                //printf("\nfs:insert for %s\n",file_descriptors[index].file_name);
                insert_into_list(&file_descriptors[index]);
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

    /* insufficient args */
    if(strlen(P1)<1 || strlen(P2)<1 /*|| type==NULL*/)
        return 0;
    /* invalid name*/
    if(strstr(P1,"/")!=NULL)
        return 2;

    /* check if path starts with a leading /, else pre-pend it */
    if(P2[0]!=delims[0])
    {
        //strcpy(path,"/");
        //strcat(path,P2);
        return 0; // path does not begin with root
    }
    else
        strcpy(path,P2);


    strcpy(name,P1);


    /* to counter the addtional '/' in the beginning of the path */
    // if(strlen(path)!=1) path++;
    if((path[strlen(path)-1]!=delims[0]) && strcmp(path,"/"))
        strcat(path,"/");

    if(strcmp(name,"/"))
        strcat(path,name);
    else
        flag=3;//     strcpy(path,name);
    //printf("\npath=%s and name=%s\n",path,name);
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
            if (insert(result,temp1,type,0)==TRUE)
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
                //printf("\nInside while result=%s temp1=%s and path=%s\n",result,temp1,path);
                if ( strcmp(path,temp1) && insert(result,temp1,type,0)==TRUE)
                    flag=SUCCESS;
                else
                {
                    //free(fd_dummy);
                    flag=1;/* unable to create new dir */
                }

            }
        }
        /* Insert the actual node */
        //printf("\n\n\nInserting actual node name=%s path=%s and flag=%d",name,path,flag);
        if(strlen(temp1)>0 && insert(name, path, type,0))
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
int insert_file_descriptor(char* name, char *path,int type,int index,long fsize)
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
        file_descriptors[index].file_size=(int)fsize;
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
            //printf("\nSearchfile:Before for:%u",max_file_descriptors);
            for(i=1; i</*MAXFILEDESCRIPTORS*/max_file_descriptors; i++)
            {
                free(fd_temp);
                fd_temp=NULL;
                //printf("\nInside for:%d=%c",i,free_list[i]);
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
        else
        {
            free(fd_temp);
            fd_temp=NULL;
            flag=FALSE;
        }

    }
    else
    {
        flag=FALSE;
        free(fd_temp);
    }
    //printf("\nsearchfile:flag=%d\n",flag);
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
int del(char *target,int type)
{
    int loc_number=0;
    file_descriptor_t *fd_temp;
    int status=0;
    char name[100];
    char delim[]="/";
    // name++;

    /* insufficient args */
    if(strlen(target)<1 /*||  type==NULL*/)
        return 0;

    /* check if last char is '/' , then do not copy it */
    if(strlen(target)!=1 && (target[strlen(target)-1]==delim[0]))
    {
        strncpy(name,target,strlen(target)-1);
        name[strlen(target)-1]='\0';
    }
    else
        strcpy(name,target);

    if(strcmp(name,"/"))
    {
        create_file_descriptor(&fd_temp,name,name,-1);
        // printf("\nloc=%d and name=%s\n",fd_temp->loc_number,fd_temp->loc_path);
        if ((loc_number=search_node(&head->leftchild,&fd_temp))!=-1)
        {
            free(fd_temp);
            fd_temp=NULL;

            if(type!=file_descriptors[loc_number].file_type)
                return 1;//trying to delete a folder using removefile.

            fd_temp=&(/*vfs_header.*/file_descriptors[loc_number]);
            //printf("\nloc=%d and name=%s\n",fd_temp->loc_number,fd_temp->loc_path);
            status=delete_node(&head->leftchild,&fd_temp);
            if(status==1)
            {
                /*vfs_header.*/free_list[loc_number]='0';
                vfs_header.used_file_descriptors--;
                deletion(file_descriptors[loc_number].file_name,file_descriptors[loc_number].loc_path);/* delete from hash */
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
int list_directory(char *dir_path,int flag,char *text_file_path)
{
    file_descriptor_t *fd_temp;
    narry_tree_t *source_ptr;
    FILE *fptr;

    /* insufficient args */
    if(!strlen(dir_path)||!strlen(text_file_path))
        return 0;

    /* invalid flag */
    if(flag!=0 && flag!=1)
        return 2;
    source_ptr=head;
    create_file_descriptor(&fd_temp,dir_path,dir_path,-1);
    /* find source */
    if((source_ptr=(narry_tree_t *)find_node(&source_ptr,&fd_temp))!=NULL)
    {
        //free(fd_temp);
        if((fptr=fopen(text_file_path,"w")) == NULL)
        {
            //printf("\nError occured in file opening\n");
            if(fd_temp)
                free(fd_temp);
            return 4;
        }
        else
        {
            if(source_ptr)
            {
                fprintf(fptr,"%s\n",source_ptr->file_desc->loc_path);
                list_dir(source_ptr->leftchild,flag,fptr,1);
                if(fd_temp)
                    free(fd_temp);
                fclose(fptr);
                return SUCCESS;
                //free(source_ptr);
            }
        }

    }
    else
    {
        if(fd_temp)
            free(fd_temp);
        return 1;
    }
}


/*
*   Description :   Move a directory from source path to destination path
*   Input       :   Source directory path, destination directory path
*   Output      :   True for Success and False for Failure
*/
int move_dir(char *src, char *dest,int type)
{
    file_descriptor_t *fd_temp_src,*fd_temp_dest,*fd_temp;
    narry_tree_t *source_ptr,*dest_ptr;
    char name[100];


    /* if src is missing */
    if(!strlen(src))
        return 0;
    /* if destination is missing */
    if(!strlen(dest))
        return 0;

    source_ptr=head;
    //source_ptr=source_ptr->leftchild;

    create_file_descriptor(&fd_temp_src,src,src,-1);
    //printf("\nmove:src=%s:fd=%s:head=%s:\n",fd_temp_src->loc_path,src,source_ptr->file_desc->loc_path);
    /* find source */
    if((source_ptr=(narry_tree_t *)find_node(&source_ptr,&fd_temp_src))!=NULL)
    {

        /* source cannot be a file */
        if(type==1)
            if(source_ptr->file_desc->file_type==2)
            {
                if(fd_temp_src)
                    free(fd_temp_src);
                fd_temp_src=NULL;
                source_ptr=NULL;
                return 4;/* source cannot be a file */
            }


        dest_ptr=head;

        create_file_descriptor(&fd_temp_dest,dest,dest,-1);
        /* find destination */
        if((dest_ptr=(narry_tree_t *)find_node(&dest_ptr,&fd_temp_dest))!=NULL)
        {
            /* fetch parent's loc path and concatinate / to the end of it */
            // printf("\nDestination found as %s\n",dest_ptr->file_desc->loc_path);
            if(dest_ptr->parent)
            {
                strcpy(name,dest_ptr->file_desc->loc_path);
                strcat(name,"/");
            }
            else
                strcpy(name,"/");
            //if(strcmp(source_ptr->file_desc->file_name,"/"))
            strcat(name,source_ptr->file_desc->file_name);

            create_file_descriptor(&fd_temp,source_ptr->file_desc->file_name,name,-1);
            /* add a method to check if destination is a file. return failure if it is a file*/

            /* check if destination already has same named file/dir as is the source */
            if(type==1)
                if ((search_node(&dest_ptr->leftchild,&fd_temp))!=-1)
                {
                    if(fd_temp_src)
                        free(fd_temp_src);
                    if(fd_temp_dest)
                        free(fd_temp_dest);
                    if(fd_temp)
                        free(fd_temp);
                    fd_temp_src=NULL;
                    source_ptr=NULL;
                    fd_temp_dest=NULL;
                    fd_temp=NULL;
                    return 5;/* destination path already has specified directory */
                }

            /* check if destination is source's child */
            //printf("\nmove:dest=%s|src=%s and type=%d and name=%c\n",dest_ptr->file_desc->loc_path,source_ptr->file_desc->loc_path,type,dest_ptr->file_desc->loc_path[strlen(source_ptr->file_desc->loc_path)]);
            if(type==1)

                if(!strncmp(dest_ptr->file_desc->loc_path,source_ptr->file_desc->loc_path,strlen(source_ptr->file_desc->loc_path)) && dest_ptr->file_desc->loc_path[strlen(source_ptr->file_desc->loc_path)]=='/')//if(!strcmp(dest_ptr->parent->file_desc->loc_path,source_ptr->file_desc->loc_path))
                {
                    if(fd_temp_src)
                        free(fd_temp_src);
                    if(fd_temp_dest)
                        free(fd_temp_dest);
                    if(fd_temp)
                        free(fd_temp);
                    fd_temp_src=NULL;
                    source_ptr=NULL;
                    fd_temp_dest=NULL;
                    dest_ptr=NULL;
                    fd_temp=NULL;
                    return 6;/* cannot move parent to child */
                }

            /* source cannot be a file */
            if(type==1)
                if(dest_ptr->file_desc->file_type==2)
                {
                    if(fd_temp_src)
                        free(fd_temp_src);
                    if(fd_temp_dest)
                        free(fd_temp_dest);
                    if(fd_temp)
                        free(fd_temp);
                    fd_temp_src=NULL;
                    source_ptr=NULL;
                    fd_temp_dest=NULL;
                    dest_ptr=NULL;
                    fd_temp=NULL;
                    return 7;/* destination cannot be a file */
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
            if(fd_temp_src)
                free(fd_temp_src);
            if(fd_temp_dest)
                free(fd_temp_dest);
            if(fd_temp)
                free(fd_temp);
            fd_temp_src=NULL;
            source_ptr=NULL;
            fd_temp_dest=NULL;
            dest_ptr=NULL;
            fd_temp=NULL;
            return 2;
        }
    }
    else
    {
        /* source not found */
        free(fd_temp_src);
        fd_temp_src=NULL;
        source_ptr=NULL;
        return 1;
    }


    /* free interim vars and return */
    if(fd_temp_src)
        free(fd_temp_src);
    if(fd_temp_dest)
        free(fd_temp_dest);
    if(fd_temp)
        free(fd_temp);
    fd_temp_src=NULL;
    source_ptr=NULL;
    fd_temp_dest=NULL;
    dest_ptr=NULL;
    fd_temp=NULL;
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
    int type=-1;
    char fullpath[100];
    char delim[]="/";
    int index=0;
    unsigned int metaheader_size=0;
    file_descriptor_t *fd_temp;
    FILE *fptr;
    long fsize=0;
    data_block_t *file_data;
    //printf("\ncreatefile : %s\n",dest_dir_path);

    /* insufficient args */
    if(!strlen(dest_dir_path)||!strlen(file_name)||!strlen(data_file_path))
        return 0;
    /* invalid character in filename */
    if(strstr(file_name,"/")!=NULL)
        return 2;

    /* check if last char is '/' , then do not copy it */
    if(strlen(dest_dir_path)!=1 && (dest_dir_path[strlen(dest_dir_path)-1]==delim[0]))
    {
        strncpy(fullpath,dest_dir_path,strlen(dest_dir_path)-1);
        fullpath[strlen(dest_dir_path)-1]='\0';
    }
    else
        strcpy(fullpath,dest_dir_path);
    //printf("\ncreatefile copy : %s\n",fullpath);




    if(strlen(fullpath)!=1 && (fullpath[strlen(fullpath)-1]!=delim[0]))
    {
        strcat(fullpath,"/");
        //printf("\ncat1 : %s\n",fullpath);
    }

    /*Concatenate filename to path to create */
    strcat(fullpath,file_name);
    create_file_descriptor(&fd_temp,fullpath,fullpath,-1);
    //printf("\ncreatefile filename concat : %s %d\n",fullpath,search_node(&head->leftchild,&fd_temp));
    /* check if path exists */
    /* check if destination already has same named file/dir as is the source */
    if (strcmp(fd_temp->loc_path,"/") && (search_node(&head->leftchild,&fd_temp)!=-1))
    {
        free(fd_temp);
        fd_temp=NULL;
        return 3;
    }
    if(fd_temp)
    {
        free(fd_temp);
        fd_temp=NULL;
    }

    /* check if filesize exceeds block limit */
    if ( (fptr=fopen(data_file_path,"r")) == NULL )
    {
        if(fptr)
            fclose(fptr);
        return 5;
    }

    rewind(fptr);
    /* add code to check if input file is text or not and update filetype in descriptor accordingly. 1-dir,2-txt,3-non text */
    fseek(fptr,0,SEEK_END);
    fsize=ftell(fptr);
    /* if file size is greater than block size, err out */
    if(fsize>1024)
    {
        if(fptr)
            fclose(fptr);
        return 6;
    }


    /* find free fd index */
    if(!(index=search_free_list(file_name,fullpath,2)))
    {
        if(fptr)
            fclose(fptr);
        return 4;/* file system full */
    }
    else
    {
        /* check filetype 2=txt and 3=non txt*/
        if(file_name[strlen(file_name)-3]=='t' && file_name[strlen(file_name)-2]=='x' && file_name[strlen(file_name)-1]=='t' )
            type=2;
        else
            type=3;
        if(insert(file_name, fullpath, type,fsize)==TRUE)
        {
            //index=source_ptr->file_desc->loc_number;
            if(index!=0)
            {

                metaheader_size=sizeof(vfs_header)+sizeof(char)*max_file_descriptors+sizeof(file_descriptor_t)*max_file_descriptors;
                file_data=(data_block_t *) (intptr_t) read_text_from_user_file ( data_file_path, fsize);
                if(file_data && (write_block(file_data,metaheader_size ,index)==TRUE))
                {
                    //if(file_descriptors[index].file_type!=1)
                    //    insert_into_list(&file_descriptors[index]);
                    if(fptr)
                        fclose(fptr);
                    if(file_data)
                        free(file_data);
                    return SUCCESS;
                }
                else
                {
                    del(fullpath,type);
                    if(fptr)
                        fclose(fptr);
                    return 5;/* unable to create new file */
                }
            }
            else
            {
                del(fullpath,type);
                if(fptr)
                    fclose(fptr);
                return 1;/* unable to create new file : 0th location is reserved for root */
            }
        }
        else
        {
            del(fullpath,type);
            if(fptr)
                fclose(fptr);
            return 5;/* unable to create new file */
        }
    }
}


/*
*   Description :   Copy a file from source path to destination path
*   Input       :   Source file path, destination directory path
*   Output      :   True for Success and False for Failure
*/
int copy_file(char *src, char *dest)
{
    file_descriptor_t *fd_temp,*fd_temp_dest;
    narry_tree_t *source_ptr,*dest_ptr,*dest_ptr_temp;
    char fullpath[100],source_path[100],dest_path[100],dest_path_folder[100],dest_path_file[100],temp_file_name[100];
    char delim[]="/";
    char name[100];
    int index=0;
    int i;
    unsigned int metaheader_size=0;

    /* if src is missing */
    if(!strlen(src))
        return 0;
    /* if destination is missing */
    if(!strlen(dest))
        return 0;

    source_ptr=head;
    //source_ptr=source_ptr->leftchild;


    if(strlen(src)!=1 && (src[strlen(src)-1]==delim[0]))
        strncpy(source_path,src,strlen(src)-1);
    else
        strcpy(source_path,src);
    //printf("\ncopy : %s\n",source_path);

    //printf("\ncopyfile before :dest:%s\n",dest_path);
    if(strlen(dest)!=1 && (dest[strlen(dest)-1]==delim[0]))
    {
        strncpy(dest_path,dest,strlen(dest)-1);
        dest_path[strlen(dest)-1]='\0';
        //printf("\ncopyfile inside if:dest:%s\n",dest_path);
    }
    else
        strcpy(dest_path,dest);

    //printf("\ncopyfile:dest:%s\n",dest_path);
    if(rindex(dest_path,'/')==NULL)
    {
        return 2;//cannot find destination
    }
    else
    {
        strncpy(dest_path_folder,dest_path,strlen(dest_path)-strlen(rindex(dest_path,'/')));
        dest_path_folder[strlen(dest_path)-strlen(rindex(dest_path,'/'))]='\0';

        strcpy(temp_file_name,rindex(dest_path,'/'));
        for(i=1; i<strlen(temp_file_name); i++)
            dest_path_file[i-1]=temp_file_name[i];
        //dest_path_file[strlen(dest_path)-strlen(rindex(dest_path,'/'))]='\0';
        dest_path_file[i-1]='\0';

    }
    create_file_descriptor(&fd_temp,source_path,source_path,-1);
    /* find source */
    if((source_ptr=(narry_tree_t *)find_node(&source_ptr,&fd_temp))!=NULL)
    {
        free(fd_temp);

        dest_ptr=head;
        dest_ptr_temp=head;

        create_file_descriptor(&fd_temp,dest_path,dest_path,-1);
        create_file_descriptor(&fd_temp_dest,dest_path_folder,dest_path_folder,-1);
        //dest_path_file++;
        //printf("\ncopy file: des folder=%s and file=%s\n",dest_path_folder,dest_path_file);
        /* find destination */
        if(((dest_ptr=(narry_tree_t *)find_node(&dest_ptr,&fd_temp))!=NULL) || (dest_ptr_temp=(narry_tree_t *)find_node(&dest_ptr_temp,&fd_temp_dest))!=NULL)
        {
            if(dest_ptr==NULL)
                dest_ptr=dest_ptr_temp;
            else
                dest_ptr_temp=NULL;
            /* cannot copy dir to file */
            if(source_ptr->file_desc->file_type==1 /*&& dest_ptr->file_desc->file_type==2 */)
            {
                if(fd_temp)
                    free(fd_temp);
                if(fd_temp_dest)
                    free(fd_temp_dest);
                return 3;/* cannot copy dir to file */
            }

            //strcpy(name,"/");
            /* prepare filename to be searched at destination */
            strcpy(name,dest_path);
            strcat(name,"/");
            if(strcmp(source_ptr->file_desc->file_name,"/"))
                strcat(name,source_ptr->file_desc->file_name);
            //printf("\ncopyfile:name:%s\n",name);

            /*
            create_file_descriptor(&fd_temp,source_ptr->file_desc->file_name,name,-1);
            if ((search_node(&dest_ptr->leftchild,&fd_temp))!=-1)
            {
                if(fd_temp)
                    free(fd_temp);
                //return 2; destination already has same named file/dir
            }
            */
            /* if destination path does not have file already present*/
            //printf("\ndt=%p head=%p\n",dest_ptr_temp,head);
            if((dest_ptr_temp!=NULL) && (dest_ptr->file_desc->file_type==1 /*|| dest_ptr->file_desc->file_type!=3*/))
            {
                // printf("\ncopyfile:when dest has no file filetype=%d\n",dest_ptr->file_desc->file_type);
                strcpy(fullpath,dest_ptr->file_desc->loc_path);
                if(strcmp(fullpath,"/"))
                    strcat(fullpath,"/");
                /*strcat(fullpath,source_ptr->file_desc->file_name);*/
                strcat(fullpath,dest_path_file);
                //printf("\ncopyfile strcat=%s\n",fullpath);
                /* find free index */
                if(!(index=search_free_list(dest_path_file/*source_ptr->file_desc->file_name*/,fullpath,source_ptr->file_desc->file_type)))
                {
                    // printf("\ncopyfile:when dest has no file mentioned search free list index=%d\n",index);
                    return 4;/* vfs is full */
                }
                else
                {
                    if(insert(dest_path_file/*source_ptr->file_desc->file_name*/, fullpath, source_ptr->file_desc->file_type,source_ptr->file_desc->file_size)==TRUE)
                    {
                        if(index!=0)
                        {
                            metaheader_size=sizeof(vfs_header)+sizeof(char)*max_file_descriptors+sizeof(file_descriptor_t)*max_file_descriptors;
                            if(write_block(read_block ( metaheader_size ,source_ptr->file_desc->loc_number ),metaheader_size ,index)==TRUE)
                            {
                                if(fd_temp)
                                    free(fd_temp);
                                return SUCCESS;
                            }
                            else
                            {
                                // printf("\ncopyfile:when dest has no file mentioned writeblock fails=%d\n",index);
                                del(fullpath,source_ptr->file_desc->file_type);
                                return 4;/* unable to copyfile */
                            }
                        }
                        else
                        {
                            //printf("\ncopyfile:when dest has no file mentioned 2.search free list index=%d\n",index);
                            del(fullpath,source_ptr->file_desc->file_type);
                            return 4;/* unable to copyfile */
                        }
                    }
                    else
                    {
                        //printf("\ncopyfile:when dest has no file mentioned insert fails=%d %s %s %d\n",index,source_ptr->file_desc->file_name, fullpath, source_ptr->file_desc->file_type,source_ptr->file_desc->file_size);
                        del(fullpath,source_ptr->file_desc->file_type);
                        return 4;/* unable to copyfile */
                    }
                }
            }
            /* if destinationpath includes file name */
            else
            {
                //printf("\ncopyfile:when dest has file \n");
                if(dest_ptr->file_desc->file_type!=1)
                {
                    metaheader_size=sizeof(vfs_header)+sizeof(char)*max_file_descriptors+sizeof(file_descriptor_t)*max_file_descriptors;
                    if(write_block(read_block ( metaheader_size ,source_ptr->file_desc->loc_number ),metaheader_size ,dest_ptr->file_desc->loc_number)==TRUE)
                    {
                        if(fd_temp)
                            free(fd_temp);
                        return SUCCESS;
                    }
                    else
                    {
                        //printf("\ncopyfile:when dest has file mentioned write block fails\n");
                        return 4;/* unable to copyfile */
                    }
                }
                else
                {
                    if(fd_temp)
                        free(fd_temp);
                    if(fd_temp_dest)
                        free(fd_temp_dest);
                    return 2;/* path found does not have a file name */
                }
            }

        }
        else
        {
            /* destination not found */
            free(fd_temp);
            return 2;
        }

    }
    else
    {
        /* source not found */
        free(fd_temp);
        return 1;
    }

    if(fd_temp)
        free(fd_temp);
    return SUCCESS;
}



/*
*   Description :   Move a file from source path to destination path
*   Input       :   Source file path, destination file path
*   Output      :   True for Success and False for Failure
*/
int move_file(char *src, char *dest,int type)
{
    file_descriptor_t *fd_temp_src,*fd_temp_dest,*fd_temp,*fd_temp_dest_folder;
    narry_tree_t *source_ptr,*dest_ptr,*dest_ptr_temp;
    char name[100];
    char destination[100];
    char destination_folderonly[100];
    char destination_fileonly[100];
    char destination_file_temp[100];
    char source[100];
    char delim[]="/";
    data_block_t *file_data;
    int index_source=0,index_destination=0;
    unsigned int metaheader_size=0;
    int i=0;

    fd_temp_src=fd_temp_dest=fd_temp=NULL;
    /* if src is missing */
    if(!strlen(src))
        return 0;
    /* if destination is missing */
    if(!strlen(dest))
        return 0;

    source_ptr=head;
    //source_ptr=source_ptr->leftchild;
    if(strlen(src)!=1 && (src[strlen(src)-1]==delim[0]))
    {
        strncpy(source,src,strlen(src)-1);
        source[strlen(src)-1]='\0';
        //printf("\ncopyfile inside if:dest:%s\n",dest_path);
    }
    else
        strcpy(source,src);

    if(strlen(dest)!=1 && (dest[strlen(dest)-1]==delim[0]))
    {
        strncpy(destination,dest,strlen(dest)-1);
        destination[strlen(dest)-1]='\0';
        //printf("\ncopyfile inside if:dest:%s\n",dest_path);
    }
    else
        strcpy(destination,dest);


    if(rindex(destination,'/')==NULL)
    {
        return 2;//cannot find destionation
    }
    else
    {
        strncpy(destination_folderonly,destination,strlen(destination)-strlen(rindex(destination,'/')));
        destination_folderonly[strlen(destination)-strlen(rindex(destination,'/'))]='\0';

        strcpy(destination_file_temp,rindex(destination,'/'));
        for(i=1; i<strlen(destination_file_temp); i++)
            destination_fileonly[i-1]=destination_file_temp[i];

        destination_fileonly[i-1]='\0';
    }
    //printf("\nmovefile:src=%s and dest=%s folder=%s %s %ld\n",source,destination,destination_folderonly,rindex(destination,'/'),strlen(destination)-strlen(rindex(destination,'/')));
    create_file_descriptor(&fd_temp_src,source,source,-1);
    //printf("\nmove:fd=%s:src=%s:head=%s:\n",fd_temp_src->loc_path,src,source_ptr->file_desc->loc_path);
    /* find source */
    if((source_ptr=(narry_tree_t *)find_node(&source_ptr,&fd_temp_src))!=NULL)
    {

        dest_ptr=head;
        dest_ptr_temp=head;

        if(source_ptr->file_desc->file_type==1)
        {
            if(fd_temp_src)
                free(fd_temp_src);
            fd_temp_src=NULL;
            source_ptr=NULL;
            return 1;/* source filename not mentioned */
        }

        create_file_descriptor(&fd_temp_dest,destination,destination,-1);
        create_file_descriptor(&fd_temp_dest_folder,destination_folderonly,destination_folderonly,-1);
        /* find destination */
        //printf("\nmovefile:src=%s and dest=%s folder=%s %ld\n",source,destination,destination_folderonly,strlen(destination)-strlen(rindex(destination,'/')));
        if(((dest_ptr=(narry_tree_t *)find_node(&dest_ptr,&fd_temp_dest))!=NULL) || (dest_ptr_temp=(narry_tree_t *)find_node(&dest_ptr_temp,&fd_temp_dest_folder))!=NULL)
        {
            if(dest_ptr==NULL)
                dest_ptr=dest_ptr_temp;
            else
                dest_ptr_temp=NULL;
            /* if destination is only a directory path */
            if((dest_ptr_temp!=NULL) && (dest_ptr->file_desc->file_type==1))
            {
                /* fetch parent's loc path and concatinate / to the end of it */
                if(dest_ptr->parent)
                {
                    strcpy(name,dest_ptr->file_desc->loc_path);
                    strcat(name,"/");
                }
                else
                    strcpy(name,"/");
                //if(strcmp(source_ptr->file_desc->file_name,"/"))
                strcat(name,destination_fileonly /*source_ptr->file_desc->file_name*/);

                //create_file_descriptor(&fd_temp,destination_fileonly/*source_ptr->file_desc->file_name*/,name,-1);
                /* update the filename */
                strcpy(source_ptr->file_desc->file_name,destination_fileonly);
                if(update_pointers(&source_ptr))
                {
                    move_node(&source_ptr,&dest_ptr);
                    update_familypaths(&source_ptr);
                }
            }
            /* if destination path already has the file */
            else
            {
                if(dest_ptr->file_desc->file_type!=1)
                {
                    /* fetch meta heade size */
                    metaheader_size=sizeof(vfs_header)+sizeof(char)*max_file_descriptors+sizeof(file_descriptor_t)*max_file_descriptors;
                    /* fetch source block index and destination block index*/
                    index_source=source_ptr->file_desc->loc_number;
                    index_destination=dest_ptr->file_desc->loc_number;

                    /* read source block and write(overwrite) to destination block */
                    file_data=(data_block_t *) (intptr_t) read_block ( metaheader_size ,index_source );
                    if(write_block(file_data,metaheader_size ,index_destination)==TRUE)
                    {
                        /* delete source file */
                        del(source_ptr->file_desc->loc_path,2);
                        if(fd_temp_src)
                            free(fd_temp_src);
                        if(fd_temp_dest)
                            free(fd_temp_dest);
                        if(fd_temp)
                            free(fd_temp);
                        fd_temp_src=NULL;
                        source_ptr=NULL;
                        fd_temp_dest=NULL;
                        fd_temp=NULL;
                        return SUCCESS;
                    }
                    else
                    {
                        if(fd_temp_src)
                            free(fd_temp_src);
                        if(fd_temp_dest)
                            free(fd_temp_dest);
                        if(fd_temp)
                            free(fd_temp);
                        fd_temp_src=NULL;
                        source_ptr=NULL;
                        fd_temp_dest=NULL;
                        fd_temp=NULL;
                        return 2;/* unable to copyfile */
                    }
                }
                else
                {
                    if(fd_temp_src)
                        free(fd_temp_src);
                    if(fd_temp_dest)
                        free(fd_temp_dest);
                    if(fd_temp)
                        free(fd_temp);
                    fd_temp_src=NULL;
                    source_ptr=NULL;
                    fd_temp_dest=NULL;
                    fd_temp=NULL;
                    return 2;/* unable to copyfile */
                }
            }

        }
        else
        {
            //printf("\ndest ptr=%p\n",dest_ptr);
            /* destination not found */
            if(fd_temp_src)
                free(fd_temp_src);
            if(fd_temp_dest)
                free(fd_temp_dest);
            if(fd_temp)
                free(fd_temp);
            fd_temp_src=NULL;
            source_ptr=NULL;
            fd_temp_dest=NULL;
            dest_ptr=NULL;
            fd_temp=NULL;
            return 2;
        }
    }
    else
    {
        /* source not found */
        free(fd_temp_src);
        fd_temp_src=NULL;
        source_ptr=NULL;
        return 1;
    }


    /* free interim vars and return */
    if(fd_temp_src)
        free(fd_temp_src);
    if(fd_temp_dest)
        free(fd_temp_dest);
    if(fd_temp)
        free(fd_temp);
    fd_temp_src=NULL;
    source_ptr=NULL;
    fd_temp_dest=NULL;
    dest_ptr=NULL;
    fd_temp=NULL;
    return SUCCESS;
}



/* This is a debuggin function to view FD array data */
void fd_array_dump(char condition)
{
    int i;

    printf("\n\n For condition : %c :\n",condition);
    printf("\n\n Index\t\tloc_path\t\t\t\tfile_name\t\t\tsize\tloc_number\ttype");
    for(i=0; i<max_file_descriptors; i++)
    {
        /* search for an empty slot */
        if(free_list[i]==condition)
        {
            printf("\n\n %d\t\t%-30s\t\t%-30s\t%ld\t %d\t\t%d",i,file_descriptors[i].loc_path,file_descriptors[i].file_name,file_descriptors[i].file_size,file_descriptors[i].loc_number,file_descriptors[i].file_type);
        }
    }
    printf("\n\n");
}


/*
*   Description :   Update a file in vfs from a file in the main OS with the specified file name
*   Input       :   Destination file path, filepath (to read data from)
*   Output      :   True for Success and False for Failure
*/
int update_file(char *dest_file_path,char *data_file_path)
{

    int index=0;
    unsigned int metaheader_size=0;
    file_descriptor_t *fd_temp;
    long fsize=0;
    FILE *fptr;

    if(!strlen(dest_file_path)||!strlen(data_file_path))
        return 0;

    /* check if filesize exceeds block limit */
    if ( (fptr=fopen(data_file_path,"r")) == NULL )
    {
        return 2;
    }

    rewind(fptr);
    /* add code to check if input file is text or not and update filetype in descriptor accordingly. 1-dir,2-txt,3-non text */
    fseek(fptr,0,SEEK_END);
    fsize=ftell(fptr);
    /* if file size is greater than block size, err out */
    if(fsize>1024)
    {
        fclose(fptr);
        return 3;
    }

    create_file_descriptor(&fd_temp,dest_file_path,dest_file_path,-1);

    if ((index=search_node(&head->leftchild,&fd_temp))!=-1)
    {
        if(index!=0)
        {
            metaheader_size=sizeof(vfs_header)+sizeof(char)*max_file_descriptors+sizeof(file_descriptor_t)*max_file_descriptors;
            if(write_block(read_text_from_user_file ( data_file_path,fsize ),metaheader_size ,index)==TRUE)
            {
                return SUCCESS;
            }
            else
            {
                del(dest_file_path,2);
                if(fd_temp)
                    free(fd_temp);
                fd_temp=NULL;
                return 2;/* destination file not found */
            }
        }
        else
        {
            del(dest_file_path,2);
            if(fd_temp)
                free(fd_temp);
            fd_temp=NULL;
            return 1;/* invalid file name */
        }
    }
    else
    {
        del(dest_file_path,2);
        if(fd_temp)
            free(fd_temp);
        fd_temp=NULL;
        return 1;/* source file not found */
    }
}


/*
*   Description :   list a file to user specified data file
*   Input       :   Destination file path, filepath (to read data from)
*   Output      :   True for Success and False for Failure
*/
int list_file(char *file_path,char *dest_file_path,char *mode)
{

    int index=0;
    unsigned int metaheader_size=0;
    file_descriptor_t *fd_temp;
    data_block_t *data_block_read;

    if(!strlen(file_path)||!strlen(dest_file_path)||!strlen(mode))
        return 0;

    create_file_descriptor(&fd_temp,file_path,file_path,-1);

    if ((index=search_node(&head->leftchild,&fd_temp))!=-1)
    {
        /* error out if trying to export dir */
        if(file_descriptors[index].file_type==1)
        {
            //del(file_path,2);
            if(fd_temp)
                free(fd_temp);
            fd_temp=NULL;
            if(!strcmp(mode,"w"))
                return 2; /* for list file */
            else
                return 3;/* for export file */
        }

        /* error out if trying to export non text file */
        if(file_descriptors[index].file_type==3)
        {
            //del(file_path,2);
            if(fd_temp)
                free(fd_temp);
            fd_temp=NULL;
            if(!strcmp(mode,"w"))
                return 2; /* for list file */
        }

        if(index!=0)
        {
            metaheader_size=sizeof(vfs_header)+sizeof(char)*max_file_descriptors+sizeof(file_descriptor_t)*max_file_descriptors;
            data_block_read=(data_block_t *) (intptr_t) read_block(sizeof(vfs_header)+sizeof(char)*max_file_descriptors+sizeof(file_descriptor_t)*max_file_descriptors,index);
            if(write_block_to_userfile(data_block_read,dest_file_path ,mode,file_descriptors[index].file_size)==TRUE)
            {
                return SUCCESS;
            }
            else
            {
                //del(file_path,2);
                if(fd_temp)
                    free(fd_temp);
                fd_temp=NULL;

                /* destination file not found */
                if(!strcmp(mode,"w"))
                    return 3; /* for list file */
                else
                    return 2;/* for export file */
            }
        }
        else
        {
            //del(file_path,2);
            return 2;/* not a text file */
        }
    }
    else
    {
        //del(file_path,2);
        if(fd_temp)
            free(fd_temp);
        fd_temp=NULL;
        return 1;/* source file not found */
    }
}



/*
*   Description :   search files to user specified data file
*   Input       :   Destination file path, filepath (to read data from)
*   Output      :   True for Success and False for Failure
*/
int search_file(char *characters,char *dest_file_path)
{
    struct list *result=NULL;
    FILE *fptr;
    int counter=0;
    file_match_count=0;

    if(!strlen(characters)||!strlen(dest_file_path))
        return 0;

    //result=(struct list *)malloc(sizeof(struct list));
    result=(struct list *) (intptr_t) search_files(characters);
    //printf("\nresult=%p\n",result);
    if(result==NULL)
    {
        //puts("FILEs NOT FOUND");
        return SUCCESS;
    }
    else
    {
        if(result!=NULL)
        {

            if((fptr=fopen(dest_file_path,"w")) == NULL)
            {
                //printf("Error occured in file opening\n");
                return 0;
            }
            while(result!=NULL)
            {
                //printf("File %s in the path %s \n",res->file_desc->file_name,res->file_desc->loc_path);
                fprintf(fptr,"%s\n",result->file_desc->loc_path);
                result=result->next;
                counter++;
            }
            file_match_count=counter;
            fclose(fptr);
            return SUCCESS;
        }
        return SUCCESS;
    }
}


/* initializing binary search tree */
void init_btree()
{
    file_descriptor_t *fd_temp;
    bstNode *bst = NULL;
    int i;
    fd_temp=&(/*vfs_header.*/file_descriptors[0]);
    for(i=0; i</*MAXFILEDESCRIPTORS*/max_file_descriptors; i++)
    {
        if(/*vfs_header.*/free_list[i]!='0')
        {
            fd_temp=&(/*vfs_header.*/file_descriptors[i]);
            //printf("\n inside for loc=%s file_name=%s",fd_temp->loc_path,fd_temp->file_name);
            /* Actual Node insertion */

            bst = createBinaryTree(bst,fd_temp);
        }

    }
    headBst =  bst;



}

/*
	Searching with the help of Binary Search tree on basis of full path.
*/

int Bsearch (char *file_path)
{
    file_descriptor_t *fd_temp1;
    char *file_p;
    if(!strlen(file_path))
    {
        return 0;
    }
    else
    {
        init_btree();
        create_file_descriptor(&fd_temp1,file_path,file_path,-1);
        //fd_temp1->loc_path[strlen(fd_temp1->loc_path)] = '\0';

        if(BinaryTreesearching(headBst,fd_temp1))
        {
            Bsearch_flag = 11;
        }
        else
        {
            Bsearch_flag = 7;
        }
        printf("file path %s",fd_temp1->loc_path);
        DisplayBst(headBst);
        free_btree(headBst);

    }
    return SUCCESS;
}



