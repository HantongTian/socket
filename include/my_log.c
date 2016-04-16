/*
 * =====================================================================================
 *
 *       Filename:  my_common.cpp
 *
 *    Description:  my_common archive
 *
 *        Version:  1.0
 *        Created:  2016年04月10日 22时33分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (tht), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "my_log.h"

int LogInfo(const char *msg, enum PrintLog logtype)
{
	if (LOG_INFO == logtype)
	{
		return printf("[Info] %s\n", msg);
	}
	if (LOG_ERROR == logtype)
	{
		return printf("[Error] %s, error is [%d]:%s\n", msg, errno, strerror(errno));
	}
		
	return printf("[Warning] %s\n", msg);
}


