#ifndef CLIENT_H
# define CLIENT_H

# include	<protocol.h>
# include	<status.h>

# include	<stdlib.h>

# define USAGE		"%s host [ port ]"

/*
**	options
**		the program options
*/

typedef struct	s_opts
{
	char		*ip;
	int			port;
}				t_opts;

/*
**	command
**		command specification
**		command instance
*/

typedef struct	s_cmd
{
	char		*name;
	char		*help;
	char		*arg_help;
}				t_cmd;

/*
**	init.c
**		initialize the control connection
*/

int				init(int *cconp, t_opts *opts);

/*
**	run.c
**		read commands, send to server, call handler
*/

int				run(int ccon);

#endif
