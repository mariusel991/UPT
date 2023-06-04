/*
Aplicația 8.4: Se citește de la tastatură o matrice pătratică cu n<=50 linii și coloane. Să se interschimbe elementele
de deasupra diagonalei principale, considerată ca axă de simetrie, cu elementele de sub diagonala principală,
elementele de pe diagonala principală rămânând la fel. De exemplu matricea:
1 2 3
4 5 6
7 8 9
Va deveni:
1 4 7
2 5 8
3 6 9
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

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void Simetric_Change(int ***arr, unsigned const int n){
    if(!*arr)
        err("NULL MATRIX");

    for(int i = 0; i < n; i++){
        for(int j = 0; j < i; j++){
            swap(&*(*(*arr + i) + j) , &*(*(*arr + j) + i)) ;
        }
    }
    
}

int main(){

    int **a = NULL;
    int n;

    printf("n = "), scanf("%d",&n);

    AlocMatr(&a, n);
    Read(&a, n);

    printf("\n");
    Print(&a, n);

    Simetric_Change(&a, n);
    printf("\n");
    Print(&a, n);

    Delete(&a, n);

    return 0;
}
