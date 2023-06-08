/*
3.Să se citească de la tastatură două variabile de tip double (se citește cu %lf, nu cu %g!!!) și să se afișeze numele variabilei care se află la adresa 
cea mai mică de memorie utilizând pointeri.
*/


#include <stdio.h>


int main(){
    double a, b;
    
    scanf("%lf %lf", &a, &b);
   ///printf("%ld\n%ld\n", &a-&b, &b-&a);
   ///printf("%p\n%p\n", &a, &b);
    if(&a-&b > 0){
        printf("a\n");
    }
    else{
        printf("b\n");
    }
    
    return 0;
}
