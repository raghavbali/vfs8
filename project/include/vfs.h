/*************************************************************************************************************
* File Name 		:	vfs.h
* Description		:	vfs creation, mounting and unmounting functions
* Author		    :	Raghav Bali
* Date			    :	Sep 21 2012
* Version		    :	0.2
* Updates           :   [Raghav Bali Sep 21 2012]: Merged code with VFS
**************************************************************************************************************/


/*
    Create VFS in MBs
    returns 0 on failure to create
    returns 1 on success
*/
int create_vfs();

/*
    Mount VFS
    returns 0 on failure to mount
    return 1 on successful mount
*/
int mount_vfs(char vfs_name[]);


/*
    Unmount the VFS
    returns 0 on failure
    return 1 on success
*/
int unmount_vfs();


/*
    End of File
*/
