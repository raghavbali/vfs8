/***************************************************************************
	FileName	:	bst.c
	Description	:	Binary search on the basis of absolute path
	Author		:	Pratibind Jha
	Date		:	2 Sep 2012
****************************************************************************/
#define PATHLENGTH 50
/* Structure to define binary search tree */
struct binarySearchTree {
	char pathString[PATHLENGTH];
	struct binarySearchTree *lChild;
	struct binarySearchTree *rChild;
};

/* Type defination of structure as bstNode */
typedef struct binarySearchTree bstNode; 

/* End of File */
