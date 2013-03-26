#pragma once

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline void dhcpd_error(int _exit, int _errno, const char *fmt, ...)
{
	char error[512];
	error[511] = 0;

	char *err = error;

	va_list ap;
	va_start(ap, fmt);

	if (_errno != 0)
	{
		err = stpcpy(err, strerror(_errno));
		err = stpcpy(err, ": ");
	}

	vsnprintf(err, (size_t)((error + 512) - err - 1), fmt, ap);

	fputs(error, stderr);
	fputc('\n', stderr);

	if (_exit > 0)
		exit(_exit);
}

