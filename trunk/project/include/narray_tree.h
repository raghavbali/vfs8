/*************************************************************************************************************
* File Name 		:	narray_tree.h
* Description		:	n-arry tree on filenames(with paths)
*                       having left child and right siblings.
* Author		    :	Raghav Bali
* Date			    :	Sep 20 2012
* Version		    :	0.4
* Updates           :   [Raghav Bali Oct 11 2012]: Added new methods : delete_node(),search_node()
                        [Raghav Bali Oct 08 2012]: Added new methods : create_node, create_file_descriptor
                        tokenizer and free_tree
                        [Raghav Bali Sep 20 2012]: Updated Data Structures to use file_descriptors
                        [Raghav Bali Sep 20 2012]: Updated the formatting to Indian Hill
**************************************************************************************************************/


/* Tree Node */
typedef struct narry_tree_t
{
    file_descriptor_t *file_desc;
    struct narry_tree_t *leftchild;
    struct narry_tree_t *rightsibling;
    struct narry_tree_t *leftsibling;
    struct narry_tree_t *parent;
} narry_tree_t;

/* global head node */
narry_tree_t *head;

/*
* Finds the correct position of the new node
* and inserts it.
*/
int insert_pos(narry_tree_t **head,narry_tree_t **fresh);


/*
* Initializes the tree or calls inset_pos to
* insert node at correct position
*/
int insert_node(narry_tree_t **head,file_descriptor_t **file_desc);

/*
* Display the tree data
*/
void display(narry_tree_t  *head);


/*
*   Description :   Display the tree : level then left child
*   Input       :   Node to begin display with, flag (0-non recursive and 1-recursive), file pointer, level(0-base)
*   Output      :   NA
*/
void list_dir(narry_tree_t  *head,int flag,FILE *fptr,int level);

/*
*   Description :   This function creates a new node
*   Input       :   Node to be created, file descriptor to be attached
*   Output      :   True(1) if successful, FALSE(0) otherwise
*/
int create_node(narry_tree_t **node,file_descriptor_t **file_desc);

/*
*   Description :   This function creates a new file descriptor node
*   Input       :   File descriptor to be created, file_name, loc number
*   Output      :   True(1) if successful, FALSE(0) otherwise
*/
int create_file_descriptor(file_descriptor_t **file_desc,char * name,char *path,int loc_number);


/*
*   Description :   Tokenizes the node's name and inserts with the help of insert_node()
*                   file_descriptor.loc_number = -1 signifies dummy node
*                   file_descriptor.loc_number = -2 signifies root node
*   Input       :   Head Node, file descriptor to be attached
*   Output      :   NA
*/
int tokenizer(narry_tree_t **head,file_descriptor_t **file_desc);


/*
*   Description :   Recursively deallocate the tree nodes before unmounting
*   Input       :   Head Node
*   Output      :   NA
*/
void free_tree(narry_tree_t  *head);


/*
*   Description :   Recursively deallocate the tree nodes when delete is performed
*   Input       :   Head Node of the subtree
*   Output      :   NA (marks each node's loc_number as -1 : for deletion
*/
void delete_tree(narry_tree_t  *head);

/*
*   Description :   Delete the specified tree node
*   Input       :   Head node, File Descriptor to be removed
*                   Removes the complete subtree rooted at specified node
*                   Including the node itself.
*   Output      :   NA
*/
int delete_node(narry_tree_t  **head,file_descriptor_t **file_desc);

/*
*   Description :   Search the tree
*   Input       :   Head node, filepath
*   Output      :   File descriptor's loc_number, else -1(dummy)
*/
int search_node(narry_tree_t  **head,file_descriptor_t **file_desc);


/*
*   Description :   Search the tree
*   Input       :   Head node, file descriptor to be searched
*   Output      :   Pointer to narray node found
*/
narry_tree_t* find_node(narry_tree_t  **temp,file_descriptor_t **file_desc);


/*
*   Description :   Move a node from source path to destination path
*   Input       :   Source pointer, Destination Pointer
*   Output      :   NA
*/
void move_node(narry_tree_t  **source,narry_tree_t  **destination);

/*
*   Description :   Update pointers of narray node to be moved
*   Input       :   Source pointer to be moved
*   Output      :   True for success and False for Failure
*/
int update_pointers(narry_tree_t  **source);


/*
*   Description :   Update source pointer and its subtree's path after moving the node
*   Input       :   Source pointer
*   Output      :   NA
*/
void update_familypaths(narry_tree_t  **source);
