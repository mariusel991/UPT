/*
    Aplicația 11.4: La un campionat iau parte n jucători, fiecare definit prin nume (max 15 caractere) și valoare (int).
Jucătorii sunt distribuiți în m grupe, n divizibil cu m. Distribuția jucătorilor în grupe se face după valoarea lor, astfel
încât cei mai valoroși m jucători să fie fiecare în altă grupă, apoi următorii m cei mai valoroși rămași să fie și ei în
grupe diferite și tot așa, până când toți jucătorii sunt distribuiți. Să se afișeze împărțirea jucătorilor pe grupe, pentru
valori citite dintr-un fișier.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct jucator{
    char nume[16];
    int valoare;
}jucator;

typedef struct echipa{
    int slot;
    jucator *jucatori;
}echipa;


void swap(jucator *a, jucator *b){

    jucator tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(jucator *arr, int start, int end){
    
    jucator pivot = arr[end];
    int piv_slot = start;

    for(int i = start; i <= end - 1; i++){

        if(arr[i].valoare > pivot.valoare){
            swap(&arr[i],&arr[piv_slot]);
            piv_slot++;
        }
    }
    swap(&arr[piv_slot],&arr[end]);

    return piv_slot;
}

void quick_sort(jucator arr[], int start, int end){

    if(start < end){

    int piv_index = partition(arr, start, end);

    quick_sort(arr, start, piv_index-1);
    quick_sort(arr, piv_index + 1, end);
    }
}

jucator *citire_date(int n){

    jucator *arr = (jucator*) malloc(n * sizeof(jucator));
    jucator aux;

    if(arr == NULL) return NULL;/// eroare

    for(int i = 0; i < n; i++){
        
        printf(" ==== Player [%d] ==== \n", i+1);
        printf("nume - "), scanf("%15s",aux.nume);
        printf("valoare - "), scanf("%d", &aux.valoare);
        printf("\n");

        arr[i] = aux;
    }

    return arr;
}

echipa *impartire_echipe(jucator *v, int n, int m){
    
    echipa *CM = (echipa *)malloc(m * sizeof(echipa));
    int player_per_team = n/m;

    for(int i = 0; i < m; i++){/// echipa
        CM[i].jucatori = (jucator *)malloc(player_per_team * sizeof(jucator));
        CM[i].slot = i + 1;
        for(int j = 0; j < player_per_team; j++){
            CM[i].jucatori[j] = v[m*i + j];
        }
    }

    return CM;
}


int main(){

    int n, m;

    printf("n - jucatori = "), scanf("%d", &n);
    printf("m - echipe = "), scanf("%d", &m);

    jucator *v = citire_date(n);
    echipa *CM = NULL;

    quick_sort(v,0,n-1);
    CM = impartire_echipe(v,n,m);

    printf("\n");
    for(int i = 0; i < m;i++){
        printf("Echipa %d\n", i+1);
        for(int j = 0; j < (n/m); j++){
            printf("%d. %s - %d\n",j+1, CM[i].jucatori[j].nume, CM[i].jucatori[j].valoare);
        }
        printf("\n");
    }



    return 0;
}
