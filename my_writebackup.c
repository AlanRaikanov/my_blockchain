#include "my_blockchain.h"

int write_nodes(int file_fd, struct blockchain buffer)
{
	int exit_status = 0;
	char tmp[1000];
	int i;

	for (i = 0; i < buffer.nodes.size; i++)
	{
		char tmp2[18];
		my_itoa(tmp2, buffer.nodes.values[i]);
		if (i == 0)
		{
			my_strcpy(tmp, tmp2);
		}
		else
		{
			my_strcat(tmp, ",");
			my_strcat(tmp, tmp2);
		}
	}

	if (i != 0)
    {
		my_strcat(tmp, "\n");
		if (write(file_fd, tmp, my_strlen(tmp)) < 0) exit_status = -19;
	}

	return exit_status;
}

int write_blocks(int file_fd, struct blockchain buffer)
{
	int exit_status = 0;
	char tmp[1000];
	int i;

	for (i = 0; i < buffer.blocks.size; i++)
	{
		if (i == 0)
		{
			my_strcpy(tmp, buffer.blocks.list[i]);
		}
		else
		{
			my_strcat(tmp, ",");
			my_strcat(tmp, buffer.blocks.list[i]);
		}
	}

	if (i != 0)
    {
		my_strcat(tmp, "\n");
		if (write(file_fd, tmp, my_strlen(tmp)) < 0) exit_status = -19;
	}

	return exit_status;
}

int write_node_blocks(int file_fd, struct blockchain buffer)
{
	int exit_status = 0;
	char tmp[1000];

	for (int i = 0; i < buffer.nodes.size; i++)
	{
		int j;
		for (j = 0; j < buffer.node_blocks[i].content_size; j++)
		{
			if (j == 0)
			{
				my_strcpy(tmp, buffer.node_blocks[i].content[j]);
			}
			else
			{
				my_strcat(tmp, ",");
				my_strcat(tmp, buffer.node_blocks[i].content[j]);
			}
		}

		if (j == 0)
        {
            write(file_fd, "\n", 1);
        }
        else
        {
			my_strcat(tmp, "\n");
			if (write(file_fd, tmp, my_strlen(tmp)) < 0) return (exit_status = -19);
		}
	}

	return exit_status;
}

int writebackup(int file_fd, struct blockchain buffer)
{
	int exit_status = 0;

	if (write_nodes(file_fd, buffer) == -19) return (exit_status = -19);
	if (write_blocks(file_fd, buffer) == -19) return (exit_status = -19);
	if (write_node_blocks(file_fd, buffer) == -19) return (exit_status = -19);

	return exit_status;
}
