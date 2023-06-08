#include <stdio.h>
#include <stdint.h>


void bit(uint16_t n){
  uint16_t mask;
  mask = 1 << 15;
  for(int i = 0; i < 16; i++){
    if(n & mask){
      printf("1");
    }
    else{
      printf("0");
    }
    mask = mask >> 1;
  }
  printf("\n");
}

int main(){

  uint16_t n,mask,nou=0x0000;
  
  scanf("%u", &n);
  /// bit(n);
  mask = 0xF000;
  /// printf("0x%X\n", mask);
  bit(n);
  for(int i = 4; i >= 1 ; i--){
    nou = nou | ((mask & n)^mask);
    mask = mask  >> 4;
  }
  bit(nou);

  
  
  return 0;  
}
