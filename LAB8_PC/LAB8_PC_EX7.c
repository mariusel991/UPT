/* 
 7. Scrieti un program care tipareste la iesire textul citit de la intrarea standard, modificat astfel incat orice litera de la inceputul unui cuvant e transcrisa ca litera mare. La sfarsit, programul va tipari numarul total de cuvinte si numarul maxim de cuvinte pe aceeasi linie. Cuvintele sunt secvenţe de caractere despărţite prin unul sau mai multe "spatii albe".
*/

#include <stdio.h>

int main(){
    char ch, aux;
    unsigned int words = 0, max_line_words = -1;
    
    ch = getchar();/// primul cuv
    if(ch != EOF || ch != ' '){
        words++;
        max_line_words = 1;
        if(ch >= 'a' && ch <= 'z'){
            ch = ch - ('a'-'A');
        }
        putchar(ch);
        aux = ch;
    }
    
    while((ch = getchar()) != EOF){
        if(aux == ' '){
            if(ch != aux){
                words++;
                if(ch >= 'a' && ch <= 'z'){
                    ch = ch - ('a'-'A');
                }   
            } 
        }
        
        if(ch == '\n'){
            if(words > max_line_words){
                max_line_words = words;
            }
            words = 0;
        }
        
        aux = ch;
        putchar(ch);
    }
    if(aux != '\n'){
        words++;
        if(words > max_line_words){
                max_line_words = words;
            }
    }
    
    printf("%d\n", max_line_words);
    
}
