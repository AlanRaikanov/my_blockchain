#include "my_blockchain.h"

void show_message(int exit_status)
{
    switch (exit_status)
    {
        //Error messages:
        case -1:
            my_puts("my_blockchain: Error: No more resources available on the computer.");
            my_puts("my_blockchain: Hint: No more heap memory.");
            break;
        case -2:
            my_puts("my_blockchain: Error: No more resources available on the computer.");
            my_puts("my_blockchain: Hint: No more heap memory for sorting.");
            break;
        case -10:
            my_puts("my_blockchain: Error: You should specify node id.");
            break;
        case -11:
            my_puts("my_blockchain: Error: Node cannot be a negative value.");
            break;
        case -12:
            my_puts("my_blockchain: Error: Node should be a digit.");
            break;
        case -13:
            my_puts("my_blockchain: Error: This node already exists.");
            break;
        case -14:
            my_puts("my_blockchain: Error: This node doesn't exist.");
            break;
        case -15:
            my_puts("my_blockchain: Error: You should specify block id.");
            break;
        case -16:
            my_puts("my_blockchain: Error: This block already exists.");
            break;
        case -17:
            my_puts("my_blockchain: Error: This block doesn't exists.");
            break;
        case -18:
            my_puts("my_blockchain: Error: Command not found.");
            break;
        case -19:
            my_puts("my_blockchain: Error: No more resources available on the computer.");
            my_puts("my_blockchain: Hint: No more storage memory.");
            break;
        //Successfull execution messages:
        case 0:
            break;
        case 1:
            my_puts("my_blockchain: Saving and quitting.");
            break;
        case 2:
            my_puts("my_blockchain: Successfully added node.");
            break;
        case 3:
            my_puts("my_blockchain: Successfully added block.");
            break;
        case 4:
            my_puts("my_blockchain: Successfully removed node.");
            break;
        case 5:
            my_puts("my_blockchain: Successfully removed block from all nodes.");
            break;
        case 6:
            my_puts("my_blockchain: Successfully synchronised all nodes.");
            break;
        //Undefined behaviour message:
        default:
            my_puts("Unknown error.");
            break;
    }
}

void free_blockchain(struct blockchain* buffer)
{
    int troll;
    if (buffer->nodes.size == 0)
        troll = 10;
    else
        troll = buffer->nodes.size + (10 - buffer->nodes.size % 10) * ((buffer->nodes.size % 10 + 9) / 10);
        // same as:
        //      int anti_troll = buffer.nodes.size % 10 == 0 ? buffer.nodes.size : buffer.nodes.size + 10 - buffer.nodes.size % 10;
    for (int i = 0; i < troll; i++)
    {
        free(buffer->node_blocks[i].content);
    }
    free(buffer->node_blocks);
    free_arr(buffer->blocks.list, buffer->blocks.size);
    free(buffer->nodes.values);
}

char** sort_input(char* input, char separator, int* ac, char** av)
{
    *ac = 0;

    for (int i = 0; input[i]; i++)
    {
        if (input[i] == separator) continue;

        if (*ac % 10 == 0 && *ac != 0)
        {
            av = my_realloc_arr(av, *ac, *ac + 10);
            if (av == 0) return 0;
        }
        av[*ac] = malloc(30);
        if (av[*ac] == 0) return 0;

        int j = 0;
        for (; input[i] != separator && input[i]; j++)
            av[*ac][j] = input[i++];
        av[*ac][j] = '\0';
        i--;
        (*ac)++;
    }

    return av;
}

int check_input(char* input, struct blockchain* buffer)
{
    int exit_status = 0;
    int i = 0;
    int ac;
    char** av;

    if ( (av = malloc(sizeof(char*) * 10)) != 0 )
    {
        if ( (av = sort_input(input, ' ', &ac, av)) != 0 )
        {
            if (ac >= 2 && my_strcmp(av[i], "add") == 0)
            {
                i++;
                exit_status = add_case(av, ac, &i, buffer);
            }
            else if (ac >= 2 && my_strcmp(av[i], "rm") == 0)
            {
                i++;
                exit_status = rm_case(av, ac, &i, buffer);
            }
            else if (my_strcmp(av[i], "ls") == 0)
            {
                if (ac > 1) i++;

                ls_case(av[i], buffer);
            }
            else if (my_strcmp(av[i], "sync") == 0)
            {
                exit_status = synchronise(buffer);
            }
            else if (my_strcmp(av[i], "quit") == 0)
            {
                exit_status = 1;
            }
            else
            {
                exit_status = -18;
            }
        }
        else exit_status = -2;

        free_arr(av, ac);
    }
    else exit_status = -1;

    return exit_status;
}

char* is_sync(struct blockchain buffer)
{
    for (int i = 0; i < buffer.nodes.size; i++)
        if (buffer.blocks.size != buffer.node_blocks[i].content_size)
            return "-";
    return "s";
}

void get_status(struct blockchain buffer)
{
    char output[18];
    char tmp[16];
    my_strcpy(output, "[");
    my_strcat(output, is_sync(buffer));
    my_itoa(tmp, buffer.nodes.size);
    my_strcat(output, tmp);
    my_strcat(output, "]> ");
    write(1, output, my_strlen(output));
}

void prompt(struct blockchain* buffer)
{
    char* input;
    int exit_status;

    do
    {
        get_status(*buffer);
        input = my_readline(0);
        exit_status = check_input(input, buffer);
        show_message(exit_status);
        free(input);
    } while (exit_status != 1 && exit_status != -1 && exit_status != -2);
}

int initial_blockchain(struct blockchain* buffer)
{
    int exit_status = 0;

    buffer->nodes.size = 0;
    if (!(buffer->nodes.values = malloc(sizeof(int) * 10))) return (exit_status = -1);
    buffer->blocks.size = 0;
    if (!(buffer->blocks.list = malloc(sizeof(char*) * 10))) return (exit_status = -1);
    if (!(buffer->node_blocks = malloc(sizeof(struct s_node_blocks) * 10))) return (exit_status = -1);

    for (int i = 0; i < 10; i++)
    {
        if(!(buffer->node_blocks[i].content = malloc(sizeof(char*) * 10))) return (exit_status = -1);
        buffer->node_blocks[i].content_size = 0;
    }

    return exit_status;
}

int my_blockchain()
{
    int file_fd;
    int exit_status = 0;
    struct blockchain buffer;

    if ((exit_status = initial_blockchain(&buffer)) != 0) return exit_status;

    if ((file_fd = open("blockchain", O_RDONLY)) > 2)
    {
        if ( (exit_status = readbackup(file_fd, &buffer)) != 0 ) return exit_status;

        close(file_fd);
    }

    prompt(&buffer);

    if ((file_fd = open("blockchain", O_CREAT | O_WRONLY | O_TRUNC)) > 2)
    {
        if ((exit_status = writebackup(file_fd, buffer)) != 0) return exit_status;

        close(file_fd);
    }

    free_blockchain(&buffer);

    return exit_status;
}

int main()
{
    int exit_status = my_blockchain();
    show_message(exit_status);

    return 0;
}
