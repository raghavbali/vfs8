/********************************************************************************************
Name            : Deepthi
Description     : Search in hashtable using filename
Date            : Nov 21 2012
Version         : 1.1
Updates         : [Deepthi Nov 26 2012]: Handled Nulls properly to avoid segmentation faults
*********************************************************************************************/
#include "../include/main.h"
#include<stdio.h>
#include<string.h>
#include<malloc.h>

int flag_hash= FALSE;
/*Hash Function*/

int hash(char first_char)
{
    int hash_value =-1;
    if(isalnum(first_char)) 
	{   
		if(first_char >= 'A' && first_char <= 'Z')
        	hash_value=first_char%65 ;
		else if (first_char >= 'a' && first_char <= 'z')
	        hash_value=(first_char%97)+26;
		else if(first_char >= '0' && first_char <= '9')
		hash_value=(first_char%48)+52;
	}
      else if((first_char != '/'))
		 hash_value=62;
    else
       hash_value =-1;     //File name Validation needs to be done
return hash_value;
}


int display_hashdump()
{
    int i=0;
    struct list *temp;
  for(i=0; i<=HASH_SIZE; i++)
	{	if(hash_table[i]!=NULL)
		{
			flag_hash=TRUE;
			temp=hash_table[i];
			while(temp!=NULL)
			{
				printf("%s",temp->file_desc->file_name);
				if(temp->next!=NULL)
				{
					printf("-->");
				}
				temp=temp->next;
			}
			printf("\n");
		}
	}
	if(flag_hash==FALSE)
		{
			printf("\nHash Table Empty...\n");
		}
    return 1;
}

/*Inserting the node into the hash table in sorted order */

int insert_into_list(/*int hash_value,*/ file_descriptor_t *fd/*char file[],char path[]*/)
{
    struct list *node;
    int hash_value = hash(fd->file_name[0]);
    struct list *prev,*curr;

    node = (struct list *)malloc(sizeof(struct list));
//Store the file name and Fullpath in the node... and inserting in Sorted order
    node->file_desc=fd;
    node->next = NULL;

    if(hash_table[hash_value]== NULL)
    {
        hash_table[hash_value]= node;
        return 1;
    }
    //insertion at end
    /*else
    {
    	struct list *temp;
    	temp = hash_table[hash_value];

    	while(temp->next!=NULL)
    		temp = temp->next;

    	temp->next = node;
    }*/
    //insertion at beginning

    /*else
    	{
    node->next=hash_table[hash_value];
    hash_table[hash_value]=node;
    return 1;
    	}*/
/*
    //insertion in sorted order
    else if(strcmp((hash_table[hash_value]->file_desc->file_name),(node->file_desc->file_name)) > 0)
    {
        node->next=hash_table[hash_value];
        hash_table[hash_value]=node;
        return 1;
    }
    */

    else
    {
        curr=hash_table[hash_value];
        prev =hash_table[hash_value];

        while(curr!=NULL&&node != NULL)
        {
            if(strcmp((curr->file_desc->file_name),(node->file_desc->file_name)) > 0)
                break;
            prev = curr;
            curr = curr->next;
        }
        node->next = prev->next;
        prev->next = node;
        return 1;
    }

}


/*Deleting a node from the hash table based on the file name and path name*/
int deletion(char *f,char *p)
{
    int flag=0;
    struct list * temp1, *temp2,*del;
    int hash_value = hash(f[0]);

    temp1 = hash_table[hash_value];
    temp2 = hash_table[hash_value];

    if(temp1==NULL)
    {
        
        return 0;
    }

    else if(strcmp(temp1->file_desc->file_name,f)==0 && strcmp(temp1->file_desc->loc_path,p)==0)
    {
        
        flag=1;
        temp2= temp1->next;
        hash_table[hash_value]=temp2;
        free(temp1);
        return 1;
    }
    else
    {
        while(temp1!= NULL)
        {
            if(strcmp(temp1->file_desc->file_name,f)==0 && strcmp(temp1->file_desc->loc_path,p)==0)
            {
                
                {
                    temp2->next=temp1->next;
                    del=temp1;
                    temp1=temp1->next;
                    free(del);
                    flag=1;
                }
            }
            else
            {
                temp2 = temp1;
                temp1 = temp1->next;

            }
        }
        return 1;
    }
}
/*Used for search if the prefix of file name is given:
 calculates the hash key value based on the first character given and prefix of file name to searched
 for as input and assigns that key address location to the start pointer of hash Bucket and start search
 for the given file from that start location.Returns the FileDescriptor pointer*/

struct list* search_files(char *startchars)
{
    int index,length,digit=0;
	char c;
    struct list *start,*first,*temp,*head;
    head=(struct list *)malloc(sizeof(struct list));
    temp=head;
    c= startchars[0];
    index = hash(c);
	
    start=hash_table[index];
    length=strlen(startchars);
	if(hash_table[index] == NULL)
    	{	
        	return NULL;
    	}
    else if(index == -1)
    {	
        return NULL;
    }
    else
    {
        while(start!=NULL)
        {
            if (strncmp(start->file_desc->file_name,startchars,length)==0)
            {	
		digit=digit+1;                
		first= (struct list *)malloc(sizeof(struct list));
                first->file_desc=start->file_desc;
                first->next=NULL;
                temp->next=first;
                temp=first;
            }
            start = start->next;
        }

    }
	if(digit==0)
		return NULL;
	else
    return head->next;
}

void free_lists(struct list *temp)
{
    if(temp)
    {

        if(temp->next==NULL)
        {
            free(temp);
            return;
        }
        else
            {
                free_lists(temp->next);
                
            }
    }


}


void free_hash()
{
    int i;
    struct list *temp,*temp1;
    for(i=0; i<=HASH_SIZE; i++)
	{	if(hash_table[i]!=NULL)
		{
			temp=hash_table[i];
			while(temp!=NULL)
			{
				temp1=temp;
				temp=temp->next;
				free(temp1);
				temp1=NULL;
			}
			hash_table[i]=NULL;
		}
	}

}

