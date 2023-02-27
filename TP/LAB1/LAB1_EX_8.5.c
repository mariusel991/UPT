/*
Se citește de la tastatură o matrice cu n<=20 linii și coloane. Să se memoreze într-un vector suma
tuturor elementelor de pe fiecare linie și într-un alt vector, suma tuturor elementelor de pe fiecare coloană. Să se
afișeze cei doi vectori. Se vor utiliza pointeri atât pentru vectori cât și pentru matrici.
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

void myError(char *msg) {

    perror(msg);
    exit(errno);
}

int **alocare_matrice(unsigned const int lines_colums){

    int **tmp = NULL;
    tmp = malloc(lines_colums * sizeof(int *));

    if (tmp == NULL){
        myError("Error alocating mem for matrix\n");
    }

    for(uint8_t i = 0; i < lines_colums; ++i){
       
       tmp[i] = calloc(lines_colums, sizeof(int));/// De intrebat...

       if(*(tmp + i) == NULL){
            char errormsg[64];
            sprintf(errormsg, "Error alocating memory at row(line) %hhu\n",i);

            i--;
            for(; i >= 0; i--){
            //free la fiecare linie
            free(*(tmp + i));
            }

            //free la matrice
            free(tmp);
            tmp = NULL;

            myError(errormsg);
        }
    }

    return tmp;
}

int *alocare_vector(unsigned const int size){
    
    int *tmp = NULL;
    tmp = calloc(size, sizeof(int));

    if (tmp == NULL){
        
        char msg[32];
        sprintf(msg, "Eroare alocare vector\n");
        myError(msg);
    }

    return tmp;
}

void *eliberare_vector(void *array){
    free(array);
    array = NULL;

    return NULL;
}

void *eliberare_matrice(void **matrix, unsigned const int rows) {

    for (unsigned int i = 0; i < rows; ++i) {
        free(matrix[i]);
        matrix[i] = NULL;
    }
    free(matrix);
    matrix = NULL;

    return NULL;
}

void citire_matrice(int **matrix, const int line_colums){

    for(int **p = matrix;  p < matrix + line_colums; p++){
        for(int *q = *p; q != *p + line_colums; ++q){
            scanf("%d", q);
        }
    }
}

void afisare_matrice(int **matrix, const int line_colums){

    for(int **p = matrix;  p < matrix + line_colums; p++){
        for(int *q = *p; q != *p + line_colums; ++q){
            printf("%d ", *q);
        }
        printf("\b");
        printf("\n");
    }
}

void suma_linie(int **matrix, int *array, unsigned const int line_colums){

    uint32_t sum;

    for(int **p = matrix;  p < matrix + line_colums; p++){
        sum = 0;
        for(int *q = *p; q != *p + line_colums; ++q){
            sum = sum + *q;
        }
        *(array + (p - matrix)) = sum;
    }
}

void suma_coloana(int **matrix, int *array, unsigned const int line_colums){

    uint32_t sum;

    for(int j = 0; j < line_colums; ++j){
        sum = 0;
        for(int i = 0; i < line_colums; ++i){
           sum = sum + *(*(matrix + i) + j);
        }
        *(array + j) = sum;
    }
}

void afisare_suma_linie(int *array, unsigned const int size){

    for(int *p = array; p < array + size; p++){
        printf("Suma pe linia %lu: %d\n",(p - array), *p);
    }
}

void afisare_suma_coloana(int *array, unsigned const int size){

    for(int *p = array; p < array + size; p++){
        printf("Suma pe coloana %lu: %d\n",(p - array), *p);
    }
}

int main(void){

    uint8_t n;
    int **a = NULL;
    int *raw_sum = NULL;
    int *col_sum = NULL;
    
    citire:
    printf("Introduceti numarul:");
    scanf("%hhu", &n);

    if(n <= 0 || n > 20){
        fprintf(stderr, "Dimensiunea maxima este de %d x %d este prea mare!\n", n,n);
        fprintf(stderr , "Incercati un numar din intervalul [1,20]\n\n");
        goto citire;
    }

    a = alocare_matrice(n);/// avem matrice patratica deci avem linii = coloane => un singur parametru
    citire_matrice(a,n);
    raw_sum = alocare_vector(n);
    col_sum = alocare_vector(n);
    //afisare_matrice(a,n);

    suma_linie(a,raw_sum,n);
    suma_coloana(a,col_sum,n);

    afisare_suma_linie(raw_sum,n);
    printf("\n");
    afisare_suma_coloana(col_sum,n);

    ///Clean up
    eliberare_vector(raw_sum);
    eliberare_vector(col_sum);
    a = eliberare_matrice((void **)a,n);

    return 0;
}
