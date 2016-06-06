/*
 * File:   main.c
 * Author: guido
 *
 * Created on 2 novembre 2015, 17.08
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <unistd.h>
#include <inttypes.h>

#include "blue.h"
#include "socket.h"


#define MAX_NSAMPLES 2000

#define START_VELOCITY 1
#define STOP_VELOCITY  16
#define STEP_VELOCITY 1

#define FILE_PATH "/home/guido/Scrivania/data_files_final2/d"

int read_data_from_velocity(int slave_sock, int vel, int num_packets_to_read);

int main(int argc, char **argv) {
    int curr_vel = 0;
    int slave_sock = -1;


    char dest[18] = "00:16:53:08:F3:F8"; // NXT
    //char dest[18] = "A0:A8:CD:26:A5:51"; // Romas PC

    if ((slave_sock = connect_to_slave(dest)) < 0)
        return 0;

    sleep(2);
    curr_vel = START_VELOCITY;
    while (curr_vel <= STOP_VELOCITY) {

        read_data_from_velocity(slave_sock, curr_vel, MAX_NSAMPLES);
        curr_vel+=STEP_VELOCITY;
        sleep(2);

    }






    close_connection(slave_sock);

    return 0;
}



#define FILE_EXTENSION ".dat"
SMPACKET data_array[MAX_NSAMPLES];

int read_data_from_velocity(int slave_sock, int vel, int num_packets_to_read) {
    MSPACKET packet;
    FILE* file_fd = NULL;
    char file_name [1000];
    int error_code = 0;
    int num_packet_readed = 0;
    char string_to_write[100];


    // compilazione pacchetto da inviare

    packet.reference_speed = (uint8_t)vel;



    printf("Sending data, velocity: %d ....", vel);
    fflush(stdout);
    if (send(slave_sock, &packet, sizeof (MSPACKET), 0) != sizeof (MSPACKET)) {
        error_code = 1;

        goto end_function;
    }

    memset(data_array, 0x00, sizeof (SMPACKET) * num_packets_to_read);
    printf("Reading data, velocity: %d ....", vel);
    //lettura e scrittura dei dati
    num_packet_readed = 0;
    while (num_packet_readed < num_packets_to_read) {
        if (read(slave_sock, &data_array[num_packet_readed], sizeof (SMPACKET)) != sizeof (SMPACKET)) {
            error_code = 2;
            goto end_function;
        }
        printf("%d/%d\n", num_packet_readed,num_packets_to_read);
        num_packet_readed++;
    }

     // apertura/creazione file
    sprintf(file_name, "%s%d%s", FILE_PATH, vel, FILE_EXTENSION);
    file_fd = fopen(file_name, "w");
    if (file_fd == NULL) {
        error_code = 3;
        goto end_function;
    }
    num_packet_readed=0;
    while (num_packet_readed < num_packets_to_read) {
        memset(string_to_write,0x00, 100);
        sprintf(string_to_write, "%ld, %0.2f\n", data_array[num_packet_readed].system_time, data_array[num_packet_readed].speed);
        if(fwrite(string_to_write, sizeof (char), strlen(string_to_write), file_fd)!= (sizeof (char)*strlen(string_to_write))){
             error_code = 4;
             goto end_function;
        }
        num_packet_readed++;
    }

end_function:
    //chiusura del file
    if (file_fd != NULL)
        fclose(file_fd);



    switch (error_code) {
        case 0:
            printf("Readed %d packets\n", num_packet_readed);
            fflush(stdout);
            break;
        case 1:
            printf("Error send packet\n");
            fflush(stdout);
            break;
        case 2:
            printf("Error read packet\n");
            fflush(stdout);
            break;
        case 3:
            printf("Error open file\n");
            fflush(stdout);
            break;
        case 4:
            printf("Error write file\n");
            fflush(stdout);
            break;

        default:
            printf("Unk case\n");
            fflush(stdout);
            break;
    }
    return 0;
}