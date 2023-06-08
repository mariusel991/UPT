/*
  Se citește un număr n<=10 și apoi n numere întregi. Se cere să se șteargă din vector toate acele elemente care sunt urmate de un număr strict mai mare decât ele,
  păstrându-se ordinea elementelor
*/


#include <stdio.h>

int main(){
    int n, v[10];
    
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }
    
    for(int i = 0; i < n-1; i++){
        if(v[i] < v[i+1]){
            for(int j = i+1; j < n;j++){
                v[j] = v[j+1];
            }
            n--;
            i--; ///  <-- linia asta e cea care conteaza cea mai mult ea decide tipul problemei
                /// mai exact daca se sterge doar prima aparitie sau toate inclusiv cu
                ///modificarile
        }
    }
    
    for(int i = 0; i < n; i++){
        printf("%d ", v[i]);
    }
    printf("\b\n");
    
    return 0;
    
}
