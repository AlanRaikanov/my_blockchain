#include "my_blockchain.h"

int synchronise(struct blockchain* buffer)
{
	int exit_status = 6;

	for (int n_pos = 0; n_pos < buffer->nodes.size; n_pos++)
		if (buffer->node_blocks[n_pos].content_size != buffer->blocks.size)
		{
			int b_pos = 0;

			for(; b_pos < buffer->node_blocks[n_pos].content_size; b_pos++)
    			if (my_strcmp(buffer->node_blocks[n_pos].content[b_pos], buffer->blocks.list[b_pos]) != 0)
                   buffer->node_blocks[n_pos].content[b_pos] = buffer->blocks.list[b_pos];

			for (; b_pos < buffer->blocks.size; b_pos++)
				if (remember_node_block(b_pos, n_pos, b_pos, buffer) == -1) return (exit_status = -1);
		}

	return exit_status;
}
