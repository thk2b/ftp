#ifndef CLIENT_H
# define CLIENT_H

# include <protocol.h>
# include <stdlib.h>

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
**	status.c
*/

int				usage_error(char **av);
int				info(char *fmt, ...);
int				error(int ret, char *fmt, ...);
int				failure(t_request *req);
int				success(t_request *req);

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
