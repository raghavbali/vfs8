#include<main.h>


void console_output(int module, int index,char *output)
{
    //error_flag=1; /* setting to error state */

    /* CreateVFS */
    if(CREATEVFS==module)
        switch(index)
        {
        case 0  :
            printf("createvfs_FAILURE %s\n",ERR_VFS_CREATE_00);
            //error_flag=1;
            break;
        case 1  :
            printf("createvfs_FAILURE %s\n",ERR_VFS_CREATE_01);
            //error_flag=1;
            break;
        case 2  :
            printf("createvfs_FAILURE %s\n",ERR_VFS_CREATE_02);
            //error_flag=1;
            break;
        case 3  :
            printf("createvfs_FAILURE %s\n",ERR_VFS_CREATE_03);
            //error_flag=1;
            break;
        case 4  :
            printf("createvfs_FAILURE %s\n",ERR_VFS_CREATE_04);
           // error_flag=1;
            break;
        case 5  :
            printf("createvfs_FAILURE %s\n",ERR_VFS_CREATE_05);
           // error_flag=1;
            break;
        default :
            //error_flag=0; /* not in error */
            printf("createvfs_SUCCESS\n");
            break;
        }
    /* mountVFS */
    else if(MOUNTVFS==module)
        switch(index)
        {
        case 0  :
            printf("mountvfs_FAILURE %s\n",ERR_VFS_MOUNT_00);
            error_flag=1;
            break;
        case 1  :
            printf("mountvfs_FAILURE %s\n",ERR_VFS_MOUNT_01);
            error_flag=1;
            break;
        case 2  :
            printf("mountvfs_FAILURE %s\n",ERR_VFS_MOUNT_02);
            error_flag=1;
            break;
        case 3  :
            printf("mountvfs_FAILURE %s\n",ERR_VFS_MOUNT_03);
            /* vfs is already mounted-do not set err flag *///error_flag=1;
            break;
        default :
            error_flag=0; /* not in error */
            mount_flag=1; /* vfs mounted */
            printf("mountvfs_SUCCESS\n");
            break;
        }
    /* UnmountVFS */
    else if(UNMOUNTVFS==module)
        switch(index)
        {
        case 0  :
            printf("unmountvfs_FAILURE %s\n",ERR_VFS_UNMOUNT_00);
            //error_flag=1;
            break;
        case 1  :
            printf("unmountvfs_FAILURE %s\n",ERR_VFS_UNMOUNT_01);
            //error_flag=1;
            break;
        case 2  :
            printf("unmountvfs_FAILURE %s\n",ERR_VFS_UNMOUNT_02);
            //error_flag=1;
            break;
        case 3  :
            printf("unmountvfs_FAILURE %s\n",ERR_VFS_UNMOUNT_03);
            //error_flag=1;
            break;
        default :
            error_flag=0; /* not in error */
            mount_flag=0; /* vfs unmounted */
            printf("unmountvfs_SUCCESS\n");
            break;
        }

    /* MakeDIR */
    else if(MAKEDIR==module)
        switch(index)
        {
        case 0  :
            printf("makedir_FAILURE %s\n",ERR_VFS_MAKEDIR_00);
            break;
        case 1  :
            printf("makedir_FAILURE %s\n",ERR_VFS_MAKEDIR_01);
            break;
        case 2  :
            printf("makedir_FAILURE %s\n",ERR_VFS_MAKEDIR_02);
            break;
        case 3  :
            printf("makedir_FAILURE %s\n",ERR_VFS_MAKEDIR_03);
            break;
        /*case 4  :
            printf("makedir_FAILURE: %s\n",ERR_VFS_MAKEDIR_04);
            break;*/
        case 5  :
            printf("makedir_FAILURE %s\n",ERR_VFS_MAKEDIR_05);
            break;
        default :
            error_flag=0; /* not in error */
            printf("makedir_SUCCESS\n");
            break;
        }


    /* Deletedir */
    else if(DELDIR==module)
        switch(index)
        {
        case 0  :
            printf("deletedir_FAILURE %s\n",ERR_VFS_DELETEDIR_00);
            break;
        case 1  :
            printf("deletedir_FAILURE %s\n",ERR_VFS_DELETEDIR_01);
            break;
        case 2  :
            printf("deletedir_FAILURE %s\n",ERR_VFS_DELETEDIR_02);
            break;
        case 4  :
            printf("deletedir_FAILURE %s\n",ERR_VFS_DELETEDIR_04);
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
        case 0  :
            printf("movedir_FAILURE %s\n",ERR_VFS_MOVEDIR_00);
            break;
        case 1  :
            printf("movedir_FAILURE %s\n",ERR_VFS_MOVEDIR_01);
            break;
        case 2  :
            printf("movedir_FAILURE %s\n",ERR_VFS_MOVEDIR_02);
            break;
        case 4  :
            printf("movedir_FAILURE %s\n",ERR_VFS_MOVEDIR_04);
            break;
        case 5  :
            printf("movedir_FAILURE %s\n",ERR_VFS_MOVEDIR_05);
            break;
        case 6  :
            printf("movedir_FAILURE %s\n",ERR_VFS_MOVEDIR_06);
            break;
        case 7  :
            printf("movedir_FAILURE %s\n",ERR_VFS_MOVEDIR_07);
            break;
        case 8  :
            printf("movedir_FAILURE %s\n",ERR_VFS_MOVEDIR_08);
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
        case 0  :
            printf("listdir_FAILURE %s\n",ERR_VFS_LISTDIR_00);
            break;
        case 1  :
            printf("listdir_FAILURE %s\n",ERR_VFS_LISTDIR_01);
            break;
        case 2  :
            printf("listdir_FAILURE %s\n",ERR_VFS_LISTDIR_02);
            break;
        case 3  :
            printf("listdir_FAILURE %s\n",ERR_VFS_LISTDIR_03);
            break;
        case 4  :
            printf("listdir_FAILURE %s\n",ERR_VFS_LISTDIR_04);
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
        case 0  :
            printf("addfile_FAILURE %s\n",ERR_VFS_ADDFILE_00);
            break;
        case 2  :
            printf("addfile_FAILURE %s\n",ERR_VFS_ADDFILE_02);
            break;
        case 3  :
            printf("addfile_FAILURE %s\n",ERR_VFS_ADDFILE_03);
            break;
        case 4  :
            printf("addfile_FAILURE %s\n",ERR_VFS_ADDFILE_04);
            break;
        case 5  :
            printf("addfile_FAILURE %s\n",ERR_VFS_ADDFILE_05);
            break;
        case 6  :
            printf("addfile_FAILURE %s\n",ERR_VFS_ADDFILE_06);
            break;
        case 7  :
            printf("addfile_FAILURE %s\n",ERR_VFS_ADDFILE_07);
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
        case 0  :
            printf("removefile_FAILURE %s\n",ERR_VFS_REMOVEFILE_00);
            break;
        case 1  :
            printf("removefile_FAILURE %s\n",ERR_VFS_REMOVEFILE_01);
            break;
        case 2  :
            printf("removefile_FAILURE %s\n",ERR_VFS_REMOVEFILE_02);
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
        case 0  :
            printf("movefile_FAILURE %s\n",ERR_VFS_MOVEFILE_00);
            break;
        case 1  :
            printf("movefile_FAILURE %s\n",ERR_VFS_MOVEFILE_01);
            break;
        case 2  :
            printf("movefile_FAILURE %s\n",ERR_VFS_MOVEFILE_02);
            break;
        case 6  :
            printf("movefile_FAILURE %s\n",ERR_VFS_MOVEFILE_06);
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
        case 0  :
            printf("copyfile_FAILURE %s\n",ERR_VFS_COPYFILE_00);
            break;
        case 1  :
            printf("copyfile_FAILURE %s\n",ERR_VFS_COPYFILE_01);
            break;
        case 2  :
            printf("copyfile_FAILURE %s\n",ERR_VFS_COPYFILE_02);
            break;
        case 3  :
            printf("copyfile_FAILURE %s\n",ERR_VFS_COPYFILE_03);
            break;
        case 4  :
            printf("copyfile_FAILURE %s\n",ERR_VFS_COPYFILE_04);
            break;
        case 5  :
            printf("copyfile_FAILURE %s\n",ERR_VFS_COPYFILE_05);
            break;
        default :
            error_flag=0; /* not in error */
            printf("copyfile_SUCCESS\n");
            break;
        }


    /* UPdateFile */
    if(UPDATEFILE==module)
        switch(index)
        {
        case 0  :
            printf("updatefile_FAILURE %s\n",ERR_VFS_UPDATEFILE_00);
            break;
        case 1  :
            printf("updatefile_FAILURE %s\n",ERR_VFS_UPDATEFILE_01);
            break;
        case 2  :
            printf("updatefile_FAILURE %s\n",ERR_VFS_UPDATEFILE_02);
            break;
        case 3  :
            printf("updatefile_FAILURE %s\n",ERR_VFS_UPDATEFILE_03);
            break;
        case 4  :
            printf("updatefile_FAILURE %s\n",ERR_VFS_UPDATEFILE_04);
            break;
        default :
            error_flag=0; /* not in error */
            printf("updatefile_SUCCESS\n");
            break;
        }



    /* LIstFile */
    if(LISTFILE==module)
        switch(index)
        {
        case 0  :
            printf("listfile_FAILURE %s\n",ERR_VFS_LISTFILE_00);
            break;
        case 1  :
            printf("listfile_FAILURE %s\n",ERR_VFS_LISTFILE_01);
            break;
        case 2  :
            printf("listfile_FAILURE %s\n",ERR_VFS_LISTFILE_02);
            break;
        case 3  :
            printf("listfile_FAILURE %s\n",ERR_VFS_LISTFILE_03);
            break;
        case 4  :
            printf("listfile_FAILURE %s\n",ERR_VFS_LISTFILE_04);
            break;
        default :
            error_flag=0; /* not in error */
            printf("listfile_SUCCESS\n");
            break;
        }


    /* LIstFile */
    if(EXPORTFILE==module)
        switch(index)
        {
        case 0  :
            printf("exportfile_FAILURE %s\n",ERR_VFS_EXPORTFILE_00);
            break;
        case 1  :
            printf("exportfile_FAILURE %s\n",ERR_VFS_EXPORTFILE_01);
            break;
        case 2  :
            printf("exportfile_FAILURE %s\n",ERR_VFS_EXPORTFILE_02);
            break;
        case 3  :
            printf("exportfile_FAILURE %s\n",ERR_VFS_EXPORTFILE_03);
            break;
        case 4  :
            printf("exportfile_FAILURE %s\n",ERR_VFS_EXPORTFILE_04);
            break;
        default :
            error_flag=0; /* not in error */
            printf("exportfile_SUCCESS\n");
            break;
        }


        /* AddFile */
    if(SEARCHFILE==module)
        switch(index)
        {
        case 0  :
            printf("searchfile_FAILURE %s\n",ERR_VFS_SEARCHFILE_00);
            break;
        case 2  :
            printf("searchfile_FAILURE %s\n",ERR_VFS_SEARCHFILE_02);
            break;
        default :
            error_flag=0; /* not in error */
            printf("searchfile_SUCCESS %d\n",file_match_count);
            file_match_count=0;/* setting back to 0; */
            break;
        }

            /* MakeDIR */
    if(BSEARCH==module)
        switch(index)
        {
        case 0  :
            printf("BSEARCH_FAILURE %s\n",ERR_VFS_BSEARCH_00);
            break;
        case 1  :
            printf("BSEARCH_FAILURE %s\n",ERR_VFS_BSEARCH_02);
            break;
        default :
            error_flag=0; /* not in error */
            printf("BSEARCH_SUCCESS");
            if(Bsearch_flag == 11)
            	printf("FILE_FOUND\n");
            else if(Bsearch_flag == 7)
            	printf("FILE_NOT_FOUND\n");
            break;
        }
}
