/*
Să se citească de la tastatură un număr n<=10 iar apoi n valori de tip int.
 Să se afișeze dacă toate valorile pozitive sunt pare.
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
  int v[10];
  int n, ok=0;

  scanf("%d", &n);
  
  for(int i = 0; i < n; i++){
      scanf("%d", &v[i]);
    
      if(!este_par_pozitiv(v[i])){
	        printf("Nu toate val pozitive sunt pare\n");
	        return 1;
      }
      if(v[i] > 0){
	      ok=1;
      }
  }

  if(ok == 0){
    printf("Nu exista numere pozitive\n");
  }
  else{
    printf("Toate valorile pozitive sunt pare");
  }
  
  return 0;
}
