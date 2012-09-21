/*************************************************************************************************************
* File Name 		:	create_vfs.c
* Description		:	This file contains functions to create vfs, mount and unmount vfs
* Author		    :	Raghav Bali
* Date			    :	Sep 21 2012
* Version		    :	0.1
* Updates           :   [Raghav Bali Sep 21 2012]: Merged with the overall VFS code
**************************************************************************************************************/

#include "../include/main.h"

/*
    Create VFS in MBs
    returns 0 on failure to create
    returns 1 on success
*/
int create_vfs()
{
    /* dummy data to be written at the last block */
    char data_block='0';
    long int block_size=1024*1024;

    /* Multiply block size to user defined size of VFS */
    block_size*=vfs_header.vfs_size;


    /* Create VFS */
    if((vfs_file=fopen(vfs_header.label_name,"wb+"))==NULL)
    {
        /* failure */
        return FALSE;
    }
    else
    {
        /* secure file size by writing data at the last byte of the file */
        fseek(vfs_file,block_size-1, SEEK_SET);
        fwrite(&data_block,sizeof(data_block),sizeof(data_block)*block_size,vfs_file);
        fclose(vfs_file);
        /* success */
        return TRUE;
    }

}



/*
    Mount VFS
    returns 0 on failure to mount
    return 1 on successful mount
*/
int mount_vfs(char vfs_name[])
{
    if((vfs_file=fopen(vfs_name,"rb+"))==NULL)
    {
        /* failure to mount */
        return FALSE;
    }
    else
    {
        /* start from 1st byte of the file */
        rewind(vfs_file);
        /* load the meta-header */
        fread(&vfs_header,sizeof(vfs_header),1,vfs_file);
        fclose(vfs_file);
        /* successfully loaded */
        return TRUE;
    }
}



/*
    Unmount the VFS
    returns 0 on failure
    return 1 on success
*/
int unmount_vfs()
{
    if((vfs_file=fopen(vfs_header.label_name,"rb+"))==NULL)
    {
        /* failure */
        return FALSE;
    }
    else
    {
        rewind(vfs_file);
        fwrite(&vfs_header,sizeof(vfs_header),1,vfs_file);
        fclose(vfs_file);
        /* succefully written the data */
        return TRUE;
    }
}
