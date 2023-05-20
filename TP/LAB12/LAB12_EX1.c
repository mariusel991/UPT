/*
Aplicația 12.1: Se citesc doua numere naturale n si k. Generati si afisati toate toate numerele naturale formate din
n cifre care contin exact k cifre de 1.
*/

#include <stdio.h>

#define NMAX 15

int cifre[]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int v[NMAX];

void afisare(int n){
    for(int i = 0; i < n; i++){
        printf(" %d",v[i]);
    }
    printf("\n");
}

int valid(int k, int n){

    if(k <= n - 1){/// generam pana la n cifre
        return 1;
    }
    else{
        return 0;/// nu am ajuns generarea pana la n cifre
    }
}

int solutie(int k, int n, int cnt){
    
    int fr[10]={0,0,0,0,0,0,0,0,0,0}; /// vector de frecventa pentru cifre
    
    if(k == n-1){

        for(int i = 0; i <= k; i++){
            fr[v[i]]++;/// facem frecventa cifrelor
            //printf("%d - %d\n", i, fr[v[i]]);
        }

        if(fr[1] == cnt){
            return 1;
        }
        return 0;
    }

    return 0;
}

void back(int k, int n, int cnt){

    int i;

    for(i = 0; i < n; i++){

        v[k] = cifre[i];

        if(valid(k, n)){
            
            if(solutie(k, n, cnt)){
                afisare(n);
            }
            else{
                back(k + 1, n, cnt);
            }
        }
    }
}


int main(){

    int n,k;

    printf("n = "), scanf("%d",&n);
    printf("k = "), scanf("%d",&k);

    back(0,n,k);

    return 0;
}
