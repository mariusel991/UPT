#include <stdio.h>
#include <stdint.h>


int count_one(uint32_t nr){
  uint32_t mask;
  uint16_t k = 0;

  mask = 1 << 31;/// setam masca pe pozitia 1 (parcurgand de la stanga)

  for(int i = 0; i < 32; i++){
    if(nr & mask){
      k++;
    }
    mask = mask >> 1;
  }

  return k;
  
}


int main(){

  /// printf("%ld", sizeof(unsigned int));
  uint32_t n;
  uint16_t k;

  scanf("%u", &n);
  k = count_one(n);
  printf("%u\n", k);
  
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
