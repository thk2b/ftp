#include	<client.h>

#include	<stdio.h>
#include	<stdarg.h>
#include	<string.h>
#include	<errno.h>

int			usage_error(char *usage, char **av)
{
	dprintf(2, "USAGE:\t");
	dprintf(2, usage, av[0]);
	dprintf(2, "\n");
	return (1);
}

int			info(char *msg, ...)
{
	va_list			args;
	extern t_opts	g_opts;

	if (g_opts.verbose == 0)
		return (0);
	va_start(args, msg);
	dprintf(2, "INFO:\t");
	vdprintf(2, msg, args);
	dprintf(2, "\n");
	va_end(args);
	return (0);
}

int			error(int num, char *msg, ...)
{
	va_list		args;

	va_start(args, msg);
	dprintf(2, "ERROR:\t");
	vdprintf(2, msg, args);
	if (errno)
		dprintf(2, ": [%d] %s", errno, strerror(errno));
	dprintf(2, "\n");
	va_end(args);
	return (num);
}
