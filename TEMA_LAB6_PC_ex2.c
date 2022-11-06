#include <stdio.h>

int main(){
  int v[]={7, -5, 4, 3, -9, 2, -8};
  int minn;

  minn = v[0];
  
  for(int i = 1; i < 7; i++){
    if(v[i] < minn) minn = v[i];
  }

  printf("%d\n", minn);
  return 0;
}
