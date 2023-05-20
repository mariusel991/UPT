/*
    Aplicația 12.4: Se dau urmatoarele 6 culori: alb (1), galben(2), rosu(3), verde(4), albastru(5) si negru(6).
Costruiti toate steagurile formate din 3 culori care indeplinesc urmatoarele conditii:
- orice steag trebuie sa contina culoarea verde sau culoarea galben la mijloc.
- culorile din fiecare steag trebuie sa fie distincte.
*/

#include <stdio.h>
#include <string.h>

//int sol[]={ 1, 2, 3, 4, 5, 6};
char culori[][9]= {"alb","galben", "rosu", "verde", "albastru", "negru"};
char v[2][9];
int n = 6;

int valid(int k){
    if (k <= 2){

    ///int fr[10]={};

        for(int i = 0; i < k; i++){
            if(strcmp(v[i],v[k]) == 0){
                return 0;/// nu se acepta aceasi culoare de doua ori
            }
        }
        return 1;
    }
    else{
        return 0;
    }

}

int solutie(int k){
    if(k == 2){ /// steagul are maxim 3 culori
        if((strcmp(v[1],"galben") == 0) || (strcmp(v[1],"verde") == 0)){/// culoare de mijloc este galben sau verde
            
            return 1;
        }
    }
    return 0;
}

void afisare(){
    for(int i = 0; i < 3; i++){
        printf(" %s",v[i]);
    }
    printf("\n");
}

void back(int k){
    int i;

    for(i = 0; i < n; i++){
        
        strcpy(v[k],culori[i]);

        if(valid(k)){

            if(solutie(k)){
                afisare();
            }
            else{
                back(k + 1);
            }
        }
    }

}

int main(){

    back(0);
    return 0;
}
