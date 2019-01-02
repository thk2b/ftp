#ifndef			CMD_H
# define		CMD_H

typedef struct	s_cmd_ctx
{
	int			code;
	char		*filename;
	int			fd;
}				t_cmd_ctx;

typedef struct	s_cmd
{
	int			code;
	char		*names[2];
}				t_cmd;

#endif
