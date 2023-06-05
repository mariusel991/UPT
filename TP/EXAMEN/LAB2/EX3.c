/*
Aplicația 2.3: Se introduce un număr întreg n<10 și apoi n numere de tip float. Să se folosească funcția qsort
pentru a sorta aceste numere în mod crescător. Se va introduce apoi un număr x de tip float. Folosind funcția
bsearch, să se determine dacă x există în vectorul sortat. Se pot consulta paginile de manual pentru funcțiile qsort
și bsearch.
*/

#include <stdio.h>
#include <stdlib.h>

void cin(float *v, int *size){
    printf("n ="), scanf("%d", &*size);

    for(int i = 0; i < *size; i++){
        scanf("%f", &v[i]);
    }
}

int compar(const void *a, const void *b){
    float *p1 = (float *)a;
    float *p2 = (float *)b;

    return *p1 - *p2;
}

int main(){

    int n;
    float v[10], x;
    cin(v, &n);
    scanf("%f", &x);
    qsort(v, n, sizeof(float), compar);
    float *look = bsearch(&x, v, n, sizeof(float), compar);

    if(!look){
        printf("NU EXISTA\n");
    }
    else{
        printf("EXISTA\n");
    }

    return 0;
}
