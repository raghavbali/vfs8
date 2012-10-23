/*************************************************************************************************************
* File Name 		:	validate.c
* Description		:	This file contains functions to validate file path
* Author		    :	Pushpendra Sinha
* Date			    :	OCT 23 2012
* Version		    :	0.1
* Updates           :   
**************************************************************************************************************/

#include "../include/main.h"

int validate(char file_path[100]); //function to validate file path

int check_for_file_and_folder(file_descriptor_t *fd ) //function to check for files and folder
{
if(fd->file_type==2) //if file type =2 then it is file
	{
	return TRUE;
	}
else
	return FALSE;//if file type =2 then it is folder

}

int validate(file_path[100]) 
{

int i,j,k=0;
int length = strlen(file_path);
	for(i=0;i<length;i++)
	{
	if(!(((file_path[i]>=48)&&(file_path[i]<=57))||((file_path[i]>=65)&&(file_path[i]<=90))||((file_path[i]>=97)&&(file_path[i]<122))||(file_path[i]==47)||(file_path[i]==95))) //checking for special characters
		{
		k=1;	
		break;
		}
	else if(file_path[length-1]==47) //checking for file ending with /
		{
		k=1;	
		break;
		}
	else if((file_path[i]==47)&&(file_path[i-1]==47)) //checking for file containing // consequtively
		{
		k=1;	
		break;
		}
	else if((file_path[i]==47)&&(file_path[i-1]==95))//checking for file containing _/ consequtively
		{
		k=1;	
		break;
		}
	}
	
	if(k==1) {
	return FALSE;
	}
	else
	{
	return TRUE;
	}
}
