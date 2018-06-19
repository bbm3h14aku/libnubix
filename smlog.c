/*
 * log.c
 *
 *  Created on: 26.03.2018
 *      Author: jan
 */
#include "smlog.h"

char* gettimestamp()
{
	char *buffer;
	time_t rawtime;
	struct tm * timeinfo;
	buffer = (char *) malloc(sizeof(char) * 32);
	if(buffer == NULL)
		return NULL;
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	strftime (buffer, 32, "%G-%m-%d %H:%M:%S",timeinfo);
	return buffer;
}

int smlog_init(const char *loc)
{
	stdlog =fopen(loc, "a+");
	if(stdlog == NULL)
		return errno;
	else
		return 0;
}

void smlog(const char *format, ... )
{
	va_list ap;
	va_start(ap, format);
	_smlogv(format, ap);
	va_end(ap);
}

void _smlogv(const char *format, va_list ap)
{
#ifdef SMLOG_PTHREAD
	int oldstate;
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldstate);
#endif

	if(stdlog)
	{
		flockfile(stdlog);
		fprintf(stdlog, "%s   ", gettimestamp(NULL));
		vfprintf(stdlog, format, ap);
		funlockfile(stdlog);
	}

	if(verbose)
	{
		flockfile(stdout);
		printf("%s   ", gettimestamp(NULL));
		vprintf(format, ap);
		funlockfile(stdout);
	}

#ifdef SMLOG_PTHREAD
	pthread_setcancelstate(oldstate, NULL);
#endif
}

void smlog_destroy()
{
	fclose(stdlog);
}
