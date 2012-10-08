/*************************************************************************************************************
* File Name 		:	narray_tree.h
* Description		:	n-arry tree on filenames(with paths)
*                       having left child and right siblings.
* Author		    :	Raghav Bali
* Date			    :	Oct 08 2012
* Version		    :	0.3
* Updates           :   [Raghav Bali Oct 08 2012]: Added new methods : create_node, create_file_descriptor
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
} narry_tree_t;

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
int create_file_descriptor(file_descriptor_t **file_desc,char * str,int loc_number);


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
