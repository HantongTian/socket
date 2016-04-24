/*
 * =====================================================================================
 *
 *       Filename:  tcp_server.c
 *
 *    Description:  Tcp echo server
 *
 *        Version:  1.0
 *        Created:  2016年04月24日 14时33分40秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (tht), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include "../../include/my_log.h"
#include "../../include/my_socket.h"


#define CLIENT_VERSION "1.0.0.1\n"

const int BUF_SIZE = 1024;

void Usage()
{
	fprintf( stderr, "tcpServer  info\n" );
	fprintf( stderr, "Options:\n" );
	fprintf( stderr, "  -s, --serverIP    : Server IP \n" );
	fprintf( stderr, "  -h, --help        : This screen\n" );
	fprintf( stderr, "  -v, --version     : Report the installed version of tcpclient\n" );		
	exit( 0 );
}

void *EchoThreadProc(void *pclntSock);	//echo thread

int HandleTCPClient(int clntSock);


int main(int argc, char *argv[])
{
	char *pPort = NULL;
	char *serverIP = NULL;

	if(2 > argc)
	{
		LogInfo("Parameter input error", LOG_INFO);
		return -1;
	}

	static struct option long_options[] = {
		{"serverIP", 1, 0, 's'},
		{"port", 1, 0, 'p'},
		{"help", 0, 0, 'h'},
		{"version", 0, 0, 'v'},
		{0, 0, 0, 0}
	};

	while (1)
	{
		int option_index = 0;

		int c = getopt_long (argc, argv, "s:h:v", long_options, &option_index);
		if (-1 == c)
		{
			break;
		}

		switch (c)
		{
			case 's':
				{
					serverIP = optarg;
					printf("In put Server IP is [%s]\n",serverIP);
				}
				break;
			case 'p':
				{
					pPort = optarg;
					printf("the Server Port be binded is [%s]\n", pPort);
				}
				break;
			case 'h':
			case '?':
				{
					Usage();
				}
				break;
			case 'v':
				{
					//std::cout << CLIENT_VERSION << "\n";
					fprintf(stderr, CLIENT_VERSION);
					exit(0);
				}
			default:
				//fprintf( stderr, "?? getopt returned character code 0%o ??\n", c );
				break;
		}
	}
	
	int serverSock = CreateTcpServerSocket(serverIP, pPort);
	if(serverSock < 0)
	{
		LogInfo("Create tcp server socket error", LOG_INFO);		
		return -1;
	}

	while (1)
	{
		int clntSock = AcceptTCPConnection(serverSock);
		if(-1 == clntSock)
		{
			LogInfo("Error occurred when accept a tcp connect", LOG_INFO);
			return -1;
		}

		pthread_t threadID;
		int retVal = pthread_create(&threadID, NULL, EchoThreadProc, &clntSock);
		if(0 != retVal)
		{
			LogInfo("pthread_create error in main func", LOG_ERROR);
			return -1;
		}
	};

	return 0;
}

void *EchoThreadProc(void *pclntSock)
{
	int *clntSock = (int *)pclntSock;
	pthread_detach(pthread_self());

	HandleTCPClient(*clntSock);

	return NULL;
}


//
//Functon:	communicate with client
//in:		The socket that accept from the socket
//return:	true:0
//
int HandleTCPClient(int clntSock)
{
	char buffer[BUF_SIZE];

	ssize_t numRcvd = recv(clntSock, buffer, BUF_SIZE, 0);

	while(numRcvd > 0)
	{
		char echoBuffer[100] = "The tcp server have recive a message\n";
		ssize_t numSend = send(clntSock, buffer, strlen(echoBuffer), 0);
		if(numSend < 0)
		{
			LogInfo("send buffer to client error", LOG_ERROR);
			return -1;
		}
		else
		{
			if(numSend != strlen(echoBuffer))
			{
				LogInfo("unexpected number of bytes be sent", LOG_ERROR);
				return -1;
			}
		}

		memset(buffer, 0, BUF_SIZE);
		numRcvd = recv(clntSock, buffer, BUF_SIZE, 0);
		if(numRcvd < 0)
		{
			LogInfo("recv failed", LOG_ERROR);
			return -1;
		}
	};

	close(clntSock);

	return 0;
}
