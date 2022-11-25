/*
Se citesc 2 numere x și y cu x<y. Să se afișeze minimul elementelor din vectorul {7, -5, 4, 3, -9, 2, -8}, care se află în același timp și în intervalul [x,y].
*/


#include <stdio.h>
#include <limits.h>

int in_interval(int val, int x, int y){
  if (val >= x && val <= y) return 1;
  return 0;
}


int main(){
  int v[] = {7, -5, 4, 3, -9, 2, -8};
  int x, y, ok = 0, minn = INT_MAX;

  scanf("%d %d", &x, &y);

  for(int i = 0; i < 7; i++){
    if(in_interval(v[i],x,y)){
      if(v[i] <  minn){
	minn = v[i];
	ok = 1;
      }
    }
  }

  if(ok == 0){
    printf("nu exista minim intre %d si %d\n", x, y);
  }
  else{
    printf("%d\n", minn);
  }
  return 0;
}
