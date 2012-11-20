/***************************************************************************
	FileName	:	write_data_block.c
	Description	:	write the data block in virtual file system.
	Author		:	Pratibind Jha
	Date		:	20 Sep 2012
****************************************************************************/
#include "../include/main.h"

//write the data block in file system
int write_block(data_block_t *data_block,int metaheader_size,int offset)
{
    FILE *fptr;
    if((fptr=fopen(vfs_header.label_name,"rb+")) == NULL)
    {
        //printf("Error occured in file opening\n");
        return FALSE;
    }
    if(data_block!=NULL)
    {

        rewind(fptr);
        fseek(fptr,(sizeof(data_block_t)*offset)+metaheader_size,SEEK_SET);
        fwrite(data_block,sizeof(data_block_t),1,fptr);
        fclose(fptr);
        return TRUE;
    }
    else
        return FALSE;

}

//read the data block in file system and return the whole block as structure
data_block_t *read_block(int metaheader_size,int offset)
{
    FILE *fptr;
    data_block_t *data_block_read;
    data_block_read =  (data_block_t *)malloc(sizeof(data_block_t));
    if((fptr=fopen(vfs_header.label_name,"rb")) == NULL)
    {
        //printf("Error occured in file opening: file can't read\n");
        return NULL;
    }
    rewind(fptr);
    fseek(fptr,(sizeof(data_block_t)*offset)+ metaheader_size,SEEK_SET);
    fread(data_block_read,sizeof(data_block_t),1,fptr);
    fclose(fptr);
    return (data_block_t *)data_block_read ;

}

//read the text from user file and store in data_block for further use.
data_block_t *read_text_from_user_file ( char filename[],long file_size )
{

    FILE *fptr;
    data_block_t *data_read;

    data_read = (data_block_t *)malloc(sizeof(data_block_t));
    //(data_read->buffer_size,"");
    char line[1024];
    //strcpy ( data_read->buffer_size,"" ) ;
    if ( (fptr=fopen(filename,"r")) == NULL )
    {
        return NULL;
    }

    rewind(fptr);
    /* add code to check if input file is text or not and update filetype in descriptor accordingly. 1-dir,2-txt,3-non text */

    //reading the line by line text form file.
    //while ( fgets ( line, sizeof line, fptr ) != NULL )
    {
        //fgets ( line, sizeof line, fptr );
        fread(data_read->buffer_size,file_size/*strlen(data_block->buffer_size)*/,1,fptr);
        //strcat(data_read->buffer_size,line);
    }
    fclose(fptr);
    return data_read;
}



//list data block
int write_block_to_userfile(data_block_t *data_block,char *text_file_path,char *mode,long file_size)
{
    FILE *fptr;
    if((fptr=fopen(text_file_path,mode)) == NULL)
    {
        //printf("Error occured in file opening\n");
        return FALSE;
    }
    if(data_block!=NULL)
    {
        rewind(fptr);
        if(!strcmp(mode,"w"))
        {
            //fwrite(data_block,sizeof(data_block_t),1,fptr);
            fputs(data_block->buffer_size,fptr);
        }
        else
        {
            fwrite(data_block->buffer_size,file_size/*strlen(data_block->buffer_size)*/,1,fptr);
        }
        fclose(fptr);
        return TRUE;
    }
    else
        return FALSE;

}
