/*
 * File: vfsdriver.c
 *
 * Description: This is a driver program for testing your VFS system using an interaction script as input
 * You need to make additional calls to your respective functions as noted in the comments below
 * Make sure the output you display is exactly as per the given specifications for you. Do NOT print
 * any extra output (like debug messages) in the final version of your driver program. You can use this driver program
 * in a in incremental manner as you keep implementing one operator after another. For operators not yet implemented,
 * you can leave the output as given ("TO_BE_DONE"). So you can use this program as your "main" program for testing purposes.
 *
 * DO NOT write the full code for operators in the driver program! You must only CALL your functions from here.
 *
 * Usage: vfsdriver <scriptfilename>
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/main.h"

#define BUFSIZE 200
#define CMDSIZE 30
#define PARSIZE 100

void createvfs ( char *P1, int P2 );
void mountvfs ( char *P1 );
void unmountvfs ( char *P1 );
void makedir ( char *P1, char *P2 );
void deletedir ( char *P1 );
void movedir ( char *P1, char *P2 );
void listdir ( char *P1, int P2, char *P3 );
void addfile ( char *P1, char *P2, char *P3 );
void listfile ( char *P1, char *P2 );
void updatefile ( char *P1, char *P2 );
void removefile ( char *P1 );
void movefile ( char *P1, char *P2 );
void copyfile ( char *P1, char *P2 );
void exportfile ( char *P1, char *P2 );
void searchfile ( char *P1, char *P2 );
void Bsearchfile (char *P1);
void processcommand( char *command, char *P1, char *P2, char *P3 );

int main( int argc, char *argv[] )
{
    FILE *scriptfp;
    char linebuffer[BUFSIZE];
    char command[CMDSIZE], par1[PARSIZE], par2[PARSIZE], par3[PARSIZE];
    char *token;

    if( argc != 2 )
    {
        fprintf(stderr,"Usage: vfsdriver <scriptfile>\n");
        return(1);
    }

    if( (scriptfp=fopen(argv[1],"r")) == NULL )
    {
        fprintf(stderr,"Unable to open script file: %s\n", argv[1]);
        return(2);
    }

    while( fgets(linebuffer, sizeof(linebuffer), scriptfp) != NULL )
    {
        /* This output is for debugging... do not uncomment in final version */
        /*
        printf("==================================================\n");
        printf("Processing: %s", linebuffer);
        printf("==================================================\n");
        */

        /* Remove the extra newline character in the end of line */
        linebuffer[ strlen(linebuffer)-1 ] = '\0';

        /* Get the command and the parameters using tokenizer */
        strcpy( command, (token = strtok(linebuffer, " ")) == NULL ? "" : token );

        strcpy( par1, (token = strtok(NULL, " ")) == NULL ? "" : token );
        strcpy( par2, (token = strtok(NULL, " ")) == NULL ? "" : token );
        strcpy( par3, (token = strtok(NULL, " ")) == NULL ? "" : token );
        /* printf("Command:%s:p1:%s:p2:%s:p3:%s\n",command, par1, par2, par3); */

        processcommand( command, par1, par2, par3 );
    }

    //fd_array_dump('1');
}

void processcommand( char *command, char *P1, char *P2, char *P3 )
{
    if( strcmp(command, "createvfs") == 0 )
    {
        int size = atoi(P2);
        createvfs (P1,size);
    }
    else if( strcmp(command, "mountvfs") == 0 )
        mountvfs (P1);
    else if( strcmp(command, "unmountvfs") == 0 )
        unmountvfs (P1);
    else if( strcmp(command, "makedir") == 0 )
        makedir (P1,P2);
    else if( strcmp(command, "deletedir") == 0 )
        deletedir (P1);
    else if( strcmp(command, "movedir") == 0 )
        movedir (P1,P2);
    else if( strcmp(command, "listdir") == 0 )
    {
        int flag = atoi(P2);
        listdir (P1,flag,P3);
    }
    else if( strcmp(command, "addfile") == 0 )
        addfile (P1,P2,P3);
    else if( strcmp(command, "listfile") == 0 )
        listfile (P1,P2);
    else if( strcmp(command, "updatefile") == 0 )
        updatefile (P1,P2);
    else if( strcmp(command, "removefile") == 0 )
        removefile (P1);
    else if( strcmp(command, "movefile") == 0 )
        movefile (P1,P2);
    else if( strcmp(command, "copyfile") == 0 )
        copyfile (P1,P2);
    else if( strcmp(command, "exportfile") == 0 )
        exportfile (P1,P2);
    else if( strcmp(command, "searchfile") == 0 )
        searchfile (P1,P2);
    else if( strcmp(command, "Bsearchfile") == 0 )
        Bsearchfile (P1);    
    else
        printf("Ignoring invalid command %s\n", command);
}

