#include<main.h>


void console_output(int module, int index,char *output)
{
    error_flag=1; /* setting to error state */

    /* CreateVFS */
    if(CREATEVFS==module)
        switch(index)
        {
        case 1  :
            printf("createvfs_FAILURE: %s\n",ERR_VFS_CREATE_01);
            break;
        case 2  :
            printf("createvfs_FAILURE: %s\n",ERR_VFS_CREATE_02);
            break;
        case 3  :
            printf("createvfs_FAILURE: %s\n",ERR_VFS_CREATE_03);
            break;
        case 4  :
            printf("createvfs_FAILURE: %s\n",ERR_VFS_CREATE_04);
            break;
        case 5  :
            printf("createvfs_FAILURE: %s\n",ERR_VFS_CREATE_05);
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
            break;
        case 2  :
            printf("mountvfs_FAILURE: %s\n",ERR_VFS_MOUNT_02);
            break;
        case 3  :
            printf("mountvfs_FAILURE: %s\n",ERR_VFS_MOUNT_03);
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
            break;
        case 2  :
            printf("unmountvfs_FAILURE: %s\n",ERR_VFS_UNMOUNT_02);
            break;
        case 3  :
            printf("unmountvfs_FAILURE: %s\n",ERR_VFS_UNMOUNT_03);
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

}
