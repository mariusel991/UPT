/*
4. Să se scrie un program C care primește ca și argumente în linie de comandă o cale relativă sau absolută de 
director și o cale către un fișier.

Programul va avea următoarele funcționalități:

- va parcurge recursiv directorul dat ca și parametru
- pentru fiecare fișier întâlnit, programul va număra câte litere mici conține acesta
- va scrie rezultatul într-un fișier text dat ca și argument în linie de comandă, sub forma:
        <cale-director> <dimensiune> <nr-litere-mici> <tip-fișier>
        - unde tip-fișier poate fi: REG, LNK , DIR sau PIPE

-dacă primul argument nu este director, programul va afișa un mesaj de eroare
-dacă al doilea argument reprezintă un fișier deja existent pe disc, acesta va fi suprascris

Programul se va testa folosind un director ce conține directoare, fișiere obișnuite, legături simbolice
și named pipes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>           /* Definition of AT_* constants */
#include <sys/stat.h>
#include <dirent.h>
#include <ctype.h>

#define BLOCK_SIZE 1024

void scrie_fisier(char *input, int out_fd, int chars, const struct stat buff){


    char msg[64] = {0};

    if (out_fd < 0){
        return;
    }

    snprintf(msg, 63, "%s %ldB %d REG\n", input, buff.st_size, chars);
    
    if ( write(out_fd,msg,strlen(msg)) < 0 ){
        perror(NULL);
    }

}

void prelucrare_fisier(char *pathname, int out_fd){

    int fd = open(pathname, O_RDONLY);

    if ( fd < 0){
        perror(NULL);
        return;
    }

    char buf[BLOCK_SIZE] = {0};
    int bytes = 0;
    int chars = 0;

    while ( (bytes = read(fd,buf,BLOCK_SIZE)) > 0 ){

        for (int i = 0 ; i < bytes; i++){
            if (islower(buf[i])) chars++;
        }
    }

    if ( bytes == -1){
        perror("READ");
    }

    if (close(fd)){
        perror(NULL);
    }

    struct stat sb;
    if (lstat(pathname,&sb) < 0 ){
        perror(NULL);
    }

    scrie_fisier(pathname, out_fd, chars, sb);
}

void parsare_director(char *pathname, int out_fd){

    DIR *dir = opendir(pathname);
    char path[128]={0};

    if (dir == NULL){
        perror(NULL);
        return;
    }

    struct dirent *entry;
    struct stat sb;

    while ((entry = readdir(dir)) != NULL){

        if ((strcmp(entry->d_name,".") == 0) || (strcmp(entry->d_name,"..") == 0)) continue;

        if(pathname[strlen(pathname)] == '/'){
            snprintf(path, sizeof(path)-1, "%s%.*s", pathname, (int)strlen(entry->d_name), entry->d_name);
        }
        else{
            snprintf(path, sizeof(path)-1, "%s/%.*s", pathname,(int)strlen(entry->d_name), entry->d_name);
        }

        // printf("%s\n", path);
        if (lstat(path,&sb) < 0){
            perror("lstat");
            break;
        }

        if (S_ISDIR(sb.st_mode)){
            parsare_director(path, out_fd);
        }
        else if (S_ISREG(sb.st_mode)){
            prelucrare_fisier(path, out_fd);
        }

    }

    closedir(dir);

}

int main(int argc, char **argv){

    struct stat sb;

    if ( argc != 3){
        fprintf(stderr,"Invalid args");
        exit(EXIT_FAILURE);
    }

    if (lstat(argv[1], &sb) < 0){
        perror("lstat");
        exit(EXIT_FAILURE);
    }

    if(!S_ISDIR(sb.st_mode)){
        fprintf(stderr,"Primul argument nu este director");
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if ( fd < 0 ){
        perror(NULL);
    }

    if (lstat(argv[2], &sb) < 0){
        perror("lstat");
        exit(EXIT_FAILURE);
    }

    if (S_ISDIR(sb.st_mode)){
        if (close(fd) < 0){
            perror(NULL);
        }
        exit(EXIT_FAILURE);
    }
    
    parsare_director(argv[1], fd);

    return 0;
}
