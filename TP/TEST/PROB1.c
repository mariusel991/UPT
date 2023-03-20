/******************************************************************************

Rând 1

1.     Folosind câmpuri pe biți, definiți o structură pentru memorarea următoarelor informații despre filme:

-numele filmului: șir de maxim 35 caractere

-anul apariției: numar intreg, maxim 2023

-premii: da/nu

Definiți structura în așa fel încât să ocupe spațiul minim de memorie posibil. 
Cu ajutorul structurii să se salveze într-un vector de structuri  alocat dinamic informații despre mai multe filme. 
Să se citească de la tastatură informațiile despre filme și la final să se afișeze vectorul. 
Să se sorteze vectorul creat, folosind funcția qsort, astfel încât pe primele poziții din vector să se afle filmele care au fost premiate.

2.    Se citesc de la tastatură un număr n și o matrice pătratică de dimensiune n. 
Pe urmă se citește un vector. Verificați dacă vectorul apare în matrice pe orizontală spre stânga sau spre dreapta.
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct film{
    unsigned int an:11; // 3B;
    char nume[35];
    char premii[2];
}film;

film *aloc_mem(unsigned const int size){
    film *a = NULL;
    
    a = (film *)malloc(size * sizeof(film));
   
    if(a == NULL){
        return NULL;
    }
    
    return a;
}

void citire_filme(film *arr, const unsigned int size){
    film aux;
    for(int i = 0; i < size; i++){
        
        printf("FILM %d\n", i+1);
        int a;
        fgets(aux.nume,35,stdin);
        if (aux.nume[strlen(aux.nume) - 1] == '\n'){
            aux.nume[strlen(aux.nume) - 1] = 0;
        }
        scanf("%u",&a);
        aux.an = a;
        getchar();
        scanf("%2s",aux.premii);
        getchar();
        arr[i] = aux;
    }
}

int cmp(const void *a, const void *b){
    film *p1 = (film *)a;
    film *p2 = (film *)b;
    
    return strcmp("DA",p1->nume);
}

void afis(film *a,const unsigned int size){
    for(int i = 0; i < size; i++){
        printf("Nume:%s\nAn:%u\nPremii:%s\n\n",a[i].nume,a[i].an,a[i].premii);
    }
}

int main()
{   
    int n;
    film *filme = NULL;
    
    scanf("%d",&n);
    getchar();
    
    filme = aloc_mem(n);
    citire_filme(filme,n);
    
    qsort(filme,n,sizeof(film),cmp);
    afis(filme,n);
    free(filme);
    
    
    //printf("%ld\n",sizeof(film));

    return 0;
}
