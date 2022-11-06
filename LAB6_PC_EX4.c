/*
Se citește un număr k. Să se afișeze dacă în vectorul {7, -5, 4, 3, -9, 2, -8}
există cel puțin un număr mai mare decat k.
*/



#include <stdio.h>

int este_par_pozitiv(int n){
  if(n > 0){
    if(n%2 == 0) return 1;
    return 0;
  }
  return 1;
}

int main(){
  int v[] = {7, -5, 4, 3, -9, 2, -8};
  int k, ok = 0;

  scanf("%d", &k);

  for(int i = 0; i < 7; i++){
    if(v[i] > k){
      ok = 1;
      break;
    }
  }

  if(ok == 0){
    printf("Nu exista numere mai mari ca %d\n", k);
  }
  else{
    printf("Exista numere mai mari ca %d\n", k);
  }
 
  return 0;
}
