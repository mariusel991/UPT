/*
Să se citească de la tastatură un număr n<=5 iar apoi n valori de tip intreg.
 Să se afișeze toate valorile ale căror modul (valoare absolută) este strict
 mai mare decat 10.
*/



#include <stdio.h>

int abs(int x){
  if(x < 0) return -x;
  return x;
}

int main(){

  int n, x;
  scanf("%d", &n);

  for(int i=1; i <= n ;i++){
    scanf("%d", &x);
    if(abs(x) > 10){
      printf(" %d\n", x);
    }
  }
 
  return 0;
}
