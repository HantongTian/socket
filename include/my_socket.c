/*
 * =====================================================================================
 *
 *       Filename:  my_socket.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年04月10日 17时59分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>
#include "my_socket.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include "my_log.h"
#include <netdb.h>



static const int MAXPENDING = 10;	//Maximum outstanding connection requests

//create a socket
//in:socket type 
int CreateSocket(enum socketType protocal)
{
	int ret = -1;

	if(TYPE_TCP == protocal)
	{
		ret = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}

	return ret;
}

//
//my own connect func for tcp client 'connect'
//
int TcpConnect(int sock, const char *serverIP, const int port)
{
	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;	//IPV4 address family
	//convert adress
	int rtnVal = inet_pton(AF_INET, serverIP, &serverAddr.sin_addr.s_addr);
	if(0 == rtnVal)
	{
		LogInfo("Invalid address string,please input such as '127.0.0.1'", LOG_ERROR);
		return -1;
	}
	else
	{
		if(rtnVal < 0)
		{
			LogInfo("inet_pton failed", LOG_ERROR);
			return -1;
		}
	}
	serverAddr.sin_port = htons(port); //prot convert

	int iRet = connect(sock, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
	if(-1 == iRet)
	{
		LogInfo("tcp connect error", LOG_ERROR);
		return -1;
	}

	return iRet;
}

//
//Create a tcp server socket and bind port and listen
//in:   hostStr:Domain name or ip address in ipv4,ipv6
//		service:server addr
//return: a tcp socket
//
int CreateTcpServerSocket(const char * hostStr, const char *service)
{
	//Construct the server address structure
	struct addrinfo addrCriteria;	//Criteria for address match
	memset(&addrCriteria, 0, sizeof(addrCriteria));
	addrCriteria.ai_family = AF_UNSPEC;		//Any address family
	addrCriteria.ai_flags = AI_PASSIVE;		//Accept on any address/port
	addrCriteria.ai_socktype = SOCK_STREAM;	//only stream sockets
	addrCriteria.ai_protocol = IPPROTO_TCP;	//only tcp protocol

	struct addrinfo *servAddr;		//Storage list of server address
	int iRet = getaddrinfo(hostStr, service, &addrCriteria, &servAddr);
	if(0 != iRet)
	{
		LogInfo("getaddrinfo error", LOG_ERROR);
		return -1;
	}

	int iSockfd = -1;
	struct addrinfo *addr = NULL;
	for(addr = servAddr; addr != NULL; addr = addr->ai_next)
	{
		//Create a Tcp socket 
		iSockfd = socket(addr->ai_family, addr->ai_socktype,\
			   	addr->ai_protocol);
		if(iSockfd < 0)
		{
			continue;		//try next address
		}

		//Bind to the local address and set socket to list
		if(0 != bind(iSockfd, servAddr->ai_addr, servAddr->ai_addrlen))
		{
			LogInfo("[CreateTcpServersocket]bind error", LOG_ERROR);
			close(iSockfd);
			iSockfd = -1;
			continue;
		}

		if(0 != listen(iSockfd, MAXPENDING))
		{

			LogInfo("[CreateTcpServersocket]  listen error", LOG_ERROR);
			close(iSockfd);
			iSockfd = -1;
			continue;
		}

		struct sockaddr_storage localAddr;
		socklen_t addrSize = sizeof(localAddr);
		if(getsockname(iSockfd, (struct sockaddr *)&localAddr,&addrSize) < 0)
		{
			LogInfo("[CteateTcpServerSocket] getsockname error", LOG_ERROR);
			return -1;
		}

		break;
	}

	freeaddrinfo(servAddr);

	return iSockfd;
}

//
//Function: Accept a tcp connect
//in:	a tcp server socket create by server
//out:	a descriptor for the accept socket
//
int AcceptTCPConnection(int serverSock)
{
	struct sockaddr_storage clntAddr;	//Client address
	//Set length of client address structure (in-out parameter)
	socklen_t clntAddrLen = sizeof(clntAddr);

	int clntSock = accept(serverSock, (struct sockaddr *) &clntAddr, &clntAddrLen);
	if(0 > clntSock)
	{
		LogInfo("accept() error", LOG_ERROR);
	}

	return clntSock;
}
