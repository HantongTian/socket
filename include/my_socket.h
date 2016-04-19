/*
 * =====================================================================================
 *
 *       Filename:  my_socket.h
 *
 *    Description: my own socket function achieve 
 *
 *        Version:  1.0
 *        Created:  2016年04月10日 17时46分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (tht), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef MY_SOCKET
#define MY_SOCKET


#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

enum socketType
{
	TYPE_TCP = 0,
	TYPE_UDP
};

int CreateSocket(enum socketType protocal);

//Create a tcp server socket
int CreateTcpServerSocket(const char *service);

int TcpConnect(int sock, const char *serverIP, const int port);

#endif
