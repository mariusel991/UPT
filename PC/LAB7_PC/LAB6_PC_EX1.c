/*
  1. Se citesc două variabile, a și b, de tip întreg. Să se stocheze într-un pointer adresa variabilei 
  care conține valoarea maximă și apoi să se afișeze valoarea pointată
*/

#include <stdio.h>

int main(){
    int a,b, *p;
    scanf("%d %d", &a, &b);
    
    ///printf("a - %p\n", &a);
    ///printf("b - %p\n", &b);
    
    if(a > b){
        p = &a;
    }
    else{
        p = &b;
    }
    
    printf("%d\n", *p);
    
    return 0;
}
