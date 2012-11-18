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

/* module codes */
#define CREATEVFS 1
#define MOUNTVFS 2
#define UNMOUNTVFS 3
#define MAKEDIR 4
#define DELDIR 5
#define MOVEDIR 6
#define LISTDIR 7
#define ADDFILE 8
#define LISTFILE 9
#define UPDATEFILE 10
#define REMOVEFILE 11
#define MOVEFILE 12
#define COPYFILE 13
#define EXPORTFILE 14
#define SEARCHFILE 15
#define BSEARCH 16
/*
* End of File
*/


