#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define initial_size 8
#define chunk 4

int *citire_vector(int *size);
void afisare_inversa(const int *array, const int size);

/// MAIN

int main(){
    
    int *a = NULL;
    int size = 0;
    a = citire_vector(&size);
    afisare_inversa(a,size);
    
    free(a);
    
}

int *citire_vector(int *size){
    
    int *array = NULL;
    int *tmp = NULL;
    int x;
    size_t lung = initial_size;
    size_t i = 0;
    
    array = malloc(initial_size * sizeof(int));
    
    if(array == NULL){
        fprintf(stderr,"couldn't allocate memory\n");
        exit(-1);
    }
    
    while(scanf("%d",&x)){
        
        if(x == 0) break;
            
        if(i == lung){
            lung = lung + chunk;
            tmp = realloc(array, lung * sizeof(int));
            
            if(tmp == NULL){
                free(array);
                fprintf(stderr,"couldn't reallocate memory\n");
                exit(-1);
            }
            array = tmp;
        }
        *(array + i++) = x;
    }
    *size = i;
    
    return array;
}

void afisare_inversa(const int *array, const int size){
    
    for(int i = size - 1; i >= 0; i--){
        printf("%d ",array[i]);
    }
    printf("\b\n");
    
}
