#ifndef CLIENT_H
# define CLIENT_H

# define USAGE		"%s host [ port ]"
# define PROMPT		" ftp>\t"
# define REV_PROMPT	"<ftp\t"
# define PROMPT_LEN	6
# define BUF_SIZE	4

# include			<protocol.h>
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
**	get_request.c
**		read from fd, parse into a request
*/

int					get_request(t_request_ctx *req, int fd);

/*
**	send_request.c
**		send a response over the control connection
*/

int					send_request(int ccon, t_request_ctx *req);

/*
**	get_response.c
**		read and parse response from the server
*/

int					get_response(int ccon);

/*
**	status.c
*/

int					usage_error(char *usage, char **av);
int					info(char *fmt, ...);
int					error(int ret, char *fmt, ...);
int					failure(t_request *req);
int					success(t_request *req);

#endif
