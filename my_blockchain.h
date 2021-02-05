#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#ifndef READLINE_READ_SIZE
#define READLINE_READ_SIZE 70
#endif

typedef enum enum_bool
{
    TRUE = 1,
    FALSE = 0
} my_bool;

struct s_nodes
{
    int size;
    int* values;
};

struct s_blocks
{
    int size;
    char** list;
};

struct s_node_blocks
{
    int content_size;
    char** content;
};

struct blockchain
{
    struct s_nodes nodes;
    struct s_blocks blocks;
    struct s_node_blocks* node_blocks;
};

//my_func.c
int my_strcmp(const char* s1, const char* s2);
int my_strlen(char* param_1);
void my_strcpy(char* str1, char* str2);
void my_strcat(char* str1, char* str2);
int* my_realloc_int(int* array, int size, int new_size);
char* my_realloc_str(char* str, int old_size, int size);
char** my_realloc_arr(char** arr, int old_size, int new_size);
struct s_node_blocks* my_realloc_struct(struct s_node_blocks* structure, int old_size, int new_size);
int my_atoi(const char* input);
void my_itoa(char* p1, int p2);
int free_arr(char** arr, int ac);
void my_puts(char* str);
//my_add_case.c
int remember_node_block(int g_pos, int n_pos, int b_pos, struct blockchain* buffer);
int global_block_list_memory_manager(int tmp, char* av_b, struct blockchain* buffer);
int remember_global_block(char* av_b, int* g_pos, struct blockchain* buffer);
int find_node_block_pos(char* av_b, int n_pos, int* b_pos, struct blockchain* buffer);
int add_block(char* av_b, char* av_i, struct blockchain* buffer);
int add_block_to_all_nodes(char* av_b, struct blockchain* buffer);
int remember_node(int input, int tmp, struct blockchain* buffer);
int add_node(char* av_i, struct blockchain* buffer);
int add_case(char** av, int ac, int* i, struct blockchain* buffer);
//my_blockchain.c
void show_message(int exit_status);
void free_blockchain(struct blockchain* buffer);
char** sort_input(char* input, char separator, int* ac, char** av);
int check_input(char* input, struct blockchain* buffer);
char* is_sync(struct blockchain buffer);
void get_status(struct blockchain buffer);
void prompt(struct blockchain* buffer);
int initial_blockchain(struct blockchain* buffer);
int my_blockchain();
int main();
//my_remove_case.c
int find_global_block(char* av_b, int* g_pos, struct blockchain* buffer);
int forget_global_block(char* av_b, struct blockchain* buffer);
void forget_the_block_in_node(char* av_b, int n_pos, struct blockchain* buffer);
int rm_block(char* av_b, struct blockchain* buffer);
void forget_the_node(int pos, struct blockchain* buffer);
my_bool block_unique(int pos, char* str, struct blockchain* buffer);
void forget_the_node_blocks(int pos, struct blockchain* buffer);
int find_node_pos(int* pos, int input, struct blockchain* buffer);
int rm_node(char* av_i, struct blockchain* buffer);
int rm_case(char** av, int ac, int* i, struct blockchain* buffer);
//my_ls_case.c
void list_blocks(int n_pos, struct blockchain* buffer);
void list_nodes(my_bool include_blocks, struct blockchain* buffer);
void ls_case(char* av_i, struct blockchain* buffer);
//my_sync.c
int synchronise(struct blockchain* buffer);
//my_writebackup.c
int write_nodes(int file_fd, struct blockchain buffer);
int write_blocks(int file_fd, struct blockchain buffer);
int write_node_blocks(int file_fd, struct blockchain buffer);
int writebackup(int file_fd, struct blockchain buffer);
//my_readline.c
int buf_has_new_line(char* buf);
int copy_rest_of_previous_line(char* buf, char* line);
int buf_to_line(char* buf, char* line, int line_index);
void clear(char* buf);
char* my_readline(int fd);
//my_readbackup.c
int read_sorted_input(int j, int ac, char** av, struct blockchain* buffer);
int readbackup(int file_fd, struct blockchain* buffer);

