#include <stdio.h>
#include <stdint.h>


void bit(uint32_t n){
  uint32_t mask;
  mask = 1 << 31;
  for(int i = 0; i < 32; i++){
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

int functie(uint32_t nr, uint8_t n, int p){
  uint32_t mask;
  mask = 0x00FF << 8*p;
  nr = nr & (~mask); /// am resetat bitii de pe octetul cu poz p
  mask =(0x0000 | n) << 8*p;
  nr = nr | mask;
  return nr;
}

int main(){
  uint32_t nr;
  uint8_t n;
  int p;

  nr = 911947355;
  n  = 239;
  p  = 2;
  bit(nr);
  nr = functie(nr, n, p);
  bit(nr);
  
  
  return 0;  
}
