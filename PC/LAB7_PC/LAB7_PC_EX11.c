/*
Să se implementeze, fără a se folosi variabile index, un program cu următorul meniu:
1. Citire - citește o valoare reală și o adaugă într-un vector cu maxim 100 de elemente
2. Afișare - afișează toate valorile din vector
3. Ștergere - citește o valoare și șterge toate elementele egale cu valoarea citită
4. Ieșire
*/

#include <stdio.h>
#include <stdlib.h>

void meniu(){
    printf("### MENIU PROGRAM ###\n");
    printf("1. Citire - citește o valoare reală și o adaugă într-un vector cu maxim 100 de elemente\n");
    printf("2. Afișare - afișează toate valorile din vector\n");
    printf("3. Ștergere - citește o valoare și șterge toate elementele egale cu valoarea citită\n");
    printf("4. Ieșire\n");
    
    
    printf("\nSelectati: ");
    
}

void citire(int v[], int *size){
    printf("\nIntroduceti numarul: ");
    scanf("%d", &*(v+*(size)));
    *size+=1;
}

void afisare(int v[], int size){
    printf("Valori vector: ");
    for(int i = 0; i < size; i++){
        printf("%d ", *(v+i));
    }
    printf("\b\n\n");
    
    
}

void stergere(int v[], int *size){
    int x, ok = 0;
    printf("Introoduceti valoare care sa fie stearsa: ");
    scanf("%d", &x);
    
    for(int i = 0; i < *size; i++){
        if(*(v+i) == x){
            ok = 1;
            for(int j = i; j < *size; j++){
                *(v+j) = *(v+(j+1));
            }
            *(v+(*size-1)) = 0;
            *size = *size - 1;
            i--;
        }
    }
    
    if(ok == 0) printf("Vectorul nu a fost modificat\n");
    
}

int main(){
    
    int ok = 0;
    int size = 0, v[99], val = 0;
    
    while(1){
        meniu();
       if(val == 0){
            scanf("%d", &val);
        } 
       if(val >= 1 && val <= 4 ){
            if(val == 1){
                val = 0;
                ok = 1;
                citire(v, &size);
            }
            else if(val == 2){
                val = 0;
                if(ok == 0) goto eroare;
                afisare(v,size);
            }
            
            else if(val == 3){
                val = 0;
                stergere(v,&size);
            }
            
            else if(val == 4){/// caz de exit
                exit(0);
            }
       }
       else{
           goto eroare;
       }
    
    }
    
            eroare:/// caz in care nu satisface nici o conditie
            printf("EROARE\n");
            exit(1);
    
    
}
