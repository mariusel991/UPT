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
  char var;

  uint8_t a,b;
  uint8_t mask;

  scanf("%hhu %hhu", &a, &b);

  mask =(1 << 3) | (1 << 2) | (1 << 1) | (1 << 0);/// 0000 1111 masca
  var = mask & b;
  mask =(1 << 3) | (1 << 2) | (1 << 1) | (1 << 0);/// 0000 1111 masca
  mask = mask & a;
  mask = mask << 4; //// 1111 0000
  var = var | mask;

  print_bit(var);
  print_bit(a);
  print_bit(b);
  
 

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
