#ifndef CLIENT_H
# define CLIENT_H

# define USAGE		"%s host [ port ]"

# include			<protocol.h>
# include			<status.h>

# include			<sys/types.h>
# include			<stdlib.h>


/*
**	options
**		the program options
*/

typedef struct		s_opts
{
	char			*ip;
	int				port;
}					t_opts;

/*
**	command
**		command specification
**		command instance
*/

typedef struct		s_cmd
{
	char			*name;
	char			*help;
	char			*arg_help;
}					t_cmd;

ssize_t				find_command(char *name);
int					unknown_cmd_error(char **cmd);
int					bad_usage_error(char **cmd, size_t i);

/*
**	command handler
**		carries out a command
*/

// typedef int			(*t_cmd_handler_fn)(int ccon, int *dcon, t_request *req);
// typedef struct		s_cmd_handler
// {
// 	char				*name;
// 	t_cmd_handler_fn	fn;
// }					t_cmd_handler;

// t_cmd_handler_fn	find_handler(t_request *req);
// int					quit_handler(int ccon, int *dcon, t_request *req);
// int					list_handler(int ccon, int *dcon, t_request *req);
// int					cwd_handler(int ccon, int *dcon, t_request *req);
// int					pwd_handler(int ccon, int *dcon, t_request *req);
// int					retr_handler(int ccon, int *dcon, t_request *req);
// int					stor_handler(int ccon, int *dcon, t_request *req);
// int					quit_handler(int ccon, int *dcon, t_request *req);

/*
**	init.c
**		initialize the control connection
*/

int					init(int *cconp, t_opts *opts);

/*
**	run.c
**		read commands, send to server, call handler
*/

int					run(int ccon);

/*
**	get_req.c
**		read from fd, parse into a request
*/

int					get_request(t_request *req, int fd);

#endif
