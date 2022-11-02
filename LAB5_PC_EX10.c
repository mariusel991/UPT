#include <stdio.h>
#include <stdint.h>

int main(){
  int n;
  uint32_t mask;
  mask = 1 << 31;
  // printf("%ld", sizeof(int));

  scanf("%d", &n);

  if(n & mask){
    printf("1\n");
  }
  else{
    printf("0\n");
  }
  
  

  return 0;
  
  
}
