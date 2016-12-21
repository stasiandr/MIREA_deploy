#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define MAX_SIZE 80

typedef struct {
    char *name;
    char *number;
} elem;

typedef struct {
    elem **vec;
    int size;
} Contacts;

void  addContact(Contacts* A, char* name, char* number);
void  delContact(Contacts* A, int id);
void  printContact(Contacts* A);
void  changeContact(Contacts* A, int id, char* name, char* number);
char* getByName(Contacts* A, char* name);
char* getByNumber(Contacts* A, char* number);
void  printSorted(Contacts* A);
void  export(Contacts* A, char* filename);
void  import(Contacts* A, char* filename);

void addContact(Contacts *A, char *name, char* number)
{
    A->vec = (elem **) realloc(A->vec, (A->size + 1) * sizeof(elem*));
    A->vec[A->size] = (elem *) realloc(A->vec[A->size], sizeof(elem));
    A->vec[A->size]->name = (char*) realloc(A->vec[A->size]->name, sizeof(char) * MAX_SIZE);
    A->vec[A->size]->number = (char*) realloc(A->vec[A->size]->number, sizeof(char) * MAX_SIZE);
    strcpy(A->vec[A->size]->name, name);
    strcpy(A->vec[A->size]->number, number);
    A->size += 1;
}

void delContact(Contacts *A, int id)
{
    for (int i = id; i < A->size - 1; i++)
    {
        A->vec[i]->name = A->vec[i+1]->name;
        A->vec[i]->number = A->vec[i+1]->number;
    }
    A->size -= 1;
}

void printContact(Contacts *A)
{
    for (int i = 0; i < A->size; i++)
    {
        printf("%s  <->  %s\n", A->vec[i]->name, A->vec[i]->number);
    }
}

void changeContact(Contacts *A, int id, char *name, char *number)
{
    A->vec[id]->name = name;
    A->vec[id]->number = number;
}

char* getByName(Contacts *A, char* name)
{
    for (int i = 0; i < A->size; i++)
    {
        if (A->vec[i]->name == name)
        {
            return A->vec[i]->number;
        }
    }
    return "NOT FOUND!";
}

char* getByNumber(Contacts *A, char* number)
{
    for (int i = 0; i < A->size; i++)
    {
        if (A->vec[i]->number == number)
        {
            return A->vec[i]->name;
        }
    }
    return "NOT FOUND!";
}

void printSorted(Contacts *A)
{
    char **strs;
    strs = (char **) malloc(sizeof(char*) * A->size);
    for (int i = 0; i < A->size; i++)
    {
        strs[i] = (char *) malloc(sizeof(char) * MAX_SIZE);
        strcat(strs[i], A->vec[i]->name);
        strcat(strs[i], "  <-->  ");
        strcat(strs[i], A->vec[i]->number);
        strcat(strs[i], "\n");
    }

    char *buff = (char*) malloc(sizeof(char) * MAX_SIZE);
    for (int j = 0; j < A->size; j++)
    {
        for (int i = j; i < A->size - 1; i++)
        {
            if (strcmp(strs[i], strs[i+1]))
            {
                buff = strs[i];
                strs[i] = strs[i+1];
                strs[i+1] = buff;
            }
        }
    }

    for (int i = 0; i < A->size; i++)
    {
        printf("%s", strs[i]);
    }
}

void export(Contacts *A, char *filename)
{
    FILE *fp;

    fp = fopen(filename, "w+");
    for (int i = 0; i < A->size; i++)
    {
        fprintf(fp,"%s", A->vec[i]->name);
        fprintf(fp, "\n");
        fprintf(fp,"%s", A->vec[i]->number);
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void import(Contacts *A, char *filename)
{
    FILE *fp;

    fp = fopen(filename, "r");

    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;

    char *buff = malloc(sizeof(char) * MAX_SIZE);
    while ((read = getline(&line, &len, fp)) != -1) {

    line[read-1] = '\0';
        if (i % 2 == 0)
        {
            strcpy(buff, line);
        }
        if (i % 2 == 1)
        {
            printf("%s %s\n", line, buff);
            addContact(A, line, buff);
        }
        i++;
    }
    fclose(fp);
}
