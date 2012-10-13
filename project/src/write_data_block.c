/***************************************************************************
	FileName	:	write_data_block.c
	Description	:	write the data block in virtual file system.
	Author		:	Pratibind Jha
	Date		:	20 Sep 2012
****************************************************************************/
#include "../include/main.h"

//write the data block in file system
int write_block(data_block_t data_block,int offset) {
	FILE *fptr;
	if((fptr=fopen("../src/Test1Vfs.dat","ab")) == NULL) {
		printf("Error occured in file opening\n");
		return FALSE;
	}
	
	fseek(fptr,sizeof(char)*offset,SEEK_SET);
	fwrite(&data_block,sizeof(struct data_block_t),1,fptr);
	return TRUE;
	
}

//read the data block in file system and return the whole block as structure
 data_block_t *read_block(int offset) {
	FILE *fptr;
	data_block_t *data_block_read;
	if((fptr=fopen("../src/Test1Vfs.dat","rb+")) == NULL) {
		printf("Error occured in file opening: file can't read\n");
		return NULL;
	}
	rewind(fptr);
	fseek(fptr,sizeof(char)*offset,SEEK_SET);
	fread(data_block_read,sizeof(struct data_block_t),1,fptr);
	return data_block_read ;
	
}
