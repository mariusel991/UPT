#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define ARRAY_SIZE 100

int compare(const void *a, const void *b){
    int *x = (int *)a;
    int *y = (int *)b;
    return *x - *y;
}

void read_array(int *array, size_t *lung){
    int x, i = 0;
    
    scanf("%d", &x);
    while(x != 0 && i < ARRAY_SIZE){
        *(array + i) = x;
        i++;
        
        scanf("%d", &x);
    }
    *lung = i;
}

int main(){
    int v[ARRAY_SIZE];
    size_t size;
    FILE *f;
    
    if( (f = fopen("output.txt","w")) == NULL){
        perror("ERROR: ");
        exit(1);
    }
    
    read_array(v, &size);
    qsort(v, size, sizeof(int), compare);
    
    for(size_t i = 0; i < size; i++){
        fprintf(f,"%d",v[i]);
        if(i < size - 1) fprintf(f,"|");
    }
    fprintf(f,"\n");
    fclose(f);
    
    return 0;
}
