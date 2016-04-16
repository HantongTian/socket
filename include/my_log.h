/*
 * =====================================================================================
 *
 *       Filename:  main.h
 *
 *    Description:  头文件，用于实现一些常规定义
 *
 *        Version:  1.0
 *        Created:  2016年04月10日 10时57分49秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (tht), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef MY_COMMON
#define MY_COMMON

#include <stdio.h>
#include <string.h>
#include <errno.h>
//#include <ops.h>
enum PrintLog
{
	LOG_ERROR,
	LOG_WARNING,
	LOG_INFO
};

int LogInfo(const char *msg, enum PrintLog logtype);

#endif
