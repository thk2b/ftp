#ifndef	PROTOCOL_H
#define	PROTOCOL_H

#include		<sys/types.h>
#include		<stdlib.h>

enum			e_request_id {
	RID_QUIT,
	RID_LIST,
	RID_CWD,
	RID_PWD,
	RID_RETR,
	RID_STOR,
	RID_PASV,
	RID_MKD,
	MAX_RID
};

/*
**	verb and argument requirement of a request
*/
typedef struct	s_request_ctx
{
	char				**args;
	enum e_request_id	rid;
}				t_request_ctx;

typedef int		(*t_request_handler_fn)(int ccon, int *dcon, t_request_ctx *req, void *ctx);

typedef struct	s_request
{
	enum e_request_id		rid;
	char					*name;
	size_t					arg_num[2];
	t_request_handler_fn	fn;
}				t_request;

int				validate_arguments(char **cmd, t_request *req_ref);
t_request		*find_request(enum e_request_id i);
t_request		*find_request_by_name(char *name);
int				call_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx);

/*
**	request handlers
*/
int				quit_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx);
int				list_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx);
int				cwd_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx);
int				pwd_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx);
int				retr_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx);
int				stor_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx);
int				pasv_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx);
int				mkd_handler(int ccon, int *dcon, t_request_ctx *req, void *ctx);

#endif