void createvfs ( char *P1, int P2 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    /*
     if(create_vfs(P1,P2))
     {
         init_tree();
         printf(VFS_01_SUCCESS,P1);
         free_tree(head);
     }
     else
         printf(VFS_01_FAILURE);*/
    //printf("createvfs_TO_BE_DONE\n");
    console_output(CREATEVFS,create_vfs(P1,P2),P1);
    /*
    if(!error_flag)
    {
        init_tree();
    }
    */
    if(!mount_flag)
    {
        if(head)
            free_tree(head);
        free(free_list);
        free(file_descriptors);
    }


}

void mountvfs ( char *P1 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    /* if(mount_vfs(P1))
     {
         init_tree();
         printf(VFS_02_SUCCESS,P1);
         //init_tree();
     }
     else
         printf(VFS_02_FAILURE);
     //printf("mountvfs_TO_BE_DONE\n");*/
    //printf("\nmount flag=%d and error flag=%d\n",mount_flag,error_flag);
    if(!mount_flag)
    {
        console_output(MOUNTVFS,mount_vfs(P1),P1);
        if(mount_flag && !error_flag)
        {
            init_tree();
            //display_hashdump();
        }
    }
    else
        console_output(MOUNTVFS,3,P1);


}

void unmountvfs ( char *P1 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */

    if(mount_flag)
    {
        //fd_array_dump('1');
        console_output(UNMOUNTVFS,unmount_vfs(P1),P1);
        if(!mount_flag /*&& !error_flag*/)
        {
            update_free_list();
            free_hash();
            free_tree(head);
            free(free_list);
            free(file_descriptors);

            /* Nullify all globals except flags */
            head=NULL;
            free_list=NULL;
            file_descriptors=NULL;
            vfs_file=NULL;
        }
    }
    else
        console_output(UNMOUNTVFS,3,P1);
    /*
    update_free_list();
    if(unmount_vfs(P1))
    {
        printf(VFS_03_SUCCESS,P1);
        free_tree(head);
        free(free_list);
        free(file_descriptors);
    }
    else
        printf(VFS_03_FAILURE);
    }
    //printf("unmountvfs_TO_BE_DONE\n");
    */
}

void makedir ( char *P1, char *P2 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    /*
    if(insert_tokenized_file_descriptor(P2,P1,1))
        printf(VFS_04_SUCCESS,P2,P1);
    else
        printf(VFS_04_FAILURE,P2,P1);
    //printf("makedir_TO_BE_DONE\n");
    */
    if(!error_flag && mount_flag)
        console_output(MAKEDIR,insert_tokenized_file_descriptor(P2,P1,1),P1);
    else
        console_output(MAKEDIR,5,P1);

}

void deletedir ( char *P1 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    //printf("deletedir_TO_BE_DONE\n");
    /*
        if(del(P1,1))
            printf(VFS_05_SUCCESS,P1);
        else
            printf(VFS_05_FAILURE,P1);
        //fd_array_dump('1');
    */
    if(!error_flag && mount_flag)
        console_output(DELDIR,del(P1,1),P1);
    else
        console_output(DELDIR,4,P1);
}

void movedir ( char *P1, char *P2 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    //move_dir(P1,P2);
    //printf("movedir_TO_BE_DONE\n");
    if(!error_flag && mount_flag)
        console_output(MOVEDIR,move_dir(P1,P2,1),P1);
    else
        console_output(MOVEDIR,8,P1);
}

void listdir ( char *P1, int P2, char *P3 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    //printf("listdir_TO_BE_DONE\n");
    //list_directory(P1,P2,P3);
    //printf("\n");
    //fd_array_dump('1');
    if(!error_flag && mount_flag)
        console_output(LISTDIR,list_directory(P1,P2,P3),P1);
    else
        console_output(LISTDIR,3,P1);
}

