/*
3. Să se scrie un program care primește ca și argumente în linie de comandă calea către 2 fișiere:
          <program> <fișier-intrare> <fișier-ieșire>
Fișierul de intrare va conține un număr necunoscut de numere întregi pe 4 octeți.
Programul va citi fișierul de intrare în întregime și va scrie în fișierul de ieșire, în format text, numărul minim, numărul maxim și media numerelor citite din fișierul de intrare binar.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BLOCK_SIZE 4096

double avg = 0;
int min = -1;
int max = -1;
int cnt = 0;

void processInputFile(char *pathname){

    int fd = open(pathname, O_RDONLY);

    if (fd < 0){
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    char buf[BLOCK_SIZE] = {0};
    int bytes = 0;

    char char_num[5] = {};
    int num;

    // while ( (bytes = read(fd,buf,BLOCK_SIZE)) > 0 ){ /*Varianta byte cu byte - gresit? */

    //     for ( int i = 0; i < bytes; i++){

    //         char_num[i%4] = buf[i];

    //         if (i % 4 == 0 && i != 0){

    //             char_num[4]=0;
    //             num = atoi(char_num);

    //             if (min == -1 || max == -1){
    //                 min = max = num;
    //             }

    //             if (num > max) max = num;
    //             if (num < min) min = num;

    //             cnt++;
    //             avg+=num;
    //         }
    //     }
    // }

    // while ( (bytes = read(fd, &num, sizeof(int))) > 0){ /*Varinata read direct in int*/
        
    //     if (bytes != sizeof(int)) {
    //         fprintf(stderr, "Last num is not a full size int.\n");
    //         break;
    //     }

    //     if (min == -1 || max == -1){
    //         min = max = num;
    //     }

    //     if (num > max) max = num;
    //     if (num < min) min = num;

    //     cnt++;
    //     avg+=num;
    // }

    while ( (bytes = read(fd, buf, BLOCK_SIZE - 1)) > 0){ /*Varianta sscanf din buffer*/
        
        buf[bytes] = 0;

        while (sscanf(buf,"%d", &num)){

            if (min == -1 || max == -1){
            min = max = num;
            }

            if (num > max) max = num;
            if (num < min) min = num;

            cnt++;
            avg+=num;
        }
    }

    if (bytes == -1){
        perror("READ error");

        if (close(fd)){
            perror(NULL);
        }

        exit(EXIT_FAILURE);
    }

    if (close(fd)){
        perror(NULL);
        exit(EXIT_FAILURE);
    }

}

void processOutputFile(char *pathname){

    int fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if ( fd < 0 ){
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    char msg[128]={0};
    sprintf(msg,"numărul minim %d\nnumărul maxim %d\nmedia %.8lf\n", min, max, avg/cnt);
    
    if (write(fd, msg, strlen(msg)) < 0){
        perror(NULL);

        if (close(fd)){
            perror(NULL);
        }
        exit(EXIT_FAILURE);
    }

    if (close(fd)){
        perror(NULL);
        exit(EXIT_FAILURE);
    }

}

int main(int argc, char **argv){

    if ( argc != 3){
        fprintf(stderr, "Invalid args!");
        exit(EXIT_FAILURE);
    }

    processInputFile(argv[1]);
    processOutputFile(argv[2]);

    return 0;
}
