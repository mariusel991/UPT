/*
    5. Să se afișeze câte elemente negative sunt în vectorul {7, -5, 4, 3, -9, 2, -8} utilizând
    pointeri, fără indecși. (Fără indecși înseamnă că în cod nu va exista niciun v[i])
*/

#include <stdio.h>

int main(){
    
    int v[] = {7, -5, 4, 3, -9, 2, -8};
    int k = 0;
    
    for(int i = 0; i < 7 ; i++){
        if(*(v+i) < 0) k++;
    }
    
    printf("%d\n", k);
}
