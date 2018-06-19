/*
 * log.h
 *
 *  Created on: 23.03.2018
 *      Author: jan
 */

#ifndef SMART_CORE_LOG_H_
#define SMART_CORE_LOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stddef.h>
#include <pthread.h>
#include <time.h>

FILE *stdlog;
int verbose;

#define SMLOGMSG_NO_ARG 	" "
#define SMLOGLVL_ERR		"ERROR"
#define SMLOGLVL_IFO		"INFO"
#define SMLOGLVL_DBG		"DEBUG"
#define SMLOGLVL_WARN		"WARN"

#define smlog_enable()		verbose =1

#define smlogmsge(lvl, msg, arg) \
	smlog("[ %s ]\tpid=%d\t%s:%d:\t\t%s%s\n", lvl, getpid(), __FILE__, __LINE__, msg, arg); \

#define smlogmsg(lvl, msg) 		smlogmsge(lvl, msg, SMLOGMSG_NO_ARG)
#define smlogerre(msg)				smlogmsge(SMLOGLVL_ERR, msg, strerror(errno))
#define smlogerr()						smlogmsg(SMLOGLVL_ERR, strerror(errno))
#define smlogifoe(msg, arg)		smlogmsge(SMLOGLVL_IFO, msg, arg)
#define smlogifo(msg) 				smlogmsg(SMLOGLVL_IFO, msg)
#define smlogdbge(msg, arg)		smlogmsge(SMLOGLVL_DBG, msg, arg)
#define smlogdbg(msg) 				smlogmsg(SMLOGLVL_DBG, msg)
#define smlogwarn(msg)				smlogmsg(SMLOGLVL_WARN, msg)
#define smlogwarne(msg, arg)	smlogmsg(SMLOGLVL_WARN, msg, arg)

int smlog_init(const char *loc);
void smlog(const char *format, ... );
void _smlogv(const char *format, va_list ap);
void smlog_destroy();

// utility function
char* gettimestamp();

#endif /* SMART_CORE_LOG_H_ */
