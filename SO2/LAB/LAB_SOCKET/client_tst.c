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

    struct sockaddr_in in_addr;
    memset(&in_addr, 0, sizeof(struct sockaddr_in));
    in_addr.sin_family = AF_INET;
    in_addr.sin_port = htons(sport);
    
    if (inet_aton(ip, &in_addr.sin_addr) == 0){

        fprintf(stderr, "Address dosen't exits\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd, (struct sockaddr *)&in_addr, sizeof(struct sockaddr)) < 0){

        perror("Failed to connect to server.");
        exit(EXIT_FAILURE);

    }
    else{
        printf("Connected to the server\n");
    }

    char buffer[512] = {0};

    while (fgets(buffer, sizeof(buffer) - 1, stdin) != NULL){
        
        long long val = 0;

        char aux[32];
        char *p = strtok(buffer, " ");
        while(p != NULL){

            strcpy(aux, p);
            val = val + atoll(aux);
            p = strtok(NULL, " ");
        }


        if(send(sockfd, &val, sizeof(val), 0) < 0){

            perror("Error sending message!");
            break;
        }

        val = 0;


        if((recv(sockfd, &val, sizeof(val), 0)) < 0){
            
            perror("Connection intrerupted by server");
            break;
        }

        
        printf("%lld\n", val);
        
        val = 0;
    }

    
    close(sockfd);

    return 0;
}
