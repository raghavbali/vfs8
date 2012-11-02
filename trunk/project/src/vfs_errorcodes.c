#include<main.h>


void console_output(int module, int index,char *output)
{
    //error_flag=1; /* setting to error state */

    /* CreateVFS */
    if(CREATEVFS==module)
        switch(index)
        {
        case 1  :
            printf("createvfs_FAILURE: %s\n",ERR_VFS_CREATE_01);
            error_flag=1;
            break;
        case 2  :
            printf("createvfs_FAILURE: %s\n",ERR_VFS_CREATE_02);
            error_flag=1;
            break;
        case 3  :
            printf("createvfs_FAILURE: %s\n",ERR_VFS_CREATE_03);
            error_flag=1;
            break;
        case 4  :
            printf("createvfs_FAILURE: %s\n",ERR_VFS_CREATE_04);
            error_flag=1;
            break;
        case 5  :
            printf("createvfs_FAILURE: %s\n",ERR_VFS_CREATE_05);
            error_flag=1;
            break;
        default :
            error_flag=0; /* not in error */
            printf("createvfs_SUCCESS\n");
            break;
        }
    /* mountVFS */
    else if(MOUNTVFS==module)
        switch(index)
        {
        case 1  :
            printf("mountvfs_FAILURE: %s\n",ERR_VFS_MOUNT_01);
            error_flag=1;
            break;
        case 2  :
            printf("mountvfs_FAILURE: %s\n",ERR_VFS_MOUNT_02);
            error_flag=1;
            break;
        case 3  :
            printf("mountvfs_FAILURE: %s\n",ERR_VFS_MOUNT_03);
            error_flag=1;
            break;
        default :
            error_flag=0; /* not in error */
            printf("mountvfs_SUCCESS\n");
            break;
        }
    /* UnmountVFS */
    else if(UNMOUNTVFS==module)
        switch(index)
        {
        case 1  :
            printf("unmountvfs_FAILURE: %s\n",ERR_VFS_UNMOUNT_01);
            error_flag=1;
            break;
        case 2  :
            printf("unmountvfs_FAILURE: %s\n",ERR_VFS_UNMOUNT_02);
            error_flag=1;
            break;
        case 3  :
            printf("unmountvfs_FAILURE: %s\n",ERR_VFS_UNMOUNT_03);
            error_flag=1;
            break;
        default :
            error_flag=0; /* not in error */
            printf("unmountvfs_SUCCESS\n");
            break;
        }

    /* MakeDIR */
    else if(MAKEDIR==module)
        switch(index)
        {
        case 1  :
            printf("makedir_FAILURE: %s\n",ERR_VFS_MAKEDIR_01);
            break;
        case 2  :
            printf("makedir_FAILURE: %s\n",ERR_VFS_MAKEDIR_02);
            break;
        case 3  :
            printf("makedir_FAILURE: %s\n",ERR_VFS_MAKEDIR_03);
            break;
        default :
            error_flag=0; /* not in error */
            printf("makedir_SUCCESS\n");
            break;
        }


    /* MakeDIR */
    else if(DELDIR==module)
        switch(index)
        {
        case 1  :
            printf("deletedir_FAILURE: %s\n",ERR_VFS_DELETEDIR_01);
            break;
        case 2  :
            printf("deletedir_FAILURE: %s\n",ERR_VFS_DELETEDIR_02);
            break;
        case 3  :
            printf("deletedir_FAILURE: %s\n",ERR_VFS_DELETEDIR_03);
            break;
        default :
            error_flag=0; /* not in error */
            printf("deletedir_SUCCESS\n");
            break;
        }

    /* MoveDIR */
    if(MOVEDIR==module)
        switch(index)
        {
        case 1  :
            printf("movedir_FAILURE: %s\n",ERR_VFS_MOVEDIR_01);
            break;
        case 2  :
            printf("movedir_FAILURE: %s\n",ERR_VFS_MOVEDIR_02);
            break;
        case 3  :
            printf("movedir_FAILURE: %s\n",ERR_VFS_MOVEDIR_03);
            break;
        case 4  :
            printf("movedir_FAILURE: %s\n",ERR_VFS_MOVEDIR_04);
            break;
        case 5  :
            printf("movedir_FAILURE: %s\n",ERR_VFS_MOVEDIR_05);
            break;
        default :
            error_flag=0; /* not in error */
            printf("movedir_SUCCESS\n");
            break;
        }
    /* ListDIR */
    else if(LISTDIR==module)
        switch(index)
        {
        case 1  :
            printf("listdir_FAILURE: %s\n",ERR_VFS_LISTDIR_01);
            break;
        case 2  :
            printf("listdir_FAILURE: %s\n",ERR_VFS_LISTDIR_02);
            break;
        case 3  :
            printf("listdir_FAILURE: %s\n",ERR_VFS_LISTDIR_03);
            break;
        default :
            error_flag=0; /* not in error */
            printf("listdir_SUCCESS\n");
            break;
        }

    /* AddFile */
    if(ADDFILE==module)
        switch(index)
        {
        case 1  :
            printf("addfile_FAILURE: %s\n",ERR_VFS_ADDFILE_01);
            break;
        case 2  :
            printf("addfile_FAILURE: %s\n",ERR_VFS_ADDFILE_02);
            break;
        case 3  :
            printf("addfile_FAILURE: %s\n",ERR_VFS_ADDFILE_03);
            break;
        case 4  :
            printf("addfile_FAILURE: %s\n",ERR_VFS_ADDFILE_04);
            break;
        default :
            error_flag=0; /* not in error */
            printf("addfile_SUCCESS\n");
            break;
        }

    /* removeFile */
    if(REMOVEFILE==module)
        switch(index)
        {
        case 1  :
            printf("removefile_FAILURE: %s\n",ERR_VFS_REMOVEFILE_01);
            break;
        default :
            error_flag=0; /* not in error */
            printf("removefile_SUCCESS\n");
            break;
        }

    /* MoveFile */
    if(MOVEFILE==module)
        switch(index)
        {
        case 1  :
            printf("movefile_FAILURE: %s\n",ERR_VFS_MOVEFILE_01);
            break;
        case 2  :
            printf("movefile_FAILURE: %s\n",ERR_VFS_MOVEFILE_02);
            break;
        case 3  :
            printf("movefile_FAILURE: %s\n",ERR_VFS_MOVEFILE_03);
            break;
        case 4  :
            printf("movefile_FAILURE: %s\n",ERR_VFS_MOVEFILE_04);
            break;
        case 5  :
            printf("movefile_FAILURE: %s\n",ERR_VFS_MOVEFILE_05);
            break;
        default :
            error_flag=0; /* not in error */
            printf("movefile_SUCCESS\n");
            break;
        }

    /* MoveFile */
    if(COPYFILE==module)
        switch(index)
        {
        case 1  :
            printf("copyfile_FAILURE: %s\n",ERR_VFS_COPYFILE_01);
            break;
        case 2  :
            printf("copyfile_FAILURE: %s\n",ERR_VFS_COPYFILE_02);
            break;
        case 3  :
            printf("copyfile_FAILURE: %s\n",ERR_VFS_COPYFILE_03);
            break;
        case 4  :
            printf("copyfile_FAILURE: %s\n",ERR_VFS_COPYFILE_04);
            break;
        case 5  :
            printf("copyfile_FAILURE: %s\n",ERR_VFS_COPYFILE_05);
            break;
        case 6  :
            printf("copyfile_FAILURE: %s\n",ERR_VFS_COPYFILE_06);
            break;
        case 7  :
            printf("copyfile_FAILURE: %s\n",ERR_VFS_COPYFILE_07);
            break;
        case 8  :
            printf("copyfile_FAILURE: %s\n",ERR_VFS_COPYFILE_08);
            break;
        default :
            error_flag=0; /* not in error */
            printf("movefile_SUCCESS\n");
            break;
        }
}
