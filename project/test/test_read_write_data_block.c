/***************************************************************************
	FileName	:	test_read_write_data_block.c
	Description	:	read and write the data block to/from virtual file system.
	Author		:	Pratibind Jha
	Date		:	20 Sep 2012
****************************************************************************/
#include "../include/main.h"

int main() {

	char read[]={""};
	
	char filename[] = "../test/MirrorFile.txt";
	data_block_t *test_read_data_block,*temp;
	//strcpy(test_data_block->buffer_size, "THE DATA HAS BEEN WRITEN TO VFS AS A TEST CASE....\n");
	temp = (data_block_t *)malloc(sizeof(data_block_t));
	//strcpy(test_data_block->buffer_size,"");
	
	test_read_data_block = read_text_from_user_file(filename);
	if(test_read_data_block == NULL) {
		fputs("error occur", stdout);
	}
	fputs(test_read_data_block->buffer_size,stdout);
	printf("Block start writing in to VFS\n");

	//writing the data block into TestVfs.dat
	if(write_block(test_read_data_block,1))
		printf("Data block has been writen successfully.\n");
	else {
		printf("data block that has to write contain no string.\n");
		return 0;
	}
	
	printf("Block start reading Form VFS\n");

	//read data block from TestVfs.dat
	temp = read_block(1);
	if(temp == NULL) {
		printf("Error occured in Block Read\n");
	}
	else {
		fputs(temp->buffer_size,stdout);
	}
	return 0;

}
