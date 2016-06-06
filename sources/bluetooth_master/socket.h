/* 
 * File:   socket.h
 * Author: guido
 *
 * Created on 15 novembre 2015, 9.59
 */

#ifndef SOCKET_H
#define	SOCKET_H

int connect_to_slave(char* slave_address);
int close_connection(int slave_sock);

#endif	/* SOCKET_H */

