/*
Subiectul 2.2 Se citesc mai multe cuvinte din linia de comandă. Cu ajutorul pointerilor la funcții (un vector de
pointeri la funcții) să se apeleze într-o structură repetitivă următoarele funcții. Să se afișeze rezultatele pentru
fiecare cuvânt pe ecran și în fișierul text CUVINTE.TXT.
a) Primește parametru un șir de caractere și returneză lungimea șirului.
b) Primește parametru un șir de caractere și returneză numărul de vocale din text.
c) Primește parametru un șir de caractere și returneză numărul de litere mari din text.
Primește parametru un șir de caractere și returneză diferența codurilor ASCII ale primului caracter și al ultimului
caracter.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

int len(const char *str);
int nrVoc(const char *str);
int UpperCount(const char *str);
int AsciiDiff(const char *str);

void process_file(const char *cuv, FILE *fp, int (*f[4])(const char *)){
    for(int j = 0; j < 4; j++){
        int res = f[j](cuv);
        fprintf(fp,"%s - functie %d => %d\n",cuv,j,res);
    }
    fprintf(fp,"\n");
}

int main(int argc, char *argv[]){

    if(argc < 2){
        fprintf(stderr,"Nu s-au citit cuvinte\n");
        exit(errno);
    }

    FILE *fp = fopen("CUVINTE.TXT", "w");
    
    if(!fp){
        fprintf(stderr,"Cannot open the file.txt..\n");
        exit(errno);
    }

    int (*f[4])(const char *) = {len, nrVoc, UpperCount, AsciiDiff};


    for(int i = 1; i < argc; i++){
        const char *cuv = argv[i];
        process_file(cuv, fp, f);
    }

    fclose(fp);

    return 0;
}

/// FUNCTII

int len(const char *str){
    return strlen(str);
}

int nrVoc(const char *str){
    int cnt = 0;
    for(int i = 0; i < strlen(str); i++){
        if(strchr("aeiouAEIOU", str[i]) != NULL){
            cnt++;
        }
    }
    return cnt;
}

int UpperCount(const char *str){
    int cnt = 0;
    for(int i = 0; i < strlen(str); i++){
        if(isupper(str[i])){
            cnt++;
        }
    }
    return cnt;
}

int AsciiDiff(const char *str){
    return str[0] - str[strlen(str) - 1];
}
