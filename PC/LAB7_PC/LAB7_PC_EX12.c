/*
  13. Să se implementeze, fără a se folosi indecși, următorul program: se citește pe rând câte o valoare întreagă și se inserează
  într-un vector, astfel încât vectorul să fie mereu sortat crescător. După fiecare inserare se va afișa noul vector.
  Programul se termină la citirea valorii 0. Presupunem că vectorul va avea maxim 100 de elemente.
*/


#include <stdio.h>

void afisare(int v[], int size){
    for(int i = 0; i < size; i++){
        printf("%d ", *(v+i));
    }
    printf("\b\n");
}

int main(){
    int minn, maxx;
    int v[99], size = 0, x;
    
    scanf("%d", &*(v+size));
    minn  = *(v+size);
    maxx  = *(v+size);
    
    printf("%d\n", *(v+size));
    
    x = *(v+size);
    size++;
    
    while(x != 0){
        scanf("%d", &x);
        if(x == 0) break;
        if(x < minn){
            minn = x;
            for(int i = size; i >= 1; i--){
                *(v+i) = *(v+(i-1));
            }
            *(v+0) = minn;
            size++;
            afisare(v,size);
        }
        else if(x > maxx){
            maxx = x;
            *(v+size) = maxx;
            size++;
            afisare(v, size);
        }
        else if(x >= minn && x <= maxx){
            for(int i = 1; i < size; i++){
                if(x <= *(v+i)){
                    for(int j = size; j >= i+1; j--){
                        *(v+j) = *(v+(j-1));
                    }
                    *(v+i) = x;
                    size++;
                    afisare(v,size);
                    break;
                }
            }
            afisare(v,size);
        }
    }
}
