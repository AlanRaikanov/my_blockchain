#include "my_blockchain.h"

int read_sorted_input(int j, int ac, char** av, struct blockchain* buffer)
{
    int exit_status = 0;

    for (int i = 0; i < ac; i++)
    {
        if (j == 0)
        {
            if (add_node(av[i], buffer) == -1 ) return (exit_status = -1);
        }
        else if (j == 1)
        {
            int x = i;
            if (remember_global_block(av[i], &x, buffer) == -1) return (exit_status = -1);
        }
        else
        {
            char tmp[30];
            my_itoa(tmp, buffer->nodes.values[j - 2]);
            if ( (exit_status = add_block(av[i], tmp, buffer)) != 3 ) return exit_status;
            exit_status = 0;
        }
    }

    return exit_status;
}

int readbackup(int file_fd, struct blockchain* buffer)
{
	char* input;
	int exit_status = 0;

	for (int j = 0; (input = my_readline(file_fd)); j++)
	{
		char** av = malloc(sizeof(char*) * 10);
		if (av == 0) return (exit_status = -1);
		int ac = 0;

		if ( (av = sort_input(input, ',', &ac, av)) == 0 ) return -2;
        if ( (exit_status = read_sorted_input(j, ac, av, buffer)) != 0) return exit_status;

		free_arr(av, ac);
		free(input);
	}

	return exit_status;
}
