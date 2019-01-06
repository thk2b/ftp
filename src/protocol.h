#ifndef	PROTOCOL_H
#define	PROTOCOL_H

#include		<sys/types.h>
#include		<stdlib.h>

/*
**	verb and argument requirement of a request
*/
typedef struct	s_request_ctx
{
	char		**args;
	size_t		code;
}				t_request_ctx;

typedef int			(*t_request_handler_fn)(int ccon, int *dcon, t_request_ctx *req);

typedef struct	s_request
{
	char					*name;
	size_t					arg_num[2];
	t_request_handler_fn	fn;
}				t_request;

int				validate_arguments(char **cmd, t_request *req_ref);
t_request		*find_request(ssize_t i);

/*
**	request handlers
*/
int				quit_handler(int ccon, int *dcon, t_request_ctx *req);
int				list_handler(int ccon, int *dcon, t_request_ctx *req);
int				cwd_handler(int ccon, int *dcon, t_request_ctx *req);
int				pwd_handler(int ccon, int *dcon, t_request_ctx *req);
int				retr_handler(int ccon, int *dcon, t_request_ctx *req);
int				stor_handler(int ccon, int *dcon, t_request_ctx *req);
int				quit_handler(int ccon, int *dcon, t_request_ctx *req);

#endif
