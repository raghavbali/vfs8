/*************************************************************************************************************
* File Name 		:	file_system.h
* Description		:	This file contains all the data structures required
* Author		    :	Deepthi
* Date			    :	Aug 28 2012
* Version		    :	0.2
* Updates           :   [Raghav Bali Oct 11 2012]: Added function prototypes
                        [Raghav Bali Sep 20 2012]: Updated Data Structuress as required
                        [Raghav Bali Sep 20 2012]: Updated the formatting to Indian Hill
**************************************************************************************************************/


/**********************
 	Constants
**********************/
//#define MAXFILEDESCRIPTORS 1000
#define SIZEOFFILENAME 30
#define LOCATIONPATHLENGTH 100
//#define SIZEOFFILETYPE 3
#define TRUE 1
#define FALSE 0

/* Number of file descriptors */
typedef unsigned int block_size_t;

/*	struct to define dataBlock	*/
typedef struct data_block_t
{
	char buffer_size[1024];
} data_block_t;

/*	struct to define fileDescriptor		*/
typedef struct file_descriptor_t{
	char file_name[SIZEOFFILENAME];
	char loc_path[LOCATIONPATHLENGTH];
	int file_type; /* 1=dir 2=file */
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
	//char free_list[MAXFILEDESCRIPTORS];
	int used_file_descriptors;
	long int vfs_size;
	//file_descriptor_t file_descriptors[MAXFILEDESCRIPTORS];
} main_header_t;

/* global variables */
main_header_t vfs_header;
FILE *vfs_file; /* VFS File Name */
block_size_t max_file_descriptors; /* file_descriptor count */
char *free_list; /* Free list array */
file_descriptor_t *file_descriptors; /* file descriptor array */



/*
*   Description :   This function initializes the narray tree
*   Input       :   NA
*   Output      :   True(1) if successful, FALSE(0) otherwise
*/
int init_tree();

/*
*   Description :   This function inserts into fd array and update narray tree
*   Input       :   name of the directory, type : 1-directory and 2-file
*   Output      :   True(1) if successful, FALSE(0) otherwise
*/
int insert(char* name, char *path, int type);

/*
*   Description :   This function inserts into fd array after tokenizing(directory at each level)
*   Input       :   name of the directory, type : 1-directory and 2-file
*   Output      :   True(1) if successful, FALSE(0) otherwise
*/
int insert_tokenized_file_descriptor(char* name, char *path, int type);

/*
*   Description :   Insert and update file descriptor array
*   Input       :   name of the directory, type : 1-directory and 2-file and index
*   Output      :   True(1) if successful, FALSE(0) otherwise
*/
int insert_file_descriptor(char* name, char *path, int type,int index);

/*
*   Description :   search the free list
*   Input       :   name of the directory, type : 1-directory and 2-file
*   Output      :   index of the first free block or FALSE(0)
*/
int search_free_list(char *name,char *path, int type);


/*
*   Description :   delete a file descriptor
*   Input       :   name of the directory, type : 1-directory and 2-file
*   Output      :   True(1) if successful, FALSE(0) otherwise
*/
int del(char *name,int type);

/*
*   Description :   list the directory structure
*   Input       :   NA
*   Output      :   NA
*/
void list_directory();//char *name)

/*	End of File	*/
