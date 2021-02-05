#include "my_blockchain.h"

void list_blocks(int n_pos, struct blockchain* buffer)
{
    write(1, ": ", 2);

    if (buffer->node_blocks[n_pos].content_size == 0) write(1, "empty.", 6);

    for (int j = 0; j < buffer->node_blocks[n_pos].content_size; j++)
    {
        write(1, buffer->node_blocks[n_pos].content[j], my_strlen(buffer->node_blocks[n_pos].content[j]));
        if (j != buffer->node_blocks[n_pos].content_size - 1) write(1, ", ", 2);
        else write(1, ".", 1);
    }
}

void list_nodes(my_bool include_blocks, struct blockchain* buffer)
{
    for (int n_pos = 0; n_pos < buffer->nodes.size; n_pos++)
    {
        char tmp[18];
        my_itoa(tmp, buffer->nodes.values[n_pos]);
        write(1, tmp, my_strlen(tmp));
        if (include_blocks) list_blocks(n_pos, buffer);
        write(1, "\n", 1);
    }
}

void ls_case(char* av_i, struct blockchain* buffer)
{
    my_bool include_blocks = FALSE;
    if (my_strcmp(av_i, "-l") == 0) include_blocks = TRUE;
    list_nodes(include_blocks, buffer);
}
