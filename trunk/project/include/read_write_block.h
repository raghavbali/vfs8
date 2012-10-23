/***************************************************************************
	FileName	:	read_write_block.h
	Description	:	header file for reading and write the data block in virtual file system.
	Author		:	Pratibind Jha
	Date		:	20 Sep 2012
****************************************************************************/

/*
write data block into vfs
fptr:  is vfs file pointer
data_block:  is data that need to write into vfs
offset: position in a vfs file where data will write.
return succesfully writen or not.
*/
int write_block(data_block_t *data_block,int metaheader_size,int offset);


/*
Read data block into vfs
fptr:  is vfs file pointer
data_block:  after reading the data block data will be in data_block
offset: position in a vfs file where data have to read.
return the block of data
*/
data_block_t *read_block(int metaheader_size,int offset);


/*
Read a data from user file and put it into the structure and return
the structure.
Parameter: file name to be read.
return structure containing data block.
*/

data_block_t *read_text_from_user_file(char filename[]);

/*
 End of File
*/
