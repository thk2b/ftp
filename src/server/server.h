#ifndef SERVER_H
# define SERVER_H

# define	USAGE		"%s [ port ]"

# include	<protocol.h>
# include	<status.h>

# include	<stdlib.h>


/*
**	options
**		the program options
*/

typedef struct	s_opts
{
	int			port;
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

#endif
