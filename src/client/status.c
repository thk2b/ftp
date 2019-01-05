#include	<client.h>

#include	<stdio.h>
#include	<stdarg.h>

int			usage_error(char **av)
{
	dprintf(2, USAGE, av[0]);
	return (1);
}

int			info(char *msg, ...)
{
	va_list		args;

	va_start(args, msg);
	dprintf(2, "INFO:\t");
	vdprintf(2, msg, args);
	dprintf(2, "\n");
	va_end(args);
	return (0);
}
