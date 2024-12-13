#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <pthread.h>

typedef struct th_arg{

    char *buf;
    unsigned int buf_size;

}th_arg_t;

pthread_mutex_t mutexData = PTHREAD_MUTEX_INITIALIZER;

short int maxs[512] = {0};
short int max_idx = 0;
short int max_global = 0;

void *th_func(void *args){

    th_arg_t *arg = (th_arg_t *)args;
    short int nr;
    short int max;

    int i = 0;
    for(i = 0; i < arg->buf_size -1; i = i + 2){
        memcpy(&nr, &arg->buf[i], sizeof(short int));
        if (i == 0) max = nr;
        else if(nr > max) max = nr;
        // printf("%hd\n", nr);
    }

    pthread_mutex_lock(&mutexData);
    if(max_idx < 512)
        maxs[max_idx++] = max;
    pthread_mutex_unlock(&mutexData);

    // printf("%hd\n", max);
    return NULL;
}

int main(int argc, char **argv){

    if(argc != 3){
        fprintf(stderr,"args\n");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_init(&mutexData, NULL);
    int N = atoi(argv[2]);
    int fd = open(argv[1], O_RDONLY);
    struct stat sb;


    if(fd < 0){
        perror("open");
        pthread_mutex_destroy(&mutexData);
        exit(EXIT_FAILURE);
    }

    if (lstat(argv[1],&sb) < 0){
        perror("lstat");
        pthread_mutex_destroy(&mutexData);
        exit(EXIT_FAILURE);
    }

    int CHUNK = (int)ceil(((double)sb.st_size/(double)N));
    char **str = (char **)malloc(N * sizeof(char *));

    if (!str){
        fprintf(stderr, "out of mem\n");
        if (close(fd) < 0) perror("close");
        pthread_mutex_destroy(&mutexData);
        exit(EXIT_FAILURE);
    }

    th_arg_t *arg = (th_arg_t *)malloc(N * sizeof(th_arg_t));

    if(!arg){
        fprintf(stderr, "out of mem\n");
        if (close(fd) < 0) perror("close");
        free(str);
        pthread_mutex_destroy(&mutexData);
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < N; i++){
        str[i] = (char *)malloc(CHUNK * sizeof(char));

        if(!str[i]){
            fprintf(stderr, "out of mem\n");
            for(int j = 0; j < i; j++) free(str[j]);
            if (close(fd) < 0) perror("close");
            free(str);
            free(arg);
            pthread_mutex_destroy(&mutexData);
            exit(EXIT_FAILURE);
        }

        int bytes;
        bytes = read(fd, str[i], CHUNK);

        if(bytes < 0){
            perror("read");
            for(int j = 0; j < i; j++) free(str[j]);
            if (close(fd) < 0) perror("close");
            free(str);
            free(arg);
            pthread_mutex_destroy(&mutexData);
            exit(EXIT_FAILURE);
        }

        arg[i].buf = str[i];
        arg[i].buf_size = bytes;
    }

    // THREAD CREATE
    pthread_t *threads = (pthread_t *)malloc(N * sizeof(pthread_t));
    if (!threads){
        fprintf(stderr, "out of mem\n");
        for(int i = 0; i < N; i++){
            free(str[i]);
        }
        free(str);
        free(arg);
        pthread_mutex_destroy(&mutexData);
        exit(EXIT_FAILURE);
    }

    int ret;
    for(int i = 0; i < N; i++){
        if ((ret = pthread_create(&threads[i], NULL, &th_func, &arg[i])) < 0){
            fprintf(stderr,"%s\n", strerror(ret));
            for(int i = 0; i < N; i++){
                free(str[i]);
            }
            free(str);
            free(arg);
            free(threads);
            pthread_mutex_destroy(&mutexData);
            exit(EXIT_FAILURE);
        }
    }

    // JOIN
    for (int i = 0; i < N; i++){
        if ((ret = pthread_join(threads[i], NULL)) < 0){
            fprintf(stderr,"%s\n", strerror(ret));
            for(int i = 0; i < N; i++){
                free(str[i]);
            }
            free(str);
            free(arg);
            free(threads);
            pthread_mutex_destroy(&mutexData);
            exit(EXIT_FAILURE);
        }
    }

    if (close(fd) < 0){
        perror("close");
    }

    max_global = maxs[0];
    for(int i = 1; i < max_idx; i++){
        if (maxs[i] > max_global) max_global = maxs[i];
    }

    printf("Max global %d\n", max_global);

    for(int i = 0; i < N; i++){
        free(str[i]);
    }

    free(str);
    free(arg);
    free(threads);
    pthread_mutex_destroy(&mutexData);

    return 0;
}
