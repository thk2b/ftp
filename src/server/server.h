#ifndef SERVER_H
# define SERVER_H

# define	USAGE		"%s [ port ]"
# define	BACKLOG		1024

# include	<protocol.h>
# include	<status.h>

# include	<stdlib.h>


/*
**	options
**		the program options
*/

typedef struct	s_opts
{
	uint16_t	port;
}				t_opts;

/*
**	init.c
**		initialize a listening socket
*/

int				init(int *lconp, t_opts *opts);

/*
**	run.c
**		listen for connections, fork, call handler
*/

int				run(int lcon);

#endif
