#ifndef SERVER_H
# define SERVER_H

# include	<protocol.h>
# include	<status.h>

# include	<stdlib.h>

# define USAGE		"%s [ port ]"

/*
**	options
**		the program options
*/

typedef struct	s_opts
{
	int			port;
}				t_opts;

#endif
