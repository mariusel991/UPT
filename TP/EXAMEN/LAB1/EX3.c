/*
Aplicația 8.3: Se citește de la tastatură un număr n<=10 și un număr m<=20. Se cere să se scrie un program care
generează o matrice cu m linii și n coloane în care sunt puse toate numerele de la 1,2,3,...,m*n. Se vor utiliza
pointeri.
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void err(char *msg){
    fprintf(stderr, "%s:%s!\n", msg, strerror(errno));
    exit(errno);
}


void AlocMatr(int ***arr, int n, int m){
    if(*arr) return;
    
    ///Prima parte
    *arr = (int **)malloc(n * sizeof(int *));
    if(!*arr){
        err("Error allocating memory");
    }

    for(int i = 0; i < n; i++){
        
        ///A doua parte importanta
        *((*arr) + i) = (int *)malloc(m * sizeof(int));
        
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

void GenMat(int ***arr, unsigned const int n, unsigned const int m){
    if(!*arr)
        err("NULL MATRIX");

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            *(*(*arr + i) + j ) = m * i + j + 1;
        }
    }
}

void Print(int ***arr, unsigned const int n, unsigned const int m){
    
    if(!*arr)
        err("NULL MATRIX");

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            printf("%d ", *(*(*arr + i) + j ));
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

int main(){

    int **a = NULL;
    int n,m;

    printf("n = "), scanf("%d",&n);
    printf("m = "), scanf("%d",&m);

    AlocMatr(&a, n, m);
    GenMat(&a, n, m);
    Print(&a, n, m);
    Delete(&a, n);

    return 0;
}
