#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <unistd.h>

#include "blue.h"


#define MAX_ATTEMPTS 20

int connect_to_slave(char* slave_address) {
    struct sockaddr_rc addr = {0};
    int sockfd;
    int connection_status = -1;
    int attempts = 0;


    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba(slave_address, &addr.rc_bdaddr);

    // allocate a socket
    if ((sockfd = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM)) < 0) {
        printf("Error on socket creation!\n");
        return sockfd;
    }

    // connect to server
    printf("Try to connect...");
    fflush(stdout);

    while ((connection_status != 0)&&(attempts < MAX_ATTEMPTS)) {
        connection_status = connect(sockfd, (struct sockaddr *) &addr, sizeof (addr));
        if (connection_status != 0) {
            printf(".");
            fflush(stdout);
        }
        attempts++;
        sleep(1);
    }
    
    if (connection_status != 0) {        
        close(sockfd);
        sockfd = -1;
        printf("Error\n");
        fflush(stdout);
    } else {
        printf("ok!\n");
        fflush(stdout);
    }

    return sockfd;
}

int close_connection(int slave_sock){
     return close(slave_sock);
}


