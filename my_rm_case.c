#include "my_blockchain.h"

int find_global_block(char* av_b, int* g_pos, struct blockchain* buffer)
{
    int exit_status = -16;

    for (*g_pos = 0; *g_pos < buffer->blocks.size; (*g_pos)++)
        if (my_strcmp(av_b, buffer->blocks.list[*g_pos]) == 0) break;
    if (*g_pos == buffer->blocks.size) exit_status = -17;

    return exit_status;
}

int forget_global_block(char* av_b, struct blockchain* buffer)
{
    int exit_status = 0;
    int g_pos;

    if (find_global_block(av_b, &g_pos, buffer) != -17)
    {
        free(buffer->blocks.list[g_pos]);
        for (; g_pos < buffer->blocks.size - 1; g_pos++)
            buffer->blocks.list[g_pos] = buffer->blocks.list[g_pos + 1];
        buffer->blocks.size--;

        if (buffer->blocks.size != 0 && buffer->blocks.size % 10 == 0)
            buffer->blocks.list = my_realloc_arr(buffer->blocks.list, buffer->blocks.size + 10, buffer->blocks.size);
    }
    else exit_status = -17;

    return exit_status;
}

void forget_the_block_in_node(char* av_b, int n_pos, struct blockchain* buffer)
{
    int b_pos;

    if (find_node_block_pos(av_b, n_pos, &b_pos, buffer) == -16)
    {
        for (; b_pos < buffer->node_blocks[n_pos].content_size - 1; b_pos++)
            buffer->node_blocks[n_pos].content[b_pos] = buffer->node_blocks[n_pos].content[b_pos + 1];
        buffer->node_blocks[n_pos].content_size--;

        if (buffer->node_blocks[n_pos].content_size != 0 && buffer->node_blocks[n_pos].content_size % 10 == 0)
            buffer->node_blocks[n_pos].content = my_realloc_arr(buffer->node_blocks[n_pos].content, buffer->node_blocks[n_pos].content_size + 10, buffer->node_blocks[n_pos].content_size);
    }
}

int rm_block(char* av_b, struct blockchain* buffer)
{
    int exit_status = 5;

    for (int n_pos = 0; n_pos < buffer->nodes.size; n_pos++)
        forget_the_block_in_node(av_b, n_pos, buffer);

    if (forget_global_block(av_b, buffer) == -17) exit_status = -17;

    return exit_status;
}

void forget_the_node(int n_pos, struct blockchain* buffer)
{
    struct s_node_blocks tmp = buffer->node_blocks[n_pos];

    buffer->nodes.size--;
    for (; n_pos < buffer->nodes.size; n_pos++)
    {
        buffer->nodes.values[n_pos] = buffer->nodes.values[n_pos + 1];
        buffer->node_blocks[n_pos] = buffer->node_blocks[n_pos + 1];
    }
    buffer->node_blocks[n_pos] = tmp;

    if (buffer->nodes.size % 10 == 0 && buffer->nodes.size != 0)
    {
        buffer->nodes.values = my_realloc_int(buffer->nodes.values, (buffer->nodes.size + 10), buffer->nodes.size);
        buffer->node_blocks = my_realloc_struct(buffer->node_blocks, (buffer->nodes.size + 10), buffer->nodes.size);
    }
}

my_bool block_unique(int b_pos, char* str, struct blockchain* buffer)
{
    for (int j = 0; j < buffer->nodes.size; j++)
    {
        if (j == b_pos) continue;
        for (int k = 0; k < buffer->node_blocks[j].content_size; k++)
            if (strcmp(str, buffer->node_blocks[j].content[k]) == 0)
                return FALSE;
    }
    return TRUE;
}

void forget_the_node_blocks(int n_pos, struct blockchain* buffer)
{
    for (int i = 0; i < buffer->node_blocks[n_pos].content_size; i++)
        if (block_unique(n_pos, buffer->node_blocks[n_pos].content[i], buffer))
            forget_global_block(buffer->node_blocks[n_pos].content[i], buffer);
    buffer->node_blocks[n_pos].content_size = 0;
}

int find_node_pos(int* n_pos, int input, struct blockchain* buffer)
{
    for (*n_pos = 0; *n_pos < buffer->nodes.size; (*n_pos)++)
        if (input == buffer->nodes.values[*n_pos]) break;

    if (*n_pos == buffer->nodes.size) return -14;

    return -13;
}

int rm_node(char* av_i, struct blockchain* buffer)
{
    int exit_status = 4;
    int input = 0;
    int n_pos = 0;

    if ((input = my_atoi(av_i)) < 0) return ( exit_status = input );

    if (find_node_pos(&n_pos, input, buffer) == -14) return (exit_status = -14);

    forget_the_node_blocks(n_pos, buffer);

    forget_the_node(n_pos, buffer);

    return exit_status;
}

int rm_case(char** av, int ac, int* i, struct blockchain* buffer)
{
    int exit_status = 0;

    if (my_strcmp(av[*i], "node") == 0)
    {
        if (ac == 2) exit_status = -10;
        else 
        {
            if (my_strcmp(av[2], "*") == 0)
                for (int j = buffer->nodes.size - 1; j >= 0; j--)
                {
                    char tmp[20];
                    my_itoa(tmp, buffer->nodes.values[j]);
                    exit_status = rm_node(tmp, buffer);
                }
            else
                exit_status = rm_node(av[++(*i)], buffer);
        }
    }
    else if (my_strcmp(av[*i], "block") == 0)
    {
        if (ac == 2) exit_status = -15;
        else exit_status = rm_block(av[++(*i)], buffer);
    }
    else exit_status = -18;

    return exit_status;
}
