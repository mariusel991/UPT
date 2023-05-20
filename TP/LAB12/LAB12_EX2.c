/*
Aplicația 12.2: Se citeste un numar natural n. Afisati permutarile multimii 1,2,3...n in care pana la jumatate
elementele sunt in ordine descrescatoare, iar de la jumatate pana la final in ordine crescatoare.
Exemplu:
n=5
permutarile care respecta conditia sunt:
3 2 1 4 5
4 2 1 3 5
4 3 1 2 5
5 2 1 3 4
5 3 1 2 4
5 4 1 2 3

*/

/// METODA 1

#include <stdio.h>
#include <string.h>

#define NMAX 15

int sol[NMAX];

void afisare(int n){
    for(int i = 0; i < n; i++){
        printf(" %d", sol[i]);
    }
    printf("\n");
}

int valid(int k, int n){
    if(k <= n - 1){
        for(int i = 0; i < k; i++){
            if(sol[i] == sol[k]){
                return 0;
            }
        }
        return 1;
    }
    else{
        return 0;
    }
}

int solutie(int k, int n){
    if(k == n - 1){
        ///int aux = sol[0];
        
        if(n % 2 == 1){
            if(sol[n/2] !=1 ) return 0;
        }

        for(int i = 1; i < n - 1; i++){
            if(i < n/2){
                if(sol[i] > sol[i-1]){
                    return 0;
                }
            }
            else{
                if(sol[i] > sol[i+1]){
                    return 0;
                }
            }
        }

        return 1;
    }
    return 0;
}

void back(int k, int n){

    int i;

    for(i = 0; i < n; i++){
        sol[k] = i + 1;

        if(valid(k,n)){
            if(solutie(k,n)){
                afisare(n);
            }
            else{
                back(k + 1, n);
            }
        }
    }
}

int main(){

    int n;
    printf("n = "), scanf("%d",&n);

    back(0,n);

    return 0;
}




/// METODA 2 -------------------------------------

/*
    Aplicatia 12.2: Se citeste un numar natural n. Afisati permutarile multimii 1,2,3...n in care pana la jumatate
elementele sunt in ordine descrescatoare, iar de la jumatate pana la final in ordine crescatoare.
Exemplu:
n=5
permutarile care respecta conditia sunt:
3 2 1 4 5
4 2 1 3 5
4 3 1 2 5
5 2 1 3 4
5 3 1 2 4
5 4 1 2 3
*/

#include<stdio.h>

#define NMAX 15

int v[NMAX], n, freq[NMAX];

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void afisSol(){
    for(int i = 0; i < n; i++){ 
        printf("%d ",v[i]);
    }
    printf("\n");
}

void genPerm(int poz){
    if(poz == n){
        afisSol();
        return;
    }

    for(int i = 1; i <= n; i++){
        if(poz <= n / 2){
            if(poz == 0){
                v[poz] = i;
                freq[i] = 1;
                genPerm(poz + 1);
                freq[i] = 0;
            }
            else{
                if(i < v[poz - 1] && freq[i] == 0){
                   v[poz] = i;
                    freq[i] = 1;
                    genPerm(poz + 1);
                    freq[i] = 0;
                }
            }
        }
        else{
            if(poz == 0){
                v[poz] = i;
                freq[i] = 1;
                genPerm(poz + 1);
                freq[i] = 0;
            }
            else{
                if(i > v[poz - 1] && freq[i] == 0){
                    v[poz] = i;
                    freq[i] = 1;
                    genPerm(poz + 1);
                    freq[i] = 0;
                }
            }
        }
    }
    
}

int main(){
    printf("n = ");scanf("%d", &n);
    printf("Permutarile speciale sunt:\n");
    for(int i = 0; i < n; i++){
        v[i] = i + 1;
    }
    genPerm(0);
    return 0;
}
