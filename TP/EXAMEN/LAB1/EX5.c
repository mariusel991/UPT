/*
Aplicația 8.5: Se citește de la tastatură o matrice cu n<=20 linii și coloane. Să se memoreze într-un vector suma
tuturor elementelor de pe fiecare linie și într-un alt vector, suma tuturor elementelor de pe fiecare coloană. Să se
afișeze cei doi vectori. Se vor utiliza pointeri atât pentru vectori cât și pentru matrici.
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void err(char *msg){
    fprintf(stderr, "%s:%s!\n", msg, strerror(errno));
    exit(errno);
}


void AlocMatr(int ***arr, int n){
    if(*arr) return;
    
    ///Prima parte
    *arr = (int **)malloc(n * sizeof(int *));
    if(!*arr){
        err("Error allocating memory");
    }

    for(int i = 0; i < n; i++){
        
        ///A doua parte importanta
        *((*arr) + i) = (int *)malloc(n * sizeof(int));
        
        ///Error handling
        if(!*((*arr) + i)){
            i--;
            fprintf(stderr,"Error alocating column at row %d\n", i);
            for(;i >= 0; i--){
                free(*(*arr + i));
            }
            free(*arr);
            err("");
        }
    }

}

void Read(int ***arr, unsigned const int n){
    if(!*arr)
        err("NULL MATRIX");

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d",&*(*(*arr + i) + j));
        }
    }
}

void Print(int ***arr, unsigned const int n){
    
    if(!*arr)
        err("NULL MATRIX");

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", *(*(*arr + i) + j));
        }
        printf("\n");
    }
}

void Delete(int ***arr, int rows){
    if(!*arr)
        err("NULL MATRIX");

    for(int i = 0; i < rows; i++){
        free(*((*arr) + i));
    }

    free(*arr);
}

void AlocVec(int **arr, const int size){
    *arr = (int *)malloc(size * sizeof(int));
    if(!arr) err("Error allcoating vector");
}

void rows_sum(int ***a, int **acc, const int row_size){
    if(!*a) return;
    if(!*acc) return;

    int sum = 0;

    for(int i = 0; i < row_size; i++){
        sum = 0;
        for(int j = 0; j < row_size; j++){
            sum = sum + (*(*(*a + i) + j));
        }
        *(*acc + i) = sum;
    }
}

void colums_sum(int ***a, int **acc, const int col_size){
    if(!*a) return;
    if(!*acc) return;

    int sum = 0;

    for(int j = 0; j < col_size; j++){
        sum = 0;
        for(int i = 0; i < col_size; i++){
            sum = sum + (*(*(*a + i) + j));
        }
        *(*acc + j) = sum;
    }
}

void PrintVec(const int size, int *arr1, int *arr2){
    for(int i = 0; i < size; i++){
        printf("row %d sum: %d\n" ,i , *(arr1 + i));
        printf("col %d sum: %d\n" ,i , *(arr2 + i));
    }
}

int main(){

    int **a = NULL;
    int *rows = NULL;
    int *colums = NULL;
    int n;

    printf("n = "), scanf("%d",&n);

    AlocMatr(&a, n);
    Read(&a, n);

    printf("\n");
    Print(&a, n);
    printf("\n");
    
    AlocVec(&rows, n);
    AlocVec(&colums, n);
    rows_sum(&a, &rows, n);
    colums_sum(&a, &colums, n);
    PrintVec(n, rows, colums);


    Delete(&a, n);
    free(rows);
    free(colums);

    return 0;
}
