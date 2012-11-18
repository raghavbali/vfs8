/***************************************************************************
	FileName	:	bst.c
	Description	:	Binary search tree creating and writing into the Binary File
 	Author		:	Pratibind Jha 
	Date		:	2 Sep 2012
	
****************************************************************************/
#include "../include/main.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char filePathString[100];

/* Create Binary search Tree has two parameter one is root 
of tree and fileName that is going to insert into bst */
bstNode *createBinaryTree(bstNode *root, file_descriptor_t *fd) {
	bstNode *temp=NULL;
	//printf("fd---> %s",fd->loc_path);
	/* if tree is empty */
	if(root == NULL) {
		temp = (bstNode*)malloc(sizeof(bstNode));
		//strcpy(temp->file_desc->loc_path,fileName);
		temp->file_desc=fd;		
		temp->lChild = NULL;
		temp->rChild = NULL;
		root = temp;	
		//printf("root-> %s\n",root->file_desc->loc_path);
	}
	/* if fileName is alphabatecally grater or equal than rootnode fileName*/
	else if (strcmp(root->file_desc->loc_path,fd->loc_path) >= 0) {
		root->lChild = createBinaryTree(root->lChild,fd);
		//printf("right->%s\n",root->lChild->file_desc->loc_path);
		
	}
	/* if fileName is alphabatecally lesser than rootnode fileName*/
	else if (strcmp(root->file_desc->loc_path,fd->loc_path) < 0) {
		root->rChild = createBinaryTree(root->rChild,fd);
		//printf("left->%s\n",root->rChild->file_desc->loc_path);
	}
	return root;
	

}/* End of createBinaryTree */

void DisplayBst(bstNode *root) {
	if(root != NULL) {
			
		printf("%s\n",root->file_desc->loc_path);
		DisplayBst(root->lChild);
		DisplayBst(root->rChild);	
	}
	else{
		
	}
}



int BinaryTreesearching(bstNode *root,file_descriptor_t *fd) {
		
//	char fileName[100]
	/* if tree is empty */
	
	if(root == NULL) {
		
		return FALSE;
		//printf("\n received loc path is : %s \n",fd->loc_path);
		strcat(filePathString,"File does not exist");	
	}
	/*File found in tree*/
	else if(strcmp(root->file_desc->loc_path,fd->loc_path) == 0) {
	strcat(filePathString,root->file_desc->loc_path);
	
	return TRUE;
	//printf("\n %s \n ",filePathString);
	}
	/* if fileName is alphabatecally greater or equal than rootnode fileName*/
	else if (strcmp(root->file_desc->loc_path,fd->loc_path) >= 0) {
		strcat(filePathString,root->file_desc->loc_path);
		strcat(filePathString,"/");
		BinaryTreesearching(root->lChild,fd);
		//printf("\n %s \n ",filePathString);
	}
	/* if fileName is alphabatecally lesser than rootnode fileName*/
	else if (strcmp(root->file_desc->loc_path,fd->loc_path) < 0) {
		strcat(filePathString,root->file_desc->loc_path);
		strcat(filePathString,"/");		
		BinaryTreesearching(root->rChild,fd);
		//printf("\n %s \n ",filePathString);	
	}
}


/*
*   Description :   Recursively deallocate the binary search tree nodes after search
*   Input       :   Head Node
*   Output      :   NA
*/
void free_btree(bstNode *headBst)
{
    bstNode *temp;

    temp=headBst;
    if(temp)
    {
        if(temp->lChild)
        {
            free_btree(temp->lChild);
        }
        if(temp->rChild)
        {
            free_btree(temp->rChild);
        }
        free(temp);

    }
}

