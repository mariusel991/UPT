/*
2. Sa se scrie un program care primeste ca si argument un caracter si
 citeste cate o linie de la intrarea standard. Pentru fiecare linie
  citita programul va crea un thread care va numara de cate ori caracterul
   dat ca si argument se regaseste in linia citita si va printa acest numar
    la iesirea standard.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_THREADS 128
#define BUFFER_LENGTH 512

char ch;

void *process_line(void *arg){

    char *str = (char *)arg;
    char buf[BUFFER_LENGTH];
    strncpy(buf,str, BUFFER_LENGTH);
    buf[BUFFER_LENGTH - 1] = '\0';
    unsigned int cnt = 0;

    for(int i = 0; i < strlen(buf); i++){
        if (buf[i] == ch){
            cnt++;
        }
    }

    printf("%d\n", cnt);

    return NULL;
}

int main(int argc, char **argv){

    if (argc != 2){
        fprintf(stderr, "args\n");
        exit(EXIT_FAILURE);
    }

    ch = argv[1][0];

    int th_created = 0;
    pthread_t thread[MAX_THREADS];

    char line[BUFFER_LENGTH] = {0};


    while(fgets(line, sizeof(line)-1,stdin) != NULL && (th_created < MAX_THREADS)){

        int ret;

        if ((ret = pthread_create(&thread[th_created++],NULL, &process_line, line)) < 0){
            fprintf(stderr, "%s\n", strerror(ret));
            exit(EXIT_FAILURE);
        }
    }

    /// join

    for (int i = 0; i < th_created; i++){

        int ret;
        if ((ret = pthread_join(thread[i], NULL)) < 0){
            fprintf(stderr, "%s\n", strerror(ret));
        }
    }

    return 0;
}
