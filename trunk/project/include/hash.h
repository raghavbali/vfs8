/*******************************************************************
Name            : Deepthi
Description     : Search in hashtable using filename
Date            : Nov 21 2012
Version         : 1.0
********************************************************************/
#define HASH_SIZE 62

struct list
{
    file_descriptor_t *file_desc;
    struct list * next;
};

struct list *hash_table[HASH_SIZE];
int file_match_count;
