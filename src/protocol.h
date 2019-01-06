#ifndef	PROTOCOL_H
#define	PROTOCOL_H

#include		<stdlib.h>

/*
**	verb and argument requirement of a request
*/
typedef struct	s_protocol_entry
{
	char		*name;
	size_t		arg_num[2];
}				t_protocol_entry;

int				validate_arguments(size_t i, char **cmd);

/*
**	instance of a protocol entry
*/
typedef struct	s_request
{
	char		**args;
	size_t		code;
}				t_request;

/*
**	request handlers
*/
typedef int			(*t_cmd_handler_fn)(int ccon, int *dcon, t_request *req);
typedef struct		s_cmd_handler
{
	char				*name;
	t_cmd_handler_fn	fn;
}					t_cmd_handler;

t_cmd_handler_fn	find_handler(t_request *req);
int					quit_handler(int ccon, int *dcon, t_request *req);
int					list_handler(int ccon, int *dcon, t_request *req);
int					cwd_handler(int ccon, int *dcon, t_request *req);
int					pwd_handler(int ccon, int *dcon, t_request *req);
int					retr_handler(int ccon, int *dcon, t_request *req);
int					stor_handler(int ccon, int *dcon, t_request *req);
int					quit_handler(int ccon, int *dcon, t_request *req);

#endif
