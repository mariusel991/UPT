#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void afisare64(uint64_t nr){
    uint64_t mask = 0x8000000000000000;
    
    for(int i = 64; i > 0; i--){
        if((nr & mask) == 0){
            printf("0");
        }
        else{
            printf("1");
        }
        mask = mask >> 1;
    }
    printf("\n");
}

void afisare32(uint32_t nr){
    uint64_t mask = 0x80000000;
    
    for(int i = 32; i > 0; i--){
        if((nr & mask) == 0){
            printf("0");
        }
        else{
            printf("1");
        }
        mask = mask >> 1;
    }
    printf("\n");
}

int main(){
    uint64_t v[10]={0}, mask=0xFFFFFFFF;
    uint32_t msw[10]={0}, lsw[10]={0};
    uint16_t n;
    
    scanf("%hu", &n);
    
    if(n <= 0 || n > 10){
        printf("error\n");
        exit(1);
    }
    
    for(int i = 0; i < n; i++){
        scanf("%lu", &v[i]);
        mask=0xFFFFFFFF;
        lsw[i] = 0 | (v[i] & mask);
        msw[i] = 0 | ((v[i] >> 32) & mask);
    }
    
    for(int i = 0; i < n; i++){
        afisare64(v[i]);
        afisare32(msw[i]);
        afisare32(lsw[i]);
        printf("\n");
    }
    
    
    return 0;
}
