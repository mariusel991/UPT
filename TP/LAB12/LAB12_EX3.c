/*
Aplicația 12.3: Se citesc doua numere naturale n si k, k fiind mai mic decat numarul de cifre ale numarului n. Afisati
cel mai mare numar care se poate forma eliminand k cifre din numarul n.
Exemplu:
n=3452234
k=4
numarul cautat este 534
*/

#include <stdio.h>

int sol[20], v[20], freq[10], maxx = 0, nrc = 0;

void afisare(int cif_lps){
   
    for(int i = 0; i < nrc - cif_lps; i++){
        printf(" %d", sol[i]);
    }
    printf("\n");
}

int valid(int k){
    
    int rep = 1;

    for(int i = 0; i < k; i++){/// verific daca cifra nu apare de mai multe ori ca in nr N
        if(sol[i] == sol[k]) rep++;
    }

    if(rep > freq[sol[k]]){///Daca da NU se ia in considerare
        return 0;
    }

    return 1;
    
}

int solutie(int k, int cif_lps){
    if (k == nrc - cif_lps - 1) return 1;
    return 0; 
}

int maxim(int cif_lps){
    int p = 1, rez = 0, cif;

    for(int i = nrc - cif_lps - 1; i >= 0; i--){

        cif = sol[i];
        rez = rez + cif * p;
        p = p*10;
    }

    return rez;
}

void back(int k, int cif_lps, int start){
    
    int i;
    
    for(i = start; i < nrc; i++){
        
        sol[k] = v[i];

        if(valid(k)){
            if(solutie(k, cif_lps)){
                int aux = maxim(cif_lps);
                if(aux > maxx){
                    maxx = aux;
                }
                
                ///printf("%d\n",maxx);
                //afisare(cif_lps);
            }
            else{
                back(k + 1, cif_lps, i + 1);
            }
        }
    }

}

int main(){

    int n, k;

    printf("n = "), scanf("%d", &n);
    printf("k = "), scanf("%d", &k);

    int aux = 0;

    while (n > 0){
        aux = (aux * 10) + n % 10;
        freq[n%10]++;
        n = n/10;
    }

    int i = 0;

    while(aux > 0){
        v[i++] = aux%10;
        aux = aux/10;
        nrc++;
    }

    back(0,k,0);
    ///afisare();
    printf("%d\n",maxx);

    return 0;
}
