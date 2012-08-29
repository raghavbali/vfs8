/*************************************************************************************************************
* File Name 		:	fileSystem.h
* Description		:	This file contains all the data structures required
* Author		:	Deepthi
* Date			:	Aug 28 2012
* Version		:	0.1
**************************************************************************************************************/



/**********************
 	Constants
**********************/
#define MAXFILEDESCRIPTORS 15
#define SIZEOFFILENAME 23
#define LOCATIONPATHLENGTH 100
#define SIZEOFFILETYPE 10


/*	struct to define mainHeader	*/
struct mainHeader{
	char labelName[30];
	int usedFileDescriptors;
	int fileDescriptor[MAXFILEDESCRIPTORS];
	struct freeList *link;
};


/*	struct to define fileDescriptor		*/
struct fileDescriptor{
	char fileName[SIZEOFFILENAME];
	char locPath[LOCATIONPATHLENGTH];
	char fileType[SIZEOFFILETYPE];
	int locNumber;
	long fileSize;
};

/*	struct to define freeList	*/
struct freeList{
	int blockNumber;
	struct freeList *next;
};


/*	struct to define dataBlock	*/
struct dataBlock
{
	long bufferSize;
};


/*	typedefs	*/
typedef struct mainHeader mainHeader;
typedef struct fileDescriptor fileDescriptor;
typedef struct freeList freeList;
typedef struct dataBlock dataBlock;

/*	End of File	*/
