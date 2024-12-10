/*
9. Acelasi enunt ca si la probema 8 dar se va implementa folosind 
thread-uri DETACHED.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>           /* Definition of AT_* constants */
#include <string.h>
#include <pthread.h>
#include <stdint.h>
#include <ctype.h>

#define CHUNK 128

pthread_mutex_t mutexData = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

uint8_t busy_th;
uint8_t not_busy_th;

int total_size = -1;

unsigned int vf[255] = {0};

typedef struct th_args{

    char *buf;
    int buf_size;

}th_args;

void *th_func(void *arg){

    th_args *args = (th_args *)arg;

    if (!args){
        fprintf(stderr, "A th exited\n");
        pthread_exit(NULL);
    }

    for (int i = 0; i < args->buf_size; i++){
        if (isalnum(args->buf[i])){
            pthread_mutex_lock(&mutexData);
            vf[(unsigned int)args->buf[i]]++;
            pthread_mutex_unlock(&mutexData);
        }
    }


    pthread_mutex_lock(&mutexData);
    busy_th--;
    total_size -= args->buf_size;
    if(busy_th >= 0){
        pthread_cond_signal(&cond);
    }
    pthread_mutex_unlock(&mutexData);

    free(args->buf);
    free(args);

    return NULL;
}

void print_hisogram(){
    
    for(int i = '0'; i <= '9'; i++){
        printf("'%c':%d\n", i , vf[i]);
    }

    for(int i = 'A'; i <= 'Z'; i++){
        printf("'%c':%d\n", i , vf[i]);
    }

    for(int i = 'a'; i <= 'z'; i++){
        printf("'%c':%d\n", i , vf[i]);
    }
}

int main(int argc, char **argv){

    if (argc != 3){
        fprintf(stderr,"args\n");
        exit(EXIT_FAILURE);
    }

    char *file = argv[1];
    int N = atoi(argv[2]);

    struct stat sb;

    if(lstat(file,&sb) < 0){
        perror("lstat");
        exit(EXIT_FAILURE);
    }
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_mutex_init(&mutexData, NULL);
    pthread_cond_init(&cond, NULL);
    memset(vf,0,sizeof(vf));

    total_size = sb.st_size;
    busy_th = 0;
    not_busy_th = N;

    int fd = open(file, O_RDONLY);

    if (fd < 0){
        perror("open");
        pthread_attr_destroy(&attr);
        pthread_mutex_destroy(&mutexData);
        exit(EXIT_FAILURE);
    }

    pthread_mutex_lock(&mutexData);
    while (total_size > 0){

        char *buf = (char *)malloc((CHUNK + 1) * sizeof(char));
        int bytes = 0;

        if(!buf){
            pthread_attr_destroy(&attr);
            pthread_mutex_destroy(&mutexData);
            exit(EXIT_FAILURE);
        }

        th_args *args = (th_args *)malloc(sizeof(th_args));

        if (!args){
            free(buf);
            pthread_attr_destroy(&attr);
            pthread_mutex_destroy(&mutexData);
            exit(EXIT_FAILURE);
        }

        if ((bytes = read(fd,buf,CHUNK)) <= 0){
            break;
        }

        args->buf = buf;
        args->buf_size = bytes;

        if (busy_th < N){
            pthread_t th;
            int ret;

            busy_th++;
        
            if((ret = pthread_create(&th,&attr,&th_func, args)) < 0){
                fprintf(stderr, "%s\n",strerror(ret));
                pthread_attr_destroy(&attr);
                pthread_mutex_destroy(&mutexData);
                free(buf);
                free(args);
                exit(EXIT_FAILURE);
            }
            pthread_cond_wait(&cond, &mutexData);

        }
    }
    pthread_mutex_unlock(&mutexData);


    print_hisogram();

    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&mutexData);

    return 0;
}
