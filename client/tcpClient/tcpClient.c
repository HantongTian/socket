#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/socket.h>
#include <errno.h>
#include "../../include/my_log.h"
#include "../../include/my_socket.h"

#define CLIENT_VERSION "1.0.0.1\n"

void Usage()
{
	fprintf( stderr, "tcpClinet info\n" );
	fprintf( stderr, "Options:\n" );
	fprintf( stderr, "  -s, --serverIP    : ServerIP which is client need connect to\n" );
	fprintf( stderr, "  -p, --port        : the port used by client when connect to sever" );
	fprintf( stderr, "  -h, --help        : This screen\n" );
	fprintf( stderr, "  -v, --version     : Report the installed version of tcpclient\n" );		
	exit( 0 );
}


//Gloable define 
char *g_pServIP = NULL;
int g_iPort = 1234;
int g_iSock = -1;


int main(int argc, char *argv[])
{
	if(argc <3)
	{
		LogInfo("main func parameter error", LOG_WARNING);
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

		int c = getopt_long (argc, argv, "s:p:h:v", long_options, &option_index);
		if (-1 == c)
		{
			break;
		}

		switch (c)
		{
			case 's':
				{
					g_pServIP = optarg;
					printf("In put Server IP is [%s]\n", g_pServIP);
				}
				break;
			case 'p':
				{
					g_iPort = atoi(optarg);
					printf("the Server Port that clint will connect is [%d]\n", g_iPort);
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

	g_iSock = CreateSocket(TYPE_TCP);
	if (-1 == g_iSock)
	{
		LogInfo("create socket error", LOG_ERROR);	
	}

	int iRet = -1;
	iRet = TcpConnect(g_iSock, g_pServIP, g_iPort);
	if(iRet < 0)
	{
		LogInfo("Program return unormal", LOG_INFO);
		return -1;
	}

	char sendBufer[1024];
	char recvBuffer[1024];
	ssize_t iNumSend = 0;
	ssize_t numRecv;
	while(1)
	{	
#if 1
		printf("Input msg to be sent:");
		scanf("%s", sendBufer);
		iNumSend = send(g_iSock, sendBufer, strlen(sendBufer), 0);
		if(iNumSend < 0)
		{
			LogInfo("send error", LOG_ERROR);
			break;
		}
		else
		{
			if(iNumSend != strlen(sendBufer))
			{
				LogInfo("Unexpected number bytes be sent", LOG_ERROR);
				break;
			}
		}
#endif
		memset(recvBuffer, 0, 1024);
		numRecv = recv(g_iSock, recvBuffer, 1023, 0);
		if(numRecv < 0)
		{
			LogInfo("recv error", LOG_ERROR);
			break;
		}
		else
		{
			if(0 == numRecv)
			{
				LogInfo("recv number bytes is 0", LOG_ERROR);
				break;
			}
		}
		recvBuffer[numRecv] = '\0';
		printf("recvBuffer is:[%s]\n", recvBuffer);
	};
	close(g_iSock);

	LogInfo("program return now", LOG_INFO);
	return 0;
}

