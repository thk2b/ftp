#ifndef SERVER_H
# define SERVER_H

# include <protocol.h>
# include <stdlib.h>

# define USAGE		"%s [ port ]"

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
**	
*/

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
int				error(int ret, char *fmt, ...);
int				failure(t_request *req);
int				success(t_request *req);

#endif
