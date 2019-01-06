#ifndef SERVER_H
# define SERVER_H

# define	USAGE		"%s [ port ]"
# define	BACKLOG		1024

# include	<protocol.h>

# include	<stdlib.h>


/*
**	options
**		the program options
*/

typedef struct	s_opts
{
	uint16_t	port;
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

int				run(int lcon);

/*
**	controller.c
**		manages a connection with a specific client
*/

int				controller(int ccon);

/*
**	status.c
*/

int					usage_error(char *usage, char **av);
int					info(char *fmt, ...);
int					error(int ret, char *fmt, ...);
int					failure(t_request *req);
int					success(t_request *req);

#endif
