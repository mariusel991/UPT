/*
Aplicația 2.2: Să se implementeze o funcție care primește ca parametri un vector de întregi, numărul elementelor
din vector transmis prin adresă și un predicat care testează dacă un întreg îndeplinește o anumită condiție. Funcția
va sterge din vector toate elementele care nu îndeplinesc condiția dată și va actualiza numărul elementelor cu
numărul de elemente rămas în vector. Să se testeze funcția cu un predicat care testează dacă un număr este
negativ și să se afișeze vectorul rezultat.
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void citeste_vector(int **arr, int *size){
    
    printf("n = "), scanf("%d", &*size);

    *arr = (int *)malloc(*size * sizeof(int));
    
    if(!*arr){
        perror("error alcotating mem\n");
        exit(errno);
    }

    for(int i = 0; i < *size; i++){
        scanf("%d", &*(*arr + i));
    }
}

int conditie(int n){
    return n % 2 == 0;
}

void filtrare(int *v, int *nr_elem, int (*predicat)(int)){

    int poz = 0;

    for(int i = 0; i < *nr_elem; i++){
        if(predicat(*(v + i))){
            *(v + poz++) = *(v + i);
        }
    }
    *nr_elem = poz;
}

void afisare(int *v, int n){
    for(int  i = 0; i < n; i++){
        printf("%d ", *(v + i));
    }
    printf("\n");
}

int main(){

    int n;
    int *a = NULL;

    citeste_vector(&a,&n);
    filtrare(a, &n, conditie);
    afisare(a,n);

    free(a);

    return 0;
}
