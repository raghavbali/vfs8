#define HASH_SIZE 51

struct list
{
    file_descriptor_t *file_desc;
    struct list * next;
};

struct list *hash_table[HASH_SIZE];
int file_match_count;
