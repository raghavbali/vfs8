/***************************************************************************
	FileName	:	bst.c
	Description	:	Binary search on the basis of absolute path
	Author		:	Pratibind Jha
	Date		:	2 Sep 2012
****************************************************************************/
#define PATHLENGTH 50
/* Structure to define binary search tree */
struct binarySearchTree {
	file_descriptor_t *file_desc;
	//char pathString[PATHLENGTH];
	struct binarySearchTree *lChild;
	struct binarySearchTree *rChild;
};

/* Type defination of structure as bstNode */
typedef struct binarySearchTree bstNode; 
bstNode *createBinaryTree(bstNode *root, file_descriptor_t *fd);
bstNode *headBst;
int BinaryTreesearching(bstNode *root,file_descriptor_t *fd);
void free_btree(bstNode *bstnode);
int Bsearch(char *p1);
/* End of File */
