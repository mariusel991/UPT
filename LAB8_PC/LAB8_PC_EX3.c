/*
 3.Scrieți un program, folosind getchar() pentru citire, care, primind la stdin redirectat un fișier text va tipari la iesirea
 standard histograma literelor, adica distributia in procente a literelor din fisier. Se considera in calcul doar litere mari
 si litere mici. Programul va printa pe cate un rand litera si procentajul de aparitie.
*/


#include <stdio.h>
#include <string.h>

int main(){
    float v[26]={}, total = 0;
    char ch;
    
    while((ch = getchar()) != EOF){
       if(ch >= 'a' && ch <= 'z'){
            v[ch - 'a']++;
            total++;
       }
    }
    
    for(int i = 0; i < 26; i++){
        if(v[i] == 0) continue;
        v[i] = (v[i]*100)/total;
        printf("%c - %.2f%%\n", i+'a', v[i]);
    }
    
    return 0;
}

