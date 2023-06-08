/*
 6.Se va citi un n<=10. Se vor citi apoi n produse, fiecare definit prin nume (un șir de caractere), cantitate (real)
 și preț unitar (real). Unele produse pot să fie date de mai multe ori, cu valori diferite. Să se calculeze pentru
 fiecare produs cantitatea și prețul total, iar în final să se calculeze și prețul global pentru toate produsele.
 Exemplu:       

Intrare

3

mere

2.5

4

pere

2

7.5

mere

3

5

Ieșire

mere 5.5, 25
pere 2, 15
preț global: 40
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
   char nume[50];
   float pret,cantitate,suma;
} Produs;

int main(){
    int n;
    float suma_globala = 0;
    Produs p[10]={};
    scanf("%d", &n);
    if(n <= 0 || n > 10){
        printf("error\n");
        exit(1);
    }
    
    for(int i = 0; i < n; i++){
        getchar();
        fgets(p[i].nume, 49, stdin);
        scanf("%g", &p[i].cantitate);
        scanf("%g", &p[i].pret);
        
        p[i].suma = p[i].cantitate * p[i].pret;
        suma_globala += p[i].suma;/// suma globala
    }
    
    ///printf("%.0f\n", suma_globala);
    
    for(int i = 0; i < n - 1; i++){
        for(int j = i+1; j < n; j++){
            if(strcmp(p[i].nume, p[j].nume) == 0){/// am gasit duplicat
                p[i].suma += p[j].suma;
                p[i].cantitate+= p[j].cantitate;
                strcpy(p[j].nume,"");
                p[j].suma = 0;
                p[j].pret = 0;
                p[j].cantitate = 0;
            }
            else if(strcmp(p[i].nume,"") == 0) continue;
        }
    }
    
    for(int i = 0; i < n; i++){
        if(strlen(p[i].nume) > 0){
            p[i].nume[strlen(p[i].nume)-1] = 0;
            printf("%s %.1f, %0.f\n",p[i].nume,p[i].cantitate,p[i].suma);
        }
    }
    printf("pret global:%0.f\n", suma_globala);
    
    return 0;
    
}
