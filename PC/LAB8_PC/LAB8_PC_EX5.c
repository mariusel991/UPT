/*
    5.Scrieti un program care numără caracterele, cuvintele şi liniile citite de la intrarea standard, pana la sfarsitul acesteia.
    Cuvintele sunt secvenţe de caractere despărţite prin unul sau mai multe "spatii albe". Precizări O linie se numără doar când
    e încheiată cu '\n'. Programul va tipări la ieşire numărul de linii, cuvinte, şi caractere, aliniate la dreapta pe un câmp de
    lăţime 7 (se poate face cu formatul %7d), şi separate prin câte un spaţiu. Pentru comparaţie, folosiţi programul UNIX wc (word
    count).
*/

#include <stdio.h>

int main(){
    
    unsigned int words = 0, lines = 0, char_c = 0, ok = 0, k = 0;
    char ch, aux;
    
    while((ch = getchar()) != EOF){
        char_c++;
        k++;
        if(ch == '\n'){
            if(k == 2) words++;
             lines++;
             k = 0;
        }
        if(ch == ' '){
            ok = 1;
            
            if(ch != aux && ok == 1){
            words++;
            ok = 0;
            }
        }
        aux = ch;
    }
    if(aux != ' ') words++;
    
    printf("%d %7d %7d\n",lines, char_c, words);
    
    return 0;
}
