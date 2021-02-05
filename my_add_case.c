#include "my_blockchain.h"

int remember_node_block(int g_pos, int n_pos, int b_pos, struct blockchain* buffer)
{
    int exit_status = 0;

    if (b_pos % 10 == 0 && b_pos != 0)
    {
        buffer->node_blocks[n_pos].content = my_realloc_arr(buffer->node_blocks[n_pos].content, b_pos, sizeof(char*) * (b_pos + 10));
        if (buffer->node_blocks[n_pos].content == 0) return (exit_status = -1);
    }

    buffer->node_blocks[n_pos].content[b_pos] = buffer->blocks.list[g_pos];
    buffer->node_blocks[n_pos].content_size++;

    return exit_status;
}

int global_block_list_memory_manager(int tmp, char* av_b, struct blockchain* buffer)
{
    int exit_status = 0;

    if (tmp % 10 == 0 && tmp != 0)
    {
        buffer->blocks.list = my_realloc_arr(buffer->blocks.list, tmp, tmp + 10);
        if (buffer->blocks.list == 0) return (exit_status = -1);
    }
    buffer->blocks.list[tmp] = malloc(my_strlen(av_b) + 1);
    if (buffer->blocks.list[tmp] == 0) return (exit_status = -1);

    return exit_status;
}

int remember_global_block(char* av_b, int* g_pos, struct blockchain* buffer)
{
    int exit_status = 0;

    if (find_global_block(av_b, g_pos, buffer) == -17)
    {
        int tmp = buffer->blocks.size;
        if (global_block_list_memory_manager(tmp, av_b, buffer) == -1) exit_status = -1;
        my_strcpy(buffer->blocks.list[tmp], av_b);
        buffer->blocks.size++;
    }

    return exit_status;
}

int find_node_block_pos(char* av_b, int n_pos, int* b_pos, struct blockchain* buffer)
{
    for (*b_pos = 0; *b_pos < buffer->node_blocks[n_pos].content_size; (*b_pos)++)
        if (my_strcmp(av_b, buffer->node_blocks[n_pos].content[*b_pos]) == 0)
            return -16;
    return -17;
}

int add_block(char* av_b, char* av_i, struct blockchain* buffer)
{
    int exit_status;
    int n_pos;
    int input;
    int b_pos;
    int g_pos;

    if ((input = my_atoi(av_i)) >= 0)
        if (find_node_pos(&n_pos, input, buffer) != -14)
            if (find_node_block_pos(av_b, n_pos, &b_pos, buffer) != -16)
                if (remember_global_block(av_b, &g_pos, buffer) != -1) 
                    if (remember_node_block(g_pos, n_pos, b_pos, buffer) != -1) exit_status = 3;
                    else exit_status = -1;
                else exit_status = -1;
            else exit_status = -16;
        else exit_status = -14;
    else exit_status = input;

    return exit_status;
}

int add_block_to_all_nodes(char* av_b, struct blockchain* buffer)
{
    int exit_status = 3;
    char* tmp;

    if ((tmp = malloc(sizeof(char) * 30)) != 0)
    {
        for (int j = 0; j < buffer->nodes.size; j++)
        {
            my_itoa(tmp, buffer->nodes.values[j]);
            if( (exit_status = add_block(av_b, tmp, buffer)) != 3)
            {
                free(tmp);
                return exit_status;
            }
        }
        free(tmp);
    }
    else exit_status = -1;

    return exit_status;
}

int my_realloc_nodes_list(struct blockchain* buffer, int old_size, int new_size)
{
    int exit_status = 0;

    buffer->nodes.values = my_realloc_int(buffer->nodes.values, old_size, sizeof(int) * (new_size));
    if (buffer->nodes.values == 0) return (exit_status = -1);
    buffer->node_blocks = my_realloc_struct(buffer->node_blocks, old_size, new_size);
    if (buffer->node_blocks == 0) return (exit_status = -1);

    return exit_status;
}

int remember_node(int input, int tmp, struct blockchain* buffer)
{
    int exit_status;

    if (tmp % 10 == 0 && tmp != 0)
        exit_status = my_realloc_nodes_list(buffer, tmp, tmp + 10) == 0 ? 0 : -1;

    buffer->nodes.values[tmp] = input;
    buffer->node_blocks[tmp].content_size = 0;
    buffer->nodes.size++;

    return exit_status;
}

int add_node(char* av_i, struct blockchain* buffer)
{
    int exit_status;
    int input = 0;
    int n_pos = 0;

    if ((input = my_atoi(av_i)) >= 0)
        if (find_node_pos(&n_pos, input, buffer) != -13)
            exit_status = remember_node(input, buffer->nodes.size, buffer) == -1 ? -1 : 2;
        else exit_status = -13;
    else exit_status = input;

    return exit_status;
}

int add_case(char** av, int ac, int* i, struct blockchain* buffer)
{
    int exit_status = 0;

    if (my_strcmp(av[*i], "node") == 0)
    {
        if (ac == 2) exit_status = -10;
        else exit_status = add_node(av[++(*i)], buffer);
    }
    else if (my_strcmp(av[*i], "block") == 0)
    {
        if (ac == 2) exit_status = -15;
        else if (ac == 3) exit_status = -10;
        else
        {
            *i = 3;
            if (av[*i][0] == '*' && av[*i][1] == '\0')
            {
                if( (exit_status = add_block_to_all_nodes(av[2], buffer)) != 3) return exit_status;
            }
            else
                while (*i < ac)
                    if( (exit_status = add_block(av[2], av[(*i)++], buffer)) != 3) return exit_status;
        }
    }
    else exit_status = -18;

    return exit_status;
}
