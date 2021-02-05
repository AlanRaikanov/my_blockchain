#include "my_blockchain.h"

int my_strcmp(const char* s1, const char* s2)
{
    for (int i = 0; s1[i] || s2[i]; i++)
        if (s1[i] != s2[i]) return s1[i] - s2[i];
    return 0;
}

int my_strlen(char* param_1)
{
    for (int i = 0;; i++)
        if (!param_1[i]) return i;
}

void my_strcpy(char* str1, char* str2)
{
    for (int i = 0; (str1[i] = str2[i]); i++);
}

void my_strcat(char* str1, char* str2)
{
    int i = strlen(str1);
    for (int j = 0; (str1[i++] = str2[j]); j++);
}

int* my_realloc_int(int* array, int size, int new_size)
{
    int* out = malloc(sizeof(int) * new_size);
    if (out == 0) return 0;
    for (int i = 0; i < size && i < new_size; i++)
        out[i] = array[i];
    free(array);
    return out;
}

char* my_realloc_str(char* str, int old_size, int size)
{
    char* out = malloc(size);
    if (out == 0) return 0;
    for (int i = 0; i < old_size && i < size; i++)
        out[i] = str[i];
    free(str);
    return out;
}

char** my_realloc_arr(char** arr, int old_size, int new_size)
{
    char** out = malloc(sizeof(char*) * new_size);
    if (out == 0) return 0;
    for (int i = 0; i < old_size && i < new_size; i++)
        out[i] = arr[i];
    free(arr);
    return out;
}

struct s_node_blocks* my_realloc_struct(struct s_node_blocks* structure, int old_size, int new_size)
{
    struct s_node_blocks* output = malloc(sizeof(struct s_node_blocks) * new_size);
    if (output == 0) return 0;
    for (int i = 0; i < old_size && i < new_size; i++)
    {
        output[i].content = structure[i].content;
        output[i].content_size = structure[i].content_size;
    }
    for (int i = old_size; i < new_size; i++)
    {
        output[i].content = malloc(sizeof(char*) * 10);
        if (output[i].content == 0) return 0;
        output[i].content_size = 0;
    }
    for (int i = new_size; i < old_size; i++)
    {
        free(structure[i].content);
    }
    free(structure);
    return output;
}

int my_atoi(const char* input)
{
    int index = 0;
    int result = 0;

    if (input[0] == '-') return -11;
    if (input[0] == '+') index++;

    for (; input[index]; index++)
    {
        if (input[index] < '0' || input[index] > '9') return -12;
        result = result * 10 + (input[index] - '0');
    }

    return result;
}

void my_itoa(char* p1, int p2)
{
    char out_0[16];
    char* out = &out_0[15];
    *out = '\0';

    do
    {
        *--out = '0' + p2 % 10;
        p2 /= 10;
    } while (p2);

    my_strcpy(p1, out);
}

int free_arr(char** arr, int ac)
{
    for (int i = 0; i < ac; i++)
        free(arr[i]);
    free(arr);
    return 0;
}

void my_puts(char* str)
{
    write(1, str, my_strlen(str));
    write(1, "\n", 1);
}
