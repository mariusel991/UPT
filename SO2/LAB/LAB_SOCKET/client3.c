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
#define MAX_BUFF_LEN 512

void *read_sock(void *args){

    int serverfd = *((int *)args);

    while(1){

        size_t bytes = 0;
        char buff[MAX_BUFF_LEN] = {0};
        memset(buff, 0, sizeof(buff));

        if ((bytes = recv(serverfd, buff, MAX_BUFF_LEN - 1, 0)) < 0){

            if (bytes == 0){
                printf("Connection terminated by the server!\n");
            }
            else{
                printf("Error reciving data from server!\n");
            }

            break;
        }
        
        printf("%s\n", buff);
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

    if (connect(sockfd, (struct sockaddr *) &addr, sizeof(addr)) == -1){

        perror("connect");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Connection with the server was established!\n");
    pthread_t read_th;

    if ((errno = pthread_create(&read_th, NULL, &read_sock, &sockfd)) != 0){

        perror("pthread_create");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    int val = 0;
    while(1){

        if (scanf("%d", &val) != 1){

            while(getchar() != '\n')
                continue;
        }

        if (val > MAX_BUFF_LEN) continue;

        // printf("%d\n", val);

        if (send(sockfd, &val, sizeof(val), 0) < 0){
            perror("cannot send message!");
            break;
        }

        val = 0;
    }

    if ((errno = pthread_join(read_th, NULL)) != 0){

        perror("pthread_join");
        close(sockfd);
        exit(EXIT_FAILURE);
    }


    close(sockfd);
    return 0;
}
