#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>

unsigned int cifre = 0;

pthread_mutex_t mutexVar = PTHREAD_MUTEX_INITIALIZER;

void *th_func(void *args){

    char *path = (char *)args;
    if (!path) pthread_exit(NULL);

    FILE *fp = fopen(path, "rb");
    if (!fp){
        fprintf(stderr, "th_fopen\n");
        pthread_exit(NULL);
    }

    char buf[1024];
    int membs = 0;
    int cifre_local = 0;
    while((membs = fread(buf,sizeof(char),1024,fp)) > 0){
        for(int i = 0; i < membs; i++){
            if(isdigit(buf[i])){
                cifre_local++;
            }
        }
    }

    fclose(fp);

    pthread_mutex_lock(&mutexVar);
    cifre=cifre + cifre_local;
    pthread_mutex_unlock(&mutexVar);


    return NULL;
}

int main(int argc, char **argv){

    if (argc != 2){
        fprintf(stderr, "args\n");
        exit(EXIT_FAILURE);
    }

    char *file = argv[1];

    int str_size = 2;
    int str_idx = 0;

    char **str = (char **)malloc(str_size * sizeof(char *));

    if(!str){
        fprintf(stderr, "out of mem");
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(file, "r");
    if (!fp){
        perror("fopen");
        free(str);
        exit(EXIT_FAILURE);
    }

    char buf[1024];
    while(fgets(buf,sizeof(buf)-1, fp) != NULL){


        int buf_size = strlen(buf);
        if(buf[buf_size - 1] == '\n') buf[buf_size - 1] = 0, buf_size--;


        if(str_idx == str_size){
            str_size = str_size * 2;
            char **tmp = realloc(str, str_size * sizeof(char *));

            if(!tmp){
                for(int i = 0; i < str_idx; i++) free(str[i]);
                free(str);
                fclose(fp);
                exit(EXIT_FAILURE);
            }

            str = tmp;
        }

        str[str_idx] = (char *)malloc((buf_size+1)*sizeof(char));

        if(!str[str_idx]){
            fprintf(stderr, "out of mem");
            for(int i = 0; i < str_idx; i++) free(str[i]);
            free(str);
            fclose(fp);
            exit(EXIT_FAILURE);
        }
        memset(str[str_idx],0,buf_size + 1);
        strncpy(str[str_idx],buf,buf_size);
        // printf("%s\n", str[str_idx]);
        str_idx++;
    }

    fclose(fp);

    pthread_t *th = (pthread_t*)malloc(str_idx * sizeof(pthread_t));
    if (!th){
        fprintf(stderr, "out of mem");
        for(int i = 0; i < str_idx; i++) free(str[i]);
        free(str);
        exit(EXIT_FAILURE);
    }

    pthread_mutex_init(&mutexVar, NULL);

    int ret;
    for(int i = 0; i < str_idx; i++){
        if((ret = pthread_create(&th[i], NULL, &th_func, str[i])) < 0){
            fprintf(stderr,"%s\n", strerror(ret));
            for(int i = 0; i < str_idx; i++) free(str[i]);
            free(str);
            free(th);
            exit(EXIT_FAILURE);
        }
    }

    // JOIN

    for(int i = 0; i < str_idx; i++){
        if((ret = pthread_join(th[i], NULL)) < 0){
            fprintf(stderr,"%s\n", strerror(ret));
            for(int i = 0; i < str_idx; i++) free(str[i]);
            free(str);
            free(th);
            exit(EXIT_FAILURE);
        }
    }

    // for(int i = 0; i < str_idx; i++){
    //     printf("%s\n", str[i]);
    // }

    for(int i = 0; i < str_idx; i++){
        free(str[i]);
    }

    printf("Total cifre: %d\n", cifre);

    free(str);
    free(th);
    pthread_mutex_destroy(&mutexVar);

    return 0;
}
