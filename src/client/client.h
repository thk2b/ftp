#ifndef CLIENT_H
# define CLIENT_H

# include <stdlib.h>

# define USAGE		"%s host [ port ]\n"

/*
**	options
**		the program options
*/

typedef struct	s_opts
{
	char		*host;
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

typedef struct	s_comd_inst
{
	char		**args;
	size_t		code;
}				t_cmd_inst;

/*
**	status.c
*/

int				usage_error(char **av);
int				info(char *fmt, ...);
int				error(t_cmd_inst *cmd);
int				failure(t_cmd_inst *cmd);
int				success(t_cmd_inst *cmd);

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
