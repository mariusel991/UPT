#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>


#define LISTEN_BACKLOG 50
#define MAX_CONNECTIONS 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int client[MAX_CONNECTIONS] = {0};
int sums[MAX_CONNECTIONS] = {0};

int idx = 0;

void *th_func(void *args){

    int sockfd = *((int *)args);
    int local_index = -1;

    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);   
    memset(&addr, 0, sizeof(struct sockaddr_in));

    
    pthread_mutex_lock(&mutex);
    local_index = idx;
    idx++;
    pthread_mutex_unlock(&mutex);

    if (local_index >= MAX_CONNECTIONS){
        fprintf(stderr, "Max Connections reached!\n");
        pthread_exit(NULL);
    }

    if ((client[local_index] = accept(sockfd, (struct sockaddr *)&addr, &len)) < 0){

        perror("Cannot accept client");
        pthread_exit(NULL);

    }
    else{
        printf("A client connected! (%s:%d)\n",inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
    }

    sums[local_index] = 0;
    int size;

    // char local_buffer[512] = {0};

    // while((size = recv(client[local_index], local_buffer, sizeof(local_buffer)-1, 0)) > 0){

    //     char *p;
    //     char aux[64];
    //     int val;
    //     memset(aux, 0, sizeof(aux));

    //     p = strtok(local_buffer, " ");
    //     while(p != NULL){

    //         strcpy(aux,p);
    //         val = atoi(aux);
    //         sums[local_index] += val;
    //         p = strtok(NULL, " ");
    //     }

    //     sprintf(aux,"%d", sums[local_index]);
    //     if (send(client[local_index], aux, sizeof(aux), 0) < 0){
    //         perror("Failed to send");
    //         break;
    //     }
        
    // }  // SAU

    long long nr = 0;

    while((size = recv(client[local_index], &nr, sizeof(long long), 0)) > 0){

        sums[local_index] += nr;
        
        if (send(client[local_index], &sums[local_index], sizeof(int), 0) < 0){
            perror("Failed to send");
            close(client[local_index]);
            sums[local_index] = 0;

            return NULL;
        }

        nr = 0;
        
    }

    printf("Client disconnected! (%s:%d)\n",inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
    close(client[local_index]);
    sums[local_index] = 0;

    return NULL;
}

int main(int argc, char **argv){

    if (argc != 3){
        fprintf(stderr, "Args!\n");
        exit(EXIT_FAILURE);
    }

    errno = 0;

    char *ip = argv[1];
    char *port = argv[2];
    uint32_t sport = strtol(port, NULL, 0);

    if (errno != 0){

        perror("stroll");
        exit(EXIT_FAILURE);
    }

    int sockfd;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        
        perror("socket");
        exit(EXIT_FAILURE);
    }

    int opt = 1;

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){

        perror("sockopt");
        close(sockfd);
        exit(EXIT_FAILURE);
    
    }

    struct sockaddr_in in_addr;
    memset(&in_addr, 0, sizeof(struct sockaddr_in));
    in_addr.sin_family = AF_INET;
    in_addr.sin_port = htons(sport);
    
    if (inet_aton(ip, &in_addr.sin_addr) == 0){

        fprintf(stderr, "Address dosen't exits\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    if (bind(sockfd, (struct sockaddr *)&in_addr, sizeof(struct sockaddr_in)) < 0){

        perror("Cannot bind to address");
        close(sockfd);
        exit(EXIT_FAILURE);

    }
    else{
        printf("Socket successfully binded..\n");
    }

    if (listen(sockfd, LISTEN_BACKLOG) == -1){
        
        perror("listen");
        close(sockfd);
        exit(EXIT_FAILURE);

    }
    else{
        printf("Server listening on %s:%s\n", ip, port);
    }

    pthread_mutex_init(&mutex, NULL);
    pthread_t tids[MAX_CONNECTIONS];

    int ret;
    for(int i = 0; i < MAX_CONNECTIONS; i++){

        if ((ret = pthread_create(&tids[i], NULL, &th_func, &sockfd)) != 0){

            fprintf(stderr, "%s\n", strerror(ret));
            pthread_mutex_destroy(&mutex);
            close(sockfd);
            exit(EXIT_FAILURE);

        }
    }

    for (int i = 0; i < MAX_CONNECTIONS; i++){

        if ((ret = pthread_join(tids[i], NULL)) != 0){

            fprintf(stderr, "%s\n", strerror(ret));
            pthread_mutex_destroy(&mutex);
            close(sockfd);
            exit(EXIT_FAILURE);

        }
    }

    
    pthread_mutex_destroy(&mutex);
    close(sockfd);

    return 0;
}
