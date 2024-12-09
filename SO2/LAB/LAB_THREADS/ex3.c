/*
3. Acelasi enunt ca si problema 2 dar programul va afisa
 in plus si numarul total de aparitii al caracterului in
  toate liniile citite
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_THREADS 128
#define BUFFER_LENGTH 512

char ch;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int total_aparitii = 0;

void *process_line(void *arg){

    char *str = (char *)arg;
    char buf[BUFFER_LENGTH];
    strncpy(buf,str, BUFFER_LENGTH);
    buf[BUFFER_LENGTH - 1] = '\0';
    unsigned int cnt = 0;

    for(int i = 0; i < strlen(buf); i++){
        if (buf[i] == ch){
            cnt++;
            pthread_mutex_lock(&mutex);
            total_aparitii++;
            pthread_mutex_unlock(&mutex);
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
    pthread_mutex_init(&mutex, NULL);

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

    pthread_mutex_destroy(&mutex);

    printf("Total aparitii caracter '%c': %d\n", ch, total_aparitii);

    return 0;
}
