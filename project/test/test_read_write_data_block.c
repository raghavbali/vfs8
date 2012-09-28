/***************************************************************************
	FileName	:	test_read_write_data_block.c
	Description	:	read and write the data block to/from virtual file system.
	Author		:	Pratibind Jha
	Date		:	20 Sep 2012
****************************************************************************/
#include "../include/main.h"

int main() {

	char read[]={""};
	data_block_t test_data_block;
	data_block_t *test_read_data_block = NULL;
	strcpy(test_data_block.buffer_size, "THE DATA HAS BEEN WRITEN TO VFS AS A TEST CASE....\n");


	printf("Block start writing in to VFS\n");

	//writing the data block into TestVfs.dat
	if(write_block(test_data_block,1024))
		printf("Data block has been writen successfully.\n");
	else {
		printf("data block that has to write contain no string.\n");
		return 0;
	}
	
	printf("Block start reading Form VFS\n");

	//read data block from TestVfs.dat
	test_read_data_block = read_block(1024 );

	if(test_read_data_block == NULL) {
		printf("Error occured in Block Read\n");
	}
	else {
		printf("Data is \n %s\n",test_read_data_block->buffer_size);
	}
	return 0;

}
