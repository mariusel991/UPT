/*
Subiectul 1: Să se imlementeze un program care gestionează un parc de automobile. Informaţiile relative la un
automobil sunt: codul mașinii (număr între 1 si 9000), numărul de locuri (între 1 și 9), puterea (în cai putere între 1
și 500), marca, culoarea, anul fabricaţiei maşinii (între 1800 și 2017). Parcul conține n automobile, datele sunt citite
de la tastatură. Să se scrie următoarele funcții de gestiune a mașinilor:
a) Introducerea unui automobil nou;
b) Ștergerea unui anumit automobil, al cărui cod e citit de la tastatură;
c) Afișarea întregii liste de automobile;
d) Afișarea pe ecran doar a automobilelor cu un anumit număr de locuri, citit de la tastatură;
e) Ordonarea listei în funcție de anul fabricației, folosind qsort.
Să se definească structura pentru o mașină cu ajutorul structurilor cu câmpuri pe biți astfel încât spațiul ocupat să
fie minim.

*/
 #include <stdio.h>
 #include <stdlib.h>
 #include <errno.h>
 #include <string.h>
 #include <ctype.h>

#define MAX_LEN 32
#define CHUNK 4

typedef struct masina{
    
    char marca[MAX_LEN];
    char culoare[MAX_LEN];

    unsigned int cod:14;
    unsigned int locuri:4;
    unsigned int putere:9;
    unsigned int an_fabricatie:11;

}masina;

int compar(const void *a, const void *b){
    masina *p1 = (masina *)a;
    masina *p2 = (masina *)b;

    return strcmp(p1->marca, p2->marca);
}

void meniu(){

    printf("\n-------------------------\n");
    printf("1 - Adaugare automobil\n");
    printf("2 - Stergere automobil\n");
    printf("3 - Afisare toate automobilele\n");
    printf("4 - Afisare automobile cu n locuri\n");
    printf("5 - Ordonare dupa an fabricatie\n");
    printf("6 - Exit\n");
    printf("-------------------------\n\n");

}

void add_car(masina **arr, int *arr_size, int *arr_mem){
    if(*arr == NULL){
        *arr_size = *arr_size + CHUNK;
        *arr = malloc(*arr_size * sizeof(masina));
        if(!*arr){
            perror("Out of memory");
            exit(-1);
        }
    }

    if(*arr_size == *arr_mem){
        *arr_size = *arr_size + CHUNK;
        masina *tmp = NULL;
        tmp = realloc(*arr, *arr_size * sizeof(masina));
        
        if(!tmp){
            perror("Out of memory");
            free(*arr);
            free(tmp);
            tmp = NULL;
            exit(-1);
        }
        *arr = tmp;
    }
    
    masina aux;
    unsigned int aux_nr;

    printf("\nCod:"), scanf("%u", &aux_nr);
    aux.cod = aux_nr;
    printf("Nr lcouri:"), scanf("%u", &aux_nr);
    aux.locuri = aux_nr;
    printf("Cai putere:"), scanf("%u", &aux_nr);
    aux.putere = aux_nr;
    printf("Marca:"), scanf("%32s", aux.marca);
    printf("Culoare:"), scanf("%32s", aux.culoare);
    printf("An fabricatie:"), scanf("%u", &aux_nr);
    aux.an_fabricatie = aux_nr;

    (*arr)[(*arr_mem)++] = aux;
}

void del_car(masina **arr, unsigned int cod, int *arr_mem){
    if(*arr == NULL){
        perror("NULL ARRAY");
        return;
    }

    int ok = 0;
    
    for(int i = 0; i <= *arr_mem; i++){
        if((*arr)[i].cod == cod){
            ok = 1;
            for(int j = i; j < *arr_mem; j++){
                (*arr)[j] = (*arr)[j + 1];
            }
            return;
        }
    }

    if(ok == 0){
        printf("Masina nu exista in vector\n");
        return;
    }else{
        printf("Masina cu codul %d a fost stearsa cu success\n",cod);
    }
}

void afisare(masina *arr, int arr_mem){
    for(int i = 0; i < arr_mem; i++){
        printf("MASINA %d\n", i + 1);
        printf("%u\n",arr[i].cod);
        printf("%u\n",arr[i].locuri);
        printf("%u\n",arr[i].putere);
        printf("%s\n",arr[i].marca);
        printf("%s\n",arr[i].culoare);
        printf("%u\n\n",arr[i].an_fabricatie);
    }
}

void afisare_dupa_locuri(masina *arr, int arr_mem, int nr_loc){
    int index = 0;
    for(int i = 0; i <= arr_mem; i++){
        if(nr_loc == arr[i].locuri){
        index++;
        printf("MASINA %d\n", index);
        printf("%u\n",arr[i].cod);
        printf("%u\n",arr[i].locuri);
        printf("%u\n",arr[i].putere);
        printf("%s\n",arr[i].marca);
        printf("%s\n",arr[i].culoare);
        printf("%u\n\n",arr[i].an_fabricatie);
        }
    }

    if(index == 0){
        printf("Nu exista masini cu %d locuri\n", nr_loc);
    }
}

int main(){

    masina *arr = NULL;
    int arr_size = 0;
    int arr_mem = 0;

    int selector;
    unsigned int code;
    unsigned int nr_loc;

    meniu();

    while(1){
        //while(getchar() != '\n'); 
        meniu();
        printf("Obtiunea dvs.: "), scanf("%d", &selector);

        switch (selector){
        case 1:
            add_car(&arr, &arr_size, &arr_mem);
            break;
        case 2:
            printf("Codul masinii: "), scanf("%u",&code);
            del_car(&arr, code, &arr_mem);
            break;
        case 3:
            afisare(arr,arr_mem);
            break;
        case 4:
            printf("Nr locuri: "), scanf("%u",&nr_loc);
            afisare_dupa_locuri(arr,arr_mem,nr_loc);
            break;
        case 5:
            qsort(arr, arr_mem, sizeof(masina), compar);
            afisare(arr, arr_mem);
            break;
        case 6:
            free(arr);
            return 0;
        default:
            break;
        }
    }

    return 0;
}
