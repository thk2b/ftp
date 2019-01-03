#ifndef		CLIENT_H
# define	CLIENT_H
# include	<shared.h>

t_state		c_init(t_state state, void *ctx);
t_state		c_get_command(t_state state, void *ctx);
t_state		c_send_command(t_state state, void *ctx);
t_state		c_receive_response(t_state state, void *ctx);
t_state		c_process_data(t_state state, void *ctx);
t_state		c_error(t_state state, void *ctx);
t_state		c_failure(t_state state, void *ctx);
t_state		c_success(t_state state, void *ctx);

#endif
