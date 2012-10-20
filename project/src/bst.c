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
char filePathString[50];

/* Create Binary search Tree has two parameter one is root 
of tree and fileName that is going to insert into bst */
bstNode *createBinaryTree(bstNode *root, char fileName[]) {
	bstNode *temp=NULL;
	/* if tree is empty */
	if(root == NULL) {
		temp = (bstNode*)malloc(sizeof(bstNode));
		strcpy(temp->pathString,fileName);		
		temp->lChild = NULL;
		temp->rChild = NULL;
		root = temp;	
	}
	/* if fileName is alphabatecally grater or equal than rootnode fileName*/
	else if (strcmp(root->pathString,fileName) >= 0) {
		root->lChild = createBinaryTree(root->lChild,fileName);
	}
	/* if fileName is alphabatecally lesser than rootnode fileName*/
	else if (strcmp(root->pathString,fileName) < 0) {
		root->rChild = createBinaryTree(root->rChild,fileName);
	}
	return root;
	

}/* End of createBinaryTree */

/* Search binary tree on ths basis of fileName */
void BinaryTreesearching(bstNode *root, char fileName[]) {
	/* if tree is empty */
	if(root == NULL) {
		strcat(filePathString,"File does not exist");	
	}
	/*File found in tree*/
	else if(strcmp(root->pathString,fileName) == 0) {
	strcat(filePathString,root->pathString);

	}
	/* if fileName is alphabatecally grater or equal than rootnode fileName*/
	else if (strcmp(root->pathString,fileName) >= 0) {
		strcat(filePathString,root->pathString);
		strcat(filePathString,"/");
		BinaryTreesearching(root->lChild,fileName);
	}
	/* if fileName is alphabatecally lesser than rootnode fileName*/
	else if (strcmp(root->pathString,fileName) < 0) {
		strcat(filePathString,root->pathString);
		strcat(filePathString,"/");		
		BinaryTreesearching(root->rChild,fileName);
		
	}
	

}
/* End of BinaryTreesearching */

/* Display Binary search tree*/
void DisplayBst(bstNode *root) {
	if(root != NULL) {
		printf("%s\n",root->pathString);
		DisplayBst(root->lChild);
		DisplayBst(root->rChild);	
	}
	else{
		
	}
}/*End of DisplayBst*/

int main() {	
	int i;
	FILE *bstFptr;
	char fileDescriptor[50];
	bstNode *currentNode;
	currentNode = NULL;
	printf("Enter the file name:press EOF for End\n");
	gets(fileDescriptor);
	/*for(i=0;i<strlen(fileDescriptor);i++) {
		currentNode = createBinaryTree(createBinaryTree, fileDescriptor);
	}*/
	while(strcmp(fileDescriptor,"EOF") != 0) {
		currentNode = createBinaryTree(currentNode, fileDescriptor);
		gets(fileDescriptor);	
	}
	printf("Binary Search tree is:");
	DisplayBst(currentNode);
	printf("Searching on the basis of FileName\n Enter the FileName:	");
	gets(fileDescriptor);
	BinaryTreesearching(currentNode,fileDescriptor);
	if(strcmp(filePathString,"") != 0) {
		printf("%s\n",filePathString);
	}
	
return 0;
}/* End of main */
