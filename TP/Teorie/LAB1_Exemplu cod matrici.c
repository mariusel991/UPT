#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void myError(char *msg) {

    perror(msg);
    exit(errno);
}

int *allocateVector(unsigned const int size) {

    int *tmp = (int *) calloc(size, sizeof(int));

    if (NULL == tmp) {
        myError("Error at allocating dynamic memory of vector");
    }

    return tmp;
}

void *deallocateVector(void *vector) {
    free(vector);
    vector = NULL;

    return NULL;
}

int *reallocateVector(int *vector, unsigned const int oldSize, unsigned const int sizeToBeAdded) {

    int *tmp = (int *) realloc(vector, (oldSize + sizeToBeAdded) * sizeof(int));
    if (NULL == tmp) {
        myError("Error at reallocating memory of vector");
    }

    for(int i = oldSize ; i < oldSize + sizeToBeAdded; ++i){
        tmp[i] = 0;
    }

    return tmp;
}

void printVector(const int *vector, unsigned const int size) {

    for (unsigned int i = 0; i < size; ++i) {
        printf("%d ", vector[i]);
    }

    printf("\n");
}

void printVectorWithPointers(int *vector, unsigned const int size) {

    const int *end = vector + size;
    int *iterator = vector;
    
    for (; iterator != end; ++iterator) {
        printf("%d ", *iterator);
    }
    printf("\n");
}

int **allocateMatrix(unsigned const int rows, unsigned const int columns) {

    int **tmp = (int **) malloc(rows * sizeof(int *));

    if (NULL == tmp) {
        myError("Error at allocating dynamic memory of matrix");
    }

    for (long i = 0; i < rows; ++i) {
        tmp[i] = (int *) calloc(columns, sizeof(int));
        if (NULL == tmp[i]) {
            char errorMessage[100];
            sprintf(errorMessage, "Error at allocating dynamic memory of row: %ld", i);

            i--;
            for (; i >= 0; --i) {
                free(tmp[i]);
            }
            free(tmp);
            tmp = NULL;

            myError(errorMessage);
        }
    }

    return tmp;
}

void *deallocateMatrix(void **matrix, unsigned const int rows) {

    for (unsigned int i = 0; i < rows; ++i) {
        free(matrix[i]);
        matrix[i] = NULL;
    }
    free(matrix);
    matrix = NULL;

    return NULL;
}

int **reallocateMatrix(int **matrix, unsigned const int oldRows, unsigned const int oldColumns,
                       unsigned const int rowsToBeAdded, unsigned const int columnsToBeAdded) {

    unsigned const int newRows = oldRows + rowsToBeAdded;
    unsigned const int newColumns = oldColumns + columnsToBeAdded;

    int **tmp = (int **) realloc(matrix, newRows  * sizeof(int *));

    if (NULL == tmp) {
        myError("Error at reallocating memory of matrix");
    }

    for (long i = 0; i < oldRows; ++i) {
        tmp[i] = (int *) realloc(tmp[i], newColumns * sizeof(int));
        if (NULL == tmp[i]) {
            char errorMessage[100];
            sprintf(errorMessage, "Error at allocating dynamic memory of row: %ld", i);

            i--;
            for (; i >= 0; --i) {
                free(tmp[i]);
            }

            free(tmp);
            tmp = NULL;

            myError(errorMessage);
        }

        for (unsigned int j = oldColumns; j < newColumns; ++j) {
            tmp[i][j] = 0;
        }
    }

    for (long i = oldRows; i < newRows; ++i) {
        tmp[i] = (int *) calloc(newColumns, sizeof(int));
        if (NULL == tmp[i]) {
            char errorMessage[100];
            sprintf(errorMessage, "Error at allocating dynamic memory of row: %ld", i);

            i--;
            for (; i >= 0; --i) {
                free(tmp[i]);
            }

            free(tmp);
            tmp = NULL;

            myError(errorMessage);
        }
    }


    return tmp;
}

void printMatrix(const int **matrix, unsigned const int rows, unsigned const int columns) {

    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < columns; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void printMatrixWithPointers(const int **matrix, unsigned const int rows, unsigned const int columns) {

    for (const int **p = matrix; p != matrix + rows; ++p) {
        for (const int *q = *p; q != *p + columns; ++q) {
            printf("%5d", *q);
        }
        printf("\n");
    }

}

void printMatrixWithPointers2(unsigned const int rows, unsigned const int columns, const int matrix[][columns])
{
    for (const int (*p)[columns] = matrix; p != matrix + rows; ++p)
    {
        for (const int *q = *p; q != *p + columns; ++q)
        {
            printf("%5d", *q);
        }
        printf("\n");
    }
}


/**
v0 : (Va0 Va1, Va2)
v1 : (Vb0 Vb1, Vb2)
    .
    .
vn

*/

int main() {

    int *vector = allocateVector(4);
    vector[2] = 3;
    printVector(vector, 4);
    printf("with pointers:\n");
    printVectorWithPointers(vector, 4);

    vector = reallocateVector(vector, 4, 2);
    vector[5] = 4;
    printf("vector realloc:\n");
    printVector(vector, 6);

    vector = deallocateVector(vector);
    if (NULL == vector) {
        printf("vector is NULL\n");
    }

    int **matrix = allocateMatrix(3, 3);
    matrix[0][1] = 3;
    printf("with pointers:\n");
    printMatrixWithPointers((const int **) matrix, 3, 3);

    printf("matrix realloc:\n");
    matrix = reallocateMatrix(matrix, 3, 3, 2, 2);
    matrix[3][3] = 4;
    printMatrixWithPointers((const int **) matrix, 5, 5);

    matrix = deallocateMatrix((void **) matrix, 5);
    if (NULL == matrix) {
        printf("matrix is NULL");
    }

    int test[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    printMatrixWithPointers2(3, 3, test);


    return 0;
}
