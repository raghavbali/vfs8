/*************************************************************************************************************
* File Name 		:	file_system.h
* Description		:	This file contains all the data structures required
* Author		    :	Deepthi
* Date			    :	Aug 28 2012
* Version		    :	0.3
* Updates           :   [Raghav Bali Oct 29 2012]: Added function prototypes
                        [Raghav Bali Oct 11 2012]: Added function prototypes
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
#define SUCCESS 1000

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
int error_flag; /* 1-error state and 0-not in error state */



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
<<<<<<< .mine
int search_free_list(char *name,char *path, int type);


/*
*   Description :   updates free list and markes all dummy nodes as free
*   Input       :   NA
*   Output      :   NA
*/
void update_free_list();
=======
int search_free_list(char *name,char *path, int type);
>>>>>>> .r65


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
int list_directory(char *dir_path,int flag,char *text_file_path);


/*
*   Description :   Move a directory from source path to destination path
*   Input       :   Source directory path, destination directory path
*   Output      :   True for Success and False for Failure
*/
int move_dir(char *src, char *dest);


/*
*   Description :   Create a file in vfs from a file in the main OS with the specified file name
*   Input       :   Destination directory path, filename(to be created), filepath (to read data from)
*   Output      :   True for Success and False for Failure
*/
int create_file(char *dest_dir_path,char *file_name,char *data_file_path);


/*
*   Description :   Copy a file from source path to destination path
*   Input       :   Source file path, destination directory path
*   Output      :   True for Success and False for Failure
*/
int copy_file(char *src, char *dest);



/* This is a debuggin function to view FD array data */
void fd_array_dump(char condition);

/*	End of File	*/
