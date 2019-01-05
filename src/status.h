#ifndef		STATUS_H
# define	STATUS_H

#include	<protocol.h>

/*
**	status.c
*/

int				usage_error(char *usage, char **av);
int				info(char *fmt, ...);
int				error(int ret, char *fmt, ...);
int				failure(t_request *req);
int				success(t_request *req);

#endif
