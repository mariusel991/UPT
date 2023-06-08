/*
   6. Să se afișeze minimul elementelor din vectorul {7, -5, 4, 3, -9, 2, -8} utilizând pointeri, fără indecși.
*/

#include <stdio.h>

int main(){
    
    int v[] = {7, -5, 4, 3, -9, 2, -8};
    int minn;
    
    minn = *(v+0);/// presupunem ca primul elem este minim
    
    for(int i = 1; i < 7 ; i++){
        if(*(v+i) < minn) minn = *(v+i);/// am gasit un nr mai mic ca minn
    }
    
    printf("%d\n", minn);
}
