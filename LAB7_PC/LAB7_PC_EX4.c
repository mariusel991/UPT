/*
 4. Scrieți un program care interschimbă valorile a două variabile de tip întreg utilizând pointeri
*/

#include <stdio.h>


int main(){
    int a,b, *p1, *p2, aux;
    
    scanf("%d %d", &a, &b);
    p1 = &a;
    p2 = &b;
    aux = *p1;
    
    *p1 = *p2;
    *p2 = aux;
    
    printf("%d %d\n", a, b);
    
    return 0;
}
