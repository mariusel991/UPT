#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdint.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define LISTEN_BACKLOG 50
#define MAX_CLIENTS 10
#define MAX_BUFF_LEN 512

static int cfd[MAX_CLIENTS];
pthread_t th[MAX_CLIENTS];

void init_clients(){
    for(int i = 0; i < MAX_CLIENTS; i++) cfd[i] = -1;
}

typedef struct th_args{

    struct sockaddr_in addr;
    uint8_t client_poz;
    int serverfd;
    socklen_t len;

}th_args;


void *handle_client(void *args){

    th_args arg = *((th_args *)args);
    free(args);

    int clientfd = cfd[arg.client_poz];
    char err_msg[] = "N must be positive\n";

    while(1){

        size_t bytes = 0;
        int val = -1;

        if ((bytes = recv(clientfd, &val, sizeof(int), 0)) <= 0){

            if (bytes == 0){
                printf("Client %d disconnected (%s:%d)\n", arg.client_poz, inet_ntoa(arg.addr.sin_addr), ntohs(arg.addr.sin_port));
            }
            else{
                printf("Error reciving data from client!\n");
            }

            close(clientfd);
            break;
        }

        printf("%d\n", val);

        if (val < 0){
            if (send(clientfd, err_msg, sizeof(err_msg), 0) < 0){
                perror("Error sending msg to client");
                close(clientfd);
                break;
            }
        }
        else if(val > 0){
            
            char buff[MAX_BUFF_LEN] = {0};
            memset(buff, 0, sizeof(buff));

            for(int i = 0; i < val; i++){
                buff[i] = 33 + rand() % (127 - 33);
            }

            buff[val] = 0;

            // printf("%s\n", buff);
            if (send(clientfd, buff, val + 1, 0) < 0){
                perror("Error sending msg to client");
                close(clientfd);
                break;
            }
            val = 0;

        }
        
    }

    return NULL;
}

void *handle_connections(void *args){

    int serverfd = *((int *)args);
    int client_poz = 0;

    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    memset(&addr, 0, sizeof(addr));

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    init_clients();

    while (1){

        if (client_poz >= MAX_CLIENTS){
            printf("Maximum number of clients reached\n");
            break;
        }

        if ((cfd[client_poz] = accept(serverfd, (struct sockaddr *)&addr, &len)) < 0){
            perror("Error accepting a client");
            pthread_exit(NULL);
        }
        else{

            th_args *arg = malloc(sizeof(th_args));

            if (!arg){
                fprintf(stderr, "Out of mem\n");
                continue;
            }

            memset(arg, 0, sizeof(th_args));
            arg->addr = addr;
            arg->client_poz = client_poz;
            arg->serverfd = serverfd;
            arg->len = len;

            if ((errno = pthread_create(&th[client_poz], &attr, &handle_client, arg)) != 0){

                perror("pthread_create");
                pthread_exit(NULL);

            }
            printf("A new client connected (%s:%d)\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
            client_poz++;
        }
    }
    
    pthread_attr_destroy(&attr);
    return NULL;
}

int main(int argc, char *argv[]){

    srand(time(NULL));

    if (argc != 3){

        fprintf(stderr, "Args\n");
        exit(EXIT_FAILURE);
    }

    
    char *ip = argv[1];
    char *port = argv[2];

    errno = 0;
    uint16_t sport = strtol(port, NULL, 10);

    if (errno != 0){
        perror("strtol");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    if (inet_aton(ip, &addr.sin_addr) == 0){

        fprintf(stderr, "Invalid address!\n");
        exit(EXIT_FAILURE);

    }
    addr.sin_port = htons(sport);

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

    if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) == -1){

        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server bound succesfuly to %s:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

    if (listen(sockfd, LISTEN_BACKLOG) == -1){

        perror("Error listening");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening to %s:%d...\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

    pthread_t connections_th;
    
    if ((errno = pthread_create(&connections_th, NULL, &handle_connections, &sockfd)) != 0){

        perror("pthread_join");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
        

    if ((errno = pthread_join(connections_th, NULL)) != 0){

        perror("pthread_join");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    printf("Server stopped!\n");
    close(sockfd);
    return 0;
}
