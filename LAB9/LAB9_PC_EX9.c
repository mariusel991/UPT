/*
9. Sa se scrie o functie cu urmatorul antent:
  uint32_t string_replace(char *where, const char *what, const char *replace)
  
Functia inlocuieste fiecare aparitie a string-ului what in string-ul where cu string-ul replace. 
Se considera ca zona de memorie a lui where este suficient de mare ca sa poata contine noul string. 
Functia returneaza numarul de inlocuiri

char s1[1000];
char s2[] = "string";
char s3[] = "sir de caractere";

strcpy(s1, "Acesta este un string si un string este terminat cu 0x00");

int r = string_replace(s1, s2, s3);

s1 devine "Acesta este un sir de caractere si un sir de caractere este terminat cu 0x00";
s2, s3 - raman neschimbate
r = 2
*/


////### DE AICI INCEPE PRACTIC ###

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



uint32_t string_replace(char *where, const char *what, const char *replace){
    char* subsir = strstr(where, what); /// subsir - "mere delicioase\0"
    if(subsir == NULL){
        return 0;/// nu am gasit cu ce sa inlocuim in sursa - practic nu am gasit *what in *subsir deci nu se poate face nici o inlocuire
    }
    
    memmove(
        subsir + strlen(replace),///mutam cu strlen(replace) caractere in memorie pt a avea loc de replace si a nu rescrie memoria
        subsir + strlen(what),/// sursa de unde mutam
        strlen(subsir) - strlen(what) + 1 /// cate caractere = + 1 pt ca luam in
        ///considerare si '\0', deoarece strlen nu numara terminatorul de sir
    );
    
    memcpy(subsir, replace, strlen(replace));///copiem (rescriem) in memorie peste what cu replace
    return 1 + string_replace(where,what,replace);/// calculam recursiv nr de executii adica r
}


int main()
{
    ///char str[100] = "Ana are mere delicioase";
    ///char str2[]="mere";                         TEST - nu se ia in considerare
    ///char str3[]="castane";
    
    ///printf("%s\n", str);
  
    char s1[1000];
    char s2[] = "string";
    char s3[] = "sir de caractere";
    strcpy(s1, "Acesta este un string si un string este terminat cu 0x00");
    
    int r = string_replace(s1, s2, s3);
    
    ///printf("%s\n", str); /// Ana are castane delicioase
    printf("%d\n", r);
    
    

    return 0;
}
