#ifndef		SERVER_H
# define	SERVER_H
# include	<shared.h>

typedef struct	s_s_opts
{
	int			log_level;
	int			port;
}				t_s_opts;

/*
**	server listener
*/

t_state		sl_init(t_state state, void *ctx);
t_state		sl_listen(t_state state, void *ctx);
t_state		sl_error(t_state state, void *ctx);
t_state		sl_exit(t_state state, void *ctx);

typedef struct	s_sl_ctx
{
	t_s_opts	opts;
	int			sock;
}				t_sl_ctx;

/*
**	server controller
*/

t_state		sc_init(t_state state, void *ctx);
t_state		sc_receive_command(t_state state, void *ctx);
t_state		sc_send_response(t_state state, void *ctx);
t_state		sc_process_data(t_state state, void *ctx);
t_state		sc_error(t_state state, void *ctx);
t_state		sc_failure(t_state state, void *ctx);
t_state		sc_success(t_state state, void *ctx);
t_state		sc_exit(t_state state, void *ctx);

typedef struct	s_sc_ctx
{
	t_s_opts	opts;
	int			conn;
	t_cmd_ctx	cmd;
	int			status;
}				t_sc_ctx;

#endif
