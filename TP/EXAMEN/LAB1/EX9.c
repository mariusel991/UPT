/*
Aplicația 8.9: Se citește un număr n<=10. Se cere să se inițializeze o matrice a[n][n] cu 1 pe diagonale și cu 0 în
rest. Să se afișeze matricea.
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

void InitMatr(int ***arr, const int size){
    if(!*arr) return;

    for(int i = 0; i < size; i++){
        memset(*(*arr + i), 0, size * sizeof(int));
        (*(*(*arr + i) + i)) = 1;
    }
}

int main(){

    int **a = NULL;
    int n;

    printf("n = "), scanf("%d",&n);

    AlocMatr(&a, n);
    //Read(&a, n);
    InitMatr(&a, n);

    printf("\n");
    Print(&a, n);
    printf("\n");


    Delete(&a, n);

    return 0;
}
