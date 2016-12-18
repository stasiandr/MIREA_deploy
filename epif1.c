#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} dict_elem;

typedef struct {
    dict_elem  **elem_vector;
    size_t size;
} dict;


dict dict_push(dict *a, char *key, char *value)
{
    a->elem_vector = (dict_elem**) realloc(a->elem_vector, sizeof(dict_elem) * (a->size + 1));
    a->elem_vector[a->size] = (dict_elem*) realloc(a->elem_vector[a->size], sizeof(dict_elem));
    a->elem_vector[a->size]->key = key;
    a->elem_vector[a->size]->value = value;
    a->size += 1;
}

char *get_by_key(dict *a, char *key)
{
    for (size_t i = 0; i < a->size;i++)
    {
        if (!strcmp(a->elem_vector[i]->key, key))
            return a->elem_vector[i]->value;
    }
    return NULL;
}

int change_value_by_key(dict *a, char *key, char *value)
{
    for (size_t i = 0; i < a->size;i++)
    {
        if (!strcmp(a->elem_vector[i]->key, key))
            a->elem_vector[i]->value = value;
            return 0;
    }
    return 1;
}

void init_dict(dict *a)
{
    a = (dict*) malloc(sizeof(dict));
    a->size = 0;
}

/*
char *dict_to_str(dict *a) {}
*/

int args_to_dict(int argc, char **argv, dict *a)
{
    int special = 0;
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-' && argv[i][2] == '\0')
        {
            for (int j = 1; j < strlen(argv[i]); j++)
            {
                dict_push(a, &argv[i][j], "");
            }
        }
        if (argv[i][0] == '-' && argv[i][2] != '\0')
        {
            dict_push(a, &argv[i][1], "");
        }
        if (argv[i][0] != '-')
        {
            change_value_by_key(a, &argv[i-1][1], argv[i]);
        }
    }
}


int main(int argc, char **argv)
{
    dict *a;
    a = (dict*) malloc(sizeof(dict));
    a->size = 0;

    args_to_dict(argc, argv, a);

    printf("%d\n", a->size);
    for (size_t i = 0; i < a->size;i++)
    {
        printf("%s: %s\n", a->elem_vector[i]->key, a->elem_vector[i]->value);
    }


    free(a);
    return 0;
}

