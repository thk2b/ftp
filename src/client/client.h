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
	enum e_request_id	rid;
	char				*name;
	char				*help;
	char				*arg_help;
}						t_cmd;

t_cmd				*find_command(char *name, ssize_t *i);
int					unknown_cmd_error(char **cmd);
int					bad_usage_error(char **cmd, t_cmd *cmd_ref);

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

int					get_request(t_request_ctx *req, int fd);

#endif
