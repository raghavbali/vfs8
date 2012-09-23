/*************************************************************************************************************
* File Name 		:	file_system.h
* Description		:	This file contains all the data structures required
* Author		    :	Deepthi
* Date			    :	Aug 28 2012
* Version		    :	0.2
* Updates           :   [Raghav Bali Sep 20 2012]: Updated Data Structuress as required
                        [Raghav Bali Sep 20 2012]: Updated the formatting to Indian Hill
**************************************************************************************************************/


/**********************
 	Constants
**********************/
#define MAXFILEDESCRIPTORS 1000
#define SIZEOFFILENAME 30
#define LOCATIONPATHLENGTH 100
#define SIZEOFFILETYPE 3
#define TRUE 1
#define FALSE 0

/*	struct to define dataBlock	*/
typedef struct data_block_t
{
	char buffer_size[1024];
} data_block_t;

/*	struct to define fileDescriptor		*/
typedef struct file_descriptor_t{
	char file_name[SIZEOFFILENAME];
	char loc_path[LOCATIONPATHLENGTH];
	char file_type[SIZEOFFILETYPE];
	int loc_number;
	long file_size;
} file_descriptor_t;

/*	struct to define freeList	*/
typedef struct free_list_t{
	int block_number;
	struct free_list_t *next;
} free_list_t;


/*	struct to define mainHeader	*/
typedef struct main_header_t{
	char label_name[30];
	char free_list[MAXFILEDESCRIPTORS];
	int used_file_descriptors;
	long int vfs_size;
	file_descriptor_t file_descriptors[MAXFILEDESCRIPTORS];
} main_header_t;

/* global variables */
main_header_t vfs_header;
FILE *vfs_file; /* VFS File Name */

/*	End of File	*/
