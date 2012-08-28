#define MAXFILEDESCRIPTORS 10
#define SIZEOFFILENAME 23
#define LOCATIONPATHLENGTH 100
#define SIZEOFFILETYPE 10

struct mainHeader{
	char labelName[30];
	int usedFileDescriptors;
	int fileDescriptor[MAXFILEDESCRIPTORS];
	struct freeList *link;
};
struct file_Descriptor{
	char FileName[SIZEOFFILENAME];
	char locPath[LOCATIONPATHLENGTH];
	char fileType[SIZEOFFILETYPE];
	int locNumber;
	long fileSize;
};
struct freeList{
	int blockNumber;
	struct freeList *next;
};
struct dataBlock
{
long bufferSize;
};
