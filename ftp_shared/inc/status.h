#ifndef			STATUS_H
# define		STATUS_H

typedef struct	s_error_ctx
{
	int			code;
	char		fatal;
}				t_error_ctx;

typedef struct	s_failure_ctx
{
	int			code;
}				t_failure_ctx;

typedef struct	s_success_ctx
{
	int			code;
}				t_success_ctx;

typedef struct	s_status_message
{
	int			code;
	char		*text;
}				t_status_message;

#endif
