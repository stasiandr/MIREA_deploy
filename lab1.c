#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct Matrix_tag {
    int **elem;
    int n;
    int m;
} Matrix;

void m_resize (Matrix *matrix, int n, int m);
void m_scan (Matrix *matrix);
void m_print (Matrix *matrix);
void m_mul(Matrix *A, Matrix *B, Matrix *C);
void m_pow(Matrix *A, int num, Matrix *B);
void m_add(Matrix *A, Matrix *B, Matrix *C);
void m_sub(Matrix *A, Matrix *B, Matrix *C);
void m_trans(Matrix *A, Matrix *B);
void m_copy(Matrix *A, Matrix *B);


int main() {
    int n1, m1;
    printf("Enter n & m for first matrix:\n");
    scanf("%d %d", &n1, &m1);
    printf("Initialized with %d lines and %d colums\n", n1, m1);
    Matrix *A =  malloc(sizeof(Matrix));
    m_resize(A, n1, m1);
    printf("Enter %d values for first matrix:\n", n1*m1);
    m_scan(A);

    int error_flag = 0;
    char *op_name = malloc(sizeof(char) * 5);
    int n2, m2, num;

    Matrix *B, *C;

    while(1)
    {

        printf("Enter required opetration[ADD/SUB/MUL/POW/TRANS/QUIT]:\n");
        scanf("%s", op_name);

        if (!strcmp(op_name, "QUIT"))
        {
            return 0;
        }

        error_flag =0;
        B = malloc(sizeof(Matrix));

        if (strcmp(op_name, "POW"))
        {
            printf("Enter n & m for second matrix:\n");
            scanf("%d %d", &n2, &m2);
            printf("Initialized with %d lines and %d colums\n", n2, m2);
            printf("%d %d", n2, m2);
            m_resize(B, n2, m2);
            printf("Enter %d values for second matrix:\n", n2*m2);
            m_scan(B);
        }

        C = malloc(sizeof(Matrix));

        if (!strcmp(op_name, "MUL"))
        {
            if (A->m == B->n)
            {
                m_resize(C, A->n, B->m);
                m_mul(A, B, C);
            }
            else
            {
                printf("ERROR: Matrix sizes aren't valid\n");
                error_flag = 1;
            }
        }
        if (!strcmp(op_name, "POW"))
        {
            if (A->n == A->m)
            {
                printf("Enter number for raising to power:\n");
                scanf("%d", &num);
                m_resize(C, A->n, A->m);
                m_pow(A, num, C);
            }
            else
            {
                printf("ERROR: Matrix sizes aren't valid\n");
                error_flag = 1;
            }
        }
        if (!strcmp(op_name, "ADD"))
        {
            if (A->n == B->n && A->m == B->m)
            {
                m_resize(C, A->n, A->m);
                m_add(A, B, C);
            }
            else
            {
                printf("ERROR: Matrix sizes aren't valid\n");
                error_flag = 1;
            }

        }
        if (!strcmp(op_name, "SUB"))
        {
            if (A->n == B->n && A->m == B->m)
            {
                m_resize(C, A->n, A->m);
                m_sub(A, B, C);
            }
            else
            {
                printf("ERROR: Matrix sizes aren't valid\n");
                error_flag = 1;
            }
        }
        if (!strcmp(op_name, "TRANS"))
        {
            m_resize(C, A->m, A->n);
            m_trans(A, C);
        }
        if (!error_flag)
        {
            printf("Answer is:\n");
            m_print(C);

            A = C;
        }

    }

    return 0;
}



void m_resize (Matrix *matrix, int n, int m)
{
    matrix->elem = (int **) realloc(matrix->elem, n * sizeof(int*));

    for(int i = 0; i < n; i++)
    {
        matrix->elem[i] = (int *)realloc(matrix->elem[i], m * sizeof(int));
    }
    matrix->n = n;
    matrix->m = m;
}

void m_scan (Matrix *matrix)
{
    for (int i = 0; i < matrix->n; i++)
    {
        for (int j = 0; j < matrix->m; j++)
        {
            scanf("%d", &matrix->elem[i][j]);
        }
    }
}

void m_print (Matrix *matrix)
{
    for (int i = 0; i < matrix->n; i++)
    {
        for (int j = 0; j < matrix->m; j++)
        {
            printf("[%d] ", matrix->elem[i][j]);
        }
        printf("\n\n");
    }
    printf("n: %d; m: %d\n", matrix->n, matrix->m);
}

void m_mul(Matrix *A, Matrix *B, Matrix *C)
{
    for (int i = 0; i < A->n; i++)
    {
        for (int j = 0; j < B->m; j++)
        {
            C->elem[i][j] = 0;
            for (int col = 0; col < A->m; col++)
            {
                C->elem[i][j] += A->elem[i][col]*B->elem[col][j];
            }
        }
    }
}

void m_pow(Matrix *A, int num, Matrix *B)
{

    Matrix *buff = malloc(sizeof(Matrix));
    m_resize(buff, A->n, A->m);

    m_copy(A, B);

    for (int i = 1; i < num; i++)
    {
        m_mul(A, B, buff);
        m_copy(buff, B);
    }
}

void m_add(Matrix *A, Matrix *B, Matrix *C)
{
    for (int i = 0; i < A->n; i++)
    {
        for (int j = 0; j < A->m; j++)
        {
            C->elem[i][j] = A->elem[i][j] + B->elem[i][j];
        }
    }
}

void m_sub(Matrix *A, Matrix *B, Matrix *C)
{
    for (int i = 0; i < A->n; i++)
    {
        for (int j = 0; j < A->m; j++)
        {
            C->elem[i][j] = A->elem[i][j] - B->elem[i][j];
        }
    }
}

void m_trans(Matrix *A, Matrix *B)
{
    for (int i = 0; i < A->n; i++)
    {
        for (int j = 0; j < A->m; j++)
        {
            B->elem[j][i] = A->elem[i][j];
        }
    }
}

void m_copy(Matrix *A, Matrix *B)
{
    for (int i = 0; i < A->n; i++)
    {
        for (int j = 0; j < A->m; j++)
        {
            B->elem[i][j] = A->elem[i][j];
        }
    }

}
