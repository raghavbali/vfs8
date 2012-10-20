/***************************************************************************
	FileName	:	write_data_block.c
	Description	:	write the data block in virtual file system.
	Author		:	Pratibind Jha
	Date		:	20 Sep 2012
****************************************************************************/
#include "../include/main.h"

//write the data block in file system
int write_block(data_block_t *data_block,int offset) {
	FILE *fptr;
	if((fptr=fopen("../src/Test1Vfs.dat","rb+")) == NULL) {
		//printf("Error occured in file opening\n");
		return FALSE;
	}
	rewind(fptr);
	fseek(fptr,sizeof(data_block_t)*offset,SEEK_SET);
	fwrite(data_block,sizeof(data_block_t),1,fptr);
	fclose(fptr);
	return TRUE;
	
}

//read the data block in file system and return the whole block as structure
 data_block_t *read_block(int offset) {
	FILE *fptr;
	data_block_t *data_block_read;
	data_block_read =  (data_block_t *)malloc(sizeof(data_block_t));
	if((fptr=fopen("../src/Test1Vfs.dat","rb")) == NULL) {
		//printf("Error occured in file opening: file can't read\n");
		return NULL;
	}
	rewind(fptr);
	fseek(fptr,sizeof(data_block_t)*offset,SEEK_SET);
	fread(data_block_read,sizeof(data_block_t),1,fptr);
	fclose(fptr);
	return data_block_read ;
	
}

//read the text from user file and store in data_block for further use.

data_block_t *read_text_from_user_file ( char filename[] ) {
	
	FILE *fptr;
	data_block_t *data_read;
	data_read = (data_block_t *)malloc(sizeof(data_block_t));
	(data_read->buffer_size,"");
	char line[131];
	strcpy ( data_read->buffer_size,"" ) ;
	if ( (fptr=fopen(filename,"r")) == NULL ) {
		return NULL;
	}
	
	rewind(fptr);
	
	//reading the line by line text form file.
	while ( fgets ( line, sizeof line, fptr ) != NULL ) {
		strcat(data_read->buffer_size,line);
	}
	fclose(fptr);
	return data_read;	
}
