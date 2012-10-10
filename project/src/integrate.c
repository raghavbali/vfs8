/*************************************************************************************************************
* File Name 		:	integrate.c
* Description		:	integration of the whole vfs
* Author		:	Pushpendra Sinha
* Date			:	Oct 10 2012
* Version		:	0.9
* Updates               :   
**************************************************************************************************************/


#include "../include/main.h"

/*
    To fetch VFS creation data
    sets metaheader's :
        labelName and size fields
 */
int get_vfs_details()
{
    printf("\n Enter VFS Label: ");
    scanf("%s",vfs_header.label_name);
    printf("\n Enter VFS size (in MBs) :");
    scanf("%ld",&vfs_header.vfs_size);
}

/* to get the choice from the user*/

int get_choice_from_user(){
int choice;
printf("\n 1.Unmount \n 2.Make Directory \n 3.Delete Directory \n 4.Move Directory \n 5.List Directory \n 6.Create File \n 7.List Files \n 8.Update File \n 9.Remove File \n 10.Move File \n 11.Copy File \n 12.export File");
printf("\n Enter choice  : ");
scanf("&d",choice);
return choice;
}


void perform_action(int choice) {
switch choice{
	case 1:
		if(unmount_vfs())
    		{
        	printf("\n VFS %s unmounted successfully\n",vfs_header.label_name);
    		}
   		else
   		{
     		printf("\n VFS %s could not be unmounted",vfs_header.label_name);
   		}
   		break;
   	
   	case 2:
   		printf("\n Under Construction ");
   		break;
   	
   	case 3:
   		printf("\n Under Construction ");
   		break;
   		
   	case 4:
   		printf("\n Under Construction ");
   		break;
   	
   	case 5:
   		printf("\n Under Construction ");
   		break;
   		
   	case 6:
   		/* logic for taking data either from file or creating file in console */
   		if(write_block(test_data_block,1024))
		printf("Data block has been writen successfully.\n");
		else {
		printf("data block that has to write contain no string.\n");
		return 0;
		}
   		break;
   		
   	case 7:
   		printf("\n Under Construction ");
   		break;
   		
   	case 8:
   		printf("\n Under Construction ");
   		break;
   		
   	case 9:
   		printf("\n Under Construction ");
   		break;
   		
   	case 10:
   		printf("\n Under Construction ");
   		break;
   		
   	case 11:
   		printf("\n Under Construction ");
   		break;
   	case default:
   		printf("\n Enter valid choice");
   		break;
   	
}
}


void main(){
int choice1,choice2,vfs,mount;
	while(true){
	printf("\n 1. Create VFS\n 2. Mount VFS\n 3. Exit \n ");
	printf("\n Enter ur choice  :");
	scanf("&d",choice1);
		//creating 
		if(choice1==1) {
			get_vfs_details();
			if(create_vfs())
   			 {
        		printf("\n VFS %s of size %ld MB created successfully\n",vfs_header.label_name,vfs_header.vfs_size);
        		choice2 = get_choice_from_user(); //getting data from the user
        		perform_action(choice2);  //performing action as per choice
   			 }
    			else
    			{
        		printf("\n VFS %s of size %ld MB could not be created\n",vfs_header.label_name,vfs_header.vfs_size);
    			}
		}
		//mounting
		if(choice1==2) {
			printf("\n Enter VFS Label: ");
    			scanf("%s",vfs_header.label_name);
			if(mount_vfs(vfs_header.label_name)) 
			 {
			 printf("\n\n The file label after mounting is : %s , \n The meta header is of size %ld\n",vfs_header.label_name,sizeof(vfs_header));
			 choice2 = get_choice_from_user(); //getting data from the user
        		 perform_action(choice2);  //performing action as per choice
			 }
			 else
			 {
			 printf("Fail to mount "); // case of failure of mount function
			 }
		
		}
		if(choice1==3) {
		exit(2);
		}
		
		else {
		printf("\n Enter valid choice \n ");
		}
	
	
	}

}
