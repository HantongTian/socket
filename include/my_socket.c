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

	return 0;
}

