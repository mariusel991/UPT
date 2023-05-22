/*
    Aplicația 12.6: De-a lungul unei șosele trebuie amplasate una lângă alta următoarele entități: case, blocuri, grădini,
ateliere. O entitate se poate învecina doar cu una de același tip (ex: casă cu casă) sau conform următoarelor reguli
(orice relație o implică și pe cea inversă): un bloc poate avea ca vecini case; o casă sau un atelier poate avea ca
vecini grădini. Se cer de la tastatură numerele c,b,g,a care reprezintă respectiv numărul de case, blocuri, grădini
și ateliere. Să se determine toate variantele în care acestea pot fi aranjate.

*/

/// NEFUNCTIONAL

#include <stdio.h>

#define NMAX 30

int v[NMAX];
int sol[NMAX];
int fr[10];

void plasare(int c, int b, int g, int a){
    int i = 0;
    
    while(c>0){
        v[i++] = 1;
        c--;
        fr[1]++;
    }

    while(b>0){
        v[i++] = 2;
        fr[2]++;
        b--;
    }

    while(g>0){
        v[i++] = 3;
        fr[3]++;
        g--;
    }

    while(a>0){
        v[i++] = 4;
        fr[4]++;
        a--;
    }
}

void afisare(int n){
    for(int i = 0; i < n; i++){
        printf(" %d",sol[i]);
    }
    printf("\n");
}

int valid(int k){
    int rep = 0;
    for(int i = 0; i < k; i++){
        if(sol[i] == sol[k]) rep++;
    }

    if(rep > fr[sol[k]]) return 0;

    for (int i = 0; i <= k - 2; i++) { /// nu putem avea 3 entitati consecutive
    if (sol[i] == sol[i + 1] && sol[i + 1] == sol[i + 2]) {
        return 0;
    }
}

    for(int i = 0; i < k; i++){
        if(i == 0){/// poz 1
            if(sol[i] == 1){///casa
                if(sol[i+1] == 4) return 0;
            }
            else if(sol[i] == 2){/// bloc
                if((sol[i+1] == 4) || (sol[i+1] == 3)) return 0;
            }
            else if(sol[i] == 3){/// gradina
                if(sol[i + 1] == 2) return 0;
            }
            else{
                if(sol[i+1] != 3) return 0;
            }
        }
        else{/// poz oarecare
            if(sol[i] == 2){
                if((sol[i - 1] != 1) || (sol[i+1] != 1)) return 0;
            }
            else if(sol[i] == 3){
                if((sol[i - 1] == 2) || (sol[i+1] == 2)) return 0;
            }
            else if(sol[i] == 4){
                if((sol[i - 1] != 3) || sol[i+1] != 3) return 0;
            }
        }
    }
    return 1;
}

int solutie(int k,int n){
    if(k - 1 == n) return 1;
    return 0;
}


void back(int k, int n){

    int i;

    for(i = 0; i < n; i++){
        sol[k] = v[i];

        if(valid(k)){
            if(solutie(k, n)){
                
                afisare(n);
            }
            else{
                back(k + 1, n);
            }
        }
    }
}

int main(){

    int c,b,g,a;
    int n;
    
    printf("c = "), scanf("%d",&c);
    printf("b = "), scanf("%d",&b);
    printf("g = "), scanf("%d",&g);
    printf("a = "), scanf("%d",&a);

    plasare(c,b,g,a);
    n = c + b + g + a;

    back(0,n);

    return 0;
}
