#ifndef SERVER_H
# define SERVER_H

# define	USAGE		"%s [ port ]"
# define	BACKLOG		1024
# define	PUBLIC_IP	"0.0.0.0"

# define	BUF_SIZE	4069

# include	<protocol.h>

# include	<stdlib.h>
# include	<arpa/inet.h>

/*
**	options
**		the program options
*/

typedef struct	s_opts
{
	uint16_t	port;
}				t_opts;

/*
**	responses.c
**		response codes and messages
*/

typedef struct	s_response
{
	int			code;
	size_t		message_len;
	char		*message;
}				t_response;

t_response		*find_response(int code);

/*
**	client
**		represents a currently connected client
**		pwd is its virtual pwd
*/

typedef struct	s_client
{
	struct sockaddr_in	addr;
	char				*pwd;
}				t_client;

/*
**	init.c
**		initialize a listening socket
*/

int				init(int *lconp, t_opts *opts);
int				init_passive_data_connection(int ccon, int *dcon);

/*
**	run.c
**		listen for connections, fork, call handler
*/

int				run(int lcon);

/*
**	controller.c
**		manages a connection with a specific client
*/

int				controller(int ccon, t_client *client);

/*
**	get_request.c
*/

int				get_request(t_request_ctx *req, int ccon);

/*
**	send_response.c
*/

int				send_response(int code, int con);
int				send_response_data(int code, int con, char *data);

/*
**	status.c
*/

int				usage_error(char *usage, char **av);
int				info(char *fmt, ...);
int				error(int ret, char *fmt, ...);
int				error_conn(int conn, int num, int ret, char *fmt, ...);
int				success(char *fmt, ...);
int				success_conn(int conn, int num);
int				failure(int ret, char *fmt, ...);
int				failure_conn(int ret, char *fmt, ...);

/*
**	format_addr.c
*/
int				format_addr(char *buf, struct sockaddr_in *addr);

/*
**	path.c
*/

int				path_join(char **dst, char *left, char *right);
#endif
