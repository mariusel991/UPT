/*
    Aplicația 11.5: Să se scrie o funcție care primește un număr întreg 0<=n<1000 și îl afișează în formă literară. Să
se apeleze funcția pentru numere introduse de la tastatură, pană la apariția valorii 1000.
Exemple: 108 → o suta opt; 520 → cinci sute douazeci; 16 → saisprezece 
*/

#include <stdio.h>

char zeci1[][20]={"unsprezece","doisprezece","treisprezece","paisprezece","cincisprezece","saisprezece","saptesprezece","optsprezece","nouasprezece"};
char unitati[][10]={"unu","doi","trei","patru","cinci","sase","sapte","opt","noua"};
char zeci[][15] = {"zece","douazeci","treizeci","patruzeci","cincizeci","saizeci","saptezeci","optzeci","nouazeci"};
char sute[][20] = {"o suta","doua sute","trei sute","patru sute","cinci sute","sase sute","sapte sute","opt sute","noua sute"};

int forma_lit(int n){
    
    if(n < 0) return -1;

    if(n == 1000){
        printf("o mie\n");
    }
    else if(n < 1000 && n >= 100){
        printf(" %s", sute[(n/100) - 1]);
        return forma_lit(n % 100);
    }
    else if(n >= 20 && n < 100){
        printf(" %s", zeci[(n/10)%10 - 1]);
        if(n % 10 != 0){
            printf(" si");
        }
        return forma_lit(n % 10);
    }
    else if(n >= 10 && n < 20){
        printf(" %s\n",zeci1[n%10 - 1]);
        return 1;
    }
    else if (n < 10){
        printf(" %s\n",unitati[n-1]);
        return 1;
    }
    else{
        return -1; 
    }
    return 1;
    
}

int main(){
    
    int n;
    
    printf("n = "), scanf("%d",&n);
    forma_lit(n);

    return 0;
}
