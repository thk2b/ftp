#ifndef CLIENT_H
# define CLIENT_H

# define USAGE		"%s host [ port ]"
# define PROMPT		" ftp>\t"
# define REV_PROMPT	"<ftp\t"
# define PROMPT_LEN	6

# include			<protocol.h>
# include			<sys/types.h>
# include			<stdlib.h>
# include			<arpa/inet.h>


/*
**	options
**		the program options
*/

typedef struct		s_opts
{
	char			*host;
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
int					command_usage(t_cmd *cmd);
int					program_usage(void);
int					handle_help(t_request_ctx *req);

/*
**	init.c
**		initialize the control connection
*/

int					init(int *cconp, t_opts *opts);
int					init_data_connection(int ccon, int *dcon);

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
**		return the status number, and places the return string in data if not null
*/

int					get_response(int ccon, char **data);

/*
**	status.c
*/

int					usage_error(char *usage, char **av);
int					info(char *fmt, ...);
int					error(int ret, char *fmt, ...);
int					failure(t_request *req);
int					success(t_request *req);

/*
**	parse network address in format (a0,a1,a2,a3,p1,p2)
*/
int					parse_addr(struct sockaddr_in *addr, char **data);
#endif