void addfile ( char *P1, char *P2, char *P3 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    //printf("addfile_TO_BE_DONE\n");
    /*
    if(create_file(P1,P2,P3))
        printf("Data block has been writen successfully.\n");
    else
    {
        printf("data block that has to write contain no string.\n");
        //return ;
    }
    */
    if(!error_flag && mount_flag)
        console_output(ADDFILE,create_file(P1,P2,P3),P1);
    else
        console_output(ADDFILE,4,P1);

    //fd_array_dump('1');
}

void listfile ( char *P1, char *P2 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    //printf("listfile_TO_BE_DONE\n");

    if(!error_flag && mount_flag)
        console_output(LISTFILE,list_file(P1,P2,"w"),P1);
    else
        console_output(LISTFILE,4,P1);
}

void updatefile ( char *P1, char *P2 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    if(!error_flag && mount_flag)
        console_output(UPDATEFILE,update_file(P1,P2),P1);
    else
        console_output(UPDATEFILE,4,P1);


    //data_block_t *data_block_read=read_block(sizeof(vfs_header)+sizeof(char)*max_file_descriptors+sizeof(file_descriptor_t)*max_file_descriptors,4);
    // printf("\nData written :\n%s\n",data_block_read->buffer_size);

    //printf("updatefile_TO_BE_DONE\n");
}

void removefile ( char *P1 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    //printf("removefile_TO_BE_DONE\n");
    /*
    if(del(P1,2))
        printf("\nFileRemoved : %s",P1);
    else
        printf("\nCould not remove file");
        */
    if(!error_flag && mount_flag)
        console_output(REMOVEFILE,del(P1,2),P1);
    else
        console_output(REMOVEFILE,2,P1);
}

void movefile ( char *P1, char *P2 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    //move_dir(P1,P2);
    //printf("movefile_TO_BE_DONE\n");
    if(!error_flag && mount_flag)
        console_output(MOVEFILE,move_dir(P1,P2,2),P1);
    else
        console_output(MOVEFILE,6,P1);
}

void copyfile ( char *P1, char *P2 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    //printf("copyfile_TO_BE_DONE\n");
    /*
        if(copy_file(P1,P2))
            printf("File Copied successfully.\n");
        else
        {
            printf("File could not be copied\n");
            //return ;
        }
    */
    if(!error_flag && mount_flag)
        console_output(COPYFILE,copy_file(P1,P2),P1);
    else
        console_output(COPYFILE,5,P1);

    // data_block_t *data_block_read=read_block(sizeof(vfs_header)+sizeof(char)*max_file_descriptors+sizeof(file_descriptor_t)*max_file_descriptors,5);
    // printf("\nData written :\n%s\n",data_block_read->buffer_size);
    //fd_array_dump('1');
}

void exportfile ( char *P1, char *P2 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    //printf("exportfile_TO_BE_DONE\n");

    if(!error_flag && mount_flag)
        console_output(EXPORTFILE,list_file(P1,P2,"wb"),P1);
    else
        console_output(EXPORTFILE,4,P1);
}

void searchfile ( char *P1, char *P2 )
{
    /* Call the appropriate function with given arguments and display appropriate output on the screen */
    if(!error_flag && mount_flag)
        console_output(SEARCHFILE,search_file(P1,P2),P1);
    else
        console_output(SEARCHFILE,2,P1);
    /*
    struct list *res;
    res=(struct list *)malloc(sizeof(struct list));
    res=search_files(P1);
     if(res==NULL)
            {
                puts("FILE NOT FOUND");

            }
            else
            {
                printf("The files starting with %s are found in the paths \n",P1);
                while(res!=NULL)
                {
                    printf("File %s in the path %s \n",res->file_desc->file_name,res->file_desc->loc_path);
                    res=res->next;
                }

            }
            */
    // printf("searchfile_TO_BE_DONE\n");
}

void Bsearchfile ( char *P1) {

	if(!error_flag && mount_flag)
        console_output(BSEARCH,Bsearch(P1),P1);
    	else
        console_output(BSEARCH,1,P1);
	
}


