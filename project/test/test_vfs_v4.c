/*******************************************************************
Name            : Raghav Bali
Description     : Test File for create, mount and unmount vfs after
                  modifications to n_arry_tree.c
Date            : Oct 08 2012
Version         : NA
*******************************************************************/

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

int main()
{
    /* fetch vfs details */
    get_vfs_details();

    /* create vfs */
    if(create_vfs())
    {
        printf("\n VFS %s of size %ld MB created successfully\n",vfs_header.label_name,vfs_header.vfs_size);
    }
    else
    {
        printf("\n VFS %s of size %ld MB could not be created\n",vfs_header.label_name,vfs_header.vfs_size);
    }

    /*initializing free list*/
    int i;
    for(i=0; i<MAXFILEDESCRIPTORS; i++)
    {
        vfs_header.free_list[i]='0';
    }

    /* manipulating data for testing */
    vfs_header.free_list[3]='1';
    strcpy(vfs_header.file_descriptors[3].file_name,"raghav/etc");
    vfs_header.file_descriptors[3].loc_number=3;
    vfs_header.used_file_descriptors =1;

    vfs_header.free_list[7]='1';
    strcpy(vfs_header.file_descriptors[7].file_name,"raghav");
    vfs_header.file_descriptors[7].loc_number=7;
    vfs_header.used_file_descriptors++;

    vfs_header.free_list[12]='1';
    strcpy(vfs_header.file_descriptors[12].file_name,"bali");
    vfs_header.file_descriptors[12].loc_number=12;
    vfs_header.used_file_descriptors++;

    vfs_header.free_list[13]='1';
    strcpy(vfs_header.file_descriptors[13].file_name,"raghav/bin/src");
    vfs_header.file_descriptors[13].loc_number=13;
    vfs_header.used_file_descriptors++;

    vfs_header.free_list[14]='1';
    strcpy(vfs_header.file_descriptors[14].file_name,"raghav/bin");
    vfs_header.file_descriptors[14].loc_number=14;
    vfs_header.used_file_descriptors++;

    vfs_header.free_list[24]='1';
    strcpy(vfs_header.file_descriptors[24].file_name,"bali/test");
    vfs_header.file_descriptors[24].loc_number=24;
    vfs_header.used_file_descriptors++;



    /* write vfs details to file */
    if(unmount_vfs())
    {
        printf("\n VFS %s unmounted successfully\n",vfs_header.label_name);
    }
    else
    {
        printf("\n VFS %s could not be unmounted",vfs_header.label_name);
    }

    /* load vfs in the memory */
    mount_vfs(vfs_header.label_name);
    printf("\n\n The file label after mounting is : %s , \n The meta header is of size %ld\n",vfs_header.label_name,sizeof(vfs_header));
    printf("\n\n The freelist data is : %c %c\n",vfs_header.free_list[0],vfs_header.free_list[3]);

    file_descriptor_t fd_head;
    narry_tree_t *head;
    file_descriptor_t *fd_temp;


    strcpy(fd_head.file_name,"/");
    fd_head.loc_number=-2;
    fd_temp=&fd_head;

    if(create_node(&head,&fd_temp)==TRUE)
    {
        fd_temp=NULL;
        /* creating n-arry tree */
        for(i=0; i<MAXFILEDESCRIPTORS; i++)
        {
            if(vfs_header.free_list[i]!='0')
            {
                fd_temp=&(vfs_header.file_descriptors[i]);
                /* Actual Node insertion */
                if (tokenizer(&head,&fd_temp)==TRUE)
                    printf("\n Node inserted %s \n",fd_temp->file_name);
            }

        }
        display(head);
        printf("\n");
        free_tree(head);
    }
    else
        printf("\n Tree could not be created!!!\n");


    if(unmount_vfs())
    {
        printf("\n VFS %s unmounted successfully\n",vfs_header.label_name);
    }
    else
    {
        printf("\n VFS %s could not be unmounted",vfs_header.label_name);
    }
    //dummy_file_insert();
    //dummy_file_read();
    return 0;
}
