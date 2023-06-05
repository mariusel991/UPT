/*
Aplicația 8.10: Se citește un număr n<=10 de produse și pentru fiecare produs vânzările lui trimestriale pe un an
(4 valori). Se cere să se afișeze care produse au înregistrat o creștere continuă a vânzărilor în decurs de un an
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void err(char *msg){
    fprintf(stderr, "%s:%s!\n", msg, strerror(errno));
    exit(errno);
}


void AlocMatr(int ***arr, int m, int n){
    if(*arr) return;
    
    ///Prima parte
    *arr = (int **)malloc(m * sizeof(int *));
    if(!*arr){
        err("Error allocating memory");
    }

    for(int i = 0; i < m; i++){
        
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

void Read(int ***arr, unsigned const int m, unsigned const int n){
    if(!*arr)
        err("NULL MATRIX");

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            scanf("%d",&*(*(*arr + i) + j));
        }
    }
    printf("\n");
}

void Print(int ***arr, unsigned const int m, unsigned const int n){
    
    if(!*arr)
        err("NULL MATRIX");

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", *(*(*arr + i) + j));
        }
        printf("\n");
    }
    printf("\n");
}

void Delete(int ***arr, int rows){
    if(!*arr)
        err("NULL MATRIX");

    for(int i = 0; i < rows; i++){
        free(*((*arr) + i));
    }

    free(*arr);
}

void Inmultire(int ***a, int ***b, int ***c, const int m, const int n, const int p){

    int acc = 0;
    /// m n
    /// n p
    for(int i = 0; i < m; i++){
        
        for(int j = 0; j < p; j++){
            for(int k = 0; k < n; k++){
                acc = acc + ( (*a)[i][k] * (*b)[k][j] );
            }
            (*c)[i][j] = acc;
            acc = 0;

        }
    }
}


int main(){

    int **a = NULL;
    int **b = NULL;
    int **c = NULL;
    
    int m, n, p;

    printf("m = "), scanf("%d",&m);
    printf("n = "), scanf("%d",&n);
    printf("p = "), scanf("%d",&p);


    AlocMatr(&a, m, n);
    AlocMatr(&b, n, p);
    AlocMatr(&c, m, p);

    Read(&a, m, n);
    Read(&b, n, p);

    Inmultire(&a, &b, &c, m, n, p);
    Print(&c, m, p);
    printf("\n");

    Delete(&a, m);
    Delete(&b, n);
    Delete(&c, m);

    return 0;
}
