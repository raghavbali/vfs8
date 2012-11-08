#define HASH_SIZE 51

struct list
{
    /*
    char file_name[30];
        char path_name[50];
        */
    file_descriptor_t *file_desc;
    struct list * next;
};

struct list *hash_table[HASH_SIZE];
