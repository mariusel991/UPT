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


void AlocMatr(int ***arr, int n){
    if(*arr) return;
    
    ///Prima parte
    *arr = (int **)malloc(n * sizeof(int *));
    if(!*arr){
        err("Error allocating memory");
    }

    for(int i = 0; i < n; i++){
        
        ///A doua parte importanta
        *((*arr) + i) = (int *)malloc(4 * sizeof(int));
        
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
        for(int j = 0; j < 4; j++){
            scanf("%d",&*(*(*arr + i) + j));
        }
    }
}

void Print(int ***arr, unsigned const int n){
    
    if(!*arr)
        err("NULL MATRIX");

    for(int i = 0; i < n; i++){
        for(int j = 0; j < 4; j++){
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

void crestere_vanzari_produse(int ***a, const int size){

    if(!*a) return;
    int *ant = malloc(sizeof(int));
    if(!ant) return;
    int ok = 1;
    
    for(int i = 0; i < size; i++){
        ok = 1;
        *ant = *(*(*a + i) + 0);
        for(int j = 1; j < 4; j++){
            if(*(*(*a + i) + j) <= *ant){
                ok = 0;
                break;
            }
            *ant = *(*(*a + i) + j);
        }
        if(ok == 0) continue;
        else
            printf("Produsul: %d\n",i + 1);
    }
    free(ant);
}

int main(){

    int **a = NULL;
    int n;

    printf("n = "), scanf("%d",&n);

    AlocMatr(&a, n);
    Read(&a, n);
    printf("\n");
    crestere_vanzari_produse(&a,n);
    //Print(&a, n);
    //printf("\n");


    Delete(&a, n);

    return 0;
}
