/*
Subiect 8.1: Se citesc de la tastatură două numere n și m, n>=m. Pe urmă se citesc două matrici pătratice de
dimensiuni n, respectiv m, conținând numere întregi. Afișați toate pozitiile unde a doua matrice apare în prima
matrice. Afișarea se va face pe ecran sub forma unor perechi de forma (linie, coloană). Dacă a doua matrice nu
apare în prima matrice, se va afișa textul “Nu apare”.
Spre exemplu dacă se introduce:
5 3
1 0 1 1 1
0 1 0 1 1
1 0 1 1 1
0 1 0 1 1
1 0 1 1 1

0 1 1
1 0 1
0 1 1
se va afișa pe ecran:
(0,1) (2,1)

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

void exista_submatrice(int ***a, int ***b, unsigned int n, unsigned int m, int *ok){

    if(!*a || !*b){
        err("One of the martix is NULL");
    }

    for(int i = 0; i <= n - m; i++){
        for(int j = 0; j <= n - m; j++){
            /// Parcurgem matricile
            int aux = 1;
            for(int x = 0; x < m; x++){
                for(int y = 0; y < m; y++){
                    if((*b)[x][y] != (*a)[i + x][j + y]){
                        aux = 0;
                        break;
                    }
                }
                if(aux == 0) break;
            }
            
            if(aux == 1){
                *ok = 1;
                printf("(%d,%d) ",i,j);
            }            
        }
    }
    if(*ok == 1){
        printf("\n");
    }
}



int main(){

    int **a = NULL;
    int **b = NULL;
    int n,m;
    int ok = 0;

    printf("n = "), scanf("%d",&n);
    printf("m = "), scanf("%d",&m);

    if(n < m) return -1;

    AlocMatr(&a, n);
    AlocMatr(&b, m);
    Read(&a, n);
    Read(&b, m);
    
    printf("\n");
    Print(&a, n);
    printf("\n");
    Print(&b, m);
    printf("\n");

    exista_submatrice(&a, &b, n, m, &ok);
    if(ok == 0){
        printf("Nu apare\n");
    }

    Delete(&a, n);
    Delete(&b, m);

    return 0;
}
