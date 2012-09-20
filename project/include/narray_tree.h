/*************************************************************************************************************
* File Name 		:	narray_tree.h
* Description		:	n-arry tree on filenames(with paths)
*                       having left child and right siblings.
* Author		    :	Raghav Bali
* Date			    :	Sep 7 2012
* Version		    :	0.2
* Updates           :   [Raghav Bali Sep 20 2012]: Updated Data Structures to use file_descriptors
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
void insert_pos(narry_tree_t **head,narry_tree_t **fresh);


/*
* Initializes the tree or calls inset_pos to
* insert node at correct position
*/
void insert_node(narry_tree_t **head,file_descriptor_t **file_desc);

/*
* Display the tree data
*/
void display(narry_tree_t  *head);
