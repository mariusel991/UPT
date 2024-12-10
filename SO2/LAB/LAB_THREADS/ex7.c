/*
7. Sa se scrie un program care primeste ca si argument un fisier text
 si un numar N reprezentat un numar de thread-uri. Programul va
  imparti fisierul in N partitii egale si pentru fiecare partitie
   va lansa un thread care va realiza histograma caracterelor din fisier.
    Thread-urile vor completa rezultatul intr-un tablou comun de histrograma.     
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>           /* Definition of AT_* constants */
#include <ctype.h>

#define TH_N 10

pthread_mutex_t mutexSharedData = PTHREAD_MUTEX_INITIALIZER;

int BUFFER_SIZE = 0;
int N = 0;

unsigned int vf[255] = {0};

void *process_chunk(void *arg){

    char *str = (char *)arg;

    if (str == NULL){
        pthread_exit(NULL);
    }

    for (int i = 0; i < strlen(str); i++){
        if (isalnum(str[i])){
            pthread_mutex_lock(&mutexSharedData);
            vf[(unsigned int)str[i]]++;
            pthread_mutex_unlock(&mutexSharedData);
        }
    }

    return NULL;
}

char **alloc_matrix(int n, int m){

    char **s = (char **)malloc(n * sizeof(char *));

    if (!s){
        fprintf(stderr, "out of mem");
        return NULL;
    }

    for (int i = 0; i < n; i++){

        s[i] = (char *)malloc((m + 1) * sizeof(char));

        if (!s[i]){
            fprintf(stderr, "out of mem");
            for (int j = 0; j < i; j++){
                free(s[i]);
                free(s);
            }
            return NULL;
        }
    }

    return s;

}

void citeste_continut(char ***str, char *pathname){
    
    if(!*str){
        return;
    }

    int fd = open(pathname, O_RDONLY);

    if (fd < 0 ){
        perror("open");
        return;
    }

    char buf[BUFFER_SIZE + 1];
    memset(buf,0,sizeof(buf));
    memset(vf, 0 , sizeof(vf));

    for (int i = 0; i < N; i++){
        if (read(fd,buf,BUFFER_SIZE) > 0){
            memcpy((*str)[i], buf, BUFFER_SIZE + 1);
        }
        else{
            memset((*str)[i], 0, BUFFER_SIZE + 1);
        }
    }

    close(fd);
}

void print_histogram(){

    for(int i = 'a'; i <= 'z'; i++){
        if (vf[i]){
            printf("'%c' %d\n", i, vf[i]);
        }
    }

    for(int i = 'A'; i <= 'Z'; i++){
        if (vf[i]){
            printf("'%c' %d\n", i, vf[i]);
        }
    }

    for(int i = '0'; i <= '9'; i++){
        if (vf[i]){
            printf("'%c' %d\n", i, vf[i]);
        }
    }
}

int main(int argc, char **argv){

    if (argc != 3){
        fprintf(stderr,"args\n");
        exit(EXIT_FAILURE);
    }

    char *file = argv[1];
    N = atoi(argv[2]);

    struct stat sb;
    pthread_mutex_init(&mutexSharedData, NULL);

    if (lstat(file, &sb) < 0){

        perror("lstat");
        exit(EXIT_FAILURE);

    }

    BUFFER_SIZE = sb.st_size / N;

    char **s = alloc_matrix(N,BUFFER_SIZE); // alloc o matrice N x M 
    citeste_continut(&s, file);

    pthread_t *th = (pthread_t *)malloc(N * sizeof(pthread_t));

    if (!th){

        fprintf(stderr, "out of mem");
        
        for(int i = 0; i < N; i++){
            free(s[i]);
        }

        free(s);
        free(th);

        exit(EXIT_FAILURE); 
        
    }

    for(int i = 0; i < N; i++){

        int ret = 0;
        if ((ret = pthread_create(&th[i], NULL, &process_chunk, s[i])) < 0){
            fprintf(stderr, "%s\n", strerror(ret));
            continue;
        }
    }

    for(int i = 0; i < N; i++){
        int ret = 0;
        if ((ret = pthread_join(th[i], NULL)) < 0){
            fprintf(stderr, "%s\n", strerror(ret));
            continue;
        }
    }

    print_histogram();

    for(int i = 0; i < N; i++){
        free(s[i]);
    }

    free(s);
    free(th);

    pthread_mutex_destroy(&mutexSharedData);

    return 0;
}
