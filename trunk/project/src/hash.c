#include "../include/main.h
#include<stdio.h>
#include<string.h>
#include<malloc.h>

struct list
{
	char file_name[30];
        char path_name[50];	
	struct list * next;
};

struct list *hash_table[51];

/*Hash Function*/

int hash(char *file_name)
{
	char first_char;
	int hash_value =-1;       
	first_char = file_name[0];
	if(first_char >= 'A' && first_char <= 'Z')
	hash_value=first_char%65 ;
       else if (first_char >= 'a' && first_char <= 'z')
		hash_value=(first_char%97)+26;
	else
		 hash_value =-1;     //File name Validation needs to be done
    	return hash_value;
}

int display()
{
	int i=0;
	struct list *temp;
	for(i=0;i<51;i++)
	{
		while(hash_table[i]!=NULL)
		{	
			temp = hash_table[i];
			while(temp!=NULL)
			{
				printf("%s\t", temp->file_name);
				temp=temp->next;
				
			}
			printf("\n");
			i++;
			if(i==51)
				break;
		}
	}
		return 1;
}

/*Used for search if the whole file name is given:
  Takes the hash key value and file name to searched for as input and assigns that key address location 
  to the start pointer of hash Bucket and start search for the given file from that start location */

struct list* src_file(int index, char *name_File)
{	
      struct list *start,*first,*temp,*head;
	head=(struct list *)malloc(sizeof(struct list));
	temp=head;
      start=hash_table[index];	
	while(start!=NULL)
	{	if (strcmp(start->file_name,name_File)==0)
		{	
			first= (struct list *)malloc(sizeof(struct list));
		strcpy(first->path_name,start->path_name);  
		strcpy(first->file_name,start->file_name);                 
		first->next=NULL;
		temp->next=first;
		temp=first;			 
		}
		start = start->next;
	}
	return head->next;
}
/*This function will take the file name and calculates the hash value based on the first character in file name
and and calls the src_file function. Returns the FileDescriptor pointer */

struct list* search_start_point(char *name_File) 
{	int index;
	struct list *temp;
	temp=(struct list *)malloc(sizeof(struct list));
         index = hash(name_File);
	if(hash_table[index] == NULL)
	{
		printf("0 Files Found. Search Ended...\n");	
		return NULL;
	}
	else if(index == -1)
	{
		printf("Invalid file name\n");
		return NULL;
	}
	else{
		temp=src_file(index,name_File);
		
	}
	  return temp; 
}

/*Used for search if the prefix of file name is given:
 calculates the hash key value based on the first character given and prefix of file name to searched
 for as input and assigns that key address location to the start pointer of hash Bucket and start search 
 for the given file from that start location.Returns the FileDescriptor pointer*/

struct list* search_files(char *startchars)
{	int index,length;
	struct list *start,*first,*temp,*head;
	head=(struct list *)malloc(sizeof(struct list));
	temp=head;
        index = hash(startchars);
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
	else{
			while(start!=NULL)
		{	
			if (strncmp(start->file_name,startchars,length)==0)
			   {	
				first= (struct list *)malloc(sizeof(struct list));
				strcpy(first->path_name,start->path_name);  
				strcpy(first->file_name,start->file_name);                 
				first->next=NULL;
				temp->next=first;
				temp=first;		 
			   }
			start = start->next;
		}
		
	}
	  return head->next; 
}
/*Inserting the node into the hash table in sorted order */

int insert_into_list(int hash_value, char file[],char path[])
{
	struct list *node;
	node = (struct list *)malloc(sizeof(struct list));
//Store the file name and Fullpath in the node... and inserting in Sorted order	
	strcpy(node->file_name, file);
	strcpy(node->path_name, path);
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
		
	//insertion in sorted order
	else if(strcmp((hash_table[hash_value]->file_name),(node->file_name)) > 0)
	{	
		node->next=hash_table[hash_value];
		hash_table[hash_value]=node;
		return 1;
	}

		else
	{
		struct list *prev,*curr;
		curr=hash_table[hash_value];
		prev =hash_table[hash_value];
		
		while(curr!=NULL&&node != NULL)
		{			
			if(strcmp((curr->file_name),(node->file_name)) > 0)
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
int deletion(int hash_value, char *f,char *p)
{ 
        int flag=0;
	struct list * temp1, *temp2,*del;
	temp1 = hash_table[hash_value];
	temp2 = hash_table[hash_value];
        
         if(temp1==NULL)
		{
                  printf("no entry to delete");
		  return 0;
   	        }

        else if(strcmp(temp1->file_name,f)==0 && strcmp(temp1->path_name,p)==0)
	{
           printf("%s  in the path %s is deleted",f,p);
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
			if(strcmp(temp1->file_name,f)==0 && strcmp(temp1->path_name,p)==0)
			{       printf("%s  in the path %s is deleted",f,p);
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

int main()
{
	int i;

	for(i=0;i<=51;i++)
	{
		hash_table[i] = NULL;
	}

	char file[30], f[30],search_file[30],path[30],p[30],start_char[5];
	int hash_value=0;
	int option, choice;
	while(1)
	{
		printf("\nMENU\n");
		printf("1-Insert a file into hash\n");
		printf("2-Display hash\n");
		printf("3-Delete a hash\n");
                printf("4-Search for file\n");
		printf("5-Search for Files using starting characters in file_name\n");
		printf("6-Exit\n");

		printf("Enter your choice\n");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1: printf("\nEnter the file name to be inserted into the hash table\n");
					scanf("%s", file);
					printf("\nEnter the path of the file\n");
					scanf("%s", path);
					hash_value = hash(file);
					printf("%d\n", hash_value);

					if(hash_value == -1)
					{
						printf("\nInvalid file name\n");
						break;
					}

					insert_into_list(hash_value, file,path);
					break;

			case 2: display();
					break;

			case 3: printf("Enter the file name\n");
					scanf("%s", f);
					hash_value = hash(f);
				printf("Enter the Path\n");
					scanf("%s", p);
					deletion(hash_value, f,p);
					break;
		        case 4:printf("Enter the file name to be searched in the hash table\n");
                               scanf("%s",search_file);
				struct list *result;
				result=(struct list *)malloc(sizeof(struct list));
                             	result=search_start_point(search_file);
				if(result==NULL)
					puts("FILE NOT FOUND");
				else
				{	
					printf("The file %s is found in the paths \n",search_file);			
					while(result!=NULL)
					  {
						puts(result->path_name);
						result=result->next;
					}
			       }

			       break;

 		       case 5:
				printf("Enter the starting characters for the files to be searched in the hash table\n");
                                scanf("%s",start_char);
				struct list *res;
				res=(struct list *)malloc(sizeof(struct list));
                             	res=search_files(start_char);
				if(res==NULL)
				{
					puts("FILE NOT FOUND");
					
				}
				else{
					printf("The files starting with %s are found in the paths \n",start_char);
					while(res!=NULL)
					  {
						printf("File %s in the path %s \n",res->file_name,res->path_name);
						res=res->next;
					}
			      
				}
					 break;

			case 6: printf("\nProgram terminating\n");
					return 0;
					break;
			default:printf("Enter Valid choice");
				break;
					

		}
	}
}
