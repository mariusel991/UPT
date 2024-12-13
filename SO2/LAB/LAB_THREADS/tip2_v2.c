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
#include <stdint.h>

#define max_nums 1024

typedef struct th_arg{
    int16_t *nums;
    int nums_size;
}th_arg_t;

pthread_mutex_t mutexData = PTHREAD_MUTEX_INITIALIZER;

int16_t max_nr[max_nums];
int16_t max_idx = 0;


void *th_func(void *args){

    th_arg_t *arg = (th_arg_t *)args;

    if(!arg){
        pthread_exit(NULL);
    }
    
    int max_local = 0;
    if (arg->nums_size > 0) max_local = arg->nums[0];

    for(int i = 1; i < arg->nums_size; i++){
        if(arg->nums[i] > max_local) max_local = arg->nums[i];
    }

    pthread_mutex_lock(&mutexData);
    if (max_idx < max_nums)
        max_nr[max_idx++] = max_local;
    pthread_mutex_unlock(&mutexData);

    return NULL;
}

int main(int argc, char **argv){

    if(argc != 3){
        fprintf(stderr,"args\n");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_init(&mutexData, NULL);
    int N = atoi(argv[2]);

    FILE *fp = fopen(argv[1], "rb");
    struct stat sb;

    if(!fp){
        perror("fopen");
        pthread_mutex_destroy(&mutexData);
        exit(EXIT_FAILURE);
    }

    if (lstat(argv[1],&sb) < 0){
        perror("lstat");
        pthread_mutex_destroy(&mutexData);
        exit(EXIT_FAILURE);
    }
  
    int CHUNK = (int)ceil(((double)sb.st_size/(double)N));
    int16_t **str = (int16_t **)malloc(N * sizeof(int16_t *));

    if (!str){
        fprintf(stderr, "out of mem\n");
        if (fclose(fp) < 0) perror("close");
        pthread_mutex_destroy(&mutexData);
        exit(EXIT_FAILURE);
    }

    th_arg_t *arg = (th_arg_t *)malloc(N * sizeof(th_arg_t));

    if(!arg){
        fprintf(stderr, "out of mem\n");
        if (fclose(fp) < 0) perror("close");
        free(str);
        pthread_mutex_destroy(&mutexData);
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < N; i++){
        str[i] = (int16_t *)malloc((CHUNK/2) * sizeof(int16_t));

        if(!str[i]){
            fprintf(stderr, "out of mem\n");
            for(int j = 0; j < i; j++) free(str[j]);
            if (fclose(fp) < 0) perror("close");
            free(str);
            free(arg);
            pthread_mutex_destroy(&mutexData);
            exit(EXIT_FAILURE);
        }
        int nums = 0;
        for(int j = 0; j < CHUNK/2; j++){
            if(fread(&str[i][j],sizeof(int16_t),1,fp)) nums++;
            else break;
        }

        arg[i].nums = str[i];
        arg[i].nums_size = nums;
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
    int16_t max_global = 0;
    if (max_idx > 0) max_global = max_nr[0];
    for(int i = 1; i < max_idx; i++)
        if (max_nr[i] > max_global) max_global = max_nr[i];

    pthread_mutex_destroy(&mutexData);
    for(int i = 0; i < N; i++) free(str[i]);

    free(threads);
    free(str);
    free(arg);
    fclose(fp);

    printf("Max global %d\n", max_global);

    return 0;

}
