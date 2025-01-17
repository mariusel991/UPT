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

void *handle_client(void *args){

    int serverfd = *((int *)args);

    int cfd;
    char err_msg[] = "N must be positive";

    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    memset(&addr, 0, sizeof(addr));

    if ((cfd = accept(serverfd, (struct sockaddr *)&addr, &len)) < 0){

        perror("Error accepting a client");
        pthread_exit(NULL);
    }

    printf("A client connected (%s:%d)\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

    while(1){

        size_t bytes = 0;
        int val = 0;

        if ((bytes = recv(cfd, &val, sizeof(int), 0)) <= 0){

            if (bytes == 0){
                printf("Client disconnected (%s:%d)\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
            }
            else{
                printf("Error reciving data from client!\n");
            }

            close(cfd);
            break;
        }

        // printf("%d\n", val);

        if (val <= 0){
            if (send(cfd, err_msg, sizeof(err_msg), 0) < 0){
                perror("Error sending msg to client");
                close(cfd);
                break;
            }
        }
        else if(val){
            
            char buff[MAX_BUFF_LEN] = {0};
            memset(buff, 0, sizeof(buff));

            for(int i = 0; i < val; i++){
                buff[i] = 33 + rand() % (127 - 33);
            }

            buff[val] = 0;

            // printf("%s\n", buff);
            if (send(cfd, buff, val, 0) < 0){
                perror("Error sending msg to client");
                close(cfd);
                break;
            }

            val = 0;
        }

        
    }

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

    pthread_t th[MAX_CLIENTS];
    
    for (int i = 0; i < MAX_CLIENTS; i++){

        if ((errno = pthread_create(&th[i], NULL, &handle_client, &sockfd)) != 0){

            perror("pthread_create");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < MAX_CLIENTS; i++){

        if ((errno = pthread_join(th[i], NULL)) != 0){

            perror("pthread_join");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
    }
    
    printf("Server stopped\n");
    close(sockfd);
    return 0;
}
