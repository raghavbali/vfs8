/*******************************************************************
Name            : Raghav Bali
Description     : Common header file for all .c files
Date            : Sep 21 2012
Version         : 0.2
*******************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include "file_system.h"
#include "narray_tree.h"
#include "bst.h"
#include "linked_list.h"
#include "hash.h"
#include "vfs.h"
#include "vfs_errorcodes.h"

<<<<<<< .mine
/* module codes */
#define CREATEVFS 1
#define MOUNTVFS 2
#define UNMOUNTVFS 3
#define MAKEDIR 4
#define DELDIR 5
#define MOVEDIR 6
#define LISTDIR 7
#define ADDFILE 8
#define REMOVEFILE 11
#define MOVEFILE 12
#define COPYFILE 13

=======


#define VFS_01_SUCCESS "\nVFS_01_SUCCESS : %s"
#define VFS_01_FAILURE "\nVFS_01_FAILURE : File creation failed"
#define VFS_02_SUCCESS "\nVFS_02_SUCCESS : %s"
#define VFS_02_FAILURE "\nVFS_02_FAILURE "
#define VFS_03_SUCCESS "\nVFS_03_SUCCESS : %s"
#define VFS_03_FAILURE "\nVFS_03_FAILURE "
#define VFS_04_SUCCESS "\nVFS_04_SUCCESS : %s%s"
#define VFS_04_FAILURE "\nVFS_04_FAILURE : %s%s already exists"
#define VFS_05_SUCCESS "\nVFS_05_SUCCESS : %s"
#define VFS_05_FAILURE "\nVFS_05_FAILURE : %s does not exist"

>>>>>>> .r65
/*
* End of File
*/


