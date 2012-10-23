/*************************************************************************************************************
* File Name 		:	integrate.c
* Description		:	integration of the whole vfs
* Author		    :	Pushpendra Sinha
* Date			    :	Oct 10 2012
* Version		    :	0.2
* Updates           :   [Raghav Bali Oct 11 2012]: Corrected menu flow and added interfacing with
                        vfs functionality
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
    printf("\n Enter VFS size (in KBs) :");
    scanf("%ld",&vfs_header.vfs_size);
}


/*
    To fetch VFS creation data
    sets metaheader's :
        labelName and size fields
 */
void get_directory_details(char name[],char path[])
{
    printf("\n Enter directory name: ");
    scanf("%s",name);
    printf("\n Enter directory path: ");
    scanf("%s",path);
    //return name;
}

/* to get the choice from the user*/

int get_choice_from_user()
{
    int choice;
    printf("\n 1.Unmount* \n 2.Make Directory* \n 3.Delete Directory* \n 4.Move Directory \n 5.List Directory* \n 6.Create File \n 7.List Files \n 8.Update File \n 9.Remove File \n 10.Move File \n 11.Copy File \n 12.export File");
    printf("\n Enter choice  : ");
    scanf("%d",&choice);
    return choice;
}


void perform_action(int choice)
{

    data_block_t *test_data_block;
    char name[30];
    char path[100];
    char src[21];//="/raghav/bali/etc/xyz";
    char dest[21];//="/bin";
    char dest_dir_path[100];
    char file_name[100];
    char ubuntu_file_name[100];

    strcpy(dest_dir_path,"/raghav");
    strcpy(file_name,"abc.text");
    strcpy(ubuntu_file_name,"../test/MirrorFile.txt");

    strcpy(src,"/xyz");
    strcpy(dest,"/raghav");
    int option=0;
    do
    {
        switch (choice)
        {
        case 1:
            update_free_list();
            if(unmount_vfs(vfs_header.label_name))
            {
                free(free_list);
                free(file_descriptors);
                printf("\n VFS %s unmounted successfully\n",vfs_header.label_name);
                exit(0);
            }
            else
            {
                printf("\n VFS %s could not be unmounted",vfs_header.label_name);

            }
            option=1;
            break;

        case 2:
            get_directory_details(name,path);
            if(insert_tokenized_file_descriptor(name,path,1))
            {
                printf("\n directory %s created successfully\n",name);
            }
            else
            {
                printf("\n could not create/already exists %s named directory",name);
            }
            option=0;
            break;

        case 3:
            get_directory_details(name,path);
            if(del(name,1))
            {
                printf("\n directory %s deleted successfully\n",name);
            }
            else
            {
                printf("\n could not delete/does not exists %s named directory",name);
            }
            option=0;
            break;

        case 4:
            //printf("\n Under Construction ");
            move_dir(src,dest);
            option=0;
            break;

        case 5:
            //get_directory_details(name);
            display(head);
            //list_directory();//name);
            option=0;
            break;

        case 6:
            /* logic for taking data either from file or creating file in console */
            if(create_file(dest_dir_path,file_name,ubuntu_file_name))
                printf("Data block has been writen successfully.\n");
            else
            {
                printf("data block that has to write contain no string.\n");
                //return ;
            }
            option=0;
            break;

        case 7:
            printf("\n Under Construction ");
            option=0;
            break;

        case 8:
            printf("\n Under Construction ");
            option=0;
            break;

        case 9:
            printf("\n Under Construction ");
            option=0;
            break;

        case 10:
            printf("\n Under Construction ");
            option=0;
            break;

        case 11:
            printf("\n Under Construction ");
            option=0;
            break;
        default:
            if(choice==30)
            {
                fd_array_dump('1');
                option=0;
                break;
            }
            else
            {

                printf("\n Enter valid choice");
                option=0;
                break;
            }

        }
        if(!option)
        {

            printf("\n\n\n 1.Unmount* \n 2.Make Directory* \n 3.Delete Directory* \n 4.Move Directory \n 5.List Directory* \n 6.Create File \n 7.List Files \n 8.Update File \n 9.Remove File \n 10.Move File \n 11.Copy File \n 12.export File");
            printf("\n Enter choice  : ");
            scanf("%d",&choice);
        }
    }
    while(option!=1);
}


void main()
{
    int choice1,choice2,vfs,mount;


    choice1=0;
    do
    {
        printf("\n 1. Create VFS\n 2. Mount VFS\n 3. Exit \n ");
        printf("\n Enter ur choice  :");
        scanf("%d",&choice1);
        //creating
        if(choice1==1)
        {
            get_vfs_details();
            if(create_vfs(vfs_header.label_name,vfs_header.vfs_size))
            {
                printf("\n VFS %s of size %ld KB created successfully\n",vfs_header.label_name,vfs_header.vfs_size);
                init_tree();
                choice2 = get_choice_from_user(); //getting data from the user
                perform_action(choice2);  //performing action as per choice
            }
            else
            {
                printf("\n VFS %s of size %ld KB could not be created\n",vfs_header.label_name,vfs_header.vfs_size);
                choice1=0;//loop back
            }
        }
        //mounting
        else if(choice1==2)
        {
            printf("\n Enter VFS Label: ");
            scanf("%s",vfs_header.label_name);
            if(mount_vfs(vfs_header.label_name))
            {
                printf("\n\n The file label after mounting is : %s , \n The meta header is of size %ld\n",vfs_header.label_name,sizeof(vfs_header));
                /* create root node in tree if this is the first directory/file */
                init_tree();
                choice2 = get_choice_from_user(); //getting data from the user
                perform_action(choice2);  //performing action as per choice
            }
            else
            {
                printf("Failed to mount "); // case of failure of mount function
                choice1=0;//loop back
            }

        }
        else if(choice1==3)
        {
            exit(2);
        }

        else
        {
            printf("\n Enter valid choice \n ");
        }


    }
    while(choice1<1 || choice1>3);

}
