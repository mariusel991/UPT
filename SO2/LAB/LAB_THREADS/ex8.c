/*
8. Să se scrie un program care primește ca și argument un fisier text
si un numar N reprezentand un numar de threaduri. Programul 
va citi din fisier cate un buffer de dimensiunea 
CHUNK (configurabila printr-un define) si il va da spre procesare cate unui 
thread. Daca nu mai sunt thread-uri disponibile din cele N programul va 
astepta pana cand exista vreun thread disponibil pentru a prelucra urmatori 
buffer disponibil. Toate thread-urile vor completa rezultatul intr-un tablou 
comun de histograma. Este necesar ca programul sa tina evidenta starii de 
executie si de join a fiecarui thread. Numarul N nu va fi ales ca si la 
problema 7 astfel incat fisierul sa fie impartit in partitii egale. 
Se va considera ca exista un pool de N thread-uri care se va ocupa de procesare. 
Daca nu exista thread-uri disponibile din pool (toate sunt ocupate cu 
procesarea unui buffer) atunci programul va astepta eliberarea unui thread. 
Se poate utiliza o functia care sa obtina care thread este liber din pool-ul 
de thread-uri. Se va tine evidenta starii de join si se va face join pe 
fiecare thread care isi termina executia
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>           /* Definition of AT_* constants */
#include <pthread.h>
#include <ctype.h>

#define TH_N 16
#define CHUNK 128

#define IS_JOINED(th_data, th_id) ((th_data[th_id].toJoin == 0) ? 1 : 0)

unsigned int vf[255] = {0};
long workLeft = 0;

pthread_mutex_t mutexData = PTHREAD_MUTEX_INITIALIZER;

typedef struct thread_data{

    int th_id;
    int active;
    int toJoin;
    
    char *str;
    int str_size;


}thread_data;

thread_data th_data[TH_N];

void th_data_init(){
    for(int i = 0; i < TH_N; i++){
        th_data[i].th_id = i;
        th_data[i].active = 0;
        th_data[i].toJoin = 0;
        th_data[i].str = NULL;
        th_data[i].str_size = 0;
    }
}

char **aloc_matrix(int m, int n){

    char **mat = NULL;

    mat = (char **)malloc(m * sizeof(char *));

    if(!mat){
        fprintf(stderr,"out of mem\n");
        return NULL;
    }

    for (int i = 0; i < m; i++){
        mat[i] = (char *)malloc((n + 1) * sizeof(char));

        if (!mat[i]){
            fprintf(stderr,"out of mem\n");
            for(int j = 0; j < i; j++){
                free(mat[i]);
            }
            free(mat);
            return NULL;
        }
    }

    return mat;
}

void destroy_mat(char ***mat, int m){
    for(int i = 0; i < m; i++){
        free((*mat)[i]);
    }
    free(*mat);
}

int existIdleThread(){

    pthread_mutex_lock(&mutexData);
    for(int i = 0; i < TH_N; i++){
        if (!th_data[i].active){
            pthread_mutex_unlock(&mutexData);
            return i;
        }
    }
    pthread_mutex_unlock(&mutexData);

    return -1;
}

void *th_func(void *arg){

    thread_data *data = (thread_data *)arg;

    for(int i = 0; i < data->str_size; i++){
        if (isalnum(data->str[i])){
            pthread_mutex_lock(&mutexData);
            vf[(unsigned int)data->str[i]]++;
            pthread_mutex_unlock(&mutexData);
        }
    }

    pthread_mutex_lock(&mutexData);
    th_data[data->th_id].active = 0;
    th_data[data->th_id].toJoin = 1;
    pthread_mutex_unlock(&mutexData);

    // printf("Gata TH_%d\n", data->th_id);

    return NULL;
}

int main(int argc, char **argv){

    if (argc != 3){
        fprintf(stderr,"args\n");
        exit(EXIT_FAILURE);
    }

    int N = atoi(argv[2]);
    char *file = argv[1];
    struct stat sb;
    pthread_t thread[TH_N];

    memset(vf,0,sizeof(vf));
    th_data_init();
    pthread_mutex_init(&mutexData, NULL);

    char **str = aloc_matrix(N,CHUNK);
    if (!str){
        fprintf(stderr,"out of mem\n");
        pthread_mutex_destroy(&mutexData);
        exit(EXIT_FAILURE);
    }

    if (lstat(file,&sb) < 0){
        perror("lstat");
        destroy_mat(&str, N);
        pthread_mutex_destroy(&mutexData);
        exit(EXIT_FAILURE);
    }

    workLeft = sb.st_size;
    int fd = open(file, O_RDONLY);

    if (fd < 0){
        perror("open");
        destroy_mat(&str, N);
        pthread_mutex_destroy(&mutexData);
        exit(EXIT_FAILURE);
    }

    int ret;
    int bytes = 0;

    while (workLeft > 0){
        // Search for open threads
        int th_id = -1;
        
        while((th_id = existIdleThread()) == -1){
            usleep(500000L);
        }

        memset(str[th_id], 0, CHUNK + 1);
        bytes = read(fd, str[th_id], CHUNK);

        if (bytes <= 0) break;

        pthread_mutex_lock(&mutexData);
        th_data[th_id].str = str[th_id];
        th_data[th_id].str_size = bytes;
        th_data[th_id].active = 1;
        pthread_mutex_unlock(&mutexData);


        if (!IS_JOINED(th_data,th_id)){
            printf("JOIN_TH_%d\n", th_id);
            if ((ret = pthread_join(thread[th_id], NULL)) < 0){
            fprintf(stderr,"%s\n", strerror(ret));
            destroy_mat(&str, N);
            pthread_mutex_destroy(&mutexData);
            close(fd);
            exit(EXIT_FAILURE);
            }

            th_data->toJoin = 0;
        }

        printf("REUSE TH_%d\n", th_id);
        if ((ret = pthread_create(&thread[th_id], NULL, &th_func, &th_data[th_id])) < 0){
            fprintf(stderr,"%s\n", strerror(ret));
            destroy_mat(&str, N);
            pthread_mutex_destroy(&mutexData);
            close(fd);
            exit(EXIT_FAILURE);
        }

        printf("Left : %ld\n", workLeft);
        workLeft -= bytes;
    }

    printf("GATA PROGRAM\n");

    // JOIN 
    for(int i = 0; i < TH_N; i++){
        if (th_data[i].toJoin){
            if ((ret = pthread_join(thread[i], NULL)) < 0){
            fprintf(stderr,"%s\n", strerror(ret));
            }
        }
    }

    destroy_mat(&str, N);
    pthread_mutex_destroy(&mutexData);
    close(fd);

    return 0;
}
