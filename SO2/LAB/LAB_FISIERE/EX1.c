/*
1. Să se scrie un program care primește ca și argumente în linie de comandă calea către 2 fișiere:
          <program> <fișier-intrare> <fișier-ieșire>
Programul va citi în întregime <fișier-intrare>, și va afișa la ieșirea standard octeții transformați după regula următoare:
dacă octetul are valoarea între 97 și 122, va fi afișat folosind printf, ca și literă mică
altfel se va afișa în hexadecimal
La final, programul va scrie în <fișier-ieșire> o linie de forma:
''Numărul total de litere mici afișate este ...''
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFF_SIZE 4096

unsigned int litere_mici = 0;

void prelucreaza_fisier(char *pathname){
    
    int fd = open(pathname, O_RDONLY);

    if (fd < 0){
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    char buf[BUFF_SIZE];
    int bytes = 0;

    while ((bytes = read(fd, buf, BUFF_SIZE)) > 0){

        for (int i = 0; i < bytes; ++i){

            if (buf[i] >= 97 && buf[i] <= 122){
                printf("%c",buf[i]);
                litere_mici++;
            }
            else{
                printf("%X",buf[i]);
            }
        }
    }

    if (bytes == -1){
        perror("Read error");
    }

    if (close(fd)){
        perror(NULL);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv){

    if (argc != 3){
        fprintf(stderr, "Invalid arguments!\n");
        exit(EXIT_FAILURE);
    }

    struct stat sb;

    if (lstat(argv[1], &sb) == -1) {
        perror("lstat");
        exit(EXIT_FAILURE);
    }

    if (!S_ISREG(sb.st_mode)){
        fprintf(stderr, "Expected a file...\n");
        exit(EXIT_FAILURE);
    }
    else{
        prelucreaza_fisier(argv[1]);
    }

    if (litere_mici != 0){

        int fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);

        if ( fd < 0 ){
            perror(NULL);
            exit(EXIT_FAILURE);
        }

        char msg[64];
        snprintf(msg,63, "Numărul total de litere mici afișate este %d\n", litere_mici);

        if (write(fd,msg,strlen(msg)) < 0){
            perror(NULL);
        }

        if (close(fd)){
        perror(NULL);
        exit(EXIT_FAILURE);
        }
    }

    return 0;
}
