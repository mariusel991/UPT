#include <stdio.h>
#include <stdint.h>

void print_bit(uint8_t x){
  uint8_t mask = 1 << 7;
  for(int i = 0; i < 8; i++){
    if(x & mask){
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
  uint8_t n, mask;
  uint8_t s = 0;

  scanf("%hu", &n);

  mask = 1 << 3;

  for(int i = 0; i < 4; i++){
    s = s + (n & mask);
    mask = mask >> 1;
  }
  printf("%u\n", s);
  print_bit(s);
  
  
  

  return 0;
  
  
}

/*
  0000 0000
  
  0001 1
  0010 2
  0011 3
  0100 4
  0101 5
  0110 6
  0111 7
  1000 8
  1001 9
  1010 10
  

 */
